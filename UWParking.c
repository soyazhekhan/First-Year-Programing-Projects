#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

const int MAXPARK = 51;
const int MAXPARK_DEL_ADD = 26;

void readCurrPark(ifstream & fin, bool CurrPark_Status [], 
	string CurrPark_Name [])
	{
		int space = 0, status = 0, index = 0;
		string name = "";
		while (index < MAXPARK && fin >> status >> name >> space)
		{
			index ++;
			CurrPark_Status [space] = status;
			CurrPark_Name [space] = name;
		}
	}

void readDelAddPark(ifstream & finDel, bool DelPark_Status[], 
	string DelPark_Name[], ifstream & finAdd, bool AddPark_Status[], 
	string AddPark_Name[])
	{
		int index = 1;
		
		while (index < MAXPARK_DEL_ADD && finDel >> 
			DelPark_Status[index] >> DelPark_Name[index])
			{
				index++;
			}
		
		index = 1;
		
		while (index < MAXPARK_DEL_ADD && finAdd >> AddPark_Status[index]
			>> AddPark_Name[index])
			{
				index++;
			}
	}
	
void delName(string name, string CurrPark_Name[])
{
	for (int index = 1; index < MAXPARK; index++)
	{
		if (name == CurrPark_Name[index])
			CurrPark_Name[index] = "";
	}
}

int lowestVacantSpace(bool isProf, string CurrPark_Name [])
{
	for(int space = 1; space < MAXPARK; space ++)
	{
		if (CurrPark_Name[space] == "")
		{
			if (isProf)
				return space;
			else if (space > 25)
				return space;
		}
	}
	return 0;
}

void assignSpace(int status, string name, bool CurrPark_Status[], 
	string CurrPark_Name[])
	{
		int lowestVacant = lowestVacantSpace(status, CurrPark_Name);
		if (lowestVacant)
		{
			CurrPark_Status[lowestVacant] = status;
			CurrPark_Name[lowestVacant] = name;
		}
	}

void facultyParking(bool CurrPark_Status[], string CurrPark_Name[])
{
	for(int index = 26; index < MAXPARK; index ++)
	{
		if(lowestVacantSpace(CurrPark_Status[index], CurrPark_Name) && 
			lowestVacantSpace(CurrPark_Status[index], CurrPark_Name) <= 25)
			{
				string tempName = CurrPark_Name[index];
				bool tempStatus = CurrPark_Status[index];
				
				delName(CurrPark_Name[index], CurrPark_Name);
				assignSpace(tempStatus, tempName, CurrPark_Status, 
					CurrPark_Name);
			}
	}
}

void outputParking(ofstream & fout, bool CurrPark_Status[], 
	string CurrPark_Name[])
	{
		fout << setw(7) << "Status" << setw(20) 
				<< "Name" << setw(7) << "Space" << endl;
		for (int index = 1; index < MAXPARK; index++)
		{
			if (CurrPark_Name[index] != "")
				fout << setw(7) << CurrPark_Status[index] << setw(20) 
				<< CurrPark_Name[index] << setw(7) << index << endl;
			else
				fout << setw(7) << "n/a" << setw(20) << "Available" << setw(7) 
				<< index << endl;
		}
	}

int main()
{
	bool CurrPark_Status[MAXPARK]={0}, AddPark_Status[MAXPARK_DEL_ADD] = {0}, 
		DelPark_Status[MAXPARK_DEL_ADD] = {0};
	string CurrPark_Name[MAXPARK], AddPark_Name[MAXPARK_DEL_ADD], 
		DelPark_Name[MAXPARK_DEL_ADD];
	
	ifstream fin("parking_current.txt"), finDel("parking_remove.txt"), 
		finAdd("parking_add.txt");
	ofstream fout("parkingW19.txt");
	
	if(!(fin && finDel && finAdd))
	{
		cout << "ERROR";
		system("PAUSE");
		return -1;
	}
	
	readCurrPark(fin, CurrPark_Status, CurrPark_Name);
	
	readDelAddPark(finDel, DelPark_Status, DelPark_Name, finAdd, 
		AddPark_Status, AddPark_Name);
	
	for(int index = 1; index < MAXPARK_DEL_ADD; index++)
		delName(DelPark_Name[index], CurrPark_Name);
	
	facultyParking(CurrPark_Status, CurrPark_Name);
	
	for(int index = 1; index < MAXPARK_DEL_ADD; index++)
		assignSpace(AddPark_Status[index], AddPark_Name[index], 
			CurrPark_Status, CurrPark_Name);
		
	outputParking(fout, CurrPark_Status, CurrPark_Name);
	
	system("PAUSE");
	return EXIT_SUCCESS;
}

/*

parkingW19.txt

 Status                Name  Space
      1        Xie_Wei-Chau      1
      1         Hulls_Carol      2
      1       Pritzker_Mark      3
      1     Fluid_Newtonian      4
      0  Rochlitz_Alexandra      5
      1      Manezes_Alfred      6
      1       Tuncel_Levent      7
      1      McKinnon_David      8
    n/a           Available      9
    n/a           Available     10
      1         Davison_Dan     11
      1        Bedi_Sanjeev     12
    n/a           Available     13
    n/a           Available     14
    n/a           Available     15
    n/a           Available     16
    n/a           Available     17
    n/a           Available     18
      0      Malloch_Jeremy     19
    n/a           Available     20
      1        McKillop_Bob     21
    n/a           Available     22
    n/a           Available     23
    n/a           Available     24
      1     Davidson_George     25
      0            Lung_Ian     26
      0        Hmeidan_Amer     27
      0       Huot_Isabella     28
      0          Lau_Amanda     29
      0            Tan_Mark     30
      0          Mills_Joel     31
      0        Roller_Anika     32
      0    Starratt_Kathryn     33
      0        Belisle_Matt     34
      0    Jasmine_Princess     35
      0        Wang_Willian     36
      0    Samlalsingh_Ryan     37
      0    Barakat_Abdullah     38
      0          Yuan_Jacky     39
      0      Hamza_Muhammad     40
      0           Zheng_Tim     41
      0         Ratiu_Timea     42
      0       Sheng_Stephen     43
      0             Kim_Leo     44
      0    Clifford_Zachary     45
      0        Bhamare_Yash     46
      0    Yousufzay_Namoos     47
      0     Kandathil_Ashar     48
      0          Lau_Darren     49
      0       Keillor_Peter     50
*/
