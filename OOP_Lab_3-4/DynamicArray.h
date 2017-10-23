#pragma once

#include "Offer.h"
#define CAPACITY 10

typedef Offer* TElement;

typedef struct
{
	TElement* elems;
	int length;			// actual length of the array
	int capacity;		// maximum capacity of the array
} DynamicArray;

DynamicArray* createDynamicArray(int capacity);
void destroy(DynamicArray* a);
void Push(DynamicArray*a, TElement t);
void deleteFromArray(DynamicArray* a, int pos);
int getLength(DynamicArray* a);
void ReplaceInArray(DynamicArray* a, TElement x, int pos);
TElement get(DynamicArray* a, int pos);