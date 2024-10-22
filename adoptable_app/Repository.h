#pragma once
#include <vector>
#define TElem Dog*
#include "Dog.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Validator.h"
#include "Exceptions.h"
#include <stack>
using namespace std;


class Repository
{

protected:
	vector<TElem> dynamicArray;
	vector<TElem> adopted_dynamicArray;

public:
	Repository();
	bool check_if_dog_exists(string breed, string name, int age, string photo);
	bool check_if_adopted_dog_exists(string breed, string name, int age, string photo);
	int getIndexOfDog(string breed, string name, int age, string photo);
	void addDogToShelter(TElem dog);
	void addAdoptedDogToList(TElem dog);
	void giveDogToAdoption(int index_of_Dog);
	char* getStringOfDogs();
	char* getStringOfAdoptedDogs();
	void updateDogInformation(int position_of_dog, string new_breed, string new_name, int new_age, string new_photo);
	int passSizeOfArray();
	TElem pass_element(int index);
	vector<TElem> pass_dogs();
	void replace_repository(vector<TElem> new_dog_repo);
	virtual void save_repository_to_file(string filename);
	bool read_repository_from_file(string filename);
	TElem search_dog_by_name(string name);
	TElem search_dog_by_index(int index);
};


class CSVRepository : public Repository
{
public:
	void save_repository_to_file(string filename) override;
};


class HTMLRepository : public Repository
{
public:
	void save_repository_to_file(string filename) override;
};
