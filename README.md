# Krammer
A toy implementation of Huffman encoding. It crams content of input file into a compressed output file.

## Build and Install
```
make
make install
```

## Run
To compress a file run the following command:
```
krammer encode -in sample_input/hackernews.html.txt -out sample_compressed/hackernews.html.krm
```
To decode the file run:
```
krammer decode -in sample_compressed/hackernews.html.krm -out sample_decompressed/hackernews.html.txt
```

## Under the hood
Compressed files \*.krm stores the content in the following format:
```
#chars|HashTable|||binary_content
```
The hashtable is pipe-separated key value store.

#### Example:
```
33518|;1011|>11101|a101 ... |z110010010001|||O.d4g.Gs&I.$I.Y ...
```

## Output

| File | Original Size | Compressed Size | Reduction Percentage |
| --- | --- | --- | --- |
| hackernews.html | 34KB | 22KB | 35.3 % |
| newstest2013.en | 333KB | 190KB | 42.9% |
| enOST\_sample.txt | 9.2MB | 5.3MB | 42.4% |
