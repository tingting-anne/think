#ifndef _THINK_RANDOM_H_
#define _THINK_RANDOM_H_
#include <climits>         //defines INT_MAX and ULONG_MAX constant 
#include <ctime>           //defines time() function 

namespace THINK{ 
/*线性同余算法*/
class Random 
{ 
public: 
    Random(long seed=0) {_seed=(seed?seed:time(NULL));} 
    void seed(long seed=0) {_seed=(seed?seed:time(NULL));} 
    int integer() {return _next();} 
    int integer(int min,int max) 
    { 
        return min+_next()%(max-min+1); 
    } 
    double real() 
    { 
        return double(_next())/double(INT_MAX); 
    } 
private: 
   
    void _randomize();
    int _next();
private:
	 unsigned long _seed; 
}; 

} //_THINK_RANDOM_H_

#endif

