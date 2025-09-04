#ifndef THE5_MAP_H
#define THE5_MAP_H

#include "list.h"

class MapFunction {
    public:
        virtual List apply(const List& list) const;
        virtual double transform(double element) const = 0;
};

class AddConstantMapFunction: public MapFunction {
    private:
        double value;
    public:
        AddConstantMapFunction(double const);
        double transform(double element) const override;
};

class GreaterThanMapFunction: public MapFunction {
    private:
        double threshold;
    public:
        GreaterThanMapFunction(double constant);
        double transform(double element) const override;
};

#endif //THE5_MAP_H
