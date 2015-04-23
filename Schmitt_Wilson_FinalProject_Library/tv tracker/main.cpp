#include <iostream>
#include "showTraker.h"
//#include "showSort.cpp"

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
            //H.printInventory();
            head = H.sortSetup();
            show_Sort sortthing(head);
            head = sortthing.sort_by_length();
            while (head->next != NULL){
                cout<<head->ref_ptr->title<<" : "<<head->ref_ptr->lenght<<endl;
                head=head->next;
            }
            sortthing.~show_Sort();
        }
    }
    cout<<"Goodbye!"<<endl;
    return 0;
}

