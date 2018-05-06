#include <stdio.h>
#include <stdlib.h>
#include "RBTree.h"

// global
RBTree* root = NULL;

Queue* CreateQueue() {  
    Queue* q = (Queue*)malloc(sizeof(Queue));  
    if (!q) {  
        printf("space allocation failed");  
        return NULL;  
    }  
    q->front = -1;  
    q->rear = -1;  
    q->size = 0;  
    return q;
}

int queueEmpty(Queue* q){
	return (q->size == 0);
}

void queuePush(Queue* q,RBTree* item){
	if (q->size == 20) {  
        printf("queue is full\n");  
        return;  
    }
    q->rear++;  
    q->rear %= MAXSIZE;  
    q->size++;
    q->data[q->rear] = item;
    if(q->front == -1)
    	q->front = q->rear;
}

RBTree* queuePop(Queue* q){
	if (queueEmpty(q)) {  
        printf("queue is empty\n");  
        return NULL;  
    }
    int index = q->front;
    q->front++;
    q->front %= MAXSIZE; //0 1 2 3 4 5  
    q->size--;  
    return q->data[index]; 
}

void lRotate(RBTree* x){
    RBTree* y = x->right;
	x->right = y->left;
	if(y->left != NULL) y->left->p = x;
	y->p = x->p;
	if(x->p == NULL) root = y;
	else{
		if(x == x->p->left) x->p->left = y;
		else x->p->right = y;
	}
	y->left = x;
	x->p = y;
}

void rRotate(RBTree* y){
    RBTree* x = y->left;
	y->left = x->right;
	if(x->right != NULL) x->right->p = y;
	x->p = y->p;
	if(y->p == NULL) root = x;
	else{
		if(y->p->left == y) y->p->left = x;
		else y->p->right = x;
	}
	x->right = y;
	y->p = x;
}

void insertFixup(RBTree* ptr){
	
	RBTree *parent = ptr->p, *grandparent;
	
	while(parent != NULL && parent->color == RED){
		
		grandparent = parent->p;
		
		if(parent == grandparent->left){
			RBTree* uncle = grandparent->right;
			
			if(uncle != NULL && uncle->color == RED){
				parent->color = BLACK;
				grandparent->color = RED;
				uncle->color = BLACK;
				ptr = grandparent;
				continue;
			}
			
			if(parent->right == ptr){
				lRotate(parent);
				RBTree* tmp = parent;
				parent = ptr;
				ptr = tmp;
			}
			parent->color = BLACK;
			grandparent->color = RED;
			rRotate(grandparent);
		}
		else{
			RBTree* uncle = grandparent->left;
			
			if(uncle != NULL && uncle->color == RED){
				parent->color = BLACK;
				grandparent->color = RED;
				uncle->color = BLACK;
				ptr = grandparent;
				continue;
			}
			
			if(parent->left == ptr){
				rRotate(parent);
				RBTree* tmp = parent;
				parent = ptr;
				ptr = tmp;
				
			}
			parent->color = BLACK;
			grandparent->color = RED;
			lRotate(grandparent);
		}
		
	}
	
	root->color = BLACK;
}

void insertRBTree(int val){
	
	RBTree *z;
	z = (RBTree*)malloc(sizeof(RBTree));
	z->val = val;
	z->left = NULL;
	z->right = NULL;
	
	if(root == NULL){
		z->color = BLACK;
		z->p = NULL;
		root = z;
		return ;
	}
	
	RBTree *x = root, *y;
	
	while(x != NULL){
		y = x;
		if(x->val < val) x = x->right;
		else x = x->left;
	}
	
	z->color = RED;
	if(y->val < val) y->right = z;
	else y->left = z;
	z->p = y;
	insertFixup(z);
	
	
}

void printTree(RBTree* root){
    if(root == NULL) return;
    Queue *q = CreateQueue();
    queuePush(q,root);
    while(!queueEmpty(q)){
    	RBTree* ptr = queuePop(q);
    	printf("%d-",ptr->val);
    	if(ptr->color == RED)
    		printf("R");
    	else
    		printf("B");
    	printf("; ");
    	if(ptr->left != NULL)
    		queuePush(q,ptr->left);
    	if(ptr->right != NULL)
    		queuePush(q,ptr->right);
	}
}

int main(){
	
	printf("please enter the number you want to insert into the Red Black Tree.\n");
	printf("enter \'X\' to exit.\n");
	char ch[10];
	while(1){
		printf("please enter the number: ");
		gets(ch);
		char input = ch[0];
		if(input == 'X' || input == 'x')
			break;
		else{
			int index = 0;
			int num = 0;
			while(ch[index] != '\0'){
				num = num*10 + ch[index] - 48;
				index++;
			}
			insertRBTree(num);
		}
	}
	
	printTree(root);
    return 0;
}
