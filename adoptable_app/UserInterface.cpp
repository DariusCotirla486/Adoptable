#include "UserInterface.h"


UserInterface::UserInterface() : controller(Controller()) {}

ostream& operator <<(ostream& out, Dog& dog) {
	out << dog.getName() << "," << dog.getBreed() << "," << dog.getAge() << "," << dog.getPhotograph();
	return out;
}

istream& operator >>(istream& in, Dog& dog) {
	string breed, name, photograph;
	int age;
	char delimiter;

	getline(in, name, ',');
	getline(in, breed, ',');
	in >> age;
	in.get(delimiter);
	getline(in, photograph);
	dog.setBreed(breed);
	dog.setName(name);
	dog.setAge(age);
	dog.setPhotograph(photograph);

	return in;
}

void print_administrator_menu()
{
	printf("Commands: \n");
	printf("1. Add a dog to the shelter.\n");
	printf("2. Give a dog to adoption.\n");
	printf("3. Update the information of a dog.\n");
	printf("4. See all dogs.\n");
	printf("5. Read a shelter from file.\n");
	printf("6. Write a shelter to file.\n");
	printf("0. Exit the program.\n\n");
}


void print_user_menu()
{
	printf("Commands: \n");
	printf("1. Start the showcase of the dogs in shelter.\n");
	printf("During the showcase, you have 2 options: ");
	printf("1. Adopt the dog, 2. Do not adopt the dog and continue on.\n");
	printf("2. See the adoption list.\n");
	printf("3. Save the file in the chosen format.\n");
	printf("4. Open the file with a default app.\n");
	printf("0. Exit the program.\n\n");
}


void readAdminOption(char* option)
{
	if ((strcmp(option, "0") == 0) || (strcmp(option, "1") == 0) || (strcmp(option, "2") == 0)
		|| (strcmp(option, "3") == 0) || (strcmp(option, "4") == 0) || (strcmp(option, "5") == 0) || (strcmp(option, "6") == 0))
		return;
	strcpy(option, "FALSE");
}


void readUserOption(char* option)
{
	if ((strcmp(option, "0") == 0) || (strcmp(option, "1") == 0) || (strcmp(option, "2") == 0)
		|| (strcmp(option, "3") == 0) || (strcmp(option, "next") == 0) || (strcmp(option, "4") == 0))
		return;
	strcpy(option, "FALSE");
}


void UserInterface::add_Dog_ui()
{
	string breed, name, photo;
	int age;
	cout << "Breed: ";
	cin >> breed;
	Validator::validate_breed(breed);
	cout << "Name: ";
	cin >> name;
	Validator::validate_name(name);
	cout << "Age: ";
	cin >> age;
	Validator::validate_age(age);
	cout << "Photo: ";
	cin >> photo;
	Validator::validate_photo(photo);
	bool result = this->controller.add_Dog_controller(breed, name, age, photo);
	if (result == true)
		printf("Dog has found shelter!\n");
	else
		printf("Dog is already in the shelter!\n");
}


void UserInterface::give_Dog_ui()
{
	string breed, name, photo;
	int age = 0;
	printf("Dog breed: ");
	cin >> breed;
	Validator::validate_breed(breed);
	printf("Dog name: ");
	cin >> name;
	Validator::validate_name(name);
	printf("Dog age: ");
	cin >> age;
	Validator::validate_age(age);
	printf("Dog photograph: ");
	cin >> photo;
	Validator::validate_photo(photo);
	bool result = this->controller.give_Dog_controller(breed, name, age, photo);
	if (result == true)
		printf("Dog has found its parents!\n");
	else
		printf("Dog does not exist in the shelter!\n");
}


void UserInterface::update_Dog_ui()
{
	string breed, name, photo;
	int age = 0;
	printf("Dog breed: ");
	cin >> breed;
	Validator::validate_breed(breed);
	printf("Dog name: ");
	cin >> name;
	Validator::validate_name(name);
	printf("Dog age: ");
	cin >> age;
	Validator::validate_age(age);
	printf("Dog photograph: ");
	cin >> photo;
	Validator::validate_photo(photo);
	string new_breed, new_name, new_photo;
	int new_age = 0;
	printf("New dog breed: ");
	cin >> new_breed;
	Validator::validate_breed(new_breed);
	printf("New dog name: ");
	cin >> new_name;
	Validator::validate_name(new_name);
	printf("New dog age: ");
	cin >> new_age;
	Validator::validate_age(new_age);
	printf("New dog photograph: ");
	cin >> new_photo;
	Validator::validate_photo(new_photo);
	bool result = this->controller.update_Dog_controller(breed, name, age, photo, new_breed, new_name, new_age, new_photo);
	if (result == true)
		printf("Dog information has been updated!\n");
	else
		printf("Dog does not exist in the shelter!\n");
}


void UserInterface::show_Dogs()
{
	char string_with_dogs[10000];
	this->controller.getDogsFromShelter(string_with_dogs);
	if (strcmp(string_with_dogs, "") == 0)
		printf("There are no dogs in the shelter.\n");
	printf(string_with_dogs);
}


void UserInterface::read_from_file_ui()
{
	string filename;
	cout << "File name: ";
	cin >> filename;
	bool result = controller.read_from_file_controller(filename);
	if (result)
		cout << "Successfully read from file.\n";
	else cout << "File not found.\n";
}


void UserInterface::write_to_file_ui()
{
	string filename;
	cout << "File name: ";
	cin >> filename;
	this->controller.write_to_file_controller(filename);
}


void UserInterface::start_dog_adoption(char* showcase_option)
{
	vector<TElem> dogs;
	int size_of_shelter;
	if (strcmp(showcase_option, "breed") == 0) {
		char wanted_breed[30];
		int wanted_age;
		printf("Breed: ");
		scanf("%s", wanted_breed);
		printf("Oldest age: ");
		scanf("%d", &wanted_age);
		dogs = this->controller.pass_specific_dogs_controller(wanted_breed, wanted_age);
		size_of_shelter = this->controller.pass_size_of_specific_dogs_array(wanted_breed, wanted_age);
		printf("\n");
	}
	else
	{
		dogs = this->controller.pass_dogs_controller();
		size_of_shelter = this->controller.pass_size_of_repository();
	}
	bool end = false;
	char option_string[30];
	int dog_position = 0;
	while (!end)
	{
		TElem dog = dogs[dog_position];
		cout << *dog << endl;
		printf(">> ");
		scanf("%s", option_string);
		readUserOption(option_string);
		if (strcmp(option_string, "FALSE") == 0)
			printf("Invalid option!\n");
		else
		{
			int option = option_string[0] - '0';
			if (option == 1) {
				bool result = this->controller.add_adopted_Dog_controller(dog->getBreed(), dog->getName(), dog->getAge(), dog->getPhotograph());
				if (result == true)
					printf("Dog adopted!\n");
				else
					printf("Dog is already adopted!\n");
				dog_position++;
			}
			if (option == 2) {
				dog_position++;
			}

			if (dog_position == size_of_shelter)
			{
				bool valid = false;
				while (!valid) {
					printf("No more dogs left.\n");
					printf("next -> start over,   0 -> end adoption\n");
					printf(">> ");
					scanf("%s", option_string);
					if (strcmp(option_string, "0") == 0) {
						end = true;
						valid = true;
					}
					if (strcmp(option_string, "next") == 0) {
						dog_position = 0;
						valid = true;
					}
					else
						printf("Invalid option!\n");
				}
			}

			if (option == 3)
			{
				char dogs_adopted[10000];
				this->controller.getAdoptedDogsFromShelter(dogs_adopted);
				printf(dogs_adopted);
			}

			if (option == 0)
				end = true;
		}
	}
}


void UserInterface::start_user_ui()
{
	printf("Welcome to the user mode!\n\n");
	printf("Choose the type of repository(CSV or HTML): ");
	string repo_type;
	cin >> repo_type;
	string filename;
	cout << "Name of the .csv or .html file: ";
	cin >> filename;
	this->controller = Controller(repo_type);
	print_user_menu();
	while (true)
	{
		try {
			char option_string[30];
			printf("Option: ");
			scanf("%s", option_string);
			readAdminOption(option_string);
			if (strcmp(option_string, "FALSE") == 0)
				printf("Invalid option!");
			else
			{
				int option = option_string[0] - '0';
				if (option == 1) {
					char showcase_option[30];
					printf("Showcase option: all/breed\n");
					scanf("%s", showcase_option);
					if ((strcmp(showcase_option, "all") == 0) || (strcmp(showcase_option, "breed") == 0))
						start_dog_adoption(showcase_option);
				}
				if (option == 2) {
					char dogs_adopted[10000];
					this->controller.getAdoptedDogsFromShelter(dogs_adopted);
					printf(dogs_adopted);
				}
				if (option == 3) {
					this->controller.write_to_file_controller(filename);
				}
				if (option == 4) {
					string command = "start " + filename;
					system(command.c_str());
				}
				if (option == 0)
					break;
			}
		}
		catch (Exception& e) {
			cout << e.what();
		}
	}
}


void UserInterface::start_admin_ui()
{
	printf("Welcome to the admin mode!\n\n");
	print_administrator_menu();
	while (true)
	{
		try {
			char option_string[30];
			printf(">> ");
			scanf("%s", option_string);
			readAdminOption(option_string);
			if (strcmp(option_string, "FALSE") == 0)
				printf("Invalid option!\n");
			else {
				int option = option_string[0] - '0';
				if (option == 0)
					break;
				if (option == 1)
					add_Dog_ui();
				if (option == 2)
					give_Dog_ui();
				if (option == 3)
					update_Dog_ui();
				if (option == 4)
					show_Dogs();
				if (option == 5)
					read_from_file_ui();
				if (option == 6)
					write_to_file_ui();
			}
		}
		catch (Exception& e) {
			cout << e.what();
		}
	}
}


void UserInterface::start_UI()
{
	char access_mode[30];
	printf("Access mode: ");
	scanf("%s", access_mode);
	if (strcmp(access_mode, "admin") == 0)
		start_admin_ui();
	else if (strcmp(access_mode, "user") == 0)
		start_user_ui();
	else
		printf("Invalid access mode!");
}
