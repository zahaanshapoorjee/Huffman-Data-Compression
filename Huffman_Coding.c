#include <stdio.h>
#include <string.h>
 
typedef struct tree_Node {
	struct tree_Node *l, *r;
	int frequency;
	char c;
} *node;
 
struct tree_Node mapping[256] = {{0}};
node ASCII[255], *q = ASCII - 1;
int no_of_nodes = 0, queueEnd = 1;
char *codec[128] = {0}, buffer[1024];


node create_Node(int frequency, char c, node x, node y)
{
	node new = mapping + no_of_nodes++;
	if (frequency) new->c = c, new->frequency = frequency;
	else {
		new->l = x, new->r = y;
		new->frequency = x->frequency + y->frequency;
	}
	return new;
}
 

void queueInsert(node new) /* We form a priority queue using Heap Data Structure*/
{
	int j, i = queueEnd++; /*The basic rule is that the higher the frequency, the lower the priority in the Heap */
	while ((j = i / 2)) { 
		if (q[j]->frequency<= new->frequency) break; 		/* We compare the frequency of the new node with the parent frequency */
		q[i] = q[j], i = j;
	}
	q[i] = new;
}


node queueRemove() /*Function to remove the top element and move up other elements...*/
{
	int i, l;
	node n = q[i = 1];
 
	if (queueEnd < 2) return 0;
	queueEnd--;
	while ((l = i * 2) < queueEnd) {
		if (l + 1 < queueEnd && q[l + 1]->frequency < q[l]->frequency) l++;
		q[i] = q[l], i = l;
	}
	q[i] = q[queueEnd];
	return n;
}
 
void build_Huffman_Tree(node n, char *str, int len) /* Traversing tree and putting 0s and 1s ... */
{
	static char *out = buffer;
	if (n->c) {
		str[len] = 0;
		strcpy(out, str);
		codec[n->c] = out;
		out += len + 1;
		return;
	}
 
	str[len] = '0'; build_Huffman_Tree(n->l,  str, len + 1);
	str[len] = '1'; build_Huffman_Tree(n->r, str, len + 1);
}
 
void create(const char *s)
{
	int i, frequency[128] = {0};
	char c[16];
 
	while (*s) frequency[(int)*s++]++; // While Loop to count frequency of each character
 
	for (i = 0; i < 128; i++) { //This is the initial heap we create
		if (frequency[i]) queueInsert(create_Node(frequency[i], i, 0, 0));
	}
	
    //We merge nodes starting from the lowest frequency nodes using the following algorigthm:
    /* 
       (1) We delete 2 top nodes (Highest Priority, i.e., lowest frequency)
	   (2) Form another node using the 2 previous nodes while adding frequencys
	   (3) We keep track of the previous l and r nodes when making this new node
	   (4) Repeat this process until only 1 node remains.
       
    */
	while (queueEnd > 2) {
		queueInsert(create_Node(0, 0, queueRemove(), queueRemove()));
	}
 

	/* Traverse the constructed tree from root to leaves We go through the newly made tree from the root till the leaves while:
	   Labelling and Summing a '0' for l node and a '1' for the r node for each node. 
	   These accumulated 0's and 1's at each leaf are our resultant encoding...
	*/

	build_Huffman_Tree(q[1], c, 0);
}
 
void Compress(const char *string, char *out)
{
	while (*string) {
		strcpy(out, codec[*string]);
		out += strlen(codec[*string++]);
	}
}
 
void Decompress(const char *string, node x)
{
	node n = x;
	while (*string) {
		if (*string++ == '0') n = n->l;
		else n = n->r;
 
		if (n->c) putchar(n->c), n = x;
	}
	if (x != n) puts("Input is Garabge");
}

int main(void)
{
    FILE *fileStream, *updated_FileStream; char string [1024];
	puts("Reading input_Text.txt");
    fileStream = fopen ("input_Text.txt", "r+"); 
    if(fileStream==NULL) puts("FAILED TO READ FILE!");

    fgets (string, 1024, fileStream); 
    
    
    int initialbits = strlen(string)*8;
    puts("HUFFMAN TABLE: ");
	char buffer[1024];
    
	create(string);
    printf("_____________\n");
	for (int i = 0; i < 128; i++) if (codec[i]) printf("|'%c': %s |\n", i, codec[i]);
    printf("_____________\n");
		
    printf("Original String: %s\n",string);
    printf("\nUncompressed Original String in Binary = ");

    for(int i=0;i<8*strlen(string);i++) printf("%d",0 != (string[i/8] & 1 << (~i&7)));  
    printf("\n");

    updated_FileStream = fopen ("input_Text.txt", "w"); 
    for(int i=0;i<8*strlen(string);i++) fprintf(updated_FileStream,"%d",0 != (string[i/8] & 1 << (~i&7)));  

	Compress(string, buffer);

    int encodedbits = strlen(buffer);

	printf("\nEncoded/Compressed String in Binary: %s\n", buffer);
	printf("\nDecoded Binary to String: ");

	Decompress(buffer, q[1]);
    FILE *out=fopen("compressedOutput.txt","w");
    float compression = ((float)encodedbits/(float)initialbits)*100;
    fprintf(out,"%s",buffer);
    printf("\nIntial Bytes Before Compression = %d x 8 = %d bytes\n",strlen(string),initialbits);
    printf("\nAfter Compression = %d bytes\n", encodedbits);
    printf("Compression Percentage = %f%%\n",compression);

    float storage_Saved = ((float)initialbits - (float)encodedbits)/1000;
    printf("Storage Saved = %f KB", storage_Saved);
    fclose(fileStream);
    fclose(out);
	return 0;
}