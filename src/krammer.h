#include <stdio.h>
#include <stdlib.h>     // atoi
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <math.h>
#include <fstream>
#include <bitset>

using namespace std;

typedef vector<bool> Encoding;
typedef map<char, Encoding> CodeTable;
typedef map<Encoding, char> RevCodeTable;

struct HuffmanNode{
  char c;
  unsigned freq;

  HuffmanNode *left_child;
  HuffmanNode *right_child;
  
  HuffmanNode *next;
};
