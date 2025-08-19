#ifndef DYNARRAY_H
#define DYNARRAY_H

typedef struct {
    int length;
    char **address;
} dynArray;

void initDynArray(dynArray *array);
int isEmptyArr(dynArray *array);
void emptyDynArray(dynArray *array);
void appendDynArray(dynArray *array, char* str);
void deleteTopDynArray(dynArray *array);
void printDynArray(dynArray *array);
int addNullEnd(dynArray *array);
void manAppendArray(dynArray *array, char* str);

#endif // DYNARRAY_H
