#pragma once
#include "QUtil.h"

class GUI: public QDialog
{
public:
	void initialize() ;
	~GUI();
	GUI();
private:

	QVBoxLayout * mainLayout;

	QGroupBox * fileSystem;
	QGroupBox * layerHandlers;
	QGroupBox * UICreation;
	QGroupBox * archtypeManager;

	
	mapButtons buttons;
	mapComboBox comboBox;
	mapQlineEdit lineEdits;
	mpaTextDisplay textDisplays;
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

	QTextEdit * createTextDisplay(std::string key, glm::vec2 position = glm::vec2(0),glm::vec2 scale = glm::vec2(100,100),bool readOnly = false);

	QSlider * createSlider(std::string name);

	bool projectIsloaded;

	/*checks whether the project is loaded or a new project is created*/
	bool checkProjectCreationStatus() const;
	/*set status of the project*/
	void setStatus(bool status);

	
};

