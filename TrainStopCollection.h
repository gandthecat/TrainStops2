#pragma once
#include <fstream>
#include <vector>
#include <iostream>
#include <string>

class TrainStopCollection
{
private:
	std::string file_name;
	std::fstream ts_file;
	std::vector<std::string> ts_array;
	std::vector<std::pair<std::string, bool>> filtered_stops;
	int stopcount;
public:
	void set_ts_file_name(std::string filename)
	{
		file_name = filename;
	}

	std::string get_ts_file_name()
	{
		return file_name;
	}

	std::vector<std::pair<std::string, bool>> get_filtered_stops()
	{
		return filtered_stops;
	}

	void add_filtered_stop(std::string location, bool train_stop_read)
	{
		filtered_stops.push_back(make_pair(location, train_stop_read));
	}

	int get_stopcount()
	{
		return stopcount;
	}

	void set_stopcount(int sc)
	{
		stopcount = sc;
	}

	void increment_stopcount()
	{
		stopcount = stopcount + 1;
	}

	//read in the file, and add it to a vector object
	void open_file()
	{
		std::string ts_line;
		ts_file.open(file_name);

		if (ts_file.is_open())
		{
			while (std::getline(ts_file, ts_line))
			{
				ts_array.push_back(ts_line);
			}
		}
		ts_file.close();
	}

	//split each of the values passed through the textfile (location, stopping)
	//it will be added to a vector<string, bool>
	void process_train_stops()
	{
		std::string location, train_stop_read;
		bool train_stop;
		bool process_string = false;

		for (int i = 0; i < ts_array.size(); i++)
		{
			int line_stop_length = ts_array[i].length();

			for (int j = 0; j < line_stop_length; j++)
			{
				if (!process_string)
				{
					if (ts_array[i].at(j) != ',')
					{
						location += ts_array[i].at(j);
					}
					else if (ts_array[i].at(j) == ',')
					{
						process_string = true;
					}
				}
				else 
				{
					if (ts_array[i].at(j) != ' ')
					{
						train_stop_read += ts_array[i].at(j);
					}
				}
			}

			if (train_stop_read == "True")
			{
				stopcount++;
			}
			
			process_string = false;
			add_filtered_stop(location, convert_bool_string(train_stop_read));
			
			location = "";
			train_stop_read = "";
		}
	}

	//convert passed string in text file to a boolean
	bool convert_bool_string(std::string b) 
	{
		if (b == "True")
		{
			return true;
		}
		else if (b == "False")
		{
			return false;
		}
		return false;
	}
};