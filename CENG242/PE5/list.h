#ifndef THE5_LIST_H
#define THE5_LIST_H

#include <string>

class MapFunction;
class ReduceFunction;
class FilterFunction;

struct ListNode{
    double data;
    ListNode* next;
};


class List {
    private:
        ListNode* first;
        ListNode* last;
        int size = 0;
    public:
        List();
        List(const double* arr, int listSize);
        List(const List& other);
        ~List();

        void pushBack(double value);
        void pop();
        double operator[](int idx) const;

        operator std::string() const {
            std::string result = "List(";
            for(auto temp=this->first; temp != nullptr; temp = temp->next)
                result += std::to_string(temp->data) + (temp->next == nullptr ? ") " : " -> ");
            return this->size == 0 ? "Empty List" : result;
        };


        List map(const MapFunction& func) const;
        List filter(const FilterFunction& func) const;
        double reduce(const ReduceFunction& func) const;
        
        ListNode* get() const
        {
            return first;
        }

};

#endif //THE5_LIST_H
