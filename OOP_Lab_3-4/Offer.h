#pragma once

typedef struct {

	char* type;
	char* address;
	double surface;
	double price;

}Offer;

Offer* CreateNewOffer(char* type, char* address, double surface, double price);
void toString(Offer *p, char *str);
void DeleteOffer(Offer *p);
Offer* CopyOffer(Offer* p);

char* getType(Offer *p);
void setType(Offer *p, char* a);

char* getAddress(Offer *p);
void setAdress(Offer *p, char* a);

double getSurface(Offer *p);
void setSurface(Offer *p, double a);

double getPrice(Offer* p);
void setPrice(Offer *p, double a);