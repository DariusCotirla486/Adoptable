#pragma once
#include "GUI.h"

class AdminMenuWidget : public QWidget {
    Q_OBJECT
protected:
    Controller controller;

public:
    explicit AdminMenuWidget(QWidget* parent = nullptr, Controller controller = Controller());
    void setUpGetDogDetailsGroupBox();
    void hideGetDogDetailsGroupBox() const;

    QGroupBox* addDogGroupBox;
    QPushButton* addDogDetailsButton;
    void setUpAddGroupBox();

    QGroupBox* removeDogGroupBox;
    QPushButton* removeDogDetailsButton;
    QLineEdit* nameOfDogToDelete;
    void setUpRemoveGroupBox();

    QGroupBox* updateDogGroupBox;
    QPushButton* updateDogDetailsButton;
    QLineEdit* indexOfDogToUpdate;
    void setUpUpdateGroupBox();

    void showMainPushButtons() const;
    void hideMainPushButtons() const;

    const QSize buttonSize = QSize(300, 100);
    QPushButton* addDogButton;
    QPushButton* removeDogButton;
    QPushButton* updateDogButton;
    QPushButton* listAllDogsButton;
    QPushButton* undoButton;
    QPushButton* redoButton;
    QPushButton* backPushButton;

    QVBoxLayout* mainLayout;
    QVBoxLayout* optionsLayout;

    QFormLayout* addFormLayout;
    QFormLayout* removeFormLayout;
    QFormLayout* updateFormLayout;
    QTableWidget* tableWidget;

    QGroupBox* getDogDetailsGroupBox;
    QLineEdit* breedLine;
    QLineEdit* nameLine;
    QLineEdit* linkLine;
    QLineEdit* ageLine;

public slots:
    void addDogGUI() const;
    void removeDogGUI() const;
    void updateDogGUI() const;
    void listDogsGUI();
    void undoGUI();
    void redoGUI();
    void addDogDetails();
    void removeDogDetails();
    void updateDogDetails();
    void backToAdminMenu() const;
};