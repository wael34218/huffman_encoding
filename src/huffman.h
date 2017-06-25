HuffmanNode * create_linked_list(const FreqVector &);
HuffmanNode * build_huffman_tree(HuffmanNode *);
CodeTable generate_encodings(HuffmanNode *);
Encoding encode_content(string, CodeTable);
void write_file(Encoding, string);
Encoding read_file(string);
void traverse_tree(HuffmanNode *, CodeTable &, Encoding);
string decode_content(Encoding, RevCodeTable);
RevCodeTable reverse_code_table(CodeTable);
