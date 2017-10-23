*#include "stdafx.h"
#include "DynamicArray.h"
#include <stdlib.h>
#include <assert.h>

//
//	Public
//
//	Creates a new array of the type Offer of a given capacity
//
DynamicArray* createDynamicArray(int capacity){
	DynamicArray* x = (DynamicArray*)malloc(sizeof(DynamicArray));
	
	if (x == NULL)
		return NULL;

	x->capacity = capacity;
	x->length = 0;

	
	x->elems = (TElement*)malloc(capacity * sizeof(TElement));
	if (x->elems == NULL)
		return NULL;

	return x;
}


//
//	Public
//
//	Deletes the array and eliberates the memory
//
void destroy(DynamicArray* a){
	if (a == NULL)
		return;

	free(a->elems);
	a->elems = NULL;

	free(a);
	a = NULL;
}

//
//	Private
//
//	Doubles the current capacity
//
void ResizeArray(DynamicArray* a){
	if (a == NULL)
		return;

	a->capacity *= 2;
	a->elems = (TElement*)realloc(a->elems, a->capacity * sizeof(TElement));
}

// 
//	Public
//
//	Adds t to tha end of the array
//
void Push(DynamicArray*a, TElement t){
	if (a == NULL)
		return;
	if (a->elems == NULL)
		return;

	if (a->length == a->capacity)
		ResizeArray(a);
	a->elems[a->length] = t;
	a->length++;
}

void ReplaceInArray(DynamicArray* a, TElement x, int pos) {
	a->elems[pos] = x;
}

void deleteFromArray(DynamicArray* a, int pos){
	if (a == NULL)
		return;
	if (a->elems == NULL)
		return;

	DeleteOffer(get(a, pos));

	for (int i = pos; i < a->length - 1; i++)
		a->elems[i] = a->elems[i + 1];


	a->length--;
}

int getLength(DynamicArray* a){
	if (a == NULL)
		return -1;

	return a->length;
}

TElement get(DynamicArray* a, int pos){
	return a->elems[pos];
}