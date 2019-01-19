#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

int main()
{
	ifstream fin("taxi.txt");
	ofstream fout("report.txt");
	if (!fin)
	{
		cout << "File not found.";
		system("PAUSE");
		return EXIT_FAILURE;
	}
	
	fout << fixed << setprecision (2);
	fout << setw(4) << "Trip" << setw(8) << "Return" << setw(7) << "Stops"
		 << setw(10) << "Distance" << setw(8) << "Cost" << setw(12) 
		 << "Cumulative" << setw(12) << "Cumulative" << endl;
	fout << setw(49) << "Distance" << setw(14) << "Cost\n\n" ;
	
	const double COSTKM = 2.7;
	const double COSTSTOP = 11;
	
	int returnTrip = 0, tripNum = 0;
	double totalDistance = 0, totalCost = 0;
	double largestTrip = -1, cheapestTrip = 10e34;
	
	while(fin >> returnTrip)
	{
		int numStops = 0;
		double xPosOld = 0, yPosOld = 0, xPosNew = 0, yPosNew = 0;
		double length = 0, distance = 0, cost = 0;
		
		tripNum++;
		fin >> numStops;
		
		for (int count = 0; count < numStops; count++)
		{
			fin >> xPosNew >> yPosNew;
			length = sqrt(pow((xPosNew-xPosOld),2)+pow((yPosNew-yPosOld),2));
			xPosOld = xPosNew;
			yPosOld = yPosNew;
			distance += length;
		}
		
		if (returnTrip == 1)
			{
				distance += sqrt(pow(xPosNew,2)+pow(yPosNew,2));
			}
		
		cost = numStops*COSTSTOP + distance*COSTKM;
		totalDistance += distance;
		totalCost += cost;
		
		if (largestTrip < distance)
		{
			largestTrip = distance;
		}
		
		if (cheapestTrip > cost)
		{
			cheapestTrip = cost;
		}
		
		if (tripNum < 7 || tripNum%10 == 7)
		{
			fout << setw(4) << tripNum << setw(8) << returnTrip << setw(7) 
			<< numStops << setw(10) << distance << setw(8) << cost 
			<< setw(12) << totalDistance << setw(12) << totalCost << endl;
		}
	}
	fout << "\nThe cumulative distance for August was " << totalDistance 
		 << " km" << endl << "The cumulative amount collected for August was $" 
		 << totalCost << endl << "The longest trip was " << largestTrip 
		 << " km" << endl << "The cheapest trip was $" << cheapestTrip << endl;
	
	fin.close();
	fout.close();
	system("PAUSE");
	return EXIT_SUCCESS;
}

/*

Output:

Trip  Return  Stops  Distance    Cost  Cumulative  Cumulative
                                         Distance        Cost

   1       0      1     10.20   38.54       10.20       38.54
   2       1      2     12.00   54.40       22.20       92.94
   3       0      4     32.84  132.67       55.04      225.61
   4       0      3     21.03   89.78       76.07      315.40
   5       0      5     29.52  134.71      105.60      450.11
   6       1      7     51.39  215.76      156.99      665.87
   7       0      2     10.64   50.74      167.63      716.60
  17       0      5     32.35  142.34      428.67     1817.42
  27       0      3     26.75  105.21      712.19     2912.91
  37       0      2     16.65   66.96      949.68     3884.15
  47       1      2     11.93   54.21     1182.91     4832.85
  57       0      2     24.18   87.28     1434.52     5820.19
  67       0      4     30.23  125.61     1642.94     6690.93
  77       0      1      7.73   31.88     1846.99     7472.87

The cumulative distance for August was 1871.36 km
The cumulative amount collected for August was $7571.68
The longest trip was 51.39 km
The cheapest trip was $23.44

*/
