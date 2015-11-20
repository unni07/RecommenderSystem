#include "precompiled.h"
#include "GUI.h"


int main(int argc, char* argv[])
{
	QApplication mainApplication(argc, argv);
	GUI g;
	g.show();
	mainApplication.exec();
	
}
