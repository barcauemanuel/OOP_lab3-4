#pragma once
#include "Repository.h"

typedef struct {
	repo* rep;
}cont;

int ControllerVerifyType(char* x);
cont* CreateController(repo* r);
void DeleteController(cont* c);
void AddOfferControler(cont* c, char* type, char* address, double surface, double price);
repo* GetRepo(cont* c);
Offer* ReturnOfferController(cont* c, char* address);
void sortDynamiArrayByPrice(DynamicArray* a);
int DeleteOfferCont(cont* c, char* address);
void sortDynamiArrayByAdress(DynamicArray* a);
void getFilterByGreaterSurface(DynamicArray* new_array, DynamicArray* a, double surface);
void getFilterBySurface(DynamicArray* a, DynamicArray* new_array, double surface);
void getFilterByLowerPrice(DynamicArray* new_array, DynamicArray* a, double price);
void getFilterByType(cont* c, DynamicArray* new_array, char* type);
void getFilterByAddress(cont* c, DynamicArray* new_array, char* address);