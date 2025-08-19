#include <stdio.h>
#include <stdlib.h>
#include "charStack.h"


void initCharStack(charStack* stack){
	stack->bottom = NULL;
	stack->top = NULL;
}

int isEmptyCharStack(charStack* stack){
	return (stack->bottom == NULL);
}

int getDepthStack(charStack* stack){
	if(isEmptyCharStack(stack)){
		return 0;
	}
	else{
		return (stack->top - stack->bottom + 1);
	}
}

void pushCharStack(charStack* stack, char index){
	char* temp;
	int depth = getDepthStack(stack);
	temp = realloc(stack->bottom,depth+1);
	if (temp==NULL){
		perror("alloc failed");
		exit(1);
	}
	stack->bottom = temp;
	temp = NULL;
	stack->top = stack->bottom + depth;
	*(stack->top) = index;
}

char popCharStack(charStack* stack){
	if(isEmptyCharStack(stack)){
		printf("empty stack! you cannot pop!\n");
		return '\0';
	}
	char* temp;
	char last;
	int depth = getDepthStack(stack);
	if(depth==1){
		last = *stack->bottom;
		emptyCharStack(stack);
		return last;
	}
	last = *(stack->top);
	temp = realloc(stack->bottom,depth - 1);
	if (temp==NULL){
		perror("alloc failed");
		exit(1);
	}
	stack->bottom = temp;
	temp = NULL;
	stack->top = stack->bottom + depth - 2;
	return last;
}

void printCharStack(charStack* stack){
	char* i;
	if(!isEmptyCharStack(stack)){
		for(i=stack->top;i>=stack->bottom;i--){
			printf("%c > ", *i);
		}
		printf("\n");
		return;
	}
	printf("empty!\n");
}

void emptyCharStack(charStack* stack){
	free(stack->bottom);
	stack->bottom = NULL;
	stack->top = NULL;
}

