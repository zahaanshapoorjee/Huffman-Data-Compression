Huffman Coding by Zahaan Shapoorjee

Normally, characters are stored using 1 byte (8 bits). Even though we do not usually need to use all 8 bits to store these characters.

Huffman coding is a lossless data compression algorithm. The idea is to assign variable-length codes to input characters, lengths of the assigned codes are based on the frequencies 

of corresponding characters. The most frequent character gets the smallest code and the least frequent character gets the largest code.

I will use binary tree and heap data structures for my implementation. I will use the min heap to implement a priority queue in my algorithm and a binary tree to store and organise the data.

The basic algorigthm would go as follows: 

1) Build a min heap out of all leaf nodes (Min Heap is used as a priority queue) and create a leaf node for each unique character. 

2) Two nodes in the min heap are compared using the frequency field value. At first, at root is the least frequent character.

3) We then extract two nodes with the minimum frequency from the min heap. 

4) After this, we make a new internal node that has a frequency equal to the product of the frequencies of the two existing nodes. Create the second extracted node as the right child of the first extracted node and the other extracted node as the left child. To the minimum heap, add this node.

5) I will repeat this until the heap only has one node, i.e., the root node, and the tree will be complete.

I have done my own implementation by modifying this program to read a text file (input_Text.txt) , given in this zip, convert it into how it would be stored in bytes, and then re write the 

file so the size difference can be seen upon compression, into its binary equivalent. Then I will use the Huffman Greedy Algorithm to decompress the string and store that binary equivalent

in another text file (compressedOutput.txt). The terminal will output the original string read from the file, the binary equivalent that it would be stored in, the decompressed binary 

equivalent, the decoded string, and finally the compression ratio, storage saved and all the useful information that will show us why this algorithm is useful. 

Effective data compression with Huffman codes often results in savings of 20% to 90% of the original data. However, I have noticed the average compression ratio of single sentences using

my program are around 45%.

HOW TO RUN?

I have provided 3 files in this zip, an input file, a C program file, and a compressed output file. To run this program:

1) Edit the input_Text.txt file by changing it to whatever string of letters you want compressed.

2) Save the input_Text.txt file and run the C program, it will automatically read the input text file and run the compression as long as all files are in the same directory.

3) The terminal will then print the Huffman table indicating each character and their corresponding frequencies, as well as what binary equivalent will be used in the compressed string to

represent them. It will then provide all the necessary information about the compression that can be explained with a sample output (not including the table) that I will show here: 


Original String: Hello, I am Zahaan Shapoorjee and I am Extremely sad.

Uncompressed Original String in Binary = 0100100001100101011011000110110001101111001011000010000001001001001000000110000101101101001000000101101001100001011010000110000101100001011011100010000001010011011010000110000101110000011011110110111101110010011010100110010101100101001000000110000101101110011001000010000001001001001000000110000101101101001000000100010101111000011101000111001001100101011011010110010101101100011110010010000001110011011000010110010000101110

Encoded/Compressed String in Binary: 11101110001100111011000111010000010100111000010000101011111101101110010010100111111011000100101110111010100101011011001001110010001000100000101001110000100001100000000000011010111010001100011101000101110001100100001011

Decoded Binary to String: Hello, I am Zahaan Shapoorjee and I am Extremely sad.
Intial Bytes Before Compression = 53 x 8 = 424 bytes

After Compression = 218 bytes
Compression Percentage = 51.415092%
Storage Saved = 0.206000 KB


4) You can verify the truth/falsity of this data by simply clicking on the properties of the input and compressed output text files. 

DISCLAIMER: The input file is overwritten with its binary equivalent of the ASCII of what it would be stored as in a computer. That is why the input file is changed into binary upon 

running.

5) After running it once, to run it again, you can edit the input_Text.txt file once again to write a new string that you would like compressed.

Thank you 
