#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED
#include <cstdlib>
#include <ctime>

namespace Numbers {
    class Random;
}

class Numbers::Random {
    public:
        Random();
        Random( int minNumberValue, int maxNumberValue, bool IncludedOrEqualMode );
        Random( int minNumberValue, int maxnumbervalue );
        void setMinValue( int value );
        void setMaxValue( int value );
        int getMinValue();
        int getMaxValue();
        void setMode( bool mode );
        bool getMode();
        int getRandom();
    protected:
        int minValue;
        int maxValue;
        int randValue;
        bool IncludedOrEqual;
};

#endif // RANDOM_H_INCLUDED
