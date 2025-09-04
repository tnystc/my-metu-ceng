#include "list.h"
#include "map.h"
#include "filter.h"
#include "reduce.h"

List List::map(const MapFunction& func) const {
    return func.apply(*this);
}

List List::filter(const FilterFunction& func) const {
    return func.apply(*this);
}

double List::reduce(const ReduceFunction& func) const {
    return func.apply(*this);
}

List::List() {
    first = NULL;
    last = NULL;
    size = 0;
}

List::List(const double* arr, int listSize){
    first = NULL;
    last = NULL;
    size = 0;
    
    for (int i = 0; i< listSize; i++)
    {
        pushBack(arr[i]);
    }
}

List::List(const List& other){
    first = NULL;
    last = NULL;
    size = 0;
    
    ListNode* trav = other.first;
    while(trav != NULL)
    {
        pushBack(trav->data);
        trav = trav->next;
    
    }
}

List::~List(){
    int n = size;
    for (int i = 0; i < n; i++)
    {
        pop();
    }
}

void List::pushBack(double value) {
    ListNode* nn = new ListNode;
    nn->data = value;
    nn->next = NULL;
    
    if (first != NULL)
    {
        last->next = nn;
        last = nn;
        size++;
    }
    else
    {
        first = nn;
        last = nn;
        size++;
    }
    
}

void List::pop(){
    if (first == NULL) return;
    
    ListNode* tmp = first;
    first = first->next;
    delete tmp;
    
    size--;
    if (size == 0)
    {
        last = NULL;
    }
}

double List::operator[](int idx) const {
    if (size == 0) return -1;
    
    ListNode* trav = first;
    for (int i = 0; i < idx; i++)
    {
        trav = trav->next;
        
    }
    return trav->data;
}
