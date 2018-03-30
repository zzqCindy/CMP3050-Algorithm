// main.c

#include <stdio.h>
#include <string.h>
#include "hash.h"

char* trimInput(char *input){

	if(input == NULL) return NULL;

	while(*input == ' ') input++;

	int length = strlen(input);
	char *ptr = input + length - 1;
	while(ptr >= input){
		if(*ptr != ' ') break;
		*ptr = '\0';
		ptr--;
	}

	return input;
}

char* getName(char* input){

    if(input == NULL) return NULL;

    int length = strlen(input), count = 0;
	while(*input != ' ' && count++ < length)
		input++;
	while(*input == ' ' && count++ < length)
        input++;
    if(count > length) return NULL;
    return input;
}

char* getFirstName(char* input){
    int length = strlen(input);
	char *ptr = input + length - 1;
	while(*ptr != ' ' && ptr >= input){
		*ptr = '\0';
		ptr--;
	}
	while(*ptr == ' ' && ptr >= input){
        *ptr = '\0';
        ptr--;
	}
	return input;
}

int main(){

	while(1){

		printf("please input command: ");
        char input[100];
		gets(input);

		char* str = trimInput(input);
		char ch = *str;
		char *name1 = NULL, *tmp = NULL;
		char name2[100];

		switch(ch){
			case 'P':
				name1 = getName(str);
				create(name1);
				break;
			case 'F':
                name1 = getName(str);
                tmp = getName(name1);
                strcpy(name2,tmp);
                name1 = getFirstName(name1);
                makeFriend(name1,name2);
				break;
			case 'U':
                name1 = getName(str);
                tmp = getName(name1);
                strcpy(name2,tmp);
                name1 = getFirstName(name1);
                breakup(name1,name2);
				break;
			case 'L':
                name1 = getName(str);
                printFriends(name1);
				break;
			case 'Q':
                name1 = getName(str);
                tmp = getName(name1);
                strcpy(name2,tmp);
                name1 = getFirstName(name1);
                int flag = checkFriend(name1,name2);
                if(flag) printf("Yes\n");
                else printf("No\n");
				break;
			case 'X':
				return 0;
				break;
			default:
				break;
		}

	}

    freeAll();
	return 0;
}

