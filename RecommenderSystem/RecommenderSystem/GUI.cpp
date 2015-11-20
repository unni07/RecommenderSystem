#include "precompiled.h"
#include "GUI.h"


void GUI::initialize() 
{
	QHBoxLayout * mainLayout = new QHBoxLayout(this);

	fileSystem = new QGroupBox("File");
	QVBoxLayout * fileSystemLayout = new QVBoxLayout();
	auto newProject = createButton("New Project", "New Project");
	newProject->setParent(fileSystem);
	auto load = createButton("Load", "Load");
	load->setParent(fileSystem);
	auto save = createButton("Save", "Save");
	save->setParent(fileSystem);
	fileSystemLayout->addWidget(newProject);
	fileSystemLayout->addWidget(load);
	fileSystemLayout->addWidget(save);
	//fileSystemLayout->addStretch(1);
	fileSystem->setLayout(fileSystemLayout);

	layerHandlers = new QGroupBox("Layers");
	QVBoxLayout * layoutLayers = new QVBoxLayout();
	
	auto slider = createSlider("Radius Control");
	slider->setTickInterval(1);
	slider->setOrientation(Qt::Horizontal);
	slider->setTickPosition(QSlider::TicksBelow);
	slider->setRange(0, 9);
	slider->setSingleStep(1);

	layoutLayers->addWidget(slider);
	layerHandlers->setLayout(layoutLayers);
	fileSystemLayout->addWidget(layerHandlers);
	fileSystemLayout->addStretch(1);
	//layerHandlers->setVisible(false);

	UICreation = new QGroupBox("User Interface");
	QVBoxLayout * levelCreationLayout = new QVBoxLayout();
	auto CreateButton = createButton("Create Button", "Create Button"); // temporary for testing flexibility
	auto createNewGameObject = createButton("New GameObject", "New GameObject");
	auto edit = createButton("Edit", "Edit");
	auto erase = createButton("Erase", "Erase");
	levelCreationLayout->addWidget(CreateButton);
	levelCreationLayout->addWidget(createNewGameObject);
	levelCreationLayout->addWidget(edit);
	levelCreationLayout->addWidget(erase);
	levelCreationLayout->addStretch(1);
	UICreation->setLayout(levelCreationLayout);
	UICreation->setVisible(false);


	//levelCreationLayout->addWidget(archtypeManager);
	levelCreationLayout->addStretch(1);
	archtypeManager->setVisible(false);

	/*mainLayout->addWidget(fileSystem);
	mainLayout->addWidget(layerHandlers);*/

	/*mainLayout->addWidget(fileSystem);
	mainLayout->addWidget(window = MainWindow::instance());
	mainLayout->addWidget(UICreation);*/

	mainLayout->addWidget(fileSystem);
	//	mainLayout->addWidget(layerHandlers);
	
	mainLayout->addWidget(UICreation);
	mainLayout->addWidget(archtypeManager);
}





GUI::~GUI()
{
}

GUI::GUI()
{
}










QSlider* GUI::getSlider(std::string name)
{
	auto required = sliders.find(name);
	return required->second;
}

QPushButton*   GUI::getButton(std::string buttonName)
{
	auto required = buttons.find(buttonName);
	return required->second;

}

QComboBox* GUI::getComboBox(std::string buttonName, QWidget * ptr)
{
	auto required = comboBox.find(buttonName);
	return required->second;
}

QLineEdit* GUI::getLineEdit(std::string lineEditName)
{

	auto required = lineEdits.find(lineEditName);
	return required->second;
}

QWidget*   GUI::createButton(std::string key, std::string buttonName, glm::vec2 position, glm::vec2 scale)
{
	mapButtons::iterator itrBeg = buttons.begin();
	mapButtons::iterator itrEnd = buttons.end();
	auto required = buttons.find(key);
	if (required == itrEnd)
	{
		//auto w = QUtil::instance().createPushButton(buttonName, position, scale)->width();
		buttons[key] = QUtil::instance().createPushButton(buttonName, position, scale);
		return buttons[key];
	}
	return required->second;

}

QLineEdit*GUI::createLineEdit(std::string key, glm::vec2 position, glm::vec2 scale, std::string lineEditName)
{
	mapQlineEdit::iterator itrBeg = lineEdits.begin();
	mapQlineEdit::iterator itrEnd = lineEdits.end();
	auto required = lineEdits.find(key);
	if (required == itrEnd)
	{
		lineEdits[key] = QUtil::instance().createLineEdit(lineEditName, position, scale);
		return lineEdits[key];
	}

	return required->second;
}

QSlider* GUI::createSlider(std::string name)
{
	auto itrEnd = sliders.end();
	auto required = sliders.find(name);
	if (required == itrEnd)
	{
		auto slider = QUtil::instance().createSlider();
		sliders[name] = slider;
		return sliders[name];
	}

	return required->second;
}


bool  GUI::checkProjectCreationStatus()
{
	return projectIsloaded;
}




