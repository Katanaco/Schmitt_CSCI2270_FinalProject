#ifndef SHOWSORT_H_INCLUDED
#define SHOWSORT_H_INCLUDED
#include <iostream>
#include "showTraker.h"

struct show;

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
        show_Sort(show_ref *);
        ~show_Sort();
        show_ref * sort_by_rating();
        show_ref * sort_by_length();

    protected:
    private:
        show_ref * archive_list_head;


};


#endif // SHOWSORT_H_INCLUDED
