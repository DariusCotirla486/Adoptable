#pragma once
#include "Repository.h"
#include "Operations.h"


class Controller
{
private:
	Repository repository;
	std::stack<Operation*> undoStack;
	std::stack<Operation*> redoStack;
	string repo_choice;

public:
	Controller();
	Controller(string repo_choice);
	string get_repo_choice();
	void getDogsFromShelter(char* string_with_Dogs);
	void getAdoptedDogsFromShelter(char* string_with_Adopted_Dogs);
	bool add_Dog_controller(string breed, string name, int age, string photo);
	bool add_adopted_Dog_controller(string breed, string name, int age, string photo);
	bool give_Dog_controller(string breed, string name, int age, string photo);
	bool give_Dog_by_name_controller(string name);
	bool update_Dog_controller(string breed, string name, int age, string photo, string new_breed, string new_name, int new_age, string new_photo);
	bool update_Dog_by_index_controller(int index, string new_breed, string new_name, int new_age, string new_photo);
	int pass_size_of_repository();
	vector<TElem> pass_dogs_controller();
	vector<TElem> pass_specific_dogs_controller(string breed, int oldest_age);
	int pass_size_of_specific_dogs_array(string breed, int oldest_age);
	void write_to_file_controller(string filename);
	bool read_from_file_controller(string filename);
	TElem get_dog_at_index(int index);
	void undo();
	void redo();
};
