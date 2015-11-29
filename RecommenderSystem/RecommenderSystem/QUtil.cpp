#include "precompiled.h"
#include "QUtil.h"


QUtil::QUtil()
{
}


QUtil::~QUtil()
{
}

QUtil& QUtil::instance()
{
	static QUtil util; 
	return util;
}

std::string QUtil::convertQStringtoStdString(QString str)
{
	auto data = str.toLocal8Bit();
	auto size = data.size();
	auto itrEnd = data.end();
	char* qstringToChar = new char[size];
	int i = 0;
	for (auto itr = data.begin(); itr != itrEnd; itr++)
	{
		qstringToChar[i] = *itr;
		i++;
	}
	std::string charTostring(qstringToChar, size);
	return charTostring;
}


QPushButton*  QUtil::createPushButton(std::string buttoneName,
	glm::vec2 position,
	glm::vec2 scale
	)
{
	QPushButton* button = new QPushButton(buttoneName.c_str());
	button->move(position.x, position.y);
	button->setFixedWidth(scale.x);
	button->setFixedHeight(scale.y);
	return button;
}

QLineEdit*  QUtil::createLineEdit(std::string lineEditname,
	glm::vec2 position,
	glm::vec2 scale
	)
{
	QLineEdit* lineEdit = new QLineEdit(lineEditname.c_str());
	lineEdit->show();
	lineEdit->move(position.x, position.y);
	lineEdit->setFixedWidth(scale.x);
	lineEdit->setFixedHeight(scale.y);
	return lineEdit;
}

QTextEdit * QUtil::createTextDisplay(glm::vec2 position, glm::vec2 scale, bool readOnly)
{
	QTextEdit * textedit = new QTextEdit();
	textedit->move(position.x, position.y);
	textedit->setFixedWidth(scale.x);
	textedit->setFixedHeight(scale.y);
	textedit->setReadOnly(readOnly);
	return textedit;
}

QSlider* QUtil::createSlider()
{
	QSlider * slider = new QSlider();
	return slider;
}

QRadioButton * QUtil::createRadioButton(std::string name)
{
	
	QRadioButton * radio = new QRadioButton(name.c_str());
	return radio;
}

void QUtil::updateDimension(int x, int y)
{
	windowWidth = x;
	windowHeight = y;
}

void QUtil::convertStringToFlaot(std::string valStr,float &val)
{
	std::stringstream ss(valStr);
	ss >> val;
}