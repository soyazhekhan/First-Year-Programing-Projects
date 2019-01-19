#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std; 

class Fraction
{
	private:
		int numerator, denominator;
	public:
		Fraction()
		{
			set_default();
		}
		Fraction(int numer, int denom)
		{
			if (denom < 0)
			{
				numerator = -numer;
				denominator = -denom;
			}
			else if (denom = 0)
			{
				set_default();
			}
			else
			{
				numerator = numer;
				denominator = denom;
			}
		}
			
		void set_default()
		{
			numerator = 1;
			denominator = 2;
		}
		
	//Accessors
		int get_numerator()const
		{
			return numerator;
		}
		
		int get_denominator()const
		{
			return denominator;
		}
		
	//Mutators
		void set_numerator(int numer, int denom)
		{
			if(abs(numer) >= abs(denom))
	//Improper proper fraction, set default
				set_default();
			else
			numerator = numer;
		}
		
		void set_demoninator(int numer, int denom)
		{
			if (denom < 0)
			{
				numerator = -numer;
				denominator = -denom;
			}
			else if (denom = 0)
	//Invalid proper fraction, set default
				set_default();
			else
				denominator = denom;
				
			if (abs(numer) >= abs(denom))
			{
	//Invalid proper fraction, set default
				set_default();
			}
		}

	//Fraction to decimal
		double decimal(int precision)const
		{
			double fraction = double(numerator)/denominator;
			fraction *= pow(10, precision);
			round(fraction);
			fraction /= pow(10, precision);
			return fraction;
		}
		
	//Equality check
		bool isExactlySame(Fraction const & other)const
		{
			return (numerator == other.get_numerator() && denominator == other.get_denominator());
		}
		
	//Output
		void output(ostream&out)const
		{
			out << "numerator: " << numerator << "/ndenominator: " << denominator;
		}
};
