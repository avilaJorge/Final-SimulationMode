#ifndef FRACTION_H_INCLUDE
#define FRACTION_H_INCLUDE

#include <string>
#include <fstream>

typedef char Byte;
typedef char* ByteStream;

namespace Math
{
	int gcd(int x, int y);
	int lcm(int x, int y);

	class Fraction
	{
	public:
		Fraction();
		Fraction(int numerator, int denominator);
		Fraction(int numerator); //this constructor assumes numerator/1, i.e., an integer
		Fraction(std::string string); //This allows you to do a Fraction cast from a string
		//Note that the copy constructor, destructor, move constructor, etc. etc. are not necessary in this class
		Fraction operator-() const; //negation of *this
		operator double() const; //Change a Fraction to a double.  This allows you to pass a Fraction in place of a double
		operator std::string() const; //Change a Fraction to a string. Thie allows you to use a Fraction anywhere a string can be used	
		bool isUndefined(); //returns true if denominator_ is 0
		bool read(std::fstream& file); //reads a fraction from a file into this, returns true if success
		bool write(std::fstream& file); //write the fraction this into a file, returns truee if success
	protected:
		int numerator_;
		int denominator_;
		void reduce(); //recalulates the numerator_ and denominator_ so the fraction is reduced
		//friends
		friend Fraction operator+(const Fraction& f1, const Fraction& f2);
		friend Fraction operator-(const Fraction& f1, const Fraction& f2);
		friend Fraction operator*(const Fraction& f1, const Fraction& f2);
		friend Fraction operator/(const Fraction& f1, const Fraction& f2);
		friend bool operator==(const Fraction& f1, const Fraction& f2);
		friend bool operator!=(const Fraction& f1, const Fraction& f2);
		friend bool operator>(const Fraction& f1, const Fraction& f2);
		friend bool operator<(const Fraction& f1, const Fraction& f2);
	};
}
#endif