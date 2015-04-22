#include "showTraker.h"
using namespace std;

HashTable::HashTable(int s){
    hashsize=s;
    interested= new show*[s];
    watching= new show*[s];
    finished= new show*[s];

    for (int i=0; i<s;i++){
        interested[i]=NULL;
        watching[i]=NULL;
        finished[i]=NULL;
    }
}
HashTable::~HashTable(){

}
int HashTable::Hashsum(string title){
    int sum = 0;
    for (int i = 0; i<title.length();i++){
        sum=sum+(int)title[i];
    }
    sum=sum%hashsize;
    return sum;
}
void HashTable::insertshow(string series, int total, bool finished){
    int i=Hashsum(series);
    show *shw=new show(series, total, finished);
    if (interested[i]==NULL){

    interested[i]=shw;
    }else{
        show *temp=interested[i];
        if (temp->title>series){
            interested[i]=shw;
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
         if (interested[i]!=NULL){
                show *temp=interested[i];
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
void HashTable::deleteshow(string in_title){
    show* found=findshow(in_title);
    int i=Hashsum(in_title);
    if (found!=NULL){
            if (found==interested[i]){
                interested[i]=found->next;
                delete found;
            }else{
        show* temp=interested[i];
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
        if (interested[i]==NULL){
           test++;
        }else{
                show *temp=interested[i];
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
