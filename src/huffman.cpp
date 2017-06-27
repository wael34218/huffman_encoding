#include "huffman.h"

HuffmanNode * create_linked_list(const FreqVector & vec){
  HuffmanNode * head = NULL;
  HuffmanNode * node;

  for(FreqVector::const_reverse_iterator it=vec.rbegin(); it!=vec.rend(); it++) {
    node = new HuffmanNode;
    node->c = it->first;
    node->freq = it->second;
    node->next = head;
    node->left_child = NULL;
    node->right_child = NULL;
    head = node;
  }

  return head;
}

HuffmanNode * build_huffman_tree(HuffmanNode *head){
  HuffmanNode *n1, *n2, *newNode, *p, *trailing;

  while(head->next != NULL){
    n1 = head;
    n2 = head->next;
    head = n2->next;

    newNode = new HuffmanNode;
    newNode->freq = n1->freq + n2->freq;
    newNode->c = '\0';
    newNode->left_child = n1;
    newNode->right_child = n2;
    newNode->next = NULL;

    if(head != NULL && head->freq >= newNode->freq){
      // If the two smallest nodes are still smaller than the next node
      // then put the new node in front.
      newNode->next = head;
      head = newNode;
      // print_list(head);
      continue;
    }
    p = head;
    trailing = NULL;
    while(true){
      if(p == NULL){
        // Reached the end of the linked list
        if(head == NULL)
          head = newNode;
        if(trailing != NULL)
          trailing->next = newNode;
        break;
      }
      if(p->freq >= newNode->freq){
        // Insert the new node here
        newNode->next = p;
        if(trailing != NULL)
          trailing->next = newNode;
        break;
      }else{
        // Check the next node
        trailing = p;
        p = p->next;
      }
    }
    // print_list(head);
  }
  return head;
}

CodeTable generate_encodings(HuffmanNode *head){
  CodeTable encodings;
  Encoding base_encoding;
  traverse_tree(head, encodings, base_encoding);
  return encodings;
}

void traverse_tree(HuffmanNode *head, CodeTable &encodings, Encoding base_encoding){
  if(head->c == '\0'){
    base_encoding.push_back(true);
    traverse_tree(head->right_child, encodings, base_encoding);
    base_encoding.pop_back();
    base_encoding.push_back(false);
    traverse_tree(head->left_child, encodings, base_encoding);
    base_encoding.pop_back();
  }else{
    // This is to handle if there is only one character in the whole file
    if(base_encoding.empty()){
      base_encoding.push_back(true);
    }
    // Add character to encodings
    encodings[head->c] = base_encoding;
  }
}

Encoding encode_content(string text, CodeTable encodings){
  Encoding binary_encoding;
  for(int i=0; i<text.size(); i++){
    binary_encoding.insert(binary_encoding.end(), encodings[text[i]].begin(), encodings[text[i]].end());
  }
  return binary_encoding;
}

RevCodeTable reverse_code_table(CodeTable code_table){
  RevCodeTable reversed;
  for(CodeTable::iterator it=code_table.begin(); it!=code_table.end(); it++){
    reversed.insert(pair<Encoding, char>(it->second,it->first));
  }
  return reversed;
}

void write_file(Encoding encoding, CodeTable code_table, int size, string filename){
  std::ofstream code_file(filename);

  // Write how many characters in file
  code_file << size << "|";

  // Write reverse code table
  for(CodeTable::iterator it=code_table.begin(); it!=code_table.end(); it++){
    code_file << it->first;
    for(int i = 0; i < it->second.size(); i++){
      if(it->second[i])
        code_file << "1";
      else
        code_file << "0";
    }
    code_file << "|";
  }
  code_file << "||";
  code_file.close();
  const std::size_t n = encoding.size();
  int limit = (int)ceil(n/8.0);
  char byteArray[limit];

  // Write binary data
  for (std::size_t i = 0; i < limit; ++i)
    for (std::size_t j = 0; j < 8; ++j)
      byteArray[i] ^= (-encoding[i * 8 + j] ^ byteArray[i]) & (1 << j);

  std::ofstream out(filename, std::ios::binary | fstream::app);
  out.write(byteArray, sizeof(byteArray));
  out.close();
}

string decode_file(string filename){
  string tmp;
  char tchar;
  int size;
  RevCodeTable rev_code_table;
  Encoding encoding;
  Encoding char_encoding;
  std::ifstream file(filename);
  vector<char> res = vector<char>((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
  int i = 0;
  while(res[i] != '|'){
    tmp += res[i];
    i++;
  }
  i++;
  size = atoi(tmp.c_str());  

  for (; i < res.size(); ++i){
    tchar = res[i];
    i++;
    if(res[i] == '|')
      break;
    char_encoding.clear();
    while(res[i] != '|'){
      if(res[i] == '1')
        char_encoding.push_back(true);
      else
        char_encoding.push_back(false);
      i++;
    }
    rev_code_table.insert(pair<Encoding, char>(char_encoding,tchar));
  }
  i++;

  for (; i < res.size(); ++i)
    for (int j = 0; j < 8; ++j)
      encoding.push_back((res[i] >> j) & 1);
  
  string decoded = decode_content(encoding, rev_code_table, size);
  return decoded;
}

string decode_content(Encoding binary_encoding, RevCodeTable rev_code_table, int size){
  string text = "";
  Encoding tmp;
  int chars = 0;
  for(int i=0; i<binary_encoding.size(); i++){
    tmp.push_back(binary_encoding[i]);
    if(rev_code_table.count(tmp)){
      text += rev_code_table[tmp];
      chars++;
      tmp.clear();
      if(chars >= size)
        break;
    }
  }
  return text;
}
