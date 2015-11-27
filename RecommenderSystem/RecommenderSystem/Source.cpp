#include "precompiled.h"
#include "GUI.h"

#include "Features.h"
#include "City.h"
int main(int argc, char* argv[])
{
	FeatureDatabase::Initialize();
	CityDatabase::Initialize();

	QApplication mainApplication(argc, argv);
	GUI g;
	g.show();
	g.initialize();
	mainApplication.exec();
	
}
