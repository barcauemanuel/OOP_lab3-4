#include "stdafx.h"
#include "Repository.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

repo* CreateRepository() {
	repo *p = (repo*)malloc(sizeof(repo));
	p->offers = createDynamicArray(CAPACITY);

	return p;
}

void DestroyRepo(repo *p) {

	if (p == NULL)
		return;

	int i = 0;
	int max1;
	max1 = p->offers->length;
	for (i = 0; i < max1; i++) {
		Offer *a = get(p->offers, i);
		DeleteOffer(a);
	}


	destroy(p->offers);
	free(p);
}


int AddOfferRepo(Offer *p, repo* rep) {
	if (p == NULL)
		return -1;

	Offer *a = CopyOffer(p);
	Push(rep->offers, a);

	return 1;
}

int GetRepoLenght(repo *p) {
	if (p == NULL)
		return -1;


	return getLength(p->offers);
}