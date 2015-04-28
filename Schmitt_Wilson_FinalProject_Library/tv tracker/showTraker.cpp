#include "showTraker.h"
//#include "showSort.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


HashTable::HashTable(int s){
    if(s<=0){
        cout<<"invalid size"<<endl;
    }else{
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

/*
Function prototype:
int HashTable::Hashsum(string)

Function description:
This private method uses the title of a show and creates a hash value for it, adding
all the char askii value and taking the integer remainder of the sum and
the hashsize stored as a class variable.

Example;
(private function, will only run if dependent like insertshow() is called)
HashTable storetable(Hash_table_size);
storetable.insertshow(series, total, ended);

Precondition:
there must be a HashTable constructed with a valid hashsize and a dependent function must be called.

Postcondition:
it then outputs the that integer remainder for the title.
*/
int HashTable::Hashsum(string title){
    int sum = 0;
    for (int i = 0; i<title.length();i++){
        sum=sum+(int)title[i];
    }
    sum=sum%hashsize;
    return sum;
}
/*
Function prototype:
int HashTable::insertshow(string , int , bool)

Function description:
This method takes the arguments for a new show struct and crates it. then it finds
its hash value in the table and alphobeticly puts it into the hash table.

Example;
HashTable storetable(Hash_table_size);
storetable.insertshow(series, total, ended);

Precondition:
a valid HashTable must be formed and all values for a new show must be valid.

Postcondition:
a new show will be added to the hash table under its hashvalue and
alphabetically organized into a linked list.
*/
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
/*
Function prototype:
int HashTable::findshow(string)

Function description:
this method takes a title for a show and searches the hash table for a show
structure with that title and outputs the whole structure

Example;
HashTable storetable(Hash_table_size);
storetable.findshow(series);

Precondition:
a valid HashTable must be formed and a valid string must be entered.

Postcondition:
the HashTable will remain unchanged but a copy of the found
structure will be output or a NULL if it was not found.
*/
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
/*
Function prototype:
int HashTable::rateShow(string, int)

Function description:
this method takes a title for a show and a rating form 1-5 then uses
findshow to search the hash table for it and then gives it your rating.

Example;
HashTable storetable(Hash_table_size);
storetable.rateShow(series, stars);

Precondition:
a valid HashTable must be formed and a valid string must
be entered that corresponds to an archived show and give a stars
value of between 1-5 and not have been rated before.

Postcondition:
the HashTable will remain unchanged but the shows rating will be
updated returning a 1 if successful 0 if already rated and a -1 if outside the bound.
*/
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
/*
Function prototype:
int HashTable::next_episode_watched(string)

Function description:
this method takes a title for a show then uses findshow to search
the hash table for it.  then it adds one to the episode count and tells
you if what the next episode of that series is or that you are caught up.

Example;
HashTable storetable(Hash_table_size);
storetable.next_episode_watched(series);

Precondition:
a valid HashTable must be formed and a valid string must
be entered that corresponds to an archived show.

Postcondition:
the HashTable will remain unchanged but the function will tell you
what the next episode you need to watch is or that you are caught up
and increase the episode count and state the series is completed if it is.
*/
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
/*
Function prototype:
int HashTable::next_to_watch_all()

Function description:
this method takes no argument and searches the hash table for all unfinished
 series and tells you if what the next episode of that series is.

Example;
HashTable storetable(Hash_table_size);
storetable.next_to_watch_all();

Precondition:
a valid HashTable must be formed.

Postcondition:
the HashTable will remain unchanged but the function will tell you
what the next episode you need to watch is for all series in the HashTable.
*/
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
/*
Function prototype:
int HashTable::next_episode_watched(string)

Function description:
this method takes a title for a show then uses findshow to search
the hash table for it and tells you if what the next episod of
that series is or that you are caught up.

Example;
HashTable storetable(Hash_table_size);
storetable.next_episode_watched(series);

Precondition:
a valid HashTable must be formed and a valid string must
be entered that corresponds to an archived show.

Postcondition:
the HashTable will remain unchanged but the function will tell you
what the next episode you need to watch is or that you are caught up.
*/
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
/*
Function prototype:
int HashTable::print_with_restriction(string)

Function description:
this method takes a restriction type and prints out the title, and rating
of series that fit under these restrictions or that the HashTable is empty

Example;
HashTable storetable(Hash_table_size);
storetable.print_with_restriction(restrict);

Precondition:
a valid HashTable must be formed and one of the following restrictions must be entered.
restrictions:completed, watching, finished, interested.

Postcondition:
the HashTable will remain unchanged but the function will tell you
title and rating or that the HashTable is empty.
*/
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
                        cout<<temp->title<<":"<<temp->rating<<endl;
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
                        cout<<temp->title<<":"<<temp->rating<<endl;
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
/*
Function prototype:
int HashTable::deleteshow(string)

Function description:
this method takes a title for a show then uses findshow to search
the hash table for it.  then it deletes it and adjustments the HashTable
by fixing the linked list or making the cell NULL if it is now empty.

Example;
HashTable storetable(Hash_table_size);
storetable.deleteshow(series);

Precondition:
a valid HashTable must be formed and a valid string must
be entered that corresponds to an archived show.

Postcondition:
the HashTable have the given series removed and the linked list will be
adjusted and the HashTable cell will be adjusted or made NULL if it becomes empty
*/
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
/*
Function prototype:
int HashTable::printInventory()

Function description:
this method takes no argument and prints out the title, number of
episodes watched out of the length or that the HashTable is empty

Example;
HashTable storetable(Hash_table_size);
storetable.printInventory();

Precondition:
a valid HashTable must be formed.

Postcondition:
the HashTable will remain unchanged but the function will tell you
title, number of episodes whatched out of the length or that the HashTable is empty.
*/
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
/*
Function prototype:
int HashTable::clearhash()

Function description:
this method takes no argument and deletes every show in the HashTable leaving a completely empty HashTable.

Example;
HashTable storetable(Hash_table_size);
storetable.clearhash();

Precondition:
a valid HashTable must be formed.

Postcondition:
the HashTable will become empty with all cells set to NULL.
*/
void HashTable::clearhash(){
    int test=0;
    show *del;
    for (int i=0; i<hashsize; i++){
        if (archive[i]==NULL){
           test++;
        }else{
                show *temp=archive[i];
            while(temp->next!=NULL){
                del=temp;
                temp=temp->next;
                delete del;

            }
                delete temp;
                archive[i]=NULL;


        }
    }
    if (test==hashsize){
        cout << "empty" << endl;
    }
}
/*
Function prototype:
int HashTable::sortSetup()

Function description:
This private method uses the takes the hash table and makes a linked list
of show_ref structureas pointing to all the shows in the hash table.
it is used to setup for the sort functions below.

Example;
HashTable storetable(Hash_table_size);
storetable.sortSetup();

Precondition:
a valid HashTable must be formed.

Postcondition:
the HashTable will remain unchanged but the function output a show_ref
that is the head of the liked list created or a NULL if the HashTable is empty.
*/
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
/*
Function prototype:
void HashTable::write_to_file()

Function description:
This public method writes all of the class' information to the
pre-established temp file as a means of saving information between
instances of the program; in order to be used write to file
should be called at the end of the instance of the library and
read from file should be called upon the next startup.

Example;
HashTable storetable(Hash_table_size);
storetable.insertshow("name",10,10);
storetable.write_to_file();

Precondition:
a valid HashTable must be formed.

Postcondition:
the HashTable's information will be stored for reference upon calling
read_from_file().
*/
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
/*
Function prototype:
void HashTable::read_from_file()

Function description:
This public method reads all of previous use of the class' information to the
Hash table as a means of saving information between
instances of the program; in order to be used write to file should
should be called at the end of the instance of the library and
read from file should be called upon the next startup.

Example;
HashTable storetable(Hash_table_size);
storetable.read_from_file();

Precondition:
a valid HashTable must be formed. There must be valid information written
within the temp file.

Postcondition:
the HashTable's information will be read to the current instance for normal
use with the rest of the class' functions.
*/
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
