#include "Validator.h"

void Validator::validate_breed(string breed)
{
	if (breed.size() < 2 || breed.size() > 20)
		throw Exception("Breed must be between 2 and 20 characters long!\n");
}

void Validator::validate_name(string name)
{
	if (name.size() < 2 || name.size() > 20)
		throw Exception("Name must be between 2 and 20 characters long!\n");
}

void Validator::validate_age(int age)
{
	if (age <= 0 || age >= 100)
		throw Exception("Age must be between 0 and 100!\n");
}

void Validator::validate_photo(string photo)
{
	if (photo.substr(0, 5) != "https" || photo.size() < 5)
		throw Exception("Must be a https link!\n");
}
