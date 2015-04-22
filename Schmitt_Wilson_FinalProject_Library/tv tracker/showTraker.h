#ifndef SHOWTRAKER_H_INCLUDED
#define SHOWTRAKER_H_INCLUDED
#include <iostream>

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

class HashTable
{
    public:
        HashTable(int);
        ~HashTable();
        void insertshow(std::string series, int total, bool finished);
        show* findshow(std::string title);
        void deleteshow(std::string title);
        int Hashsum(std::string title);
        void printInventory();
        int rateShow(std::string, int);
        bool isCompleated(show*);
        void print_with_restriction(std::string);
        void next_episode_watched(std::string);
        void next_to_watch_all();
        void next_to_watch(std::string);

    protected:
    private:
        int hashsize;
        show ** archive;
        /*
        show **interested;
        show **watching;
        show **finished;
        */

};


#endif // SHOWTRAKER_H_INCLUDED
