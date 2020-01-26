#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "frequency.h"

// Returns new trie node (initialized to NULLs) 
node* getNode(char c) 
{ 
    node* pNode = NULL;
    pNode = (node*)malloc(sizeof(node));
    if (pNode) 
    { 
        int i;
        pNode->isEndOfWord = FALSE;
        pNode->letter = c;
        // put NULL value in his children
        for (i = 0; i < NUM_LETTERS; i++) 
            pNode->children[i] = NULL; 
    }
    return pNode; 
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
            }
            pNode = pNode->children[index];
        }
        
        if(EOF == scanf("%c", &c))
        {
            t=0;
        }
    }
    pNode->count++;
    pNode->isEndOfWord = TRUE;
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
void printUp(node* root, char* str, int level) 
{ 
    if(root == NULL)
	{
		return;
	}
    // Stopping conditions. check if this is the end of the word
    if (root->isEndOfWord)  
    { 
        str[level] = '\0'; 
		printf("%s  %ld \n", str, root->count);
    } 
    for (int i = 0; i < NUM_LETTERS; i++)
	{ 
		if (root->children[i])  
		{ 
			str[level] = i + 'a'; 
			printUp(root->children[i], str, level + 1); 
		} 
	}  
}

// print all the words in a reverse lexicographic order
void printDown(node* root, char* str, int level) 
{ 
    if(root == NULL)
	{
		return;
	}
    // Stopping conditions. check if this is the end of the word
    if (root->isEndOfWord)  
    { 
        str[level] = '\0'; 
		printf("%s  %ld \n", str, root->count);
    }
	for (int i = NUM_LETTERS - 1; i >= 0; i--)
	{ 
		if (root->children[i])  
		{ 
			str[level] = i + 'a'; 
			printDown(root->children[i], str, level + 1); 
		} 
	}   
}

int main(int argc,char* argV[])
{
    char c;
    char* str = (char *)malloc(sizeof(char) * 2);
    int t = 1;
    node *root = getNode(' ');
    while(scanf("%c", &c) != EOF && t)
    {
        t = insert(root, c);
    }
    // read from the terminal in which order to print the trie
    if(argc == 2 && *argV[1] == 'r')
    {
        printDown(root, str, 0);
    }
    else
    {
        printUp(root, str, 0);
    }
    freeTrie(&root);
    return 0;
}

