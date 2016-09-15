#ifndef _SORT_STACK_HEADER
#define _SORT_STACK_HEADER


#include <cstdint>










struct datum{
  int tile;
  int depth = 0;
  int x, y;
};










struct sortstack{
  datum data [2048];
  datum altn [2048];
  int top = -1;
};










datum Datum(int, int, int, int);
void push (sortstack*, datum);
void flush (sortstack*);
sortstack* mergeSort (sortstack*);
sortstack* bubbleSort (sortstack*);
sortstack* sort (sortstack*);




#endif
