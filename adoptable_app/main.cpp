#include "GUI.h"
#include "UserInterface.h"


int main(int argc, char** argv) {
	QApplication a(argc, argv);
	MainWidget mainWidget;
	mainWidget.show();
	return a.exec();
}