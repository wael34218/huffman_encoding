# Krammer
A toy implementation of Huffman encoding. It crams content of input file into a compressed output file.

## Build
```
g++ src/krammer.cpp -o bin/krammer
```

## Run
To compress a file run the following command:
```
./bin/krammer encode -in sample_input/hackernews.html -out sample_compressed/hackernews.krm
```
To decode the file run:
```
./bin/krammer decode -in sample_compressed/hackernews.krm -out sample_decompressed/hackernews.html
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

| File | Original Size | Compressed Size |
| --- | --- | --- |
| hackernews.html | 34KB | 22KB |
| newstest2013.en | 333KB | 190KB |
