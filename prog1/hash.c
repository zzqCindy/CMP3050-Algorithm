// hash.c

#include "hash.h"

int char2int(char value){
	if(value > 96)
		return value - 96;
	else return value - 64;
}

int hash1(char* key){
	int length = strlen(key);
	int sum = 0, i;
	for(i = 0; i < length; i++)
		sum = (sum + char2int(key[i])) % NUM;
	return sum;
}

int hash2(char* key){
	int length = strlen(key);
	int sum = 0, i;
	for(i = 0; i < length; i++)
		sum = (sum + char2int(key[i])) % 11;
	return sum;
}

int hashFunc(char* key, int count){
	int h1 = hash1(key), h2 = hash2(key);
	return h1 + count * h2;
}

int findPos(char* key){
	int count = 0, index = hashFunc(key,count);
	while(strcmp(hashTable[index]->value,key))
		index = hashFunc(key,++count);
	return index;
}

void create(char* key){
	int count = 0, index = hashFunc(key,count);
	while(hashTable[index] != NULL)
		index = hashFunc(key,++count);
	hashTable[index] = (node*)malloc(sizeof(node));
	strcpy(hashTable[index]->value,key);
	hashTable[index]->next = NULL;
}

void makeFriend(char* s1, char* s2){
	int index1 = findPos(s1), index2 = findPos(s2);
	node *head1 = hashTable[index1], *head2 = hashTable[index2];
	node *ptr1 = head1, *ptr2 = head2;

	while(ptr1->next != NULL) ptr1 = ptr1->next;
	while(ptr2->next != NULL) ptr2 = ptr2->next;

	ptr1->next = (node*)malloc(sizeof(node));
	ptr2->next = (node*)malloc(sizeof(node));

	strcpy(ptr1->next->value,s2);
	strcpy(ptr2->next->value,s1);
	ptr1->next->next = NULL;
	ptr2->next->next = NULL;
}

void breakup(char* s1,char* s2){
	int index1 = findPos(s1), index2 = findPos(s2);
	node *head1 = hashTable[index1], *head2 = hashTable[index2];
	node *ptr1 = head1, *ptr2 = head2;

	while(strcmp(ptr1->next->value,s2)) ptr1 = ptr1->next;
	while(strcmp(ptr2->next->value,s1)) ptr2 = ptr2->next;

	node *tmp = ptr1->next;
	ptr1->next = tmp->next;
	free(tmp);
	tmp = ptr2->next;
	ptr2->next = tmp->next;
	free(tmp);
}

void printFriends(char* s){
	int index = findPos(s);
	node *ptr = hashTable[index]->next;
	if(ptr == NULL){
		printf("%s\n",hashTable[index]->value);
		printf(" doesn't have friend.");
	}
	while(ptr != NULL){
		printf(ptr->value);
		printf(" ");
		ptr = ptr->next;
	}
	printf("\n");
}

int checkFriend(char* s1,char* s2){
	int index = findPos(s1);
	node *head = hashTable[index]->next;
	while(head != NULL && strcmp(head->value,s2)) head = head->next;
	if(head == NULL) return 0;
	return 1;
}

void printAll(){
	int i;
	for(i = 0; i < NUM; i++){
		if(hashTable[i] != NULL)
			printf("%s ",hashTable[i]->value);
	}
	printf("\n");
}

void freeAll(){
    int i;
	for(i = 0; i < NUM; i++)
		if(hashTable[i] != NULL)
			free(hashTable[i]);
}
