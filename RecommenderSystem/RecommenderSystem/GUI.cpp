#include "precompiled.h"
#include "GUI.h"
#include "KeyWordSearch.h"


void GUI::initialize() 
{
	KeyWordSearch::getInstance().initialize();
	QGroupBox * input = new QGroupBox("Input");
	QHBoxLayout * inputArea = new QHBoxLayout();
	int width = this->width();
	int height = this->height();
	auto inputTextEdit =  createLineEdit("input", { 0.03f*width ,0.05f* height }, { 200,15 });
	inputTextEdit->setParent(this);
	auto recommnedButton = createButton("RecommendButton", "Find", { 0.5f * width, 0.05* height }, { 50,20 });
	recommnedButton->setParent(this);

	inputArea->addWidget(inputTextEdit);
	inputArea->addWidget(recommnedButton);
	inputArea->addStretch(1);
	input->setLayout(inputArea);

	QGroupBox * output = new QGroupBox("Output");
	QGroupBox * outputButtons = new QGroupBox("Output");
	QHBoxLayout * outputArea = new QHBoxLayout();
	auto outputTextEdit = createLineEdit("output", { 0.03f*width ,0.05f* height }, { 500,500 });
	outputTextEdit->setParent(this);
	outputArea->addWidget(outputTextEdit);
	
	QVBoxLayout * outputButtonArea = new QVBoxLayout();
	auto button1 = createCheckBox("button1", "button1", { 0,0 },false);
	auto button2 = createCheckBox("button2", "button2", { 0,0 },false);
	auto button3 = createCheckBox("button3", "button3", { 0,0 },false);
	auto button4 = createCheckBox("button4", "button4", { 0,0 },false);
	button1->setParent(this);
	button2->setParent(this);
	button3->setParent(this);
	button4->setParent(this);
	outputButtonArea->addWidget(button1);
	outputButtonArea->addWidget(button2);
	outputButtonArea->addWidget(button3);
	outputButtonArea->addWidget(button4);
	outputButtonArea->addStretch(1);
	outputButtons->setLayout(outputButtonArea);
	outputArea->addWidget(outputButtons);

	output->setLayout(outputArea);
	outputArea->addStretch(1);
	mainLayout->addWidget(input);
	mainLayout->addWidget(output);
	mainLayout->addStretch(1);

	connectToTask();
}





GUI::~GUI()
{
}

GUI::GUI()
{
	mainLayout = new QVBoxLayout(this);
	this->resize(800, 600);
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

QCheckBox* GUI::createCheckBox(std::string key, std::string boxName, glm::vec2 position, bool checked)
{
	auto checkBox = checkBoxes.find(key);
	if(checkBox == checkBoxes.end())
	{
		auto newCheckBox = QUtil::instance().createCheckbox(boxName, position, checked);
		checkBoxes[key] = newCheckBox;
		return newCheckBox;
	}
	return checkBox->second;
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


bool  GUI::checkProjectCreationStatus() const
{
	return projectIsloaded;
}

void GUI::connectToTask()
{
	auto find = getButton("RecommendButton");
	 
	QObject::connect(find,SIGNAL(clicked()),this,SLOT(search()));
}

void GUI::search()
{
	auto textEdit = getLineEdit("input");
	auto qSearchString = textEdit->text();
	if(qSearchString.size() == 0)
	{
		return;
	}
	std::string searchString = QUtil::instance().convertQStringtoStdString(qSearchString);
	KeyWordSearch::getInstance().search(searchString);
	checkBoxSelected();
}

void GUI::checkBoxSelected()
{
	auto itr = checkBoxes.begin();
	auto itrEnd = checkBoxes.end();
	std::vector<std::string> checkedBoxes;
	while(itr != itrEnd)
	{
		if(itr->second->isChecked())
		{
			checkedBoxes.push_back(QUtil::instance().convertQStringtoStdString(itr->second->text()));
		}
		++itr;
	}
}

