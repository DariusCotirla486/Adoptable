#pragma once
#include "Exceptions.h"


class Validator
{
public:
	static void validate_breed(string breed);
	static void validate_name(string name);
	static void validate_age(int age);
	static void validate_photo(string photo);
};
