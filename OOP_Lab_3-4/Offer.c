
#include "stdafx.h"
#include "Offer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS


//
//	Public
//
//	Takes 4 parameters:
//		string	-	type
//		string	-	address
//		double	-	surface
//		double	-	price
//
//	Returns a pointer to the new variable created
//
Offer* CreateNewOffer(char* type, char* address, double surface, double price) {

	Offer *p = (Offer*)malloc(sizeof(Offer));
	
	p->type = (char*)malloc((strlen(type) + 1)*sizeof(char));
	strcpy(p->type, type);

	p->address = (char*)malloc((strlen(address) + 1)*sizeof(char));
	strcpy(p->address, address);

	p->surface = surface;

	p->price = price;

	return p;
}

//
//	Public
//
// Takes two variables
//		Offer*	-	the object
//		String	-	the char* where the output will be saved
//
//		Takes the oject and creates a string format respectivly ant saves it in str
//
void toString(Offer *p, char *str) {
	sprintf(str, "Offer has the type: %s, the address: %s,the surface %.2lf and the price %.2lf", p->type, p->address, p->surface, p->price);
}

//
//	Public
//
// Frees the memory of p
//
void DeleteOffer(Offer *p) {
	if (p == NULL)
		return;
	free(p->address);
	free(p->type);
	free(p);
}


Offer* CopyOffer(Offer* p) {
	if (p == NULL)
		return NULL;
	Offer *a = CreateNewOffer(p->type, p->address, p->surface, p->price);
	return a;
}


//
//	Public
//
char* getType(Offer *p) {
	return p->type;
}
//
//	Public
//
void setType(Offer *p, char* a) {
	free(p->type);
	p->type = (char*)malloc((strlen(a) + 1) * sizeof(char));
	strcpy(p->type, a);
}


//
//	Public
//
char* getAddress(Offer *p) {
	return p->address;
}
//
//	Public
//
void setAdress(Offer *p,char* a) {
	free(p->address);
	p->address = (char*)malloc((strlen(a) + 1) * sizeof(char));
	strcpy(p->address, a);
}


//
//	Public
//
double getSurface(Offer *p) {
	return p->surface;
}
//
//	Public
//
void setSurface(Offer *p,double a) {
	p->surface = a;
}


//
//	Public
//
double getPrice(Offer* p) {
	return p->price;
}
//
//	Public
//
void setPrice(Offer *p, double a) {
	p->price = a;
}
