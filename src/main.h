#include <stdio.h>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <fstream>
#include <bitset>

using namespace std;

typedef vector<bool> Encoding;
typedef map<char, Encoding> CodeTable;

struct HuffmanNode{
  char c;
  unsigned freq;

  HuffmanNode *left_child;
  HuffmanNode *right_child;
  
  HuffmanNode *next;
};
