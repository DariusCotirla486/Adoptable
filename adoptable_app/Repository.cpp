#include "Repository.h"



void intToString(int age, char* age_string)
{
	int position = 0;
	while (age != 0)
	{
		int digit = age % 10;
		age_string[position++] = digit + '0';
		age /= 10;
	}
	age_string[position] = '\0';
	int j = position - 1, k = 0;
	char temp_string[30];
	while (j >= 0)
	{
		temp_string[k++] = age_string[j--];
	}
	temp_string[k] = '\0';
	strcpy(age_string, temp_string);
}


void addDogToString(TElem dog, char* string_with_dogs)
{
	string breed, name, photo;
	int age = dog->getAge();
	breed = dog->getBreed();
	name = dog->getName();
	photo = dog->getPhotograph();
	strcat(string_with_dogs, "Breed: ");
	strcat(string_with_dogs, breed.c_str());
	strcat(string_with_dogs, " | Name: ");
	strcat(string_with_dogs, name.c_str());
	strcat(string_with_dogs, " | Age: ");
	char age_string[30];
	intToString(age, age_string);
	strcat(string_with_dogs, age_string);
	strcat(string_with_dogs, " | Photo link: ");
	strcat(string_with_dogs, photo.c_str());
	strcat(string_with_dogs, "\n");
}


Repository::Repository()
{
	read_repository_from_file("dogs.txt");
}


bool Repository::check_if_dog_exists(string breed, string name, int age, string photo)
{
	for (auto& dog : dynamicArray)
	{
		if ((dog->getAge() == age) && (dog->getBreed() == breed) && (dog->getName() == name) && (dog->getPhotograph() == photo))
			return true;
	}
	return false;
}


bool Repository::check_if_adopted_dog_exists(string breed, string name, int age, string photo)
{
	for (auto& adopted_dog : adopted_dynamicArray)
	{
		if ((adopted_dog->getAge() == age) && (adopted_dog->getBreed() == breed)
			&& (adopted_dog->getName() == name) && (adopted_dog->getPhotograph() == photo))
			return true;
	}
	return false;
}


int Repository::getIndexOfDog(string breed, string name, int age, string photo)
{
	int dog_position = 0;
	for (auto& dog : dynamicArray) {
		if ((dog->getAge() == age) && (dog->getBreed() == breed) && (dog->getName() == name) && (dog->getPhotograph() == photo))
			return dog_position;
		dog_position++;
	}
	return -1;
}


void Repository::addDogToShelter(TElem dog)
{
	this->dynamicArray.push_back(dog);
}


void Repository::addAdoptedDogToList(TElem dog)
{
	this->adopted_dynamicArray.push_back(dog);
}


void Repository::giveDogToAdoption(int index_of_Dog)
{
	if (index_of_Dog < 0 || index_of_Dog >= dynamicArray.size())
		throw std::exception("Dog does not exist!\n");
	else
		this->dynamicArray.erase(dynamicArray.begin() + index_of_Dog);
}


char* Repository::getStringOfDogs()
{
	char dogs_string[3000] = "";
	for (auto& dog : dynamicArray)
		addDogToString(dog, dogs_string);
	return dogs_string;
}


char* Repository::getStringOfAdoptedDogs()
{
	char adopted_dogs_string[3000] = "";
	for (auto& adopted_dog : adopted_dynamicArray)
		addDogToString(adopted_dog, adopted_dogs_string);
	return adopted_dogs_string;
}


void Repository::updateDogInformation(int position_of_dog, string new_breed, string new_name, int new_age, string new_photo)
{
	if (position_of_dog < 0 || position_of_dog >= dynamicArray.size())
		throw std::exception("Dog does not exist!\n");
	else {
		dynamicArray[position_of_dog]->setAge(new_age);
		dynamicArray[position_of_dog]->setBreed(new_breed);
		dynamicArray[position_of_dog]->setName(new_name);
		dynamicArray[position_of_dog]->setPhotograph(new_photo);
	}
}


int Repository::passSizeOfArray()
{
	return dynamicArray.size();
}


TElem Repository::pass_element(int index)
{
	if (index < 0 || index >= dynamicArray.size())
		throw std::exception("Dog does not exist!\n");
	else
		return dynamicArray[index];
}


vector<TElem> Repository::pass_dogs()
{
	return dynamicArray;
}

void Repository::replace_repository(vector<TElem> new_dog_repo)
{
	this->dynamicArray = new_dog_repo;
}

void Repository::save_repository_to_file(string filename)
{
	ofstream file(filename);
	file.clear();
	if (adopted_dynamicArray.size() == 0)
		for (const auto& dog : dynamicArray)
			file << *dog << "\n";
	else
		for (const auto& dog : adopted_dynamicArray)
			file << *dog << "\n";
	file.close();
}

bool Repository::read_repository_from_file(string filename)
{
	ifstream file(filename);
	if (!file.is_open())
		return false;

	TElem new_dog = new Dog();
	dynamicArray.clear();
	while (file >> *new_dog)
	{
		dynamicArray.push_back(new_dog);
		new_dog = new Dog();
	}
	return true;
}

TElem Repository::search_dog_by_name(string name)
{
	for (const auto& dog : dynamicArray) {
		if (dog->getName() == name)
			return dog;
	}
	return nullptr;
}

TElem Repository::search_dog_by_index(int index)
{
	if (0 < index < dynamicArray.size())
		return dynamicArray[index];
	else
		return nullptr;
}


void CSVRepository::save_repository_to_file(string filename)
{
	ofstream file(filename);
	if (!file)
		return;

	for (const auto& dog : adopted_dynamicArray) {
		file << dog->getBreed() << "," << dog->getName() << "," << dog->getAge() << "," << dog->getPhotograph() << "\n";
	}
	file.close();
}


void HTMLRepository::save_repository_to_file(string filename)
{
	ofstream file(filename);
	if (!file)
		return;

	file << "<!DOCTYPE html>\n"
		<< "<html>\n"
		<< "<head>\n"
		<< "    <title>Shelter Dogs</title>\n"
		<< "</head>\n"
		<< "<body>\n"
		<< "<table border=\"1\">\n";
	for (const auto& dog : adopted_dynamicArray)
	{
		file << "    <tr>\n";
		file << "        <td>" << dog->getName() << "\n</td>";
		file << "        <td>" << dog->getBreed() << "\n</td>";
		file << "        <td>" << dog->getAge() << "\n</td>";
		file << "        <td>" << dog->getPhotograph() << "\n</td>";
		file << "    </tr>\n";
	}
	file << "</table>\n";
	file << "</body>\n";
	file << "</html>\n";
	file.close();
}
