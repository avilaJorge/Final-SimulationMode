#include "Fraction.h"

namespace Math
{


	int gcd(int x, int y)
	{
		int gcd = 1;
		for (int i = 1; i <= x && i <= y; i++)
		{
			if (x % i == 0 && y % i == 0)
			{
				gcd = i;
			}
		}
		return gcd;
	}

	int lcm(int x, int y)
	{
		int multiple = 1;
		while (!(multiple % x == 0 && multiple % y == 0))
		{
			multiple++;
		}
		return multiple;
	}

	Fraction::Fraction()
	{
		numerator_ = 0;
		denominator_ = 1;
	}

	Fraction::Fraction(int numerator, int denominator)
	{
		numerator_ = numerator;
		denominator_ = denominator;
	}

	Fraction::Fraction(int numerator)
	{
		numerator_ = numerator;
	}

	Fraction::Fraction(std::string string)
	{
		int divisionSymbolPos = string.find_first_of("/");

		numerator_ = atoi((string.substr(0, divisionSymbolPos)).c_str());
		denominator_ = atoi((string.substr(divisionSymbolPos + 1, string.size() - (divisionSymbolPos + 1))).c_str());
	}

	Fraction Fraction::operator-() const
	{
		Fraction negation(numerator_ * -1, denominator_);
		return negation;
	}

	Fraction::operator double() const
	{
		return static_cast<double>(numerator_) / static_cast<double>(denominator_);
	}

	Fraction::operator std::string() const
	{
		std::string fraction;
		fraction += std::to_string(numerator_);
		fraction += "/";
		fraction += std::to_string(denominator_);
		return fraction;
	}

	bool Fraction::isUndefined()
	{
		if (denominator_ == 0)
			return true;
		else return false;
	}

	bool Fraction::write(std::fstream& file)
	{
		file.write(reinterpret_cast<ByteStream>(&numerator_), sizeof(int));
		file.write(reinterpret_cast<ByteStream>(&denominator_), sizeof(int));

		if (file)
			return true;
		else return false;
	}

	bool Fraction::read(std::fstream& file)
	{
		file.read(reinterpret_cast<ByteStream>(&numerator_), sizeof(int));
		file.read(reinterpret_cast<ByteStream>(&denominator_), sizeof(int));
		if (file)
			return true;
		else return false;
	}

	void Fraction::reduce()
	{
		int number = gcd(numerator_, denominator_);
		numerator_ = (numerator_ / number);
		denominator_ = (denominator_ / number);
	}

	Fraction operator+(const Fraction& f1, const Fraction& f2)
	{
		int multiple = lcm(f1.denominator_, f2.denominator_);
		int sum_numerator = (f1.numerator_ * (multiple / f1.denominator_)) +
			(f2.numerator_ * (multiple / f2.denominator_));
		int sum_denominator_ = multiple;
		Fraction sum(sum_numerator, sum_denominator_);
		sum.reduce();
		return sum;
	}

	Fraction operator-(const Fraction& f1, const Fraction& f2)
	{
		return f1 + -f2;
	}
	Fraction operator*(const Fraction& f1, const Fraction& f2)
	{
		Fraction product(f1.numerator_ * f2.numerator_, f1.denominator_ * f2.denominator_);
		product.reduce();
		return product;
	}

	Fraction operator/(const Fraction& f1, const Fraction& f2)
	{
		Fraction quotient(f1.numerator_ * f2.denominator_, f1.denominator_ * f2.numerator_);
		quotient.reduce();
		return quotient;
	}

	bool operator==(const Fraction& f1, const Fraction& f2)
	{
		int reduce_numerator = gcd(f1.numerator_, f2.numerator_);
		int reduce_denominator = gcd(f1.denominator_, f2.denominator_);
		if ((f1.numerator_ / reduce_numerator) == (f2.numerator_ / reduce_numerator) &&
			(f1.denominator_ / reduce_denominator) == (f2.denominator_ / reduce_denominator))
			return true;
		else return false;
	}

	bool operator!=(const Fraction& f1, const Fraction& f2)
	{
		if (!(f1 == f2))
			return true;
		else return false;
	}

	bool operator>(const Fraction& f1, const Fraction& f2)
	{
		double f1Value = f1;
		double f2Value = f2;
		if (f1Value > f2Value)
			return true;
		else return false;
	}

	bool operator<(const Fraction&f1, const Fraction& f2)
	{
		if (f2 > f1)
			return true;
		else return false;
	}
}