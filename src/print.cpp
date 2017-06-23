#include "print.h"

void print_vec(const FreqVector & vec) {
  for(FreqVector::const_iterator it=vec.begin(); it!=vec.end(); it++) {
    cout << ' ' << it->first << ":" << it->second << " - ";
  }
  cout << '\n';
}

void print_list(HuffmanNode *head) {
  HuffmanNode *i  = head;
  while(true){
    cout << ' ' << i->c << ":" << i->freq << " - ";
    if(i->next != NULL)
      i = i->next;
    else
      break;
  }
  cout << '\n';
}

void print_encoding(CodeTable &encoding) {
  for(CodeTable::iterator it=encoding.begin(); it!=encoding.end(); it++){
    string en = "";
    for(Encoding::iterator i=it->second.begin(); i!=it->second.end(); i++){
      if(*i)
        en = en + "1";
      else
        en = en + "0";
    }
    cout << ' ' << it->first << ":" << en<< " - ";
  }
  cout << '\n';
}
