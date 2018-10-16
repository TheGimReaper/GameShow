#include "Contestant.h"

using namespace std;

/* Constructors and Deleters */
Contestant::Contestant()
{
    id = -1;
    points = -1;
}

Contestant::Contestant(int my_id, int my_points)
{
    id = my_id;
    points = my_points;
}

int Contestant::get_id()
{
    return id;
}

int Contestant::get_points()
{
    return points;
}

void Contestant::set_points(int new_points)
{
    points = new_points;
}