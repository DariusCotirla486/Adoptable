#include "Dog.h"
#include <string.h>


Dog::Dog(string breed, string name, int age, string photograph)
{
	this->breed = breed;
	this->name = name;
	this->age = age;
	this->photograph = photograph;
}


Dog::Dog() : name(""), breed(""), age(0), photograph("") {}


int Dog::getAge() const
{
	return this->age;
}

string Dog::getName() const
{
	return this->name;
}

string Dog::getBreed() const
{
	return breed;
}

string Dog::getPhotograph() const
{
	return photograph;
}

void Dog::setAge(int age)
{
	this->age = age;
}

void Dog::setName(string name)
{
	this->name = name;
}

void Dog::setBreed(string breed)
{
	this->breed = breed;
}

void Dog::setPhotograph(string photograph)
{
	this->photograph = photograph;
}
