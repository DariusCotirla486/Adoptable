#include "Operations.h"


AddOperation::AddOperation(Repository& repo, Dog added_element) : repo(repo)
{
	this->added_element = added_element;
}

void AddOperation::executeUndo()
{
	int index = repo.getIndexOfDog(added_element.getBreed(), added_element.getName(), added_element.getAge(), added_element.getPhotograph());
	repo.giveDogToAdoption(index);
}

void AddOperation::executeRedo()
{
	repo.addDogToShelter(&added_element);
}

RemoveOperation::RemoveOperation(Repository& repo, Dog removed_element) : repo(repo)
{
	this->removed_element = removed_element;
}

void RemoveOperation::executeUndo()
{
	repo.addDogToShelter(&removed_element);
}

void RemoveOperation::executeRedo()
{
	int index = repo.getIndexOfDog(removed_element.getBreed(), removed_element.getName(), removed_element.getAge(), removed_element.getPhotograph());
	repo.giveDogToAdoption(index);
}
