#pragma once
#include "Controller.h"
#include "UndoRedoFunction.h"

typedef struct {
	cont* cont;
	ur_cont* ur_cont;
}UI;

UI* CreateUI(cont* c,ur_cont* ur);
void DeleteUI(UI* u);
void StartUI(UI* ui);