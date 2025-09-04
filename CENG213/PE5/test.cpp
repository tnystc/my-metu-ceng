#include <iostream>

#include "list.h"
#include "map.h"
#include "filter.h"
#include "reduce.h"


int main() {
    double arr[] = {3, 6, 5};
    List emptyList;
    std::cout << "Empty list test: " << (std::string)emptyList << std::endl;
    List list1(arr, 3);
    std::cout << "List with 3 elements test: " << (std::string)list1 << std::endl;
    List list2(list1);
    list1.pop();
    std::cout << "Copy list test: " << (std::string)list2 << std::endl;
    std::cout << "Pop test: " << (std::string)list1 << std::endl;
    emptyList.pushBack(4);
    std::cout << "Push back test 1 element test: " << (std::string)emptyList << std::endl;
    std::cout << "Index test: " << list1[1] << std::endl;


    double temp = list2.map(AddConstantMapFunction(5))
                       .filter(GreaterThanFilterFunction(9))
                       .reduce(MultiplyReduceFunction());
    std::cout << "AddConstant-Filter-Multiply test: " << temp << std::endl;

    double count = list2.map(GreaterThanMapFunction(4))
                        .filter(EqualToOneFilterFunction())
                        .reduce(SumReduceFunction());
    std::cout << "Number of elements greater than 4 test: " << count << std::endl;

    /* Output:
    Empty list test: Empty List
    List with 3 elements test: List(3.000000 -> 6.000000 -> 5.000000)
    Copy list test: List(3.000000 -> 6.000000 -> 5.000000)
    Pop test: List(6.000000 -> 5.000000)
    Push back test 1 element test: List(4.000000)
    Index test: 5
    AddConstant-Filter-Multiply test: 110
    Number of elements greater than 4 test: 2
     */
    return 0;
}
