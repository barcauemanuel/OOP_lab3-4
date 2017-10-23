// OOP Lab 3-4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "UI.h"

int main()
{
	repo* Repository = CreateRepository();
	cont* Controller = CreateController(Repository);
	ur_cont* UndoRedo = CreateUndoRedo(Controller);
	UI* ui = CreateUI(Controller,UndoRedo);

	AddOfferControler(Controller, "house", "str. Tatarilor nr. 34", 100, 40);
	AddOfferControler(Controller, "house", "piez", 10, 60);
	AddOfferControler(Controller, "apartament", "str. Tatarilor nr. 36", 900, 400);
	AddOfferControler(Controller, "penthouse", "str. Tatarilor nr. 33", 100.38, 40.19);

	StartUI(ui);

	DeleteUI(ui);

	_CrtDumpMemoryLeaks();

    return 0;
}

