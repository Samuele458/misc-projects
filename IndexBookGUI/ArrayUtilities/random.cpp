#include  "random.h"

Numbers::Random::Random() : Random( 0, 1000, true ) { }

Numbers::Random::Random( int minNumberValue, int maxNumberValue, bool IncludedOrEqualMode ) {
    minValue = minNumberValue;
    maxValue = maxNumberValue;
    IncludedOrEqual = IncludedOrEqualMode;
    randValue = 0;
}

Numbers::Random::Random( int minNumberValue, int maxNumberValue ) : Random( minNumberValue, maxNumberValue, true ) { }

void Numbers::Random::setMinValue( int value ) {
    minValue = value;
}

void Numbers::Random::setMaxValue( int value ) {
    maxValue = value;
}

int Numbers::Random::getMinValue() {
    return minValue;
}

int Numbers::Random::getMaxValue() {
    return maxValue;
}

void Numbers::Random::setMode( bool mode ) {
    IncludedOrEqual = mode;
}

bool Numbers::Random::getMode() {
    return IncludedOrEqual;
}

int Numbers::Random::getRandom() {
    if ( IncludedOrEqual ) {
        randValue = rand() % ( maxValue - minValue + 1 ) + minValue;
    } else {
        randValue = rand() % ( maxValue - minValue - 1 ) + minValue + 1;
    }

    return randValue;
}
