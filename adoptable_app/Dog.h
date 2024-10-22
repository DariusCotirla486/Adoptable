#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;


class Dog
{
private:
	int age;
	string name, breed, photograph;

public:
	Dog();
	Dog(string breed, string name, int age, string photograph);
	string getName() const;
	string getBreed() const;
	string getPhotograph() const;
	int getAge() const;
	void setAge(int age);
	void setName(string name);
	void setBreed(string breed);
	void setPhotograph(string photograph);

	friend ostream& operator <<(ostream& out, Dog& dog);
	friend istream& operator >>(istream& in, Dog& dog);
};
