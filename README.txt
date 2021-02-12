Alan Castillo
Video: https://youtu.be/mFzuIeU0vas

---CODE OVERVIEW
I created a BST.h and BST.c for the binary search tree. My main program, wordfreak.c,
contained the majority of the functions and was split up by getting Standard input, 
working with the environmental variable, and working with argv. All of the three input
 types followed the same method for parsing.

---BSTs
The structure of a BST node consisted only of the required fields, word name, count of
the word, left node pointer, and right node pointer. BST had a constructor with dynamic
allocation through malloc and also had two helper functions that kept track of the largest 
word and digits of all the counts so that output could be properly formatted later on. 
The two tracker functions made use of an int pointer that was passed by reference and was
updated whenever a new word was added. Finally, the last function in BST was the addWord 
function which string compared the current node word name to the given word and traversed 
according to whether the word was the same, bigger, or smaller. Eventually the word would 
reach a duplicate and increment count or it would hit a NULL node and take that position in the BST.

---WORDFREAK.c (MAIN)
In wordfreak.c I had several functions and algorithms. First of all though 
I created a hashtable with size of 26 of type struct BST pointer and dynamically allocated 
each one and declared it the proper letter. "a" being at index 0 and "z" being at index 25.

---PARSING
Then for each of the three methods of input, argv, standard input, and the environmental 
variable I created a temporary empty string to store the words as I parsed through each file. 
To parse through each file I did a while loop and would read into a moderately sized buffer 
until there was nothing left to read. However while reading each block of text, I would parse 
through the buffer, first checking if each character was either a character or a symbol. 
if it was a character I would concatenate it to an empty string outside the loop, and when 
the character was a symbol I would pass the word to a hash function and then reset the outside 
string to empty and continue the process until the end of the file was reach, ie. the last block of text was read. 

---HASH FUNCTION
The hash function would store take the first letter of the word which is a char, 
and would subtract it by 97 to get the index for which root BST the word belonged too. 
And then it would add then it would add that word to the BST.

---FREEING
Finally at the end of the file I would free each BSTnode using post traversal and free its corresponding word field.

---ERRORS
My program recieves a malloc() corrupt top size error when working with the newton.txt, 
holmer.txt, or shakespeare.txt files. regardless of whether it is piped in, 
uses the environment variable, or is passed through argv. Valgrind suggest that there is a 
memory leakage in my addword function in BST.c and/or in my main function when I use strcat and strcpy, 
however I am not sure what it is. The other files work perfectly.
