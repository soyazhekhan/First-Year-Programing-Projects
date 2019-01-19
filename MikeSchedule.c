#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

const int STARTTIME = 800;
const int ENDTIME = 1700;
const int MAXTASKS = 9;
const int MINTASKS = 1;

class Task
{
	private:
		string taskName;
		int startTime;
		int duration;
	
	public:
		Task()
		{
			taskName = "";
			startTime = 0;
			duration = 0;
		}
		
		Task(string taskName0, int startTime0, int duration0)
		{
			set_taskName(taskName0);
			set_startTime(startTime0);
			set_duration(duration0);
		}
		
		void set_taskName(string taskName0)
		{
			taskName = taskName0;
		}
		
		void set_startTime(int startTime0)
		{
			if (startTime0 >= STARTTIME && startTime0 <= ENDTIME)
				startTime = startTime0 / 100 * 100;
			else
				startTime = STARTTIME;
		}
		
		void set_duration(int duration0)
		{
			if (duration0 >= MINTASKS && duration <= MAXTASKS)
				duration = int(ceil(double(duration0)));
			else
				duration = 0;
		}
		
		string get_taskName()const
		{
			return taskName;
		}
		
		int get_startTime()const
		{
			return startTime;
		}
		
		int get_duration()const
		{
			return duration;
		}
		
		int endTime()const
		{
			return startTime + duration * 100;
		}
		
		bool tooLong()const
		{
			return (endTime() > ENDTIME);
		}
		
		/*Conlfict means overlapping time slots between two tasks, 
		including if two tasks start at the same time. If a task ends at x
		and another task starts at x, it will not be counted as a conflict*/
		bool doesConflict(Task const & other) const
		{
			if (startTime < other.startTime)
				return (endTime() > other.startTime);
			
			else if (other.startTime < startTime)
				return (other.endTime() > startTime);
			
			else
				return true;
		}
		
		void output(ostream & out)const
		{
			if (duration != 0)
			{
			out << setw(20) << taskName << setw(12) << startTime << setw(10) 
				<< duration;
			if ((*this).tooLong())
				out << setw(5) << "LATE";
			out << endl;
			}
		}
		
		bool input(istream & in)
		{
			string taskName = "";
			int startTime = 0, duration = 0;
			if(in == cin)
				cout << "Enter a task, start time, duration:";
			if(in >> taskName >> startTime >> duration)
			{
				(*this).set_taskName(taskName);
				(*this).set_startTime(startTime);
				(*this).set_duration(duration);
				return true;
			}
			return false;
		}
		
		bool operator > (Task const & other)const
		{
			return (startTime > other.startTime);
		}
		
		bool operator < (Task const & other)const
		{
			return (startTime < other.startTime);
		}
		
		friend istream & operator >> (istream & in, Task & other);
		friend ostream & operator << (ostream & out, Task const & other);
};

istream & operator >> (istream & in, Task & other)
{
	string taskName = "";
	int startTime = 0, duration = 0;
	if(in == cin)
		cout << "Enter a task, start time, duration:";
	in >> taskName >> startTime >> duration;
	other.set_taskName(taskName);
	other.set_startTime(startTime);
	other.set_duration(duration);
	return in;
}

ostream & operator << (ostream & out, Task const & other)
{
	if (other.duration != 0)
	{
		out << setw(20) << other.get_taskName() << setw(12) 
			<< other.get_startTime() << setw(10) << other.get_duration();
		if (other.tooLong())
			out << setw(5) << "LATE";
		out << endl;
	}
	return out;
}

int fillArray (ifstream & fin, Task mikeTasks [MAXTASKS])
{
	int numTasks = 0; 
	Task t1;
	while (numTasks < MAXTASKS && fin >> t1)
	{
		mikeTasks[numTasks] = t1;
		numTasks ++;
	}
	return numTasks;
}

void sortArray(Task mikeTasks[MAXTASKS], int size)
{
	for(int pass = 0; pass < size-1; pass++)
	{
		Task earliestTask = mikeTasks[pass];
		int minIndex = pass;
		for(int index = pass+1; index < size; index++)
		{
			if (mikeTasks[index] < earliestTask)
			{
				earliestTask = mikeTasks[index];
				minIndex = index;
			}
		}
		mikeTasks[minIndex] = mikeTasks[pass];
		mikeTasks[pass] = earliestTask;
	}
}

int main()
{	
	ifstream fin("mike_tasks_hard.txt");
	if (!fin)
	{
		cout << "ERROR";
		system("PAUSE");
		return EXIT_FAILURE;
	}
	
	int numConflict = 0, numTasks = 0;
		
	Task mikeTasks[MAXTASKS];
	numTasks = fillArray(fin, mikeTasks);
	sortArray(mikeTasks, numTasks);
	
	for (int count = 0; count < numTasks; count ++)
	{
		cout << mikeTasks[count];
	}
	
	for(int previous = 0; previous < numTasks - 1; previous++)
	{
		for(int current = previous+1; current < numTasks; current++)
		{
			if (mikeTasks[previous].doesConflict (mikeTasks[current]))
			{
				numConflict++;
			}
		}
	}
	
	cout << "\nNumber of conflicts:" << numConflict << endl;
	fin.close();
	system("PAUSE");
	return EXIT_SUCCESS;
}

/*Output:
     GENE121_marking         800         3
            walk_dog         800         1
    Clean_whiteboard         900         1
       TA_management        1100         3
     MTE100_planning        1400         2
               lunch        1600         1
             meeting        1600         2 LATE
Number of conflicts:3
Press any key to continue . . .
*/
