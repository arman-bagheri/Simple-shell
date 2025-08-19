#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "dynArrayString.h"


void initDynArray(dynArray *array){
	array->address = NULL;
	array->length = 0;
}

int isEmptyArr(dynArray *array){
	return (array->length == 0);
}


void emptyDynArray(dynArray *array){
	int i;
	if(isEmptyArr(array)) return;
	for(i=0; i<array->length; i++){
		free(array->address[i]);
	}
	free(array->address);
	array->length = 0;
	array->address = NULL;
}

void manAppendArray(dynArray *array, char* str){
	char **temp = realloc((void *)array->address, (array->length+1) * sizeof(char*));
	if(temp==NULL){
		perror("realloc failed");
		return;
	}
	array->address = temp;
	array->length++;
	*(array->address + (array->length-1)) = str;
}

void appendDynArray(dynArray *array, char* str){
	char **temp = realloc((void *)array->address, (array->length+1) * sizeof(char*));
	char *sentemp = malloc(strlen(str) + 1);
	if((temp==NULL) || (sentemp==NULL)){
		perror("realloc failed");
		return;
	}
	strcpy(sentemp, str);
	array->address = temp;
	array->length++;
	*(array->address + (array->length-1)) = sentemp;
	
}

void deleteTopDynArray(dynArray *array){
	if(array->length==0) return;
	if(array->length==1){
		emptyDynArray(array);
		return;
	}
	char *lastSen = *(array->address + array->length - 1);
	free(lastSen);
	char **temp = realloc((void *)array->address, (array->length-1) * sizeof(char*));
	if(temp==NULL){
		perror("realloc failed");
		return;
	}	

	array->address = temp; 
	array->length--;
}

int addNullEnd(dynArray *array){
	char **temp = realloc((void*)array->address, (array->length + 1)*(sizeof(char*)));
	if(temp==NULL){
		perror("realloc failed");
		return 1;
	}
	array->address = temp;
    temp = NULL;
	array->address[array->length] = NULL;
	return 0;
}

void printDynArray(dynArray *array){
	printf("[ ");

	int i=0;

	for(i=0; i<array->length; i++){
		if((*(array->address + i))==NULL) continue;

		printf("\"%s\", ",*(array->address + i));
	}

	printf(" ]\n");
}
