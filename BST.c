#include "BST.h"

struct BSTnode* newNode(char word[50]) {
   struct BSTnode* newNode = NULL;
   newNode = (struct BSTnode*) malloc(sizeof(struct BSTnode));
   if (newNode == NULL) {
      printf("malloc has failed and returned NULL\n");
      return NULL;
   }

   char* wordTemp = (char*) malloc(50 * sizeof(char));
   strcpy(wordTemp, word);
   newNode->word = wordTemp;
   wordTemp=NULL;
   free(wordTemp);

   newNode->count = 0;
   newNode->leftNode = NULL;
   newNode->rightNode = NULL;

   return newNode;
}



/*wordAlignTracker and countAlignTracker - determines if a word's size and count is bigger than the current biggest count and word.
  helps with formating for writeToOutput. Returns the current biggest*/
void wordAlignTracker(int* curWordLengthMax, char* word) {
   if (strlen(word) > *curWordLengthMax) {
      *curWordLengthMax = strlen(word);
   }
}

void countAlignTracker(int* curCountDigitMax, struct BSTnode* node) {
   int numDigits = 0;
   int temp = node->count;
   while (temp > 0) {
      temp = temp /10;
      numDigits++;
   }

   if (numDigits > *curCountDigitMax) {
      *curCountDigitMax = numDigits;
   }
}

struct BSTnode* addWord(struct BSTnode* node, char* word, int* curCDM, int* curWLM) {
   int result;

   //If the next node is null
   if (node == NULL) {
      //checks if the new node has a large string length than the current largest string
      struct BSTnode* wordNode = newNode(word);
      wordAlignTracker(curWLM, word);
      wordNode->count = 1;
      return wordNode;
   }

   result = strcmp(node->word, word);

   //if the given word is the same as the current node, increment word count by 1
   if (result == 0) {
      // checks if the duplicate node has more count digits than the current biggest amount of digits
      countAlignTracker(curCDM, node);
      node->count = (node->count) + 1;
   } //If root is bigger than the new node. new node goes left
   else if (result > 0) {
      node->leftNode = addWord(node->leftNode, word, curCDM, curWLM);
   } //If root is smaller than the new node. new node goes right
   else if (result < 0) {
      node->rightNode = addWord(node->rightNode, word, curCDM, curWLM);
   }

   return node;
}

