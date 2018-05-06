#ifndef RBTREE_H
#define RBTREE_H
#define MAXSIZE 20

enum Color{
    RED, BLACK
};

typedef struct _RBTree{
    int val;
    enum Color color;
    struct _RBTree *left, *right, *p;

}RBTree;

typedef struct {  
    RBTree* data[MAXSIZE];  
    int front;
    int rear;  
    int size; 
}Queue;

void lRotate(RBTree*);
void rRotate(RBTree*);
void insertFixup(RBTree*);
void insertRBTree(int);
void printTree(RBTree*);

Queue* createQueue();
int queueEmpty(Queue*);
void queuePush(Queue*,RBTree*);
RBTree* queuePop(Queue*);

#endif
