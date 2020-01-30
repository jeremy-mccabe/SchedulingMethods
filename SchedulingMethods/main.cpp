#include <iostream>
#include <vector>
#include <tuple>
#include <iomanip>


int main(int argc, char ** argv)
{

	int mode = 0;
	int numOfProcesses = 0;
	/// first: processID (letter), second: burstTime (value)
	std::vector<std::tuple<int, int> > processes;
	int burstTime = 0;
	int totalBurstTime = 0;
	int displayValue = 0;
	// int totalIdleTime = 0;
	// int clock = 0;

	// averaging variables:
	double avgWaitTime = 0;
	double avgTurnTime = 0;
	int runningBurstTotal = 0;
	int runningTurnTotal = 0;

	while (1)
	{

		//Write a program to simulate the operation of two of CPU scheduling methods.
		//The program lets the user select one of the two methods to implement the CPU scheduling.
		/// 1: first come first serve	2: shortest job first
		std::cout << "Select Scheduling Method:\n 1: First Come First Serve (FCFS)\n 2: Shortest Job First (SJF)" << std::endl;
		std::cin >> mode;
		if (mode != 1 && mode != 2) return 0;

		//Get the number of processes from the user.
		/// 1 - 5
		std::cout << "\nEnter number of processes (range must be from 1 to 5):" << std::endl;
		std::cin >> numOfProcesses;
		if (numOfProcesses != 1 &&
			numOfProcesses != 2 &&
			numOfProcesses != 3 &&
			numOfProcesses != 4 &&
			numOfProcesses != 5) return 0;
		std::cout << std::endl;

		//Get the burst time of each process from the user.
		for (int i = 0; i < numOfProcesses; i++)
		{
			std::cout << "Enter the burst time for process " << char(i + 65) << std::endl;
			std::cin >> burstTime;
			totalBurstTime += burstTime;
			processes.push_back(std::make_tuple(i + 65, burstTime));
		}
		std::cout << "\n\n\nGantt Chart:\n------------\n";

		//Assume that all processes arrive at "0" to the ready queue.
		switch (mode)
		{
			//FCFS
		case 1:
			// 
			//The program shows scheduling time of the CPU by using Gant Chart or table.
			///Gantt Display:
			///top-rack
			for (int i = 0; i < processes.size(); i++)
			{
				std::cout << "|" << char(i + 65) << " ";

				for (int j = 0; j < std::get<1>(processes.at(i)) - 1; j++)
				{
					std::cout << "  ";
				}
			}
			std::cout << "|\n";
			///bottom-rack
			for (int i = 0; i < processes.size(); i++)
			{
				std::cout << "|";
				for (int j = 0; j < std::get<1>(processes.at(i)); j++)
				{
					std::cout << "__";
				}
			}
			std::cout << "|\n";
			///values
			std::cout << "0";
			for (int i = 0; i < processes.size(); i++)
			{
				/// ternary for single-digit/double-digit offset:
				((displayValue + std::get<1>(processes.at(i))) < 10) ? std::cout << "  " : std::cout << " ";

				for (int j = 0; j < std::get<1>(processes.at(i)) - 1; j++)
				{
					std::cout << "  ";
				}

				displayValue += std::get<1>(processes.at(i));
				std::cout << displayValue;

			}
			break;

			//SJF
		case 2:
			/// bubble sort
			int symbolTemp = 0;
			int burstTemp = 0;
			for (int i = 0; i < numOfProcesses; i++)
			{
				for (int j = 0; j < numOfProcesses - 1; j++)
				{
					if (std::get<1>(processes.at(j)) > std::get<1>(processes.at(j + 1)))
					{
						symbolTemp = std::get<0>(processes.at(j + 1));
						burstTemp = std::get<1>(processes.at(j + 1));
						std::get<0>(processes.at(j + 1)) = std::get<0>(processes.at(j));
						std::get<1>(processes.at(j + 1)) = std::get<1>(processes.at(j));
						std::get<0>(processes.at(j)) = symbolTemp;
						std::get<1>(processes.at(j)) = burstTemp;
					}
				}
			}

			// 
			//The program shows scheduling time of the CPU by using Gant Chart or table.
			///Gantt Display:
			///top-rack
			for (int i = 0; i < processes.size(); i++)
			{
				std::cout << "|" << char(std::get<0>(processes.at(i))) << " ";

				for (int j = 0; j < std::get<1>(processes.at(i)) - 1; j++)
				{
					std::cout << "  ";
				}
			}
			std::cout << "|\n";
			///bottom-rack
			for (int i = 0; i < processes.size(); i++)
			{
				std::cout << "|";
				for (int j = 0; j < std::get<1>(processes.at(i)); j++)
				{
					std::cout << "__";
				}
			}
			std::cout << "|\n";
			///values
			std::cout << "0";
			for (int i = 0; i < processes.size(); i++)
			{
				/// ternary for single-digit/double-digit offset:
				((displayValue + std::get<1>(processes.at(i))) < 10) ? std::cout << "  " : std::cout << " ";

				for (int j = 0; j < std::get<1>(processes.at(i)) - 1; j++)
				{
					std::cout << "  ";
				}

				displayValue += std::get<1>(processes.at(i));
				std::cout << displayValue;

			}
			break;
		}

		//Vector Summary Printout:
		std::cout
			<< "\n\n\nProcess/Burst\n"
			<< "-------------\n";

		for (int i = 0; i < processes.size(); i++)
		{
			std::cout 
				<< char(std::get<0>(processes.at(i)))
				<< " : "
				<< std::get<1>(processes.at(i))
				<< std::endl;
		}

		//The program calculates the average waiting time and the average turnaround time.

			// AWT:
		for (int i = 0; i < processes.size() - 1; i++)
		{
			for (int j = 0; j <= i; j++)
			{
				runningBurstTotal += std::get<1>(processes.at(j));
			}
		}
		avgWaitTime = (double)runningBurstTotal / (double)numOfProcesses;

		// ATAT:
		for (int i = 0; i < processes.size(); i++)
		{
			for (int j = 0; j <= i; j++)
			{
				runningTurnTotal += std::get<1>(processes.at(j));
			}
		}
		avgTurnTime = (double)runningTurnTotal / (double)numOfProcesses;

		getchar();

		/// final output:
		std::cout << "\n\nMode: " << mode << std::endl;
		std::cout << "# Processes: " << numOfProcesses << std::endl;
		std::cout << "Total Burst Time: " << totalBurstTime << std::endl;
		std::cout << "Avg. Wait Time: " << std::setprecision(2) << std::fixed << avgWaitTime << std::endl;
		std::cout << "Avg. Turnaround Time: " << avgTurnTime << std::endl;
		std::cout << "\n-(Press any key to restart)-" << std::endl;
		/// 

		getchar();

		std::cout << "\n------------------------------\n" << std::endl;

		mode = 0;
		numOfProcesses = 0;
		/// first: processID (letter), second: burstTime (value)
		processes.clear();
		burstTime = 0;
		totalBurstTime = 0;
		displayValue = 0;
		// int totalIdleTime = 0;
		// int clock = 0;

		// averaging variables:
		avgWaitTime = 0;
		avgTurnTime = 0;
		runningBurstTotal = 0;
		runningTurnTotal = 0;
		
	}

	return 0;
}