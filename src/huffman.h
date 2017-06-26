HuffmanNode * create_linked_list(const FreqVector &);
HuffmanNode * build_huffman_tree(HuffmanNode *);
CodeTable generate_encodings(HuffmanNode *);
Encoding encode_content(string, CodeTable);
void write_file(Encoding, CodeTable, int, string);
void traverse_tree(HuffmanNode *, CodeTable &, Encoding);
string decode_file(string);
string decode_content(Encoding, RevCodeTable, int);
RevCodeTable reverse_code_table(CodeTable);
