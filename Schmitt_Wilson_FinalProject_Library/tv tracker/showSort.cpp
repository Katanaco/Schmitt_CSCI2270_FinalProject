
using namespace std;
/*
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
    show_ref * out_head;
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
            out_temp->next = NULL
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
        void quickSort(show_ref *, int, show_ref*, int);

};;
            out_tail=out_temp;
        }
        }
    }
    archive_list_head = out_head;
    return out_head;
}
show_ref * show_Sort::sort_by_length(){
    //quicksort implimentation
    show_ref * i_ref = archive_list_head;
    show_ref * j_ref = archive_list_head;
    int i_int = 0;
    int j_int = 0;
    int tempint = 0;
    while (j_ref->next != NULL){
        j_ref = j_ref->next;
        j_int++;
    }
    quickSort(i_ref, i_int, j_ref, j_int);
    while (i_ref->prev != NULL){
        i_ref = i_ref->prev;
    }
    return i_ref;
}

void show_Sort::quickSort(show_ref* l_ref, int l_int, show_ref* r_ref, int r_int){
    show_ref *temp = archive_list_head;
    show_ref *temp2;
    show_ref *temp3;
    show_ref * i_ref = l_ref;
    int i = l_int;
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
        void quickSort(show_ref *, int, show_ref*, int);

};
    show_ref * j_ref = r_ref;
    int j = r_int;
    for (int i = 0; i < (j/2); i++){
        temp = temp->next;
    }
    int pivot = temp->ref_ptr->lenght;
    while (i<=j){
        while(i_ref->ref_ptr->lenght < pivot){
            i_ref=i_ref->next;
            i++;
        }
        while(j_ref->ref_ptr->lenght > pivot){
            j_ref=j_ref->prev;
            j--;
        }
        if (i <= j){
            temp = i_ref;
            temp2 = j_ref;
            if (temp->next != NULL)
                temp->next->prev = temp2;
            if (temp->prev != NULL)
                temp->prev->next = temp2;
            if (temp2->next != NULL)
                temp2->next->prev = temp;
            if (temp2->prev != NULL)
                temp2->prev->next = temp;
            temp3 = temp->next;
            temp->next = temp2->next;
            temp2->next = temp3;
            temp3 = temp->prev;
            temp->prev = temp2->prev;
            temp2->prev = temp3;
            i_ref=i_ref->next;
            i++;
            j_ref=j_ref->prev;
            j--;
        }
    }
    while (temp->prev != NULL)
        temp = temp->prev;
    archive_list_head = temp;
    if (l_int < j){
        quickSort(l_ref, l_int, j_ref, j);
    }
    if (i < r_int){
        quickSort(i_ref, i, r_ref, r_int);
    }
}
*/
