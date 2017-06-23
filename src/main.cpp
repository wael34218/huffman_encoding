#include "main.h"
#include "quick_sort.cpp"
#include "print.cpp"
#include "huffman.cpp"

/* text -> FreqTable (map<char, count>) -> FreqVector -> sorted huffman_code -> CodeTable (map<char, code>) */

int main(){
  string pp;
  cout << "Input string to compress:\n";
  getline(cin, pp);
  // Step 1: Count the frequencies of each character in a map
  FreqTable char_counts = counts(pp);
  // Step 2: Convert map into a vector
  FreqVector char_vector = reshape(char_counts);
  print_vec(char_vector);
  // Step 3: Sort the vector in assending order
  quick_sort(char_vector);
  print_vec(char_vector);
  // Step 4: Create linked list
  HuffmanNode * head = create_linked_list(char_vector);
  print_list(head);
  // Step 5
  HuffmanNode * tree_head = build_huffman_tree(head);
  // Step 6
  CodeTable encodings = generate_encodings(tree_head);
  print_encoding(encodings);

  Encoding file_encoding = encode_content(pp, encodings);
  
  write_file(file_encoding, "encoded");
  return 0;
}
