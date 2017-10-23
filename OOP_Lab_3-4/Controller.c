#include "stdafx.h"
#include "Controller.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

cont* CreateController(repo* r) {
	
	cont* c = (cont*)malloc(sizeof(cont));
	c->rep = r;

	return c;
}

void DeleteController(cont* c) {
	DestroyRepo(c->rep);
	free(c);
}

int ControllerVerifyType(char* x) {
	if (strcmp(x, "house") == 0 || strcmp(x, "House") == 0) {
		return 1;
	}
	if (strcmp(x, "apartament") == 0 || strcmp(x, "Apartament") == 0) {
		return 1;
	}
	if (strcmp(x, "penthouse") == 0 || strcmp(x, "Penthouse") == 0) {
		return 1;
	}

	return 0;
}

Offer* ReturnOfferController(cont* c, char* address) {
	int i;
	for (i = 0; i < GetRepoLenght(c->rep); i++) {
		if (strcmp(address, getAddress(get(c->rep->offers, i))) == 0) {
			return get(c->rep->offers, i);
		}
	}
	return NULL;
}

void AddOfferControler(cont* c, char* type, char* address, double surface, double price) {
	Offer* new_offer = CreateNewOffer(type, address, surface, price);
	int r=AddOfferRepo(new_offer, c->rep);
	DeleteOffer(new_offer);
}

int DeleteOfferCont(cont* c, char* address) {
	int i;
	for (i = 0; i < GetRepoLenght(c->rep); i++) {
		if (strcmp(address, getAddress(get(c->rep->offers,i)))==0){
			deleteFromArray(c->rep->offers, i);
			return 1;
		}
	}
	return 0;
}

void sortDynamiArrayByPrice(DynamicArray* a) {
	Offer* aux;
	int i, j;
	for (i = 1; i < a->length; i++) {
		for (j = 0; j < i; j++) {
			if (get(a, i)->price < get(a, j)->price) {
				aux = get(a, i);
				ReplaceInArray(a, get(a, j), i);
				ReplaceInArray(a, aux, j);
			}
		}
	}
}

void sortDynamiArrayByAdress(DynamicArray* a) {
	Offer* aux;
	int i, j;
	for (i = 1; i < a->length; i++) {
		for (j = 0; j < i; j++) {
			if (strcmp(get(a, i)->address, get(a, j)->address) < 0) {
				aux = get(a, i);
				ReplaceInArray(a, get(a, j), i);
				ReplaceInArray(a, aux, j);
			}
		}
	}
}

void getFilterByLowerPrice(DynamicArray* new_array, DynamicArray* a, double price) {
	int i;
	for (i = 0; i < a->length; i++) {
		if (get(a, i)->price <= price) {
			Push(new_array, get(a, i));
		}
	}
}

void getFilterBySurface(DynamicArray* new_array, DynamicArray* a, double surface) {
	int i;
	for (i = 0; i < a->length; i++) {
		if (get(a, i)->surface == surface) {
			Push(new_array, get(a, i));
		}
	}
}

void getFilterByGreaterSurface(DynamicArray* new_array, DynamicArray* a, double surface){
	int i;
	for (i = 0; i < a->length; i++) {
		if (get(a, i)->surface >= surface) {
			Push(new_array, get(a, i));
		}
	}
}

void getFilterByType(cont* c, DynamicArray* new_array, char* type) {
	int i;
	for (i = 0; i < GetRepoLenght(c->rep); i++) {
		if (strcmp(get(c->rep->offers, i)->type, type) == 0) {
			Push(new_array, get(c->rep->offers, i));
		}
	}
}

void getFilterByAddress(cont* c,DynamicArray* new_array,char* address) {
	int i;
	for (i = 0; i < GetRepoLenght(c->rep); i++) {
		//printf("%d\n", strstr(get(c->rep->offers, i)->address, address));
		
		if (strstr(get(c->rep->offers, i)->address, address) != NULL || strcmp(address,"")==0) {
			//Offer* x=CopyOffer(get(c->rep)
			Push(new_array, get(c->rep->offers, i));
		}
	}
}


repo* GetRepo(cont* c) {
	return c->rep;
}