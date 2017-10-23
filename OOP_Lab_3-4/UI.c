#include "stdafx.h"
#include "UI.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

UI* CreateUI(cont* c,ur_cont* ur) {
	UI* u = (UI*)malloc(sizeof(UI));
	u->cont = c;
	u->ur_cont = ur;
	return u;
}

void DeleteUI(UI* u) {
	DeleteController(u->cont);
	DeleteUndoRedo(u->ur_cont);
	free(u);
}

void PrintMenu() {
	printf("\n******************************************************************\n"); 
	printf("	1.  Add an offer\n");
	printf("	2.  Delete an offer by its address\n");
	printf("	3.  Modify an order selecting it by the current address\n");
	printf("	4.  Filter by address\n");
	printf("	5.  List all offers\n");
	printf("	6.  Display all offers of a given type, with a greater surface then the one specified.\n");
	printf("	7.  Display all offers of a given surface sorted by price\n");
	printf("	8.  Undo\n");
	printf("	9.  Redo\n");
	printf("	10. Display all offers having the price less than a given value, sorted ascending by price\n");
	printf("	0.  Exit\n");
	printf("******************************************************************\n\n");
}														 

void readStringWithSpaces(const char* message, int maxStrSize, char str[])
{
	printf(message);
	fgets(str, maxStrSize, stdin);
	int size = strlen(str) - 1;
	if (str[size] == '\n')
		str[size] = '\0';
}


int readIntegerNumber(const char* message)
{
	char s[16];
	int res = 0;
	int flag = 0;
	int r = 0;

	while (flag == 0)
	{
		printf(message);
		scanf("%s", &s);

		r = sscanf(s, "%d", &res);	
		flag = (r == 1);
		if (flag == 0)
			printf("Error reading number!\n");
	}
	return res;
}

void StartUI(UI* ui) {
	int ok_while = 1;
	while (ok_while == 1) {
		PrintMenu();
		int command = readIntegerNumber("Command: ");

		if (command == 0) {
			ok_while = 0;
		}
		else if (command == 1) {
			
			char *t = (char*)malloc(100 * sizeof(char));
			char *a = (char*)malloc(100 * sizeof(char));
			double s;
			double p;

			fgetc(stdin);
			readStringWithSpaces("	Type: ", 100, t);
			readStringWithSpaces("	Adress:", 100, a);
			printf("	Surface: ");
			scanf("%lf", &s);
			printf("	Price: ");
			scanf("%lf", &p);

			if (ControllerVerifyType(t) == 1 && ReturnOfferController(ui->cont,a)==NULL) {
				AddOfferControler(ui->cont, t, a, s, p);
				PutAddUndoRedo(ui->ur_cont, get(ui->cont->rep->offers, ui->cont->rep->offers->length-1));
			}
			else {
				printf("Invalid type or offer may already exist\n");
			}
			free(a);
			free(t);
			
		}
		else if (command == 2) {
			char* a = (char*)malloc(sizeof(char) * 100);
			fgetc(stdin);
			readStringWithSpaces("Adress of the offer: ", 100, a);

			Offer* obi = CopyOffer( ReturnOfferController(ui->cont, a));

			int o=DeleteOfferCont(ui->cont, a);
			free(a);
			
			if (o == 0) {
				printf("	Offer was not found\n");
			}
			else {
				PutDeleteUndoRedo(ui->ur_cont, obi);
				printf("	Offer was deleted\n");
			}
			DeleteOffer(obi);
		}
		else if (command == 3) {
			char* a = (char*)malloc(sizeof(char) * 100);
			fgetc(stdin);
			readStringWithSpaces("Adress of the offer: ", 100, a);

			Offer* obj = CopyOffer( ReturnOfferController(ui->cont, a));

			int o = DeleteOfferCont(ui->cont, a);
			free(a);

			if (o == 0) {
				printf("	Offer was not found\n");
			}
			else {
				//PutDeleteUndoRedo(ui->ur_cont, obj);

				char *t = (char*)malloc(100 * sizeof(char));
				char *a = (char*)malloc(100 * sizeof(char));
				double s;
				double p;

				readStringWithSpaces("new Type: ", 100, t);
				readStringWithSpaces("new Adress:", 100, a);
				printf("new Surface: ");
				scanf("%lf", &s);
				printf("new Price: ");
				scanf("%lf", &p);

				AddOfferControler(ui->cont, t, a, s, p);
				
				//PutAddUndoRedo(ui->ur_cont, get(ui->cont->rep->offers, ui->cont->rep->offers->length - 1));

				PutModify(ui->ur_cont, get(ui->cont->rep->offers, ui->cont->rep->offers->length - 1), obj);

				free(a);
				free(t);
			}
			DeleteOffer(obj);
		}
		else if (command == 4) {
			char* a = (char*)malloc(100 * sizeof(char));
			fgetc(stdin);
			readStringWithSpaces("	Adress: ",100,a);
			
			DynamicArray* new_array = createDynamicArray(10);
			getFilterByAddress(ui->cont,new_array, a);
			sortDynamiArrayByPrice(new_array);
			free(a);

			char* s = (char*)malloc(sizeof(char) * 200);

			Offer* x;
			int i;
			for (i = 0; i < new_array->length; i++) {
				x = get(new_array, i);
				toString(x, s);
				printf("	%s\n", s);
			}
			free(s);
			destroy(new_array);

		}
		else if (command == 5) {

			printf("\n\n	Offers: \n");

			int i;
			//printf("%d", GetRepoLenght(ui->cont->rep));
			for (i = 0; i < GetRepoLenght(ui->cont->rep); i++) {
				char *s = (char*)malloc(200 * sizeof(char));
				//char s[100];
				Offer* a;
				a=get(ui->cont->rep->offers, i);
				toString(a, s);
				printf("	%s\n", s);
				free(s);
				
			}
		}
		else if (command == 6) {
			char* a = (char*)malloc(sizeof(char) * 100);
			fgetc(stdin);

			readStringWithSpaces("	Type: ", 100, a);
			printf("	Surface: ");
			double surf;
			scanf("%lf", &surf);

			DynamicArray* new_array = createDynamicArray(10);
			DynamicArray* final_array = createDynamicArray(10);
			getFilterByType(ui->cont, new_array, a);
			getFilterByGreaterSurface(final_array, new_array, surf);

			free(a);

			char* s = (char*)malloc(sizeof(char) * 200);

			Offer* x;
			int i;
			for (i = 0; i < final_array->length; i++) {
				x = get(final_array, i);
				toString(x, s);
				printf("	%s\n", s);
			}
			free(s);
			destroy(new_array);
			destroy(final_array);
		}
		else if (command == 7) {

			printf("	Surface: ");
			double surf;
			scanf("%lf", &surf);

			DynamicArray* new_array = createDynamicArray(10);
			
			getFilterBySurface(new_array,	ui->cont->rep->offers, surf);
			sortDynamiArrayByPrice(new_array);


			char* s = (char*)malloc(sizeof(char) * 200);

			Offer* x;
			int i;
			for (i = 0; i < new_array->length; i++) {
				x = get(new_array, i);
				toString(x, s);
				printf("	%s\n", s);
			}
			free(s);
			destroy(new_array);
			
		}
		else if (command == 8) {
			Undo(ui->ur_cont);
		}
		else if (command == 9) {
			Redo(ui->ur_cont);
		}
		else if (command == 10) {
			printf("	Price: ");
			double price;
			scanf("%lf", &price);

			DynamicArray* new_array = createDynamicArray(10);

			getFilterByLowerPrice(new_array, ui->cont->rep->offers, price);
			
			sortDynamiArrayByPrice(new_array);

			char* s = (char*)malloc(sizeof(char) * 200);

			Offer* x;
			int i;
			for (i = 0; i < new_array->length; i++) {
				x = get(new_array, i);
				toString(x, s);
				printf("	%s\n", s);
			}
			free(s);
			destroy(new_array);
		}
		else
		{
			printf("\n\n	Invalid command\n\n");
		}
	}
}