#include <fstream>

#include "Priority_Queue.h"

using namespace std;

int findNumber(string s)
{
    string filter = "";
    for (int i = 0; i < s.length(); i++)
    {
        if (s.at(i) >= '0' && s.at(i) <= '9')
        {
            filter += s.at(i);
        }
    }
    char filter2[filter.length()];
    for (int i = 0; i < filter.length(); i++) filter2[i] = filter[i];
    return atoi(filter2);
}

int main(int argc, char *argv[])
{
    ifstream input(argv[1]);
    ofstream output(argv[2]);
    string command;
    int size;
    string k, s, p;
    input >> size;
    Priority_Queue pq(size);
    while (input >> command)
    {
        if (command == "findContestant")
        {
            input >> k;
            Contestant* this_contestant = pq.findContestant(findNumber(k));
            output << command << " " << k << endl;
            if (this_contestant == NULL) 
            {
                output << "Contestant " << k << " is not in the extended heap." << endl; 
            }
            else
            {
                output << "Contestant <" << k << "> is in the extended heap with score <" <<
                this_contestant->get_points() << ">." << endl;
            }
        }
        else if (command == "insertContestant")
        {
            input >> k >> s;
            output << command << " " << k << " " << s << endl;
            char result = pq.insertContestant(findNumber(k), findNumber(s));
            if (result == 'a')
            {
                output << "Contestant " << k << " inserted with initial score " <<
                s << "." << endl;
            }
            else if (result == 'b')
            {
                output << "Contestant " << k << " could not be inserted because the " <<
                "extended heap is full." << endl; 
            }
            else 
            {
                output << "Contestant " << k << " is already in the extended heap: " <<
                "cannot insert." << endl;
            }
        }
        else if (command == "eliminateWeakest")
        {
            output << command << endl;
            Contestant* weakest = pq.eliminateWeakest();
            if (weakest != NULL)
            {
                output << "Contestant <" << (weakest->get_id()) << "> with current lowest score <" << weakest->get_points() <<
                "> eliminated." << endl;
            }
            else 
            {
                output << "No contestant can be eliminated since the extended heap is" <<
                " empty." << endl;
            }
        }
        else if (command == "earnPoints")
        {
            input >> k >> p;
            output << command << " " << k << " " << p << endl;
            Contestant* this_contestant = pq.earnPoints(findNumber(k), findNumber(p));
            if (this_contestant == NULL)
            {
                output << "Contestant " << k << " not in the extended heap." << endl;
            }
            else
            {
                output << "Contestant " << k << "'s score increased by " << p <<
                " points to <" << this_contestant->get_points() << ">." << endl;
            }
        }
        else if (command == "losePoints")
        {
            input >> k >> p;
            output << command << " " << k << " " << p << endl;
            Contestant* this_contestant = pq.losePoints(findNumber(k), findNumber(p));
            if (this_contestant == NULL)
            {
                output << "Contestant " << k << " not in the extended heap." << endl;
            }
            else
            {
                output << "Contestant " << k << "'s score decreased by " << p <<
                " points to <" << this_contestant->get_points() << ">." << endl;
            }
        }
        else if (command == "showContestants")
        {
            output << command << endl;
            pq.showContestants(output);
        }
        else if (command == "showHandles")
        {
            output << command << endl;
            pq.showHandles(output);
        }
        else if (command == "showLocation")
        {
            input >> k;
            output << command << " " << k << endl;
            int result = pq.showLocation(findNumber(k));
            if (result == -1)
            {
                output << "There is no Contestant " << k << " stored in the extended heap: handle[" <<
                k << "] = -1." << endl; 
            }
            else
            {
                output << "Contestant " << k << " stored in extended heap location <" <<
                result + 1<< ">." << endl;
            }
        }
        else if (command == "crownWinner")
        {
            output << command << endl;
            Contestant* this_contestant = pq.crownWinner();
            output << "Contestant <" << this_contestant->get_id() << 
            "> wins with score <" << this_contestant->get_points() << 
            ">!" << endl;
        }
    }
    output.close();
    input.close();

    return 0;
}
