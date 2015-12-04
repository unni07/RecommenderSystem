#pragma once
#include "QUtil.h"

class GUI: public QDialog
{
	Q_OBJECT
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
	mapCheckBox checkBoxes;
	mapSliders sliders;

	QPushButton * getButton(std::string);
	QComboBox * getComboBox(std::string, QWidget * ptr);
	QLineEdit * getLineEdit(std::string);
	QTextEdit * getTextEdit(std::string);

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

	QCheckBox * createCheckBox(std::string key,
							   std::string boxName,
							   glm::vec2 position = glm::vec2(0),
							   bool checked = false);

	QSlider * createSlider(std::string name);

	bool projectIsloaded;

	/*checks whether the project is loaded or a new project is created*/
	bool checkProjectCreationStatus() const;
	/*set status of the project*/
	void setStatus(bool status);
	/*Connect the buttons*/
	void connectToTask();
	/*show output*/
	void showOutput(std::vector<std::string> output);
	/*to read the feature lsist*/
	void readFeatureList();
	/*Display the output*/
	void Display(const std::vector<std::string>& output);
private:
	std::map<std::string, std::vector<std::string>> featureList;
private slots:
	/*function to call Search*/
	void search();
	/*check check boxes selected*/
	void checkBoxSelected();
	/*to display recommended list*/
	void recommendation(const std::map<std::string, std::vector<std::string>>& output);
	QGroupBox * outputButtons;
	
};

