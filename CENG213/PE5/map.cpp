#include "map.h"

List MapFunction::apply(const List& list) const {
    List l;
    
    ListNode* trav = list.get();
    while(trav != NULL)
    {
        l.pushBack(transform(trav->data));
        trav = trav->next;
        
    }
    
    return l;
}

AddConstantMapFunction::AddConstantMapFunction(double constant) {
    value = constant;
}

double AddConstantMapFunction::transform(double element) const {
    return element + value;
}

GreaterThanMapFunction::GreaterThanMapFunction(double constant) {
    threshold = constant;
}

double GreaterThanMapFunction::transform(double element) const {
    if (element > threshold)
    {
        return 1;
    }
    else return 0;
}
