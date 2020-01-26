#define NUM_LETTERS ((int)26)

typedef enum {FALSE=0, TRUE=1} boolean;

typedef struct node {
    char letter;
    long unsigned int count;
    struct node* children[NUM_LETTERS];
    boolean isEndOfWord; 
} node;

node* getNode(char c);

char lowerCase(char c);

int insert(node* root, char c);

void freeTrie(node** root);

void printUp(node* root, char* str, int level);

void printDown(node* root, char* str, int level);