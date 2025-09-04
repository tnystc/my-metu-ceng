#ifndef THE5_FILTER_H
#define THE5_FILTER_H

#include "list.h"

class FilterFunction {
    public:
        virtual List apply(const List& list) const;
        virtual bool check(double element) const = 0;
};

class GreaterThanFilterFunction: public FilterFunction {
    private:
        double constant;
    public:
        GreaterThanFilterFunction(double value);
        bool check(double element) const override;
};

class EqualToOneFilterFunction: public FilterFunction {
    public:
        bool check(double element) const override;
};

#endif //THE5_FILTER_H
