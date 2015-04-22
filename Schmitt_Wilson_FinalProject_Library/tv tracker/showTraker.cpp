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
