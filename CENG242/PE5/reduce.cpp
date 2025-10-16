#include "reduce.h"

double ReduceFunction::apply(const List &list) const {
    ListNode* trav = list.get();
    
    if (trav == NULL) return 0;
    double n = trav->data;
    trav = trav->next;
    
    while (trav != NULL)
    {
        n = function(n, trav->data);
        trav = trav->next;
    }
    
    return n;
}

double SumReduceFunction::function(double acc, double current) const {
    return current + acc;
}

double MultiplyReduceFunction::function(double acc, double current) const {
    return current * acc;
}
