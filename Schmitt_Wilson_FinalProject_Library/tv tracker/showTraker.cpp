#include "showTraker.h"
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
int HashTable::rateShow(show * show_to_rate, int stars){
    if (show_to_rate->rating != -1){
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
void HashTable::print_with_restriction(string restrict){
    if (restrict == "completed"){

    } else if (restrict == "watching"){

    } else if (restrict == "finished"){

    } else if (restrict == "interested"){

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
