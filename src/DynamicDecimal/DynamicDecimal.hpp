/*
These structs are solely for converting a binary number to decimal
*/

struct DecimalNode {

private:
	const uint64_t base = 1000000000000000000ULL;

public:
	uint64_t data;
	DecimalNode* left;
	DecimalNode* right;

	DecimalNode(uint64_t newData);
	void add(uint64_t adder);
	void print(std::ostream& os);

};

struct DynamicDecimal {

private:
	const uint64_t base = 1000000000000000000ULL;
	DecimalNode* onesDigit;
	DecimalNode* leadDigit;

	void updateLead();

public:

	DynamicDecimal(uint64_t initNum);
	~DynamicDecimal();

	void multiplyByTwo();
	void addOne();

	void print(std::ostream& os);

};
