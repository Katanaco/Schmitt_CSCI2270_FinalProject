#include "showTraker.h"
//#include "showSort.h"
#include <iostream>
#include <fstream>
#include <string>
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
    show * temp;
    show * temp2;
    for (int i = 0; i < hashsize; i++){
            if (archive[i] != NULL){
                temp = archive[i];
                temp2 = temp;
                while (temp->next != NULL){
                    temp2 = temp->next;
                    delete temp;
                    temp = temp2;
                }
                delete temp;
            }
}
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
                previous = tempref;
                temp=temp->next;
            }
                show_ref *tempref=new show_ref(temp, NULL, NULL);
                tempref->prev=previous;

                if (previous==NULL){
                    head=tempref;

                }else{
                    previous->next=tempref;
                }
                previous = tempref;


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

void HashTable::write_to_file(){
    ofstream temp_file;
    temp_file.open("temp.txt");
    string write_out = "";
    show * temp;
    int test=0;
    for (int i=0; i<hashsize; i++){
        if (archive[i]==NULL){
           test++;
        }else{
                temp = archive[i];
            while(temp->next!=NULL){
                write_out.append(temp->title);
                write_out+= '\n';
                write_out.append(to_string(temp->episode));
                write_out+= '\n';
                write_out.append(to_string(temp->lenght));
                write_out+= '\n';
                write_out.append(to_string(temp->rating));
                write_out+= '\n';
                if (temp->finished==true){
                    write_out+= '1';
                } else {
                    write_out+= '0';
                }
                write_out+= '\n';
                temp=temp->next;
            }
                write_out.append(temp->title);
                write_out+= '\n';
                write_out.append(to_string(temp->episode));
                write_out+= '\n';
                write_out.append(to_string(temp->lenght));
                write_out+= '\n';
                write_out.append(to_string(temp->rating));
                write_out+= '\n';
                if (temp->finished==true){
                    write_out+= '1';
                } else {
                    write_out+= '0';
                }
                write_out+= '\n';
        }
    }
    temp_file<<write_out;
    temp_file.close();
}

void HashTable::read_from_file(){
    string file_to_read = "temp.txt";
    ifstream file;
    file.open(file_to_read);
    string token;
    int i = 0;
    string title;
    int length;
    int episodes;
    int rating;
    bool finished;
    show * temp;
    while (!file.eof()){
        getline(file, token);
        if (i == 0){
            title = token;
        } else if (i == 1){
            episodes = atoi(token.c_str());
        } else if (i == 2){
            length = atoi(token.c_str());
        } else if (i == 3){
            rating = atoi(token.c_str());
        } else {
            if (token == "1"){
                finished = true;
            } else {
                finished = false;
            }
            i = -1;
            insertshow(title, length, finished);
            rateShow(title, rating);
            temp = findshow(title);
            temp->episode = episodes;
        }
        i++;
    }
    file.close();
}

show_Sort::show_Sort(show_ref * head){
    archive_list_head = head;
    //all sorting algorithms return a list of low to high
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
/*
Function prototype:
void show_Sort::sort_by_rating()

Function description:
This method uses the head of the linked list of show references stored privately
in the class and rearranges it, sorting it low to high by rating, unrated being
first with rating values -1 and proceeding ratings of 0 to 5 after.

Example;
show_Sort sortlist(pre_sort_head);
sortlist.sort_by_rating();

Precondition:
There is a properly linked list of struct show_ref where the head is stored
privately in the class, which holds if the class is properly initialized.

Postcondition:
No show_ref structs or show structs are added or removed from storage, however
linked list of show_ref structs is now ordered low to high of the rating of
the referenced show. Also privately stored head of list is updated.
*/
void show_Sort::sort_by_rating(){
    show_ref * temp = archive_list_head;
    show_ref * head = archive_list_head;
    show_ref * temp2;
    int high=-1;
    while (temp->next != NULL)
    {
        if (temp->ref_ptr->rating > high){
            head = temp;
            high = temp->ref_ptr->rating;
        }
        temp = temp->next;
    }
    if (head != archive_list_head){
    if (head->next != NULL){
    head->next->prev = head->prev;
    }
    if (head->prev != NULL){
    head->prev->next = head->next;
    }
    head->prev = NULL;
    head->next = archive_list_head;
    }
    for (int i = high; i >= -1; i--){
            temp = head->next;
        while (temp != NULL){
        if (temp->ref_ptr->rating==i){
            if (temp->next != NULL){
                temp->next->prev = temp->prev;
            }
            if (temp->prev != NULL){
                temp->prev->next = temp->next;
            }
            temp2 = temp;
            temp=temp->prev;
            temp2->next = head;
            head = temp2;
            head->prev = NULL;
            }
            temp = temp->next;
        }
    }
    archive_list_head = head;
    }

/*
Function prototype:
void show_Sort::sort_by_length()

Function description:
This method frames the recursive quickSort(int, int) function that orders the
linked list whose head is stored privately in the class by the length of the
reference pointers. Only necessary because quickSort(int, int) needs the
first and last positions in the list to be passed in and to simplify
the recursion of quickSort(int, int).

Example;
show_Sort sortlist(pre_sort_head);
sortlist.sort_by_length();

Precondition:
There is a properly linked list of struct show_ref where the head is stored
privately in the class, which holds if the class is properly initialized.

Postcondition:
No show_ref structs or show structs are added or removed from storage, however
linked list of show_ref structs is now ordered low to high of the length of
the referenced show. Also privately stored head of list is updated.
*/
void show_Sort::sort_by_length(){
    //quicksort implimentation
    show_ref * i_ref = archive_list_head;
    show_ref * j_ref = archive_list_head;
    int i_int = 0;
    int j_int = 0;
    while (j_ref->next != NULL){
        j_ref = j_ref->next;
        j_int++;
    }
    quickSort(i_int, j_int);;
}

show_ref * show_Sort::get_head(){
    return archive_list_head;
}

/*
Function prototype:
void show_Sort::quickSort(int, int)

Function description:
For private use inside show_Sort class only. Is a recursive function that
implements the quick sort method of sorting. Sorts smaller and smaller sections
of the linked list and pivots in order to completely sort the list by the
referenced length of the show_ref struct list.

Example;
(private function, will only run if sort_by_length() is called)
show_Sort sortlist(pre_sort_head);
sortlist.sort_by_length();

Precondition:
There is a properly linked list of struct show_ref where the head is stored
privately in the class, which holds if the class is properly initialized.

Postcondition:
No show_ref structs or show structs are added or removed from storage, however
linked list of show_ref structs is now ordered low to high of the length of
the referenced show. Also privately stored head of list is updated.
*/
void show_Sort::quickSort(int l_int, int r_int){
    show_ref *templeft = archive_list_head;
    for (int x = 0; x < l_int; x++){
        templeft = templeft->next;
    }
    show_ref *tempright = archive_list_head;
    for (int y = 0; y < r_int; y++){
        tempright = tempright->next;
    }
    show_ref *temp2;
    show_ref *temp3;
    show_ref * i_ref = templeft;
    int i = l_int;
    show_ref * j_ref = tempright;
    int j = r_int;
    show_ref * temp = archive_list_head;
    for (int i = 0; i < ((i+j)/2); i++){
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
            if (temp->next==temp2){
                swap(temp->ref_ptr, temp2->ref_ptr);
                i_ref = temp->next;
                j_ref = temp2->prev;
            } else{
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
            temp3 = i_ref->prev;
            i_ref=temp2->next;
            j_ref=temp->prev;
            }
            i++;
            j--;
            }
    }
    while (temp2->prev != NULL)
        temp2 = temp2->prev;
    archive_list_head = temp2;
    if (l_int < j){
        quickSort(l_int, j);
    }
    if (i < r_int){
        quickSort(i, r_int);
    }
}
