
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "dynArrayString.h"
#include <dirent.h>
#include <limits.h>
#include <sys/wait.h>
#include "charStack.h"


dynArray parsed;
char current_directory_path[PATH_MAX];
char line[100]={'\0'};
DIR *current_directory;
struct dirent *entry;
charStack s1;

char* remove_quotes(char* word){
	char* cleanned = malloc(strlen(word)+1);
	if(cleanned==NULL){
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

char* tokenize(char buffer[], int* start){
	int finish = 0;
	char* token;
	int beginning = 0;
	if(*start==-1){
		return NULL;
	}

	while(!beginning){       //remove the leading spaces
		if(buffer[*start] == ' '){
			(*start)++;
		}
		else beginning = 1;
	}

	token = buffer + *start;

	while(!finish){
		if(buffer[*start]=='\''){
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
			if(isEmptyCharStack(&s1)){
				buffer[*start] = '\0';
				finish = 1;
			}
		}
		else if(buffer[*start]=='\0'){
			*start = -2;
			finish = 1;
		}
		*start += 1;
	}
	return token;
}


void parse(char* buffer){
	emptyCharStack(&s1);
	char *token;
	int start = 0;

	token = tokenize(buffer,&start);
	if (token == NULL || *token == '\0') return;
	while (token != NULL){
		manAppendArray(&parsed,remove_quotes(token));
		token = tokenize(buffer, &start);
	}
}



void execute(dynArray* array){
	if(isEmptyArr(&parsed)) return;
	else if((strcmp(*(array->address),"pwd")) == 0){           //pwd
		printf("%s\n", current_directory_path);
	}
	else if((strcmp(*(array->address),"ls")) == 0){      //ls
		while((entry = readdir(current_directory)) != NULL){
			printf("%s\n",entry->d_name);
		}
		rewinddir(current_directory);
	}
	else if((strcmp(*(array->address),"cd")) == 0){  //cd
		DIR *newdir;
		if(array->length==1){
			newdir = opendir("/");
			if(newdir==NULL){
				printf("Sorry, couldn't open the specified directory.\n");
				return;
			}
			closedir(current_directory);
			current_directory = newdir;
			chdir("/");
			newdir = NULL;
			if (getcwd(current_directory_path, PATH_MAX) == NULL) {
    		perror("getcwd");
   			exit(1);
}
			return;
		}
		else if(array->length>2){
			printf("Too many arguments for the command cd.\n");
			return;
		}
		else{
			newdir = opendir(array->address[1]);
			if(newdir!=NULL){
				closedir(current_directory);
				current_directory = newdir;
				newdir = NULL;
				chdir(array->address[1]);
				if (getcwd(current_directory_path, PATH_MAX) == NULL) {
    			perror("getcwd");
    			exit(1);
}

			}
			else {
				printf("Sorry, couldn't open the specified directory.\n");
			}
		}

	}
	else if((strcmp(*(array->address),"exit")) == 0){	 //exit
		exit(0);
	}

	else {
		pid_t pid = fork();
		if(pid==0){ //child
			if(addNullEnd(array) != 0){
				perror("realloc failure");
				exit(1);
			}
			int stat = execvp(array->address[0], array->address);

			perror("execvp failed! ");
			exit(1);
		}
		else if(pid>0){//parent
			int status;
			waitpid(pid,&status,0);
			return;
		}
		else{
			perror("sorry, couldn't start the process\n");
			return;
		}
	}
}

int main(){
	//initializing
	initDynArray(&parsed);
	initCharStack(&s1);
	getcwd(current_directory_path, PATH_MAX);
	current_directory = opendir(current_directory_path);
	if(current_directory==NULL){
		perror("couldn't open directory!");
		exit(1);
	}

	while(1){
		printf("ArmanShell at %s prompt>",current_directory_path);
		fgets(line, 100, stdin);
		line[strcspn(line, "\n")] = '\0';
		parse(line);
		execute(&parsed);
		emptyDynArray(&parsed);
	}
	return 0;
}