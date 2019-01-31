#include <iostream>

#include "DynamicDecimal.hpp"

// DecimalNode //

DecimalNode::DecimalNode(uint64_t newData) :

	data(newData),
	left(nullptr),
	right(nullptr)

	{

	uint64_t overflow = newData / base;
	if(overflow) {
		left = new DecimalNode(overflow);
		left->right = this;
		data %= base;
	}

}

void DecimalNode::add(uint64_t adder) {
	data += adder;
	uint64_t overflow = data / base;
	if(overflow) {
		if(left) {
			left->add(overflow);
		}
		else {
			left = new DecimalNode(overflow);
			left->right = this;
		}
		data %= base;
	}
}

void DecimalNode::print(std::ostream& os) {
	unsigned char zeros = 18;
	uint64_t dataCopy = this->data;

	while(dataCopy) {
		dataCopy /= 10;
		--zeros;
	}
	while(zeros--)
		os << "0";
	os << this->data;
}

// DynamicDecimal //

void DynamicDecimal::updateLead() {
	while(leadDigit->left) leadDigit = leadDigit->left;
}

DynamicDecimal::DynamicDecimal(uint64_t initNum) :

	onesDigit(nullptr),
	leadDigit(nullptr)

	{

	onesDigit = new DecimalNode(initNum);
	leadDigit = (onesDigit->left ? onesDigit->left : onesDigit);

}

DynamicDecimal::~DynamicDecimal() {
	DecimalNode* temp;
	while(onesDigit) {
		temp = onesDigit->left;
		delete onesDigit;
		onesDigit = temp;
	}
}

void DynamicDecimal::multiplyByTwo() {
	DecimalNode* currNode = onesDigit;
	uint64_t overflow = 0;
	while(currNode) {
		currNode->data <<= 1;
		currNode->data += overflow;
		overflow = currNode->data / base;
		if(overflow) {
			currNode->data %= base;
			if(!currNode->left) {
				currNode->left = new DecimalNode(0);
				currNode->left->right = currNode;
			}
		}
		currNode = currNode->left;
	}
	updateLead();
}

void DynamicDecimal::addOne() {
	onesDigit->add(1);
}

void DynamicDecimal::print(std::ostream& os) {
	updateLead();
	DecimalNode* currNode = leadDigit;

	while((!currNode->data) && currNode->right)
		currNode = currNode->right;

	os << currNode->data;
	currNode = currNode->right;

	while(currNode) {
		currNode->print(os);
		currNode = currNode->right;
	}
}
