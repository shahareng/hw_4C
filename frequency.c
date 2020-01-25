#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NUM_LETTERS ((int)26)

typedef enum {FALSE=0, TRUE=1} boolean;

typedef struct node {
    char letter;
    long unsigned int count;
    long unsigned int countChild;
    struct node* children[NUM_LETTERS];
    boolean isEndOfWord; 
} node;

// Returns new trie node (initialized to NULLs) 
node* getNode(char c) 
{ 
    node* pNode = NULL;
    pNode = (node*)malloc(sizeof(node));
    if (pNode) 
    { 
        int i; 
        pNode->countChild=0;
        pNode->isEndOfWord = FALSE;
        pNode->letter = c;
        // put NULL value in his children
        for (i = 0; i < NUM_LETTERS; i++) 
            pNode->children[i] = NULL; 
    }
    return pNode; 
}

// count how many children the node has
void countChild(node* root)
{
    node *pNode = root;
    int i;
    pNode->countChild = 0;
    for(i =0; i<NUM_LETTERS; i++)
    {
        if(pNode->children[i] != NULL && root->children[i]->countChild != -1)
        {
            pNode->countChild++;
        }
    }
}

// turn all the leeters to lowercase
char lowerCase(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return c + 32;
    }
    return c;
}

// insert nodes to the trie
int insert(node* root, char c) 
{
    int index;
    int t=1;
    node *pNode = root;
    // check if all the sord insert to the trie
    while (c != ' ' && c != '\t' && c != '\n' && t)
    {
        c = lowerCase(c);
        // if it's a letter and not evreything else
        if(isalpha((int) c))
        {
            index = ((int)c - (int)'a');
            if (!pNode->children[index]) 
            {
                // create new node if he isn't exist
                pNode->children[index] = getNode(c);
                pNode->countChild++;
            }
            // pNode->children[index]->countChild++; //
            pNode = pNode->children[index];
        }
        
        if(EOF == scanf("%c", &c))
        {
            t=0;
        }
    }
    pNode->count++;
    pNode->isEndOfWord = TRUE;
    // pNode->countChild++;
    return t;
}

// free all the nodes in the tree
void freeTrie(node** root)
{
   // if the node isn't null
   if(*root!=NULL)
    {
        // free all his children
        for(int i=0 ;i<NUM_LETTERS; i++)
        {
            freeTrie(&((*root)->children[i]));
        }
        free(*root);
        return;
    }
}

// print all the words in a lexicographic order
void printUp(node** root) 
{ 
    // check if the node is the last one in the word
    if ((*root)->countChild == 0 && (*root)->isEndOfWord)
    {
        printf("%c  %ld\n", (*root)->letter, (*root)->count);
        (*root)->countChild = -1;
        return; 
    }

    if((*root)->countChild == 0 && !((*root)->isEndOfWord))
    {
        (*root)->isEndOfWord = TRUE;
        (*root)->countChild = -1;
        return;
    }  

    for(int i=0; i<NUM_LETTERS; i++)
    {
        if((*root)->children[i] != NULL && (*root)->children[i]->countChild != -1)
        {
            printf("%c", (*root)->letter);
            printUp(&((*root)->children[i]));
            if((*root)->children[i]->isEndOfWord)
            {
                (*root)->countChild--;
            }
        }
    }   
}

// print all the words in a reverse lexicographic order
void printDown(node** root) 
{ 
    // check if the node is the last one in the word
    if ((*root)->countChild == 0 && (*root)->isEndOfWord)
    {
        printf("%c  %ld\n", (*root)->letter, (*root)->count);
        (*root)->countChild = -1;
        return; 
    }

    if((*root)->countChild == 0 && !((*root)->isEndOfWord))
    {
        (*root)->isEndOfWord = TRUE;
        (*root)->countChild = -1;
        return;
    }  

    for(int i=NUM_LETTERS; i>=0; i--)
    {
        if((*root)->children[i] != NULL && (*root)->children[i]->countChild != -1)
        {
            if((*root)->children[i]->isEndOfWord)
            {
                (*root)->countChild--;
            }
            printf("%c", (*root)->letter);
            printDown(&((*root)->children[i]));
        }
    }   
}

int main(int argc,char* argv[])
{
    boolean printR;
    // read from the terminal
    if(argc==2 && strcmp(argv[1], "r") == 0)
    {
        printR = TRUE;
    }
    char c;
    int t = 1;
    int i=0;
    node *root = getNode(' ');
    while(scanf("%c", &c) != EOF && t)
    {
        t = insert(root, c);
    }
    if(!root->countChild)
    {
        printf("%s\n", "Trie is empty");
        return 0;
    }
    node *pNode = root;
    if(printR)
    {
        for(i=NUM_LETTERS-1; i>=0; i--)
    
        if(pNode->children[i] != NULL && root->children[i]->countChild != -1)
        {
            pNode = pNode->children[i];
            while(pNode->countChild > 0)
            {
                printDown(&(pNode));
                countChild(pNode);
            }
            pNode->countChild = -1;
        }
        pNode = root;
    
    }
    else
    {
    for(i=0; i<NUM_LETTERS; i++)
    {
        if(pNode->children[i] != NULL && pNode->children[i]->countChild != -1)
        {
            pNode = pNode->children[i];
            while(pNode->countChild > 0)
            {
                printUp(&(pNode));
                countChild(pNode);
            }
            pNode->countChild = -1;
        }
        pNode = root;
    }
    freeTrie(&root);
    return 0;
}
} 
