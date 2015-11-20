#pragma once
#include "QUtil.h"

class GUI: public QWidget
{
public:
	void initialize() ;
	~GUI();
	GUI();
private:

	QHBoxLayout * mainLayout;

	QGroupBox * fileSystem;
	QGroupBox * layerHandlers;
	QGroupBox * UICreation;
	QGroupBox * archtypeManager;

	
	mapButtons buttons;
	mapComboBox comboBox;
	mapQlineEdit lineEdits;

	mapSliders sliders;

	QPushButton * getButton(std::string);
	QComboBox * getComboBox(std::string, QWidget * ptr);
	QLineEdit * getLineEdit(std::string);

	QSlider * getSlider(std::string name);
	QWidget * createButton(std::string key,				                  // key val for the map
		std::string buttoneName,						                  // this saves the name of the button													        
		glm::vec2 position = glm::vec2(0),				                  // this saves the position of the button												            
		glm::vec2 scale = glm::vec2(80, 20)				                  // this scales the button;
		);
	QLineEdit * createLineEdit(std::string key,                           // key val for the map
		glm::vec2 position,								                  // this saves the position of the button
		glm::vec2 scale,								                  // this scales the button
		std::string lineEditName = ""					                  // this saves the name of the button
		);

	QLabel * createLabel(std::string,
		glm::vec2                    // position
		);

	QSlider * createSlider(std::string name);

	bool projectIsloaded;

	/*checks whether the project is loaded or a new project is created*/
	bool checkProjectCreationStatus();
	/*set status of the project*/
	void setStatus(bool status);

	
};

