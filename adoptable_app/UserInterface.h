#pragma once
#include "Controller.h"


class UserInterface
{

private:
	Controller controller;

public:
	UserInterface();
	void add_Dog_ui();
	void give_Dog_ui();
	void update_Dog_ui();
	void show_Dogs();
	void read_from_file_ui();
	void write_to_file_ui();
	void start_user_ui();
	void start_admin_ui();
	void start_dog_adoption(char* showcase_option);
	void start_UI();
};
