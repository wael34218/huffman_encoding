HuffmanNode * create_linked_list(const FreqVector &);
HuffmanNode * build_huffman_tree(HuffmanNode *);
CodeTable generate_encodings(HuffmanNode *);
Encoding encode_content(string, CodeTable);
void write_file(Encoding, string);
void traverse_tree(HuffmanNode *, CodeTable &, Encoding);
