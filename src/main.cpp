#include "main.h"
#include "quick_sort.cpp"
#include "print.cpp"
#include "huffman.cpp"

/* text -> FreqTable (map<char, count>) -> FreqVector -> sorted huffman_code -> CodeTable (map<char, code>) */

int main(){
  string text;
  cout << "Input string to compress:\n";
  getline(cin, text);
  // Step 1: Count the frequencies of each character in a map
  FreqTable char_counts = counts(text);

  // Step 2: Convert map into a vector
  FreqVector char_vector = reshape(char_counts);
  print_vec(char_vector);

  // Step 3: Sort the vector in assending order
  quick_sort(char_vector);
  print_vec(char_vector);

  // Step 4: Create linked list
  HuffmanNode * head = create_linked_list(char_vector);
  print_list(head);

  // Step 5: Create Huffman Tree
  HuffmanNode * tree_head = build_huffman_tree(head);

  // Step 6: Extract encoding hashtable from the tree
  CodeTable code_table= generate_encodings(tree_head);
  print_code_table(code_table);

  // Step 7: Use hastable to encode the original text
  Encoding file_encoding = encode_content(text, code_table);

  // Step 8: Prepare reverse lookup map for decoding
  RevCodeTable rev_code_table = reverse_code_table(code_table);
  print_rev_code_table(rev_code_table);

  // Step 9: Write decoded content into file
  write_file(file_encoding, "encoded.bin");

  // Step 10: Decode content of the file
  string decoded = decode_content(file_encoding, rev_code_table);
  cout << endl << endl << "Decoded: " << decoded << endl << endl;
  return 0;
}
