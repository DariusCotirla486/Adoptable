#pragma once
#include "GUI.h"


class UserMenuWidget : public QWidget {
	Q_OBJECT
protected:
	Controller controller;

public:
	explicit UserMenuWidget(QWidget* parent = nullptr, Controller controller = Controller());

	void show_push_buttons() const;
	void hide_push_buttons() const;
	void manage_breed_widgets();

	QVBoxLayout* mainLayout;
	QVBoxLayout* optionsLayout;
	QHBoxLayout* showcaseOptionLayout;
	QFormLayout* choose_breed_layout;
	QTableWidget* adopted_dogs_tableWidget;
	QHBoxLayout* buttonLayout;

	QPushButton* showcase_button;
	QPushButton* save_list_button;
	QPushButton* open_file_button;
	QPushButton* back_button;
	QPushButton* selected_breed_button;
	QPushButton* adopt_button;
	QPushButton* skip_button;

	QPushButton* breed_button;
	QPushButton* all_button;
	QLineEdit* what_breed;
	QLineEdit* what_age;
	QLabel* breedLabel;
	QLabel* nameLabel;
	QLabel* ageLabel;
	QLabel* photoLabel;

	QString style = "QPushButton { font-size: 24pt; color: white; background-color: Blue; }";

	void selectAll();
	void selectBreed();
	string showcase_option;
	QString breed;
	int oldest_age, index_of_adopted_dog;
	vector<TElem> dogs;

	const QSize buttonSize = QSize(100, 100);

public slots:
	void choose_showcase_option_GUI();
	void showcase_dogs_GUI();
	void save_adopted_list_GUI();
	void open_file_with_dogs_GUI();
	void back_to_user_menu() const;
	void onAdoptButtonClicked();
	void onSkipButtonClicked();
	void showCurrentDog();
};
