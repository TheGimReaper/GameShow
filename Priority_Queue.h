#ifndef __CS375_GAMESHOW_PRIORITY_QUEUE_H__
#define __CS375_GAMESHOW_PRIORITY_QUEUE_H__

#include <fstream>
#include <string>
#include <iostream>

#include "Contestant.h"

class Priority_Queue
{
    private:
        Contestant** heap;
        int* handle;
        int max_size;
        int curr_size;
        int curr_id;
        std::string input;
        std::string output;
        Contestant* root;
    
    public:
        Contestant** get_heap();
        int get_max_size();
        int get_curr_size();
        int* get_handle();
        void set_curr_size(int new_size);
        Priority_Queue();
        Priority_Queue(int size);
        ~Priority_Queue();
        Contestant* findContestant(int k);
        char insertContestant(int k, int s);
        void swap(int index1, int index2);
        void min_heapify(int pos);
        Contestant* eliminateWeakest();
        Contestant* earnPoints(int k, int p);
        Contestant* losePoints(int k, int p);
        void showContestants(std::ofstream &output);
        void showHandles(std::ofstream &output);
        int showLocation(int k);
        Contestant* crownWinner();
};

#endif
