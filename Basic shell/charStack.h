#ifndef CHARSTACK_H
#define CHARSTACK_H

typedef struct {    //growing direction, upwards
	char* top;
	char* bottom;
} charStack;

void initCharStack(charStack*);
int isEmptyCharStack(charStack*);
void pushCharStack(charStack*,char);
char popCharStack(charStack*);
int getDepthStack(charStack*);
void printCharStack(charStack*);
void emptyCharStack(charStack*);

#endif