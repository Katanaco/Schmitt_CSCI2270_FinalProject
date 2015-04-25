#include <iostream>
#include "showTraker.h"
//#include "showSort.cpp"
#include <fstream>

using namespace std;

void displayMenu(){
cout << "======Main Menu======" << endl;
cout << "1. Insert show" << endl;
cout << "2. Delete show" << endl;
cout << "3. Find show" << endl;
cout << "4. Print contents" << endl;
cout << "5. "<<endl;
cout << "5. Quit" << endl;
}
int main(){
    int i;
    cout<<"enter hash table size"<<endl;
    cin>>i;
    HashTable H(i);
    show_ref * head;
    string input = "";
    int input2;
    bool checkdistricts=false;
    /*
    H.insertshow("code lyoko",200,true);
    H.insertshow("adventure time",80,false);
    H.insertshow("steven universe",40,false);
    H.insertshow("flcl",6,true);
    H.insertshow("jojos",110,false);
    H.insertshow("archer",60,false);
    H.rateShow("adventure time",1);
    H.rateShow("steven universe",3);
    H.rateShow("flcl",4);
    H.rateShow("jojos",4);
    */
    H.read_from_file();
    while (input != "5"){
        displayMenu();
        cin>>input;
        if (input == "1"){
            cout << "Enter title:" << endl;
            getline(cin>>ws, input);
            cout << "Enter year:" << endl;
            cin>>input2;
            H.insertshow(input, input2, false);
        } else if (input == "2"){
            cout << "Enter title:" << endl;
            getline(cin>>ws, input);
            H.deleteshow(input);

        } else if (input == "3"){
            cout << "Enter title:" << endl;
            getline(cin>>ws, input);
            show *found=H.findshow(input);



        } else if (input == "4"){
            head = H.sortSetup();
            show_Sort sortthing(head);
            sortthing.sort_by_length();
            head = sortthing.get_head();
            while (head->next != NULL){
                cout<<head->ref_ptr->title<<" : "<<head->ref_ptr->lenght<<endl;
                head=head->next;
            }
            cout<<head->ref_ptr->title<<" : "<<head->ref_ptr->lenght<<endl;
            sortthing.sort_by_rating();
            head = sortthing.get_head();
            while (head->next != NULL){
                cout<<head->ref_ptr->title<<" : "<<head->ref_ptr->rating<<endl;
                head=head->next;
            }
            cout<<head->ref_ptr->title<<" : "<<head->ref_ptr->rating<<endl;
            sortthing.~show_Sort();
        }
    }

    H.write_to_file();
    H.printInventory();
    //H.~HashTable();
    cout<<"Goodbye!"<<endl;
    return 0;
}

