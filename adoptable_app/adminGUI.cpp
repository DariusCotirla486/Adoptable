#include "adminGUI.h"


AdminMenuWidget::AdminMenuWidget(QWidget* parent, Controller controller_choice) : QWidget(parent), controller(controller_choice) {
    this->setWindowTitle("Admin menu");
    this->resize(800, 800);

    this->mainLayout = new QVBoxLayout(this);
    this->mainLayout->setAlignment(Qt::AlignCenter);
    this->optionsLayout = new QVBoxLayout();
    this->tableWidget = new QTableWidget(this);

    this->addDogButton = new QPushButton("Add dog", this);
    this->addDogButton->setStyleSheet("QPushButton { font-size: 16pt; color: black; background-color: AliceBlue; }");
    this->addDogButton->setFixedSize(buttonSize);
    connect(this->addDogButton, &QPushButton::clicked, this, &AdminMenuWidget::addDogGUI);
    this->optionsLayout->addWidget(addDogButton);

    this->removeDogButton = new QPushButton("Give dog", this);
    this->removeDogButton->setStyleSheet("QPushButton { font-size: 16pt; color: black; background-color: AliceBlue; }");
    this->removeDogButton->setFixedSize(buttonSize);
    connect(this->removeDogButton, &QPushButton::clicked, this, &AdminMenuWidget::removeDogGUI);
    this->optionsLayout->addWidget(removeDogButton);

    this->updateDogButton = new QPushButton("Update dog", this);
    this->updateDogButton->setStyleSheet("QPushButton { font-size: 16pt; color: black; background-color: AliceBlue; }");
    this->updateDogButton->setFixedSize(buttonSize);
    connect(this->updateDogButton, &QPushButton::clicked, this, &AdminMenuWidget::updateDogGUI);
    this->optionsLayout->addWidget(updateDogButton);

    this->listAllDogsButton = new QPushButton("List dogs", this);
    this->listAllDogsButton->setStyleSheet("QPushButton { font-size: 16pt; color: black; background-color: AliceBlue; }");
    this->listAllDogsButton->setFixedSize(buttonSize);
    connect(this->listAllDogsButton, &QPushButton::clicked, this, &AdminMenuWidget::listDogsGUI);
    this->optionsLayout->addWidget(listAllDogsButton);

    this->undoButton = new QPushButton("Undo", this);
    this->undoButton->setStyleSheet("QPushButton { font-size: 16pt; color: black; background-color: AliceBlue; }");
    this->undoButton->setFixedSize(buttonSize);
    connect(this->undoButton, &QPushButton::clicked, this, &AdminMenuWidget::undoGUI);
    this->optionsLayout->addWidget(undoButton);

    this->redoButton = new QPushButton("Redo", this);
    this->redoButton->setStyleSheet("QPushButton { font-size: 16pt; color: black; background-color: AliceBlue; }");
    this->redoButton->setFixedSize(buttonSize);
    connect(this->redoButton, &QPushButton::clicked, this, &AdminMenuWidget::redoGUI);
    this->optionsLayout->addWidget(redoButton);

    this->backPushButton = new QPushButton("Back", this);
    this->backPushButton->setStyleSheet("QPushButton { font-size: 16pt; color: black; background-color: AliceBlue; }");
    connect(backPushButton, &QPushButton::clicked, this, &AdminMenuWidget::backToAdminMenu);
    this->backPushButton->hide();

    this->mainLayout->addLayout(this->optionsLayout);
    this->setLayout(this->mainLayout);

    this->setUpGetDogDetailsGroupBox();
    this->setUpAddGroupBox();
    this->setUpRemoveGroupBox();
    this->setUpUpdateGroupBox();
}

void AdminMenuWidget::hideMainPushButtons() const {
    this->addDogButton->hide();
    this->removeDogButton->hide();
    this->updateDogButton->hide();
    this->listAllDogsButton->hide();
}

void AdminMenuWidget::showMainPushButtons() const {
    this->addDogButton->show();
    this->removeDogButton->show();
    this->updateDogButton->show();
    this->listAllDogsButton->show();
}

void AdminMenuWidget::setUpGetDogDetailsGroupBox() {
    getDogDetailsGroupBox = new QGroupBox(this);

    this->breedLine = new QLineEdit();
    this->nameLine = new QLineEdit();
    this->ageLine = new QLineEdit();
    this->linkLine = new QLineEdit();
    this->indexOfDogToUpdate = new QLineEdit();

    this->addFormLayout = new QFormLayout();
    this->addFormLayout->addRow("Breed:", breedLine);
    this->addFormLayout->addRow("Name:", nameLine);
    this->addFormLayout->addRow("Age:", ageLine);
    this->addFormLayout->addRow("Link:", linkLine);

    getDogDetailsGroupBox->setLayout(addFormLayout);
}

void AdminMenuWidget::hideGetDogDetailsGroupBox() const {
    this->getDogDetailsGroupBox->hide();
    this->breedLine->clear();
    this->nameLine->clear();
    this->linkLine->clear();
    this->ageLine->clear();
}

void AdminMenuWidget::setUpAddGroupBox() {
    addDogGroupBox = new QGroupBox("Add Dog", this);

    auto vbox = new QVBoxLayout();
    vbox->addWidget(this->getDogDetailsGroupBox);

    addDogDetailsButton = new QPushButton("Add Dog", addDogGroupBox);
    vbox->addWidget(addDogDetailsButton);
    connect(addDogDetailsButton, &QPushButton::clicked, this, &AdminMenuWidget::addDogDetails);

    addDogGroupBox->setLayout(vbox);
    mainLayout->addWidget(addDogGroupBox);

    this->addDogGroupBox->hide();
}

void AdminMenuWidget::addDogDetails() {
    this->addDogGroupBox->show();
    QString breed = breedLine->text();
    QString name = nameLine->text();
    QString link = linkLine->text();
    int age = ageLine->text().toInt();

    bool result = controller.add_Dog_controller(breed.toStdString(), name.toStdString(), age, link.toStdString());
    if (!result)
        QMessageBox::information(nullptr, "Error", QString::fromUtf8("Error on adding dog.\n"));

    this->addDogGroupBox->hide();
    this->hideGetDogDetailsGroupBox();
    this->controller.write_to_file_controller("dogs.txt");
    this->showMainPushButtons();
}

void AdminMenuWidget::addDogGUI() const {
    this->hideMainPushButtons();
    this->addDogGroupBox->show();
    this->getDogDetailsGroupBox->show();
}

void AdminMenuWidget::setUpRemoveGroupBox() {
    this->removeDogGroupBox = new QGroupBox("Remove dog", this);

    this->nameOfDogToDelete = new QLineEdit();
    this->removeFormLayout = new QFormLayout();
    this->removeFormLayout->addRow("Name of dog to Remove", nameOfDogToDelete);

    auto vbox = new QVBoxLayout();
    vbox->addLayout(removeFormLayout);

    removeDogDetailsButton = new QPushButton("Remove dog", removeDogGroupBox);
    vbox->addWidget(removeDogDetailsButton);
    connect(removeDogDetailsButton, &QPushButton::clicked, this, &AdminMenuWidget::removeDogDetails);

    removeDogGroupBox->setLayout(vbox);
    mainLayout->addWidget(removeDogGroupBox);

    this->removeDogGroupBox->hide();
}

void AdminMenuWidget::removeDogDetails() {
    QString name = this->nameOfDogToDelete->text();

    bool result = this->controller.give_Dog_by_name_controller(name.toStdString());
    if (!result) {
        QMessageBox::information(nullptr, "Error", QString::fromUtf8("Cannot find dog with this name.\n"));
    }

    this->controller.write_to_file_controller("dogs.txt");
    this->removeDogGroupBox->hide();
    this->showMainPushButtons();
}

void AdminMenuWidget::undoGUI()
{
    controller.undo();
    QMessageBox::information(nullptr, "Undo SUCCESS", QString::fromUtf8("Undo operation executed successfully."));
}

void AdminMenuWidget::redoGUI()
{
    controller.redo();
    QMessageBox::information(nullptr, "Redo SUCCESS", QString::fromUtf8("Redo operation executed successfully."));
}

void AdminMenuWidget::removeDogGUI() const {
    this->hideMainPushButtons();
    this->removeDogGroupBox->show();
}

void AdminMenuWidget::updateDogGUI() const {
    this->hideMainPushButtons();
    this->updateDogGroupBox->show();
}

void AdminMenuWidget::setUpUpdateGroupBox() {
    this->updateDogGroupBox = new QGroupBox("Update dog", this);
    this->indexOfDogToUpdate = new QLineEdit();

    this->updateFormLayout = new QFormLayout();
    this->updateFormLayout->addRow("Index of dog to update", indexOfDogToUpdate);

    auto vbox = new QVBoxLayout();
    vbox->addLayout(updateFormLayout);

    updateDogDetailsButton = new QPushButton("Update Dog", updateDogGroupBox);
    vbox->addWidget(updateDogDetailsButton);
    connect(updateDogDetailsButton, &QPushButton::clicked, this, &AdminMenuWidget::updateDogDetails);

    updateDogGroupBox->setLayout(vbox);
    mainLayout->addWidget(updateDogGroupBox);

    this->updateDogGroupBox->hide();
}

void AdminMenuWidget::updateDogDetails() {
    int index = this->indexOfDogToUpdate->text().toInt();
    QString breed = breedLine->text();
    QString name = nameLine->text();
    QString link = linkLine->text();
    int age = ageLine->text().toInt();

    try {
        this->controller.update_Dog_by_index_controller(index, breed.toStdString(), name.toStdString(), age, link.toStdString());
    }
    catch (Exception& e) {
        QMessageBox::information(nullptr, "Error", QString::fromUtf8(e.what()));
    }

    getDogDetailsGroupBox->hide();
    this->hideGetDogDetailsGroupBox();
    this->controller.write_to_file_controller("dogs.txt");
    showMainPushButtons();
}

void AdminMenuWidget::listDogsGUI() {
    this->hideMainPushButtons();
    this->controller.read_from_file_controller("dogs.txt");
    vector<TElem> dogs = controller.pass_dogs_controller();

    this->tableWidget->setRowCount(dogs.size());
    this->tableWidget->setColumnCount(4);

    QStringList headers = { "Breed", "Name", "Age", "Photograph link" };
    this->tableWidget->setHorizontalHeaderLabels(headers);

    for (int i = 0; i < dogs.size(); i++) {
        TElem dog = dogs[i];
        this->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(dog->getBreed())));
        this->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(dog->getName())));
        this->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(dog->getAge())));
        this->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(dog->getPhotograph())));
    }

    this->mainLayout->addWidget(this->tableWidget);
    this->mainLayout->setStretchFactor(this->tableWidget, 3);
    this->tableWidget->show();
    this->mainLayout->addWidget(this->backPushButton);
    this->mainLayout->setStretchFactor(this->backPushButton, 1);
    this->backPushButton->show();
}

void AdminMenuWidget::backToAdminMenu() const {
    this->tableWidget->hide();
    this->backPushButton->hide();
    this->showMainPushButtons();
}