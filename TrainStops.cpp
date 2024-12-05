// TrainStops.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

#include "TrainStopCollection.h"
#include "TrainStopMessage.h"
#include "TrainStopPoint.h"

#include <iostream>
#include <fstream>
#include <vector>

TrainStopCollection tsc;
TrainStopMessage tsm;
TrainStopPoint tsp;
std::vector<std::pair<std::string, bool>> filtered_stop_collection;
std::vector<TrainStopPoint> sequence_collection;

//since more than 1 train stop may be included in the text file,
//process each train stop sequence at a time
void generatesequence()
{
    int gfs_count = 0;
    int index = 1;
    for (const auto& gfs : tsc.get_filtered_stops())
    {
        gfs_count++;
        if (gfs.first == "")
        {
            //process here
            //tsm.eval_sequence(filtered_stop_collection);
            tsm.eval_sequence(sequence_collection);
            
            filtered_stop_collection.clear();
            sequence_collection.clear();
            index = 0;
        }
        else if (gfs_count == tsc.get_filtered_stops().size() && gfs.first != "")
        {
            //filtered_stop_collection.push_back(make_pair(gfs.first, gfs.second));
            tsp = TrainStopPoint(gfs.first, gfs.second, index);
            sequence_collection.push_back(tsp);
            //process here
            tsm.eval_sequence(sequence_collection);
        }
        else if (gfs.first != "")
        {
            //std::cout << "actual " << gfs.first << " >> " << gfs.second << "\n";
            //std::cout << gfs_count << "\n";
            //filtered_stop_collection.push_back(make_pair(gfs.first, gfs.second));
            tsp = TrainStopPoint(gfs.first, gfs.second, index);
            sequence_collection.push_back(tsp);
        }

        index++;

    }
}

// pass in the text file name, open and convert each of the values to a relevant output message
void readfile(std::string textfile) {
    //to only process 1 train stop sequence in the text file
    //tsc.set_ts_file_name(textfile);
    //tsc.open_file();
    //tsc.process_train_stops();
    //tsm.generate_message(tsc.get_stopcount(), tsc.get_filtered_stops());

    tsc.set_ts_file_name(textfile);
    tsc.open_file();
    tsc.process_train_stops();
    tsc.set_stopcount(0);
    generatesequence();
    
}

int main(int argc, char* argv[])
{
    //File argument set in Project Solution (Train Stops) > Properties > Configuration Properties > Debugging > Command Arguments
    //The file name is ts.txt and is located in the TrainStops directory
    readfile(argv[1]);
    return 0;
}