// hash.h

#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NUM 100 // set the default size of hash table to be 100

typedef struct node{
	char value[100];
	struct node* next;
}node;

node *hashTable[NUM];

int char2int(char);
int hash1(char*);
int hash2(char*);
int hashFunc(char*,int);
int findPos(char*);

void create(char*);
void makeFriend(char*,char*);
void breakup(char*,char*);
void printFriends(char*);
int checkFriend(char*,char*);
void printAll();
void freeAll();


#endif
