#include <iostream>
#include <vector>
#include <string>

#ifndef BIGINT_H
#define BIGINT_H

class BigInt {
public:
	// Constructors
	BigInt() {};
	BigInt(long long num);
	BigInt(std::string num);

	// Addition
	BigInt operator+(const BigInt& rhs);
	BigInt operator+=(const BigInt& rhs);
	BigInt operator+(const long long& rhs);
	BigInt operator+=(const long long& rhs);
	BigInt operator+(const std::string& rhs);
	BigInt operator+=(const std::string& rhs);

	// Subtraction
	BigInt operator-(const BigInt& rhs);
	BigInt operator-=(const BigInt& rhs);
	BigInt operator-(const long long& rhs);
	BigInt operator-=(const long long& rhs);
	BigInt operator-(const std::string& rhs);
	BigInt operator-=(const std::string& rhs);

	// Multiplication
	BigInt operator*(const BigInt& rhs);
	BigInt operator*= (const BigInt& rhs);
	BigInt operator*(const long long& rhs);
	BigInt operator*= (const long long& rhs);
	BigInt operator*(const std::string& rhs);
	BigInt operator*= (const std::string& rhs);

	// Division
	BigInt operator/(const BigInt& rhs);
	BigInt operator/=(const BigInt& rhs);
	BigInt operator/(const long long& rhs);
	BigInt operator/=(const long long& rhs);
	BigInt operator/(const std::string& rhs);
	BigInt operator/=(const std::string& rhs);

	// Copy Assignment
	BigInt& operator=(const BigInt& rhs);
	BigInt& operator=(const long long& rhs);
	BigInt& operator=(const std::string& rhs);

	// Extraction Operators
	friend std::istream& operator>>(std::istream& in, BigInt& rhs);
	friend std::istream& operator>>(std::istream& in, long long& rhs);
	friend std::istream& operator>>(std::istream& in, std::string& rhs);

	// Insertion Operators
	friend std::ostream& operator<<(std::ostream& out, const BigInt& rhs);
	friend std::ostream& operator<<(std::ostream& out, const long long& rhs);
	friend std::ostream& operator<<(std::ostream& out, const std::string& rhs);
	
	// Comparison Operators
	bool operator<(const BigInt& rhs) const;
	bool operator<=(const BigInt& rhs) const;
	bool operator>(const BigInt& rhs) const;
	bool operator>=(const BigInt& rhs) const;
	bool operator<(const long long& rhs) const;
	bool operator<=(const long long& rhs) const;
	bool operator>(const long long& rhs) const;
	bool operator>=(const long long& rhs) const;
	bool operator<(const std::string& rhs) const;
	bool operator<=(const std::string& rhs) const;
	bool operator>(const std::string& rhs) const;
	bool operator>=(const std::string& rhs) const;

	// Return number
	long long get_num();
private:
	std::vector<long long> digits;
	bool is_neg = false;
};

#endif