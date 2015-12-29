#include "minic.h"
#include <math.h>

#define MAX_NODE_LEN_TEXT 64
#define MAX_NODE_CHILD 10
#define MAX_NODE_NUM 10000
#define MAX_NODE_WIDTH 5

typedef struct Node
{
    int x;
    int id;
    int pid;
    int width;
    struct Node *child;
    struct Node *sibling;
    int cindex;//index of child
    char name[MAX_NODE_LEN_TEXT];
} TreeNode;

TreeNode *tree;
TreeNode *nodes[MAX_NODE_NUM];
