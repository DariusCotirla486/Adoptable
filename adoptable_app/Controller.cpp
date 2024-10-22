#include "Controller.h"


Controller::Controller(string repo_choice)
{
	this->repo_choice = repo_choice;
	if (repo_choice == "CSV")
		this->repository = CSVRepository();
	else if (repo_choice == "HTML")
		this->repository = HTMLRepository();
	else
		this->repository = Repository();
}

string Controller::get_repo_choice()
{
	return repo_choice;
}

Controller::Controller()
{
	this->repository = Repository();
}


bool Controller::add_Dog_controller(string breed, string name, int age, string photo)
{
	bool does_dog_exist = this->repository.check_if_dog_exists(breed, name, age, photo);
	if (does_dog_exist == true)
		return false;
	TElem new_dog = new Dog(breed, name, age, photo);
	Operation* operation = new AddOperation(repository, *new_dog);
	undoStack.push(operation);
	while (!redoStack.empty()) {
		delete redoStack.top();
		redoStack.pop();
	}
	this->repository.addDogToShelter(new_dog);
	return true;
}


bool Controller::add_adopted_Dog_controller(string breed, string name, int age, string photo)
{
	bool does_dog_exist = this->repository.check_if_adopted_dog_exists(breed, name, age, photo);
	if (does_dog_exist == true)
		return false;
	TElem adopted_dog = new Dog(breed, name, age, photo);
	this->repository.addAdoptedDogToList(adopted_dog);
	return true;
}


void Controller::getDogsFromShelter(char* string_with_Dogs)
{
	strcpy(string_with_Dogs, this->repository.getStringOfDogs());
}


void Controller::getAdoptedDogsFromShelter(char* string_with_Adopted_Dogs)
{
	strcpy(string_with_Adopted_Dogs, this->repository.getStringOfAdoptedDogs());
}


bool Controller::give_Dog_controller(string breed, string name, int age, string photo)
{
	int position_of_Dog = this->repository.getIndexOfDog(breed, name, age, photo);
	if (position_of_Dog == -1)
		return false;
	TElem dog = repository.pass_element(position_of_Dog);
	Operation* operation = new RemoveOperation(repository, *dog);
	undoStack.push(operation);
	while (!redoStack.empty()) {
		delete redoStack.top();
		redoStack.pop();
	}
	this->repository.giveDogToAdoption(position_of_Dog);
	return true;
}


bool Controller::give_Dog_by_name_controller(string name)
{
	TElem dog = repository.search_dog_by_name(name);
	if (dog == nullptr)
		return false;
	else {
		string breed = dog->getBreed();
		string link = dog->getPhotograph();
		int age = dog->getAge();
		this->give_Dog_controller(breed, name, age, link);
		return true;
	}
}


bool Controller::update_Dog_controller(string breed, string name, int age, string photo, string new_breed, string new_name, int new_age, string new_photo)
{
	int position_of_Dog = this->repository.getIndexOfDog(breed, name, age, photo);
	if (position_of_Dog == -1)
		return false;
	this->repository.updateDogInformation(position_of_Dog, new_breed, new_name, new_age, new_photo);
	return true;
}


bool Controller::update_Dog_by_index_controller(int index, string new_breed, string new_name, int new_age, string new_photo)
{
	TElem dog = repository.search_dog_by_index(index);
	if (dog == nullptr)
		return false;
	else {
		this->update_Dog_controller(dog->getBreed(), dog->getName(), dog->getAge(), dog->getPhotograph(), new_breed, new_name, new_age, new_photo);
		return true;
	}
}


int Controller::pass_size_of_repository()
{
	return this->repository.passSizeOfArray();
}


vector<TElem> Controller::pass_dogs_controller()
{
	return this->repository.pass_dogs();
}


vector<TElem> Controller::pass_specific_dogs_controller(string breed, int oldest_age)
{
	vector<TElem> dogs = this->repository.pass_dogs();
	int size = this->repository.passSizeOfArray();
	vector<TElem> specific_dogs;
	specific_dogs.clear();
	for (auto& dog : dogs)
	{
		if ((dog->getBreed() == breed) && (dog->getAge() <= oldest_age))
			specific_dogs.push_back(dog);
	}
	return specific_dogs;
}


int Controller::pass_size_of_specific_dogs_array(string breed, int oldest_age)
{
	int number_of_dogs = 0;
	vector<TElem> dogs = this->repository.pass_dogs();
	int size = this->repository.passSizeOfArray();
	for (auto& dog : dogs)
	{
		if ((dog->getBreed() == breed) && (dog->getAge() <= oldest_age))
			number_of_dogs++;
	}
	return number_of_dogs;
}


void Controller::write_to_file_controller(string filename)
{
	repository.save_repository_to_file(filename);
}


bool Controller::read_from_file_controller(string filename)
{
	return repository.read_repository_from_file(filename);
}

TElem Controller::get_dog_at_index(int index)
{
	return repository.pass_element(index);
}

void Controller::undo()
{
	if (!undoStack.empty()) {
		Operation* operation = undoStack.top();
		undoStack.pop();
		operation->executeUndo();
		redoStack.push(operation);
	}
}

void Controller::redo()
{
	if (!redoStack.empty()) {
		Operation* operation = redoStack.top();
		redoStack.pop();
		operation->executeRedo();
		undoStack.push(operation);
	}
}


