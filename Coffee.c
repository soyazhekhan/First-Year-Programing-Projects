#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

int const ARR_ROW = 4;
int const ARR_COL = 9;
int const LOWDEG = 91;
/*using a constant of 91 because the lowest temp is 91 and we need access
to index 0 */

void fill_array(ifstream & fin, int cexperiment[ARR_ROW][ARR_COL]) 
{
	int temp = 0, grind = 0,rating = 0;
	
	while(fin >> temp >> grind >> rating) 
	{
	//row index is "grind-1" to fill index 0-3
		cexperiment[grind-1][temp-LOWDEG]=rating;
	}
}

void outputData(int cexperimentSum[ARR_ROW][ARR_COL]) 
{
	cout << setw(15) << "Temperature" << setw(10) << "Grind" << setw(10)
	     << "Rating" << endl;

	for (int col = 0; col < ARR_COL; col ++) 
	{
		for (int row = 0; row < ARR_ROW; row++) 
		{
			cout << setw(15) << col + LOWDEG << setw(10) << row +1 << setw(10)
			     << cexperimentSum[row][col] << endl;
		}
	}
}

int sum_data(int cexperimentSum[ARR_ROW][ARR_COL], bool isrow, int index) 
{
	int sum = 0;

	if (isrow) 
	{
		for (int col = 0; col < ARR_COL; col++) 
		{
			sum += cexperimentSum[index][col];
		}
	}
	else 
	{
		for (int row = 0; row < ARR_ROW; row++) 
		{
			sum += cexperimentSum[row][index];
		}
	}
	return sum;
}


void bestCoffee(int cexperimentSum[ARR_ROW][ARR_COL], int & grind,
                int & temperature) 
{
	int highestRating1 = -1;
	
	for (int row = 0; row < ARR_ROW; row++) 
	{
		for(int col = 0; col < ARR_COL; col++) 
		{
			if ( cexperimentSum[row][col] > highestRating1) 
			{
				highestRating1 = cexperimentSum[row][col];
				temperature = col + LOWDEG;
				grind = row + 1;
			}
		}
	}
}

int main() 
{
	int cexperiment1[ARR_ROW][ARR_COL] = {0},
	    cexperiment2[ARR_ROW][ARR_COL] = {0},
	    cexperiment3[ARR_ROW][ARR_COL] = {0},
	    cexperimentSum[ARR_ROW][ARR_COL] = {0};
	    
	int bestTemp = -274, temperature = -274, highestRating = -1;

	ifstream fin1("coffee1.txt"), fin2("coffee2.txt"), fin3("coffee3.txt");

	fill_array(fin1,cexperiment1);
	fill_array(fin2,cexperiment2);
	fill_array(fin3,cexperiment3);

	for (int col = 0; col < ARR_COL; col ++) 
	{
		for (int row = 0; row < ARR_ROW; row++) 
		{
			cexperimentSum[row][col] = cexperiment1[row][col] +
			cexperiment2[row][col] + cexperiment3[row][col];
		}
	}

	outputData(cexperimentSum);

	for(int col = 0; col < ARR_COL ; col++) 
	{
		int rating = sum_data(cexperimentSum, 0, col);
		if ( rating > highestRating) 
		{
			highestRating = rating;
			bestTemp = col + LOWDEG;
		}
	}

	cout << "\nTemperature of " << bestTemp << " degrees gives the best coffee" 
		 << endl;

	int grind = 0;

	bestCoffee(cexperimentSum, grind, temperature);

	cout << "Ideal combination for coffee is " << temperature 
		 << " degrees and " << grind << " coarseness" << endl;

	system("PAUSE");
	return EXIT_SUCCESS;
}

/*Output:

    Temperature     Grind    Rating
             91         1        10
             91         2        21
             91         3        12
             91         4        18
             92         1        17
             92         2         7
             92         3        18
             92         4        11
             93         1        17
             93         2        27
             93         3        19
             93         4        17
             94         1        13
             94         2        12
             94         3        11
             94         4        15
             95         1        13
             95         2        15
             95         3        19
             95         4        21
             96         1        15
             96         2        14
             96         3        14
             96         4        15
             97         1        15
             97         2        28
             97         3        12
             97         4        18
             98         1        16
             98         2        16
             98         3        16
             98         4        19
             99         1        25
             99         2        14
             99         3        12
             99         4        18

Temperature of 93 gives the best coffee
Ideal combination for coffee is 97 degrees and 2 coarseness
Press any key to continue . . .

*/
