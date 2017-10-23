#pragma once

#include "Offer.h"
#include "DynamicArray.h"

typedef struct {
	DynamicArray* offers;
}repo;

repo* CreateRepository();
void DestroyRepo(repo *p);
int AddOfferRepo(Offer *p, repo* rep);
int GetRepoLenght(repo *p);