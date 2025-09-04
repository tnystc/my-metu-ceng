#include "filter.h"

List FilterFunction::apply(const List& list) const {
    List l;
    
    ListNode* trav = list.get();
    while(trav != NULL)
    {
        if (check(trav->data))
        {
            l.pushBack(trav->data);
        }
        
        trav = trav->next;
        
    }
    
    return l;
}

bool GreaterThanFilterFunction::check(double element) const {
    if (element > constant) return 1;
    else return 0;
}

GreaterThanFilterFunction::GreaterThanFilterFunction(double value) {
    constant = value;
}

bool EqualToOneFilterFunction::check(double element) const {
    if (element == 1) return 1;
    else return 0;
}
