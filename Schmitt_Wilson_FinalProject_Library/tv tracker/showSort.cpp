#include "showTraker.h"
#include "showSort.h"
using namespace std;

show_Sort::show_Sort(show_ref * ah){
    archive_list_head = ah;
}
show_Sort::~show_Sort(){
    show_ref * temp = archive_list_head;
    show_ref * temp2 = temp;
    while (temp->next != NULL){
        temp2 = temp2->next;
        delete temp;
        temp = temp2;
    }
    delete temp;
}
show_ref * show_Sort::sort_by_rating(){
    show_ref * temp = archive_list_head;
    show_ref * out_head = NULL;
    show_ref * out_temp;
    show_ref * out_tail;
    int high=-1;
    while (temp->next != NULL)
    {
        if (temp->ref_ptr->rating > high){
            out_head = temp;
            high = temp->ref_ptr->rating;
        }
        temp = temp->next;
    }
    if (out_head->next != NULL){
    out_head->next->prev = out_head->prev;
    }
    if (out_head->prev != NULL){
    out_head->prev->next = out_head->next;
    }
    out_head->prev = NULL;
    out_head->next = NULL;
    out_tail = out_head;
    for (int i = high; i >= -1; i--){
        while (temp->prev != NULL){
            temp = temp->prev;
        }
        while (temp->next != NULL){
        if (temp->ref_ptr->rating==i){
            out_temp = temp;
            temp = temp->next;
            if (out_temp->next != NULL){
                out_temp->next->prev = temp->prev;
            }
            if (out_temp->prev != NULL){
                out_temp->prev->next = temp->next;
            }
            out_temp->prev = out_tail;
            out_tail->next = out_temp;
            out_temp->next = NULL;
            out_tail=out_temp;
        }
        }
    }
    archive_list_head = out_head;
    return out_head;
}
show_ref * show_Sort::sort_by_length(){
}

