#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct BSTnode {
   char* word;
   int count;
   struct BSTnode* leftNode;
   struct BSTnode* rightNode;
};

struct BSTnode* newNode(char word[50]);

/*wordAlignTracker and countAlignTracker - determines if a word's size and count is bigger than the current biggest count and word.
  helps with formating for writeToOutput. Returns the current biggest*/
void wordAlignTracker(int* curWordLengthMax, char* word);
void countAlignTracker(int* curCountDigitMax, struct BSTnode* node);

struct BSTnode* addWord(struct BSTnode* node, char* word, int* curCDM, int* curWLM);
