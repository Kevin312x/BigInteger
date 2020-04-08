#include <utility>
#include "BigInt.h"

const std::string max_llong = "9223372036854775807";
const std::string min_llong = "-9223372036854775807";

// Constructors
BigInt::BigInt(long long num) {
	if (num < 0) {
		is_neg = true;
		num *= -1;
	}

	do {
		digits.push_back(num % 10);
		num /= 10;
	} while (num);
}

BigInt::BigInt(std::string num) {
	for (int i = num.size() - 1; i >= 0; --i) {
		if (num[i] == '-') {
			this->is_neg = !this->is_neg;
			continue;
		}

		digits.push_back(int(num[i]) - '0');
	}
}

// Addition
BigInt BigInt::operator+(const BigInt& rhs) {
	BigInt op1 = *this, op2 = rhs, result;
	int carry = 0;

	if (op1.is_neg != op2.is_neg) {
		if (op1.is_neg) {
			op1.is_neg = false;
			return op2 - op1;
		} else {
			op2.is_neg = false;
			return op1 - op2;
		}
	}

	// Ensures operand 1 is greater than or equal to operand 2
	if (digits.size() >= rhs.digits.size()) {
		op1 = *this;
		op2 = rhs;
	} else {
		op1 = rhs;
		op2 = *this;
	}

	for (int i = 0; i < op2.digits.size(); ++i) {
		op1.digits[i] += op2.digits[i];
	}

	for (int i = 0; i < op1.digits.size(); ++i) {
		op1.digits[i] += carry;
		carry = op1.digits[i] / 10;
		op1.digits[i] %= 10;
	}

	while (carry) {
		op1.digits.push_back(carry % 10);
		carry /= 10;
	}

	return op1;
}

BigInt BigInt::operator+=(const BigInt& rhs) {
	*this = *this + rhs;
	return *this;
}

BigInt BigInt::operator+(const long long& rhs) {
	BigInt right(rhs);
	return *this + right;
}

BigInt BigInt::operator+=(const long long& rhs) {
	*this = *this + rhs;
	return *this;
}

BigInt BigInt::operator+(const std::string& rhs) {
	BigInt right(rhs);
	return *this + right;
}

BigInt BigInt::operator+=(const std::string& rhs) {
	*this = *this + rhs;
	return *this;
}

// Subtraction
BigInt BigInt::operator-(const BigInt& rhs) {
	BigInt op1 = *this, op2 = rhs, result;
	int count;
	bool flip = false;

	// Opposite signs
	if (op1.is_neg != op2.is_neg) {
		result = op1 + op2;
		result.is_neg = op1.is_neg;
	} else {
		// Same signs

		// Both are negative
		if (op1.is_neg) {
			op1.is_neg = false;
			op2.is_neg = false;
			flip = true;
		}

		// Subtracting a larger number results in sign swap
		if ((op1 < op2) || flip) {
			result = op2 - op1;
			result.is_neg = !op1.is_neg;
		} else {
			// Subtracing a smaller or equal number
			for (int i = 0; i < op2.digits.size(); ++i) {

				count = 1;
				if (op1.digits[i] < op2.digits[i]) {
					op1.digits[i] += 10;

					while (i + count < result.digits.size() - 1) {
						if (op1.digits[i + count] == 0) {
							op1.digits[i + count] = 9;
							++count;
						} else {
							break;
						}
					}

					--op1.digits[i + count];
				}

				op1.digits[i] -= op2.digits[i];
			}

			result = op1;
		}
	}
	if (flip) result.is_neg = !result.is_neg;
	return result;
}

BigInt BigInt::operator-=(const BigInt& rhs) {
	*this = (*this - rhs);
	return *this;
}

BigInt BigInt::operator-(const long long& rhs) {
	BigInt right(rhs);
	return *this - right;
}

BigInt BigInt::operator-=(const long long& rhs) {
	*this = (*this - rhs);
	return *this;
}

BigInt BigInt::operator-(const std::string& rhs) {
	BigInt right(rhs);
	return *this - right;
}

BigInt BigInt::operator-=(const std::string& rhs) {
	*this = (*this - rhs);
	return *this;
}

// Multiplication
BigInt BigInt::operator*(const BigInt& rhs) {
	BigInt result = 0;
	int sum, carry = 0;

	if (is_neg != rhs.is_neg) {
		is_neg = !is_neg;
	}

	for (int i = 0; i < rhs.digits.size(); ++i) {
		BigInt product;
		int mul;

		for (int zeros = 0; zeros < i; ++zeros) {
			product.digits.push_back(0);
		}

		for (int j = 0; j < digits.size(); ++j) {
			mul = digits[j] * rhs.digits[i] + carry;
			carry = mul / 10;
			product.digits.push_back(mul % 10);
		}

		while (carry) {
			product.digits.push_back(carry % 10);
			carry /= 10;
		}
		
		result += product;
	}

	return result;
}

BigInt BigInt::operator*= (const BigInt& rhs) {
	*this = *this * rhs;
	return *this;
}

BigInt BigInt::operator*(const long long& rhs) {
	BigInt right(rhs);
	return *this * right;
}

BigInt BigInt::operator*= (const long long& rhs) {
	*this = *this * rhs;
	return *this;
}

BigInt BigInt::operator*(const std::string& rhs) {
	BigInt right(rhs);
	return *this * right;
}

BigInt BigInt::operator*= (const std::string& rhs) {
	*this = *this * rhs;
	return *this;
}

// Division
BigInt BigInt::operator/(const BigInt& rhs) {
	BigInt right(rhs), left = *this;
	BigInt result(0);
	bool neg = false;

	if (right.is_neg != left.is_neg) {
		neg = true;
	}

	right.is_neg = false;
	left.is_neg = false;

	if ((right < max_llong) && (*this < max_llong)) {
		long long left_num = left.get_num();
		long long right_num = right.get_num();
		return (left_num / right_num);
	} else {
		while (left > 0) {
			(left -= right);
			(result += 1);
		}
	}
	
	if (neg) result.is_neg = true;
	return result;
}

BigInt BigInt::operator/=(const BigInt& rhs) {
	*this = (*this / rhs);
	return *this;
}

BigInt BigInt::operator/(const long long& rhs) {
	BigInt right(rhs);
	return (*this / right);
}

BigInt BigInt::operator/=(const long long& rhs) {
	*this = (*this / rhs);
	return *this;
}

BigInt BigInt::operator/(const std::string& rhs) {
	BigInt right(rhs);
	return (*this / right);
}

BigInt BigInt::operator/=(const std::string& rhs) {
	*this = (*this / rhs);
	return *this;
}

// Copy Assignment
BigInt& BigInt::operator=(const BigInt& rhs) {
	digits = rhs.digits;
	return *this;
}

BigInt& BigInt::operator=(const long long& rhs) {
	BigInt right(rhs);
	digits = right.digits;
	return *this;
}

BigInt& BigInt::operator=(const std::string& rhs) {
	BigInt right(rhs);
	digits = right.digits;
	return *this;
}

// Extraction Operator
std::istream& operator>>(std::istream& in, BigInt& rhs) {
	std::string num;
	in >> num;
	rhs = num;

	return in;
}

// Insertion Operator
std::ostream& operator<<(std::ostream& out, const BigInt& rhs) {
	bool leading_zeros = true;
	if (rhs.is_neg) out << '-';

	for (int i = rhs.digits.size() - 1; i >= 0; --i) {
		if (rhs.digits[i] != '0') leading_zeros = false;
		if (leading_zeros) continue;
		out << rhs.digits[i];
	}

	return out;
}

// Comparison Operators
bool BigInt::operator<(const BigInt& rhs) const {
	return !(*this >= rhs);
}

bool BigInt::operator<=(const BigInt& rhs) const {
	BigInt left = *this;
	BigInt right(rhs);
	
	// If signs are opposite, then the negative is less than positive
	if (left.is_neg != right.is_neg) {
		if (left.is_neg) {
			return true;
		} else {
			return false;
		}
	}

	// Assumes signs are equal
	// If the digits of right is greater, then left is less than right, unless they're both negative
	if (left.digits.size() < right.digits.size()) {
		return (left.is_neg ? false : true);
	} else if (left.digits.size() > right.digits.size()) {
		return (left.is_neg ? true : false);
	} else {
		// If both are negative, then swap left and right
		if (left.is_neg) {
			swap(left.digits, right.digits);
		}
		// Iterates through all digits, and compares
		for (int i = left.digits.size() - 1; i >= 0; --i) {
			if (left.digits[i] < right.digits[i]) {
				return true;
			}
		}
		return false;
	}
}

bool BigInt::operator>(const BigInt& rhs) const {
	return !(*this <= rhs);
}

bool BigInt::operator>=(const BigInt& rhs) const {
	BigInt left = *this;
	BigInt right(rhs);

	// If signs are opposite, then the negative is less than positive
	if (left.is_neg != right.is_neg) {
		if (left.is_neg) {
			return false;
		}
		else {
			return true;
		}
	}

	// Assumes signs are equal
	// If the digits of right is lesser, then left is greater than right, unless they're both negative
	if (left.digits.size() < right.digits.size()) {
		return (left.is_neg ? true : false);
	}
	else if (left.digits.size() > right.digits.size()) {
		return (left.is_neg ? false : true);
	} else {
		// If number of digits of left and right are equal
		// If both are negative, then swap left and right
		if (left.is_neg) {
			swap(left.digits, right.digits);
		}
		// Iterates through all digits, and compares
		for (int i = left.digits.size() - 1; i >= 0; --i) {
			if (left.digits[i] > right.digits[i]) {
				return true;
			}
		}
		return false;
	}
}

bool BigInt::operator==(const BigInt& rhs) const {
	return ((*this <= rhs) && (*this >= rhs));
}

bool BigInt::operator!=(const BigInt& rhs) const {
	return !(*this == rhs);
}

bool BigInt::operator<(const long long& rhs) const {
	BigInt right(rhs);
	return *this < right;
}

bool BigInt::operator<=(const long long& rhs) const {
	return !(*this > rhs);
}

bool BigInt::operator>(const long long& rhs) const {
	BigInt right(rhs);
	return *this > right;
}

bool BigInt::operator>=(const long long& rhs) const {
	return !(*this < rhs);
}

bool BigInt::operator==(const long long& rhs) const {
	BigInt right(rhs);
	return *this == right;
}

bool BigInt::operator!=(const long long& rhs) const {
	BigInt right(rhs);
	return !(*this == right);
}

bool BigInt::operator<(const std::string& rhs) const {
	BigInt right(rhs);
	return *this < right;
}

bool BigInt::operator<=(const std::string& rhs) const {
	return !(*this > rhs);
}

bool BigInt::operator>(const std::string& rhs) const {
	BigInt right(rhs);
	return *this > right;
}

bool BigInt::operator>=(const std::string& rhs) const {
	return !(*this < rhs);
}

bool BigInt::operator==(const std::string& rhs) const {
	BigInt right(rhs);
	return *this == right;
}

bool BigInt::operator!=(const std::string& rhs) const {
	BigInt right(rhs);
	return !(*this == right);
}

// Return number
long long BigInt::get_num() {
	long long value = 0;

	for (int i = digits.size() - 1; i >= 0; --i) {
		value *= 10;
		value += digits[i];
	}

	value = (is_neg ? -value : value);

	return value;
}