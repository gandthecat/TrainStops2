#pragma once
#include <string>

class TrainStopPoint
{
private:
	std::string stationName;
	bool stopping;
	int index;
public:
	TrainStopPoint(){}

	TrainStopPoint(std::string st, int s, int i)
		: stationName(st), stopping(s), index(i){}
	
	void setStationName(std::string name)
	{
		stationName = name;
	}

	std::string getStationName()
	{
		return stationName;
	}

	void setStop(bool stop)
	{
		stopping = stop;
	}

	bool getStop()
	{
		return stopping;
	}

	void setIndex(int i)
	{
		index = i;
	}

	int getIndex()
	{
		return index;
	}

};

