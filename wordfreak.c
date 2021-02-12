#include "BST.h"
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

/*hashWord - (helper function) takes a given word and puts it into a hash function 
  to get the index of the proper BST in an array, then adds that word to the BST*/
void hashWord(char* word, struct BSTnode* hashtable[26], int* curCDM, int* curWLM) {
   int index;
   index = word[0] - 97;
   hashtable[index] = addWord(hashtable[index], word, curCDM, curWLM);   
}

//writeToOutput - Traverses the BSTs recursively and alphabetically and writes words and counts to output.txt
void writeToOutput(int fdOut, struct BSTnode* node, int* curCDM, int* curWLM) {
   int size = (*curCDM + *curWLM + 4);
   char buf[size];

   if (node == NULL) {
      return;
   }
   //Traverses all the way left until null
   writeToOutput(fdOut, node->leftNode, curCDM, curWLM);
  
   //prints fomratted node info to a buffer, and then writes that buffer into output.txt
   if (node->count != 0) {
      sprintf(buf, "%-*s : %*d\n", *curWLM, node->word, *curCDM, node->count);
      write(fdOut, buf, size);
   }
   //printf("word: %*s\n", *curWLM, node->word);
   //printf("count: %*i\n", *curCDM, node->count);

   writeToOutput(fdOut, node->rightNode, curCDM, curWLM);
} 

void freeTree(struct BSTnode* node) {
   if(node == NULL) {
     return;
   }

   freeTree(node->leftNode);
   freeTree(node->rightNode);
   free(node->word);
   free(node);
}

int main(int argc, char* argv[]) {
//Hash table a-z
   struct BSTnode* hashtable[26];
   
   struct BSTnode* aBST = newNode("a");
   hashtable[0] = aBST;
   struct BSTnode* bBST = newNode("b");
   hashtable[1] = bBST;
   struct BSTnode* cBST = newNode("c");
   hashtable[2] = cBST;
   struct BSTnode* dBST = newNode("d");
   hashtable[3] = dBST;
   struct BSTnode* eBST = newNode("e");
   hashtable[4] = eBST;
   struct BSTnode* fBST = newNode("f");
   hashtable[5] = fBST;
   struct BSTnode* gBST = newNode("g");
   hashtable[6] = gBST;
   struct BSTnode* hBST = newNode("h");
   hashtable[7] = hBST;
   struct BSTnode* iBST = newNode("i");
   hashtable[8] = iBST;
   struct BSTnode* jBST = newNode("j");
   hashtable[9] = jBST;
   struct BSTnode* kBST = newNode("k");
   hashtable[10] = kBST;
   struct BSTnode* lBST = newNode("l");
   hashtable[11] = lBST;
   struct BSTnode* mBST = newNode("m");
   hashtable[12] = mBST;
   struct BSTnode* nBST = newNode("n");
   hashtable[13] = nBST;
   struct BSTnode* oBST = newNode("o");
   hashtable[14] = oBST;
   struct BSTnode* pBST = newNode("p");
   hashtable[15] = pBST;
   struct BSTnode* qBST = newNode("q");
   hashtable[16] = qBST;
   struct BSTnode* rBST = newNode("r");
   hashtable[17] = rBST;
   struct BSTnode* sBST = newNode("s");
   hashtable[18] = sBST;
   struct BSTnode* tBST = newNode("t");
   hashtable[19] = tBST;
   struct BSTnode* uBST = newNode("u");
   hashtable[20] = uBST;
   struct BSTnode* vBST = newNode("v");
   hashtable[21] = vBST;
   struct BSTnode* wBST = newNode("w");
   hashtable[22] = wBST;
   struct BSTnode* xBST = newNode("x");
   hashtable[23] = xBST;
   struct BSTnode* yBST = newNode("y");
   hashtable[24] = yBST;
   struct BSTnode* zBST = newNode("z");
   hashtable[25] = zBST;

//tracker variables to help with formatting in writeToOutput 
   int wordAlign = 0;
   int countAlign = 0;

//Standard Input
  char buf[512];
  int size;
  char temp[15] = "";
  while ((size = read(0, buf, 512)) > 0) {
     for (int i = 0; i < 512; i++) {
        if (isalpha(buf[i]) == 0) {
           if (strcmp(temp, "") == 0) {
               continue;
            } else {
               hashWord(temp, hashtable, &wordAlign, &countAlign);
               strcpy(temp, "");
            }
         } else {
            char letter = tolower(buf[i]);
            char str[2] = {letter,'\0'};
            strcat(temp,str);
         }
     }
  } 

//Work_Freak environmental variable
  int fdEV;
  char* EVfile = getenv("WORD_FREAK");
  if (EVfile != NULL) {
     fdEV = open(EVfile, O_RDONLY);
     while ((size = read(fdEV, buf, 512)) > 0) {
        for (int i = 0; i < 512; i++) {
           if (isalpha(buf[i]) == 0) {
              if (strcmp(temp, "") == 0) {
                  continue;
               } else {
                  hashWord(temp, hashtable, &wordAlign, &countAlign);
                  strcpy(temp, "");
               }
            } else {
               char letter = tolower(buf[i]);
               char str[2] = {letter,'\0'};
               strcat(temp,str);
            }
        }
     }
  }

//Argv   
   for (int i = 1; i < argc; i++) {
      int fd = open(argv[i], O_RDONLY);
      if (fd < 0) {
         printf("there was an error opening the input file\n");
         exit(1);
       }

       while ((size = read(fd, buf, 512)) > 0) {
          for (int i = 0; i < 512; i++) {
             if (isalpha(buf[i]) == 0) {
                if (strcmp(temp, "") == 0) {
                   continue;
                } else {
                   hashWord(temp, hashtable, &wordAlign, &countAlign);
                   strcpy(temp, "");
                }
              } else {
                 char letter = tolower(buf[i]);
                 char str[2] = {letter,'\0'};
                 strcat(temp,str);
              }
           }
       }
   }

//Writing to output.txt
   int fdOut = open("output.txt", O_CREAT|O_RDWR|O_TRUNC, 0644);

   if (fdOut < 0) {
      printf("there was error opening the output file\n");
      exit(1);
   }

   for (int i=0; i < 26; i++) {
      writeToOutput(fdOut, hashtable[i], &wordAlign, &countAlign);
   }

   //IMPORTANT: FREE  PROPERLY
   for (int i=0; i <26; i++) {
     freeTree(hashtable[i]);
   }

   return 0;
}
