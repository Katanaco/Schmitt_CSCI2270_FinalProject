#include "showTraker.h"
#include "showSort.h"
using namespace std;

show_Sort::show_Sort(show_ref * ah){
    archive_list_head = ah;
}
show_Sort::~show_Sort(){
}
show_ref * show_Sort::sort_by_rating(){
    show_ref * temp = archive_list_head;

}
show_ref * show_Sort::sort_by_length(){
}

