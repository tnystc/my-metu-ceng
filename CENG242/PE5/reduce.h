#ifndef THE5_REDUCE_H
#define THE5_REDUCE_H

#include "list.h"

class ReduceFunction {
    public:
        virtual double apply(const List& list) const;
        virtual double function(double acc, double current) const = 0;
};


class SumReduceFunction: public ReduceFunction {
    public:
        double function(double acc, double current) const override;
};

class MultiplyReduceFunction: public ReduceFunction {
    public:
        double function(double acc, double current) const override;
};


#endif //THE5_REDUCE_H
