#ifndef __CS375_GAMESHOW_CONTESTANT_H__
#define __CS375_GAMESHOW_CONTESTANT_H__

#include <iostream>
#include <string>

class Contestant
{
    private:
        int id;
        int points;
    public:
        int get_id();
        int get_points();
        void set_id(int new_id);
        void set_points(int new_points);
        Contestant();
        Contestant(int my_id, int my_points);
};

#endif
