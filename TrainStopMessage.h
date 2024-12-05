#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "TrainStopPoint.h";

class TrainStopMessage
{
private:
	std::string outputmessage = "";
public:
	void set_outputmessage(std::string m)
	{
		outputmessage += m;
	}

	void reset_outputmessage()
	{
		outputmessage = "";
	}

	std::string get_outputmessage()
	{
		return outputmessage;
	}

	void reset_list()
	{

	}
	
	void eval_sequence(std::vector<TrainStopPoint> sequence)
	{
		std::vector<TrainStopPoint> stopsequence;
		
		int stopcount = 0;

		for (int i = 0; i < sequence.size(); i++)
		{
			//std::cout << sequence[i].getStationName() << " " << sequence[i].getStop() << "\n";
			if (sequence[i].getStop())
			{
				stopcount++;
			}

		}
		std::cout << "\n";

		if (stopcount == sequence.size())
		{
			std::cout << "This train stops at all stations\n";
		}
		else if (stopcount == sequence.size() - 1)
		{
			std::cout << "This train stops at all stations except ";
			for (int i = 0; i < sequence.size(); i++)
			{
				if (!sequence[i].getStop())
				{
					std::cout << sequence[i].getStationName() << "\n";
				}
			}
		}
		else if (stopcount == 2)
		{
			std::cout << "This train runs express from ";
			std::cout << sequence.front().getStationName() << " to " << sequence.back().getStationName() << "\n";
		}
		else if (stopcount == 3)
		{
			std::cout << "This train runs express from ";
			std::cout << sequence.front().getStationName() << " to " << sequence.back().getStationName() << ", stopping only at ";
			for (int i = 1; i < sequence.size() - 1; i++)
			{
				if (sequence[i].getStop())
				{
					std::cout << sequence[i].getStationName() << "\n";
				}
			}

		}
		else if (stopcount >= 4)
		{
			std::sort(sequence.begin(), sequence.end(), [](TrainStopPoint& tsp1, TrainStopPoint& tsp2) { return tsp1.getStop() > tsp2.getStop(); });

			
			for (int i = 0; i < sequence.size(); i++)
			{
				if (sequence[i].getStop() && i == 0)
				{
					std::cout << "This train runs express from ";
					std::cout << sequence.front().getStationName() << " to ";
				}
				if (sequence[i].getStop() && i == 2)
				{
					std::cout << sequence[i].getStationName();
				}

				if (!sequence[i].getStop())
				{
					break;
				}
				
				if (i > 1)
				{
					if (i % 2 == 0)
					{
						if (sequence[i].getStop() && sequence[i - 1].getStop())
						{
							std::cout << ", stopping only at " << sequence[i - 1].getStationName();
						}
					}
					else {

						if (sequence[i].getStop() && sequence[i + 1].getStop())
						{
							std::cout << ", then runs express from " << sequence[i-1].getStationName() << " to " << sequence[i + 1].getStationName();
						}
					}
				}
				
				
				
				}
			}
		std::cout << "\n";
	}

};