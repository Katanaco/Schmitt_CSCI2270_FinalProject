#ifndef SHOWTRAKER_H_INCLUDED
#define SHOWTRAKER_H_INCLUDED
#include <iostream>

struct show{
    std::string title;  //the titles of the series
    int episode;        //current episode you are on
    int lenght;         //the total length of the series currently
    bool compleated;    //wether or not they are still making episodeds for it;
    show *next;

    show(){};

    show(std::string series, int total, bool finished)
    {
        title = series;
        episode = 0;
        lenght = total;
        compleated=finished;
        next=NULL;
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

    protected:
    private:
        int hashsize;
        show **interested;
        show **watching;
        show **finished;

};


#endif // SHOWTRAKER_H_INCLUDED
