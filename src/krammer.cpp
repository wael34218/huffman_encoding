#include "krammer.h"
#include "quick_sort.cpp"
#include "print.cpp"
#include "huffman.cpp"

/* text -> FreqTable (map<char, count>) -> FreqVector -> sorted huffman_code -> CodeTable (map<char, code>) */

int main(int argc, char *argv[]){
  if(argc < 5 || argc > 6){
    cout << "Usage: kramer [encode|decode] -in [filename] -out [filename]" << endl;
    exit(0);
  }

  // Get arguments
  string operation;
  string in_file;
  string out_file;
  for(int i=1; i < argc; i++){
    if(i == 1)
      operation = argv[i];
    if(strcmp(argv[i], "-in") == 0)
      in_file = argv[++i];
    if(strcmp(argv[i], "-out") == 0)
      out_file = argv[++i];
  }

  // Validate arguments
  if(operation != "encode" && operation != "decode"){
    cout << "Usage: kramer [encode|decode] -in [filename] -out [filename]" << endl;
    exit(0);
  }
  ifstream valid_file(in_file);
  if(!valid_file){
    cout << "In file does not exist" << endl;
    exit(0);
  }
  
  if(operation == "encode"){
    ifstream in_stream(in_file);
    string text((istreambuf_iterator<char>(in_stream)),istreambuf_iterator<char>());
    // cout << "Input string to compress:\n";
    // getline(cin, text);
    // Step 1: Count the frequencies of each character in a map
    FreqTable char_counts = counts(text);

    // Step 2: Convert map into a vector
    FreqVector char_vector = reshape(char_counts);
    // print_vec(char_vector);

    // Step 3: Sort the vector in assending order
    quick_sort(char_vector);
    // print_vec(char_vector);

    // Step 4: Create linked list
    HuffmanNode * head = create_linked_list(char_vector);
    // print_list(head);

    // Step 5: Create Huffman Tree
    HuffmanNode * tree_head = build_huffman_tree(head);

    // Step 6: Extract encoding hashtable from the tree
    CodeTable code_table= generate_encodings(tree_head);
    // print_code_table(code_table);

    // Step 7: Use hastable to encode the original text
    Encoding file_encoding = encode_content(text, code_table);

    // Step 8: Write decoded content into file
    write_file(file_encoding, code_table, text.size(), out_file);
  }else{
    // Step 10: Decode content of the file
    string content = decode_file(in_file);
    ofstream decompressed_file(out_file);
    decompressed_file << content;
    decompressed_file.close();
  }

  return 0;
}
