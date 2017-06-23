#include "quick_sort.h"

FreqTable counts(string text){
  FreqTable counts;
  for(int i=0; i < text.size(); i++){
    if(counts.find(text[i]) == counts.end()){
      counts[text[i]] = 1;
    }else{
      counts[text[i]] += 1;
    }
  }
  return counts;
}

FreqVector reshape(FreqTable freq){
  FreqVector vec;
  for(FreqTable::iterator it=freq.begin(); it!=freq.end(); it++){
    vec.push_back(make_pair(it->first, it->second));
  }
  return vec;
}

void quick_sort(FreqVector & vec, int start /*=0*/, int end /*=-1*/){
  end = (end < 0) ? vec.size() - 1 : end;
  // cout << start << " - " << end << "\n";

  if(start < end){
    int partition_index = partition(vec, start, end);
    quick_sort(vec, start, partition_index - 1);
    quick_sort(vec, partition_index + 1, end);
  }
}

int partition(FreqVector & vec, int start, int end){
  pair<char, unsigned> pivot = vec[end];
  int p = pivot.second;
  int pi = start;
  for(int i=start; i<end;i++){
    if(vec[i].second <= p){
      swap(vec[i], vec[pi]);
      pi++;
    }
  }
  if(pi == end -1 && vec[pi].second < vec[end].second){
    pi++;
  }else{
    swap(vec[pi], vec[end]);
  }
  return pi;
}
