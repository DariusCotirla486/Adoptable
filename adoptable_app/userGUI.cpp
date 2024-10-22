#include "userGUI.h"

UserMenuWidget::UserMenuWidget(QWidget* parent, Controller controller_choice)
    : QWidget(parent), controller(controller_choice), index_of_adopted_dog(0)
{
    this->setWindowTitle("User menu");
    this->resize(800, 800);

    this->mainLayout = new QVBoxLayout(this);
    this->mainLayout->setAlignment(Qt::AlignCenter);
    this->optionsLayout = new QVBoxLayout();
    this->showcaseOptionLayout = new QHBoxLayout();
    this->choose_breed_layout = new QFormLayout();
    this->buttonLayout = new QHBoxLayout();

    breedLabel = new QLabel(this);
    nameLabel = new QLabel(this);
    ageLabel = new QLabel(this);
    photoLabel = new QLabel(this);

    breedLabel->hide();
    nameLabel->hide();
    ageLabel->hide();
    photoLabel->hide();

    mainLayout->addWidget(breedLabel);
    mainLayout->addWidget(nameLabel);
    mainLayout->addWidget(ageLabel);
    mainLayout->addWidget(photoLabel);

    showcase_button = new QPushButton("Showcase dogs", this);
    showcase_button->setStyleSheet(style);
    showcase_button->setFixedSize(QSize(500, 100));
    connect(showcase_button, &QPushButton::clicked, this, &UserMenuWidget::choose_showcase_option_GUI);

    save_list_button = new QPushButton("Save the list of adopted dogs", this);
    save_list_button->setStyleSheet(style);
    save_list_button->setFixedSize(QSize(500, 100));
    connect(save_list_button, &QPushButton::clicked, this, &UserMenuWidget::save_adopted_list_GUI);

    open_file_button = new QPushButton("Open file with adopted dogs", this);
    open_file_button->setStyleSheet(style);
    open_file_button->setFixedSize(QSize(500, 100));
    connect(open_file_button, &QPushButton::clicked, this, &UserMenuWidget::open_file_with_dogs_GUI);

    optionsLayout->addWidget(showcase_button);
    optionsLayout->addWidget(save_list_button);
    optionsLayout->addWidget(open_file_button);

    back_button = new QPushButton("Back", this);
    back_button->setStyleSheet(style);
    back_button->setFixedSize(QSize(50, 50));
    connect(back_button, &QPushButton::clicked, this, &UserMenuWidget::back_to_user_menu);
    back_button->hide();

    adopt_button = new QPushButton("Adopt", this);
    adopt_button->setStyleSheet(style);
    adopt_button->setFixedSize(QSize(300, 100));
    connect(adopt_button, &QPushButton::clicked, this, &UserMenuWidget::onAdoptButtonClicked);
    adopt_button->hide();

    skip_button = new QPushButton("Skip", this);
    skip_button->setStyleSheet(style);
    skip_button->setFixedSize(QSize(300, 100));
    connect(skip_button, &QPushButton::clicked, this, &UserMenuWidget::onSkipButtonClicked);
    skip_button->hide();

    buttonLayout->addWidget(adopt_button);
    buttonLayout->addWidget(skip_button);

    all_button = new QPushButton("ALL", this);
    all_button->setStyleSheet(style);
    all_button->setFixedSize(QSize(300, 300));
    connect(all_button, &QPushButton::clicked, this, &UserMenuWidget::selectAll);

    breed_button = new QPushButton("BREED", this);
    breed_button->setFixedSize(QSize(300, 300));
    breed_button->setStyleSheet(style);
    connect(breed_button, &QPushButton::clicked, this, &UserMenuWidget::selectBreed);

    selected_breed_button = new QPushButton("Select", this);
    selected_breed_button->setFixedSize(500, 100);
    selected_breed_button->setStyleSheet(style);
    connect(selected_breed_button, &QPushButton::clicked, this, &UserMenuWidget::showcase_dogs_GUI);

    what_breed = new QLineEdit();
    what_age = new QLineEdit();
    choose_breed_layout->addRow("Breed: ", what_breed);
    choose_breed_layout->addRow("Oldest age: ", what_age);
    choose_breed_layout->addRow(selected_breed_button);
    what_breed->hide();
    what_age->hide();
    selected_breed_button->hide();

    showcaseOptionLayout->addWidget(all_button);
    showcaseOptionLayout->addWidget(breed_button);
    all_button->hide();
    breed_button->hide();

    mainLayout->addLayout(optionsLayout);
}

void UserMenuWidget::show_push_buttons() const
{
    showcase_button->show();
    save_list_button->show();
    open_file_button->show();
}

void UserMenuWidget::hide_push_buttons() const
{
    showcase_button->hide();
    save_list_button->hide();
    open_file_button->hide();
}

void UserMenuWidget::choose_showcase_option_GUI() {
    hide_push_buttons();
    mainLayout->addLayout(showcaseOptionLayout);
    all_button->show();
    breed_button->show();
}

void UserMenuWidget::selectAll()
{
    this->showcase_option = "all";
    all_button->hide();
    breed_button->hide();
    selected_breed_button->show();
}

void UserMenuWidget::manage_breed_widgets()
{
    what_breed->clear();
    what_age->clear();
    what_breed->hide();
    what_age->hide();
    selected_breed_button->hide();
}

void UserMenuWidget::selectBreed()
{
    mainLayout->addLayout(choose_breed_layout);
    this->showcase_option = "breed";
    all_button->hide();
    breed_button->hide();
    what_breed->show();
    what_age->show();
    selected_breed_button->show();
    breed = what_breed->text();
    oldest_age = what_age->text().toInt();
}

void UserMenuWidget::showcase_dogs_GUI()
{
    manage_breed_widgets();
    mainLayout->addLayout(buttonLayout);
    back_button->show();
    skip_button->show();
    adopt_button->show();
    breedLabel->show();
    nameLabel->show();
    ageLabel->show();
    photoLabel->show();

    if (showcase_option == "all")
        dogs = controller.pass_dogs_controller();
    else if (showcase_option == "breed")
        dogs = controller.pass_specific_dogs_controller(breed.toStdString(), oldest_age);

    index_of_adopted_dog = 0;
    showCurrentDog();
}

void UserMenuWidget::save_adopted_list_GUI()
{
    if (controller.get_repo_choice() == "HTML")
        controller.write_to_file_controller("dogs.html");
    else if (controller.get_repo_choice() == "CSV")
        controller.write_to_file_controller("dogs.csv");
    QMessageBox::information(this, "Success", "The list of adopted dogs has been successfully saved to file!");
}

void UserMenuWidget::open_file_with_dogs_GUI()
{
    if (controller.get_repo_choice() == "HTML")
    {
        std::string command = "start dogs.html";
        system(command.c_str());
    }
    else if (controller.get_repo_choice() == "CSV")
    {
        std::string command = "start dogs.csv";
        system(command.c_str());
    }
}

void UserMenuWidget::back_to_user_menu() const
{
    breedLabel->hide();
    nameLabel->hide();
    ageLabel->hide();
    photoLabel->hide();
    adopt_button->hide();
    skip_button->hide();
    show_push_buttons();
    back_button->hide();
}

void UserMenuWidget::onAdoptButtonClicked()
{
    if (index_of_adopted_dog < dogs.size()) {
        this->controller.add_adopted_Dog_controller(dogs[index_of_adopted_dog]->getBreed(), dogs[index_of_adopted_dog]->getName(),
            dogs[index_of_adopted_dog]->getAge(), dogs[index_of_adopted_dog]->getPhotograph());
        index_of_adopted_dog++;
        showCurrentDog();
    }
}

void UserMenuWidget::onSkipButtonClicked()
{
    if (index_of_adopted_dog < dogs.size()) {
        index_of_adopted_dog++;
        showCurrentDog();
    }
}

void UserMenuWidget::showCurrentDog()
{
    if (index_of_adopted_dog < dogs.size()) {
        TElem dog = dogs[index_of_adopted_dog];

        breedLabel->setText("Breed: " + QString::fromStdString(dog->getBreed()));
        nameLabel->setText("Name: " + QString::fromStdString(dog->getName()));
        ageLabel->setText("Age: " + QString::number(dog->getAge()));
        photoLabel->setText("Photograph: " + QString::fromStdString(dog->getPhotograph()));
    }
    else {
        QMessageBox::information(this, "End", "No more dogs to show.");
        back_to_user_menu();
    }
}