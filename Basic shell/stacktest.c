#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "charStack.h"

charStack s1;

char* remove_quotes(char* word){
	char* cleanned = malloc(strlen(word)+1);
	if(cleaned==NULL){
		perror("malloc failure\n");
		exit(1);
	}
	int i=0;
	int j=0;
	int removed = 0;
	while(word[i]!='\0'){
		if(!removed){
			if((word[i]=='\'') || (word[i]=='\"')){
				if(isEmptyCharStack(&s1)){
					pushCharStack(&s1,word[i]);
					i++;
				}
				else{
					if(*s1.top==word[i]){
						if(getDepthStack(&s1)==1){
						i++;
						removed = 1;
						continue;
						}
						popCharStack(&s1);
						cleanned[j] = word[i];
						i++;
						j++;
					}
					else{
						pushCharStack(&s1,word[i]);
						cleanned[j] = word[i];
						i++;
						j++;
					}
				}
			}
			else{
				cleanned[j] = word[i];
				i++;
				j++;
		}
		}
		else{
			cleanned[j] = word[i];
			i++;
			j++;
		}
	}
	cleanned[j] = '\0';
	return cleanned;
}

char* remove_quotes(const char* word) {
    size_t len = strlen(word);
    if (len < 2) {
        return strdup(word);  // Nothing to clean
    }

    char first = word[0];
    char last = word[len - 1];

    if ((first == '\'' && last == '\'') || (first == '"' && last == '"')) {
        char* cleaned = malloc(len - 1); // len - 2 for chars + 1 for \0
        if (cleaned == NULL) {
            perror("malloc failed");
            exit(1);
        }
        strncpy(cleaned, word + 1, len - 2);
        cleaned[len - 2] = '\0';
        return cleaned;
    }

    // No matching outer quotes — just duplicate the original
    return strdup(word);
}

char* tokenize(char buffer[], int* start){
	int finish = 0;
	char* token;
	int beginning = 0;

	while(!beginning){       //remove the leading spaces
		if(buffer[*start] == ' '){
			(*start)++;
		}
		else beginning = 1;
	}

	token = buffer + *start;
	printf("spaces removed");

	while(!finish){
		if(buffer[*start]=='\''){
			printf("saw a \'\n");
			if(isEmptyCharStack(&s1)){
				pushCharStack(&s1,'\'');
			}
			else if((*s1.top)=='\''){
				popCharStack(&s1);
			}
			else {
				pushCharStack(&s1,'\'');
			}
		}
		else if(buffer[*start]=='\"'){
			printf("saw a \"\n");
			if(isEmptyCharStack(&s1)){
				pushCharStack(&s1,'\"');
			}
			else if((*(s1.top))=='\"'){
				popCharStack(&s1);
			}
			else {
				pushCharStack(&s1,'\"');
			}
		}
		else if(buffer[*start]==' '){
			printf("saw a space\n");
			if(isEmptyCharStack(&s1)){
				buffer[*start] = '\0';
				finish = 1;
			}
		}
		else if(buffer[*start]=='\0'){
			printf("finished the string, let's restart!\n");
			*start = -1;
			finish = 1;
		}
		*start += 1;
	}
	printf("%d  the next word starts at\n", *start);
	return token;
}

int main(){

	initCharStack(&s1);
	char buff[] = "hello my 'dear lover' re, i love taylor swift";
	char* token;
	int start = 0;
	int i;
	token = tokenize(buff, &start);
	printf("%s\n", token);
	printf("%s\n", remove_quotes(token));
	printf("\n");
	token = tokenize(buff, &start);
	printf("%s\n", token);
	printf("%s\n", remove_quotes(token));
	printf("\n");
	token = tokenize(buff, &start);
	printf("%s\n", token);
	printf("%s\n", remove_quotes(token));
	printf("\n");
	token = tokenize(buff, &start);
	printf("%s\n", token);
	printf("%s\n", remove_quotes(token));
	printf("\n");
	token = tokenize(buff, &start);
	printf("%s\n", token);
	printf("%s\n", remove_quotes(token));
	printf("\n");
	token = tokenize(buff, &start);
	printf("%s\n", token);
	printf("%s\n", remove_quotes(token));
	printf("\n");
	token = tokenize(buff, &start);
	printf("%s\n", token);
	printf("%s\n", remove_quotes(token));
	printf("\n");
	token = tokenize(buff, &start);
	printf("%s\n", token);
	printf("%s\n", remove_quotes(token));
	printf("\n");
	return 0;
}
