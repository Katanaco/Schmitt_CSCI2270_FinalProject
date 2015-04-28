#ifndef SHOWTRAKER_H_INCLUDED
#define SHOWTRAKER_H_INCLUDED
#include <iostream>
//#include "showSort.cpp"
//#include "showSort.h"

struct show{
    std::string title;  //the titles of the series
    int episode;        //current episode you are on
    int lenght;         //the total length of the series currently
    bool finished;      //weather or not they are still making episodes for it;
    show *next;
    int rating;         //rating of show on scale of 0 to 5 (stars)
    bool interested;    //intend to watch
    bool watching;      //currently watching
    bool compleated;    //have watched

    show(){};

    show(std::string series, int total, bool ended)
    {
        title = series;
        episode = 0;
        lenght = total;
        finished=ended;
        next=NULL;
        rating = -1;

    }

};
struct show_ref{
    show * ref_ptr;
    show_ref * next;
    show_ref * prev;

    show_ref(){};

    show_ref(show * rp, show_ref * n, show_ref * p)
    {
        ref_ptr = rp;
        next = n;
        prev = p;
    }

};

class show_Sort
{
    public:
        show_Sort(show_ref*);
        ~show_Sort();
        void sort_by_rating();
        void sort_by_length();
        show_ref * get_head();

    protected:
    private:
        show_ref * archive_list_head;
        void quickSort(int, int);

};


class HashTable
{
    public:
        HashTable(int);
        ~HashTable();
        void insertshow(std::string series, int total, bool finished);
        show* findshow(std::string title);
        void deleteshow(std::string title);
        void printInventory();
        int rateShow(std::string, int);
        void print_with_restriction(std::string);
        void next_episode_watched(std::string);
        void next_to_watch_all();
        void next_to_watch(std::string);
        show_ref* sortSetup();
        void write_to_file();
        void read_from_file();
        void clearhash();

    protected:
    private:
        int hashsize;
        show ** archive;
        int Hashsum(std::string title);
        //show_Sort sorter;
        /*
        show **interested;
        show **watching;
        show **finished;
        */

};


#endif // SHOWTRAKER_H_INCLUDED
