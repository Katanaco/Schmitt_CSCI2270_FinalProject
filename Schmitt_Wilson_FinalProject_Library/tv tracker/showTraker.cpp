#include "showTraker.h"
//#include "showSort.h"
using namespace std;


HashTable::HashTable(int s){
    hashsize=s;
    archive = new show*[s];
    /*
    interested= new show*[s];
    watching= new show*[s];
    finished= new show*[s];
    */

    for (int i=0; i<s;i++){
        archive[i]=NULL;
        /*
        interested[i]=NULL;
        watching[i]=NULL;
        finished[i]=NULL;
        */
    }
}
HashTable::~HashTable(){
    for (int i = 0; i < hashsize; i++)
            if (archive[i] != NULL)
                delete archive[i];
    delete[] archive;
}

int HashTable::Hashsum(string title){
    int sum = 0;
    for (int i = 0; i<title.length();i++){
        sum=sum+(int)title[i];
    }
    sum=sum%hashsize;
    return sum;
}
void HashTable::insertshow(string series, int total, bool ended){
    int i=Hashsum(series);
    show *shw=new show(series, total, ended);
    if (archive[i]==NULL){

    archive[i]=shw;
    }else{
        show *temp=archive[i];
        if (temp->title>series){
            archive[i]=shw;
            shw->next=temp;
        }else if (temp->next==NULL){
            temp->next=shw;
            shw->next=NULL;
        }else{
            while(temp->next->title<series){
                temp=temp->next;
                if (temp->next==NULL){
                temp->next=shw;
                shw->next=NULL;
                temp=temp->next;
                break;
                }
            }
            if (temp->next!=NULL){
            shw->next=temp->next;
            temp->next=shw;
            }
        }

}

}
show *HashTable::findshow(string in_title){
    for (int i=0; i<hashsize; i++){
         if (archive[i]!=NULL){
                show *temp=archive[i];
            while(temp->next!=NULL){
                if (temp->title==in_title){
                    return temp;
                }
                temp=temp->next;
            }
            if (temp->title==in_title){
                return temp;
            }


        }

    }
    return NULL;
}
int HashTable::rateShow(string title, int stars){
    show *show_to_rate = findshow(title);
    if (show_to_rate==NULL){
        cout<<"show not found"<<endl;
    }else if (show_to_rate->rating != -1){
        return 0;
    } else if (stars >-1 && stars < 6){
        show_to_rate->rating = stars;
        return 1;
    } else {
        return -1;
    }
    //returns:
    //0 if show already rated
    //-1 if rating outside [0,5]
    //1 if successfully rated
}
bool HashTable::isCompleated(show * show_to_check){
    if (show_to_check->compleated==true){
        return true;
    } else {
        return false;
    }
}
void HashTable::next_episode_watched(string title){
    show *watching = findshow(title);
    if (watching==NULL){
        cout<<"show not found"<<endl;
    }else if (watching->compleated &&watching->finished){
        cout<<"you have completed this show"<<endl;
    }else if(watching->finished){
        cout<<"you are caught up in the series"<<endl;
    }else{
        cout<<"Next episode:"<<watching->episode+1<<"of "<<watching->lenght<<endl;
    }

}
void HashTable::next_to_watch_all(){
    int test=0;
    for (int i=0; i<hashsize; i++){
            if (archive[i]==NULL){
               test++;
            }else{
                    show *temp=archive[i];
                while(temp->next!=NULL){
                    if (temp->episode!=0 && temp->episode!=temp->lenght){
                        cout<<temp->title<<". Next episode:"<<temp->episode+1<<endl;
                    }
                    temp=temp->next;
                }
                    if (temp->episode!=0 && temp->episode!=temp->lenght){
                        cout<<temp->title<<". Next episode:"<<temp->episode+1<<endl;
                    }
            }
        }
        if (test==hashsize){
            cout << "empty" << endl;
        }
}
void HashTable::next_to_watch(string title){
    show *watching = findshow(title);
    if (watching==NULL){
        cout<<"show not found"<<endl;
    }else if(watching->compleated){
        cout<<"this show has already been completed"<<endl;
    }else{
        watching->episode=watching->episode+1;
        if (watching->episode==watching->lenght){
            watching->compleated=true;
            cout<<"you have completed this series"<<endl;
        }else{
            cout<<watching->title<<". Next episode:"<<watching->episode+1<<endl;
        }
    }
}
void HashTable::print_with_restriction(string restrict){
    int test=0;
    if (restrict == "completed"){
        for (int i=0; i<hashsize; i++){
            if (archive[i]==NULL){
               test++;
            }else{
                    show *temp=archive[i];
                while(temp->next!=NULL){
                    if (temp->compleated){
                        cout<<temp->title<<":"<<temp->rating<<endl;
                    }
                    temp=temp->next;
                }
                    if (temp->compleated){
                        cout<<temp->title<<":"<<temp->rating<<endl;
                    }

            }
        }
        if (test==hashsize){
            cout << "empty" << endl;
        }
    } else if (restrict == "watching"){
        for (int i=0; i<hashsize; i++){
            if (archive[i]==NULL){
               test++;
            }else{
                    show *temp=archive[i];
                while(temp->next!=NULL){
                    if (temp->episode!=0 && temp->episode!=temp->lenght){
                        cout<<temp->title<<":"<<temp->rating<<endl;
                    }
                    temp=temp->next;
                }
                    if (temp->episode!=0 && temp->episode!=temp->lenght){
                        cout<<temp->title<<":"<<temp->rating<<"next episode:"<<temp->episode+1<<endl;
                    }
            }
        }
        if (test==hashsize){
            cout << "empty" << endl;
        }
    } else if (restrict == "finished"){
        for (int i=0; i<hashsize; i++){
            if (archive[i]==NULL){
               test++;
            }else{
                    show *temp=archive[i];
                while(temp->next!=NULL){
                 if (temp->finished){
                        cout<<temp->title<<":"<<temp->rating<<endl;
                    }
                    temp=temp->next;
                }
                    if (temp->finished){
                        cout<<temp->title<<":"<<temp->rating<<endl;
                    }
            }
        }
        if (test==hashsize){
            cout << "empty" << endl;
        }
    } else if (restrict == "interested"){
        for (int i=0; i<hashsize; i++){
            if (archive[i]==NULL){
               test++;
            }else{
                    show *temp=archive[i];
                while(temp->next!=NULL){
                    if (temp->episode==0 ){
                        cout<<temp->title<<":"<<temp->rating<<endl;
                    }
                    temp=temp->next;
                }
                    if (temp->episode==0 ){
                        cout<<temp->title<<":"<<temp->rating<<"next episode:"<<temp->episode+1<<endl;
                    }
            }
        }
        if (test==hashsize){
            cout << "empty" << endl;
        }
    } else {
        cout<<"unknown print restriction"<<endl;
    }
}
void HashTable::deleteshow(string in_title){
    show* found=findshow(in_title);
    int i=Hashsum(in_title);
    if (found!=NULL){
            if (found==archive[i]){
                archive[i]=found->next;
                delete found;
            }else{
        show* temp=archive[i];
        while (temp->next->title!=in_title){
            temp=temp->next;
        }
        temp->next=found->next;
        delete found;
    }
    }
}
void HashTable::printInventory(){
    int test=0;
    for (int i=0; i<hashsize; i++){
        if (archive[i]==NULL){
           test++;
        }else{
                show *temp=archive[i];
            while(temp->next!=NULL){
                cout<<temp->title<<":"<<temp->episode<<"/"<<temp->lenght<<endl;
                temp=temp->next;
            }
                cout<<temp->title<<":"<<temp->episode<<"/"<<temp->lenght<<endl;


        }
    }
    if (test==hashsize){
        cout << "empty" << endl;
    }

}
show_ref* HashTable::sortSetup(){
    int test=0;
    show_ref *previous=NULL;
    show_ref *head;
    for (int i=0; i<hashsize; i++){
        if (archive[i]==NULL){
           test++;
        }else{
            show *temp=archive[i];
            while(temp->next!=NULL){
                show_ref *tempref=new show_ref(temp, NULL, NULL);
                tempref->prev=previous;

                if (previous==NULL){
                    head=tempref;

                }else{
                    previous->next=tempref;
                }
                temp=temp->next;
            }
                show_ref *tempref=new show_ref(temp, NULL, NULL);
                tempref->prev=previous;

                if (previous==NULL){
                    head=tempref;

                }else{
                    previous->next=tempref;
                }


        }
    }
    if (test==hashsize){
        return NULL;
    }else{
        return head;
    }

}
int HashTable::gethashsize(){
    return hashsize;

}

show_Sort::show_Sort(show_ref * head){
    archive_list_head = head;
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
            out_temp->next = NULL;
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
