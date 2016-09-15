#include "../sortstack.hpp"
#include <iostream>










datum Datum(int t, int d, int x, int y){
	datum dt;
	dt.tile = t;
	dt.depth = d;
	dt.x = x;
	dt.y = y;
	return dt;
}










inline int getDepth(datum m){
  return m.depth;
}










void push (sortstack* s, datum n){
  s->top++;
  if(s->top < 0) s->top = 0;
  if(s->top >= 2048){
    s->top--;
    return;
  }
  s->data[s->top] = n;
}










void flush (sortstack* s){

  for(int i = 0; i < s->top; i++)
    s->data[i] = Datum(0,0,0,0);

  s->top = -1;
}










void mergesort (sortstack* a, int start, int end, int x){
  int pivot = ((start + end) / 2);

  if(start < end -1){
    mergesort(a, start, pivot, x+1);
    mergesort(a, pivot, end, x+1);
  }else{
    if(getDepth(a->data[start]) < getDepth(a->data[start+1])){
      a->altn[start] = a->data[start];
      a->altn[start+1] = a->data[start+1];
    }else{
      a->altn[start] = a->data[start+1];
      a->altn[start+1] = a->data[start];
    }
    return;
  }

  int index0 = start;
  int index1 = pivot;
  int indexB = start;

  bool cont = true;
  while(cont){
    if(getDepth(a->data[index0]) < getDepth(a->data[index1])){
      a->altn[indexB] = a->data[index0];
      index0++;
    }else{
      a->altn[indexB] = a->data[index1];
      index1++;
    }

    indexB++;
    cont = index0 < pivot;
    if(index0 >= pivot){
      for(int i = index1; i < end; i++){
        a->altn[indexB] = a->data[i];
        indexB++;
      }
      cont = false;
    }else if(index1 >= end){
      for(int i = index0; i < pivot; i++){
        a->altn[indexB] = a->data[i];
        indexB++;
      }
      cont = false;
    }
  }

  for(int i = start; i < end; i++)
    a->data[i] = a->altn[i];

}










sortstack* mergeSort (sortstack* s){
  //if(s == nullptr) return nullptr;

  for(int i = 0; i <= s->top; i++)
    s->altn[i] = s->data[i];
    
  int top = s->top;

  mergesort(s, 0, s->top + 1, 0);
  
  s->top = top;
  return s;
}










sortstack* bubbleSort (sortstack* s){
  //if(s == nullptr) return nullptr;
  for(int i = 0; i <= s->top; i++){
    int min = getDepth(s->data[i]);
    int index = i;
    for(int j = i + 1; j <= s->top; j++){
      if(min > getDepth(s->data[j])){
        min = getDepth(s->data[j]);
        index = j;
      }
    }
    datum n = s->data[i];
    s->data[i] = s->data[index];
    s->data[index] = n;
  }
  return s;
}










sortstack* sort (sortstack* s){
  //if(s == nullptr) return nullptr;
  return (s->top < 37)? bubbleSort(s) : mergeSort(s);
}
