#pragma once
#include <unordered_map>


typedef std::unordered_map<std::string, QPushButton*> mapButtons;
typedef std::unordered_map<std::string, QLineEdit*> mapQlineEdit;
typedef std::unordered_map<std::string, QComboBox*> mapComboBox;
typedef std::unordered_map<std::string, QCheckBox*> mapCheckBox;

typedef std::unordered_map<std::string, QTextEdit*> mpaTextDisplay;

typedef std::vector<QLabel*> listLabel;
typedef std::unordered_map<std::string, QSlider*> mapSliders;
enum GUIElements
{
	PushButtons = 0,
	ComboBox
};
class QUtil
{
public:
	static QUtil& instance();
	/*this function converts QString to std::string*/
	std::string convertQStringtoStdString(QString str);
	/*Convert string into glm::vectors*/
	
	/*this funtion will create a button*/
	QPushButton* createPushButton(std::string buttoneName = "",			     // this saves the name of the button
		                          glm::vec2 position = glm::vec2(0, 0),      // this saves the position of the button
		                          glm::vec2 scale = glm::vec2(60, 30)        // this scales the button
		                         );

	/*this function will create a line edit */
	QLineEdit * createLineEdit(std::string lineEditName= "",			     // this saves the name of the button
		                       glm::vec2 position = glm::vec2(0,0),      // this saves the position of the button
          					   glm::vec2 scale = glm::vec2(60,30)        // this scales the button
							  );

	QTextEdit * createTextDisplay(glm::vec2 position = glm::vec2(0), glm::vec2 scale = glm::vec2(100, 100), bool readOnly = false);

	QCheckBox * createCheckbox(std::string boxName = "",			     // this saves the name of the button
		glm::vec2 position = glm::vec2(0, 0),      // this saves the position of the button
		bool checked = false
		);
	QSlider * createSlider();
	/*update window width and height*/
	void updateDimension(int x, int y);
	/*creates a radio button with an ID and name*/
	QRadioButton * createRadioButton(std::string name);

private:
	QUtil();
	~QUtil();
	int windowWidth;
	int windowHeight;
	void convertStringToFlaot(std::string,float &val);
};

