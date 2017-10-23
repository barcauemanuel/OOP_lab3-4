#include "stdafx.h"
#include "UndoRedoFunction.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define Nr_Undo 500

ur_cont* CreateUndoRedo(cont* c) {
	
	ur_cont* ur = (ur_cont*)malloc(sizeof(ur_cont));
	
	ur->c = c;

	int* st = (int*)malloc(sizeof(int) * Nr_Undo);
	int* ac = (int*)malloc(sizeof(int) * Nr_Undo);
	ur->steps = st;
	ur->action = ac;

	DynamicArray* ar = createDynamicArray(30);
	ur->vec = ar;

	ur->cstep = 0;
	ur->max_step = 0;

	int i;
	for (i = 0; i < Nr_Undo; i++) {
		ur->steps[i] = -1;
		ur->action[i] = -1;
	}

	return ur;
}

void DeleteUndoRedoFromAtoB(ur_cont* ur) {
	int i;
	//printf("%d  %d \n", ur->cstep, ur->max_step);
	for (i = 0; i < Nr_Undo; i++) {
		if (ur->steps[i] > ur->cstep && ur->steps[i] <= ur->max_step) {
			//printf("%d\n", ur->steps[i]);
			ur->steps[i] = -1;
			ur->action[i] = -1;
			Offer* a = get(ur->vec, i);
			DeleteOffer(a);
			ur->vec->length--;
		}
		else
			if (ur->steps[i] == -1) {
				i = Nr_Undo + 1;
			}
	}
}

void PutDeleteUndoRedo(ur_cont* ur, Offer* of) {
	int i;

	DeleteUndoRedoFromAtoB(ur);
	ur->cstep++;
	ur->max_step = ur->cstep;


	for (i = 0; i < Nr_Undo; i++) {
		if (ur->steps[i] == -1) {
			ur->steps[i] = ur->cstep;
			ur->action[i] = 2;
			Offer* new_offer = CopyOffer(of);
			Push(ur->vec, new_offer);
			i = Nr_Undo + 1;
		}
	}
}

void DecreaseCurrentStep(ur_cont* ur) {
	ur->cstep--;
}

void PutModify(ur_cont* ur, Offer* add, Offer* del) {
	int i;

	DeleteUndoRedoFromAtoB(ur);
	ur->cstep++;
	ur->max_step = ur->cstep;

	for (i = 0; i < Nr_Undo; i++) {
		if (ur->steps[i] == -1) {
			ur->steps[i] = ur->cstep;
			ur->action[i] = 2;
			Offer* new_offer = CopyOffer(del);
			Push(ur->vec, new_offer);
			i = Nr_Undo + 1;
		}
	}

	for (i = 0; i < Nr_Undo; i++) {
		if (ur->steps[i] == -1) {
			ur->steps[i] = ur->cstep;
			ur->action[i] = 1;
			Offer* new_offer = CopyOffer(add);
			Push(ur->vec, new_offer);
			i = Nr_Undo + 1;
		}
	}
}

void PutAddUndoRedo(ur_cont* ur, Offer* of) {
	int i;
	
	DeleteUndoRedoFromAtoB(ur);
	ur->cstep++;
	ur->max_step = ur->cstep;
	

	for (i = 0; i < Nr_Undo; i++) {
		if (ur->steps[i] == -1) {
			ur->steps[i] = ur->cstep;
			ur->action[i] = 1;
			Offer* new_offer = CopyOffer(of);
			Push(ur->vec, new_offer);
			i = Nr_Undo + 1;
		}
	}
}


void Undo(ur_cont* ur) {
	int i;

	if (ur->cstep > 0) {
		for (i = 0; i < Nr_Undo; i++) {
			if (ur->steps[i] == ur->cstep) {
				if (ur->action[i] == 1) {
					DeleteOfferCont(ur->c, get(ur->vec, i)->address);
				}
				else
				if (ur->action[i] == 2) {
					Offer* a = get(ur->vec, i);
					AddOfferControler(ur->c, a->type, a->address, a->surface, a->price);
				}
			}
			else
				if (ur->steps[i] == -1) {
					i = Nr_Undo + 1;
				}
		}
		ur->cstep--;

	}
}

void Redo(ur_cont* ur) {
	int i;
	if (ur->cstep <ur->max_step ) {
		for (i = 0; i < Nr_Undo; i++) {
			if (ur->steps[i] == ur->cstep+1) {
				if (ur->action[i] == 1) {
					Offer* a = get(ur->vec, i);
					AddOfferControler(ur->c, a->type, a->address, a->surface, a->price);
				}
				else
				if (ur->action[i] == 2) {
					DeleteOfferCont(ur->c, get(ur->vec, i)->address);
				}
			}
			else
				if (ur->steps[i] == -1) {
					i = Nr_Undo + 1;
				}
		}
		ur->cstep++;
	}
}


void DeleteUndoRedo(ur_cont* ur) {
	int i;
	for (i = 0; i < ur->vec->length; i++) {
		Offer* a = get(ur->vec, i);
		DeleteOffer(a);
	}
	destroy(ur->vec);
	free(ur->action);
	free(ur->steps);

	free(ur);
}


