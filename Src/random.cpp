#include "random.h"

void Random::_randomize() 
{ 
    _seed=(314159265*_seed+13579)%ULONG_MAX; 
} 
int Random::_next() 
{ 
    int iterations=_seed%3; 
    for(int i=0;i<=iterations;i++) 
        _randomize(); 
    return int(_seed/2); 
} 


