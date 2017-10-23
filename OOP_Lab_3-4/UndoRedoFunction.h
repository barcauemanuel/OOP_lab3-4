#pragma once
#include "Controller.h"


typedef struct {
	cont* c;
	DynamicArray* vec;
	int* steps;
	int* action;
	int cstep;
	int max_step;
}ur_cont;

ur_cont* CreateUndoRedo(cont* c);
void DeleteUndoRedo(ur_cont* ur);

void Redo(ur_cont* ur);
void Undo(ur_cont* ur);
void PutAddUndoRedo(ur_cont* ur, Offer* of);
void PutDeleteUndoRedo(ur_cont* ur, Offer* of);
void DecreaseCurrentStep(ur_cont* ur);
void PutModify(ur_cont* ur, Offer* del, Offer* add);