/*
dialog.cpp

Created On: November 15th
Author: Nicholas Wan
*/
#include "dialog.h"
//#include "../SaccadeDetector.cpp"
//#include "../Scan.cpp"
//#include "../Saccade.cpp"
//#include "../ScanParser.cpp"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    data = new QString("Need some data");

    fileLabel = new QLabel("File: ");
    chooseFileBox = new QComboBox();
    chooseFileBox -> addItem("step008");
    chooseFileBox -> addItem("step012");
    chooseFileBox -> addItem("step066");
    chooseFileBox -> addItem("step069");

    chooseFileButton = new QPushButton("Choose File");
    chooseFileButton->setDefault(true);
    chooseFileButton->setEnabled(false);

    displayArea = new QTextEdit();

    connect(chooseFileBox ,SIGNAL(activated(const QString &)),
            this, SLOT(changeSelectedFile(const QString &)));

    connect(chooseFileButton, SIGNAL(clicked()),
            this, SLOT(submitClicked()));

    QHBoxLayout *chooseLayout = new QHBoxLayout;
    chooseLayout -> addWidget(fileLabel);
    chooseLayout -> addWidget(chooseFileBox);
    chooseLayout -> addWidget(chooseFileButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout -> addLayout(chooseLayout);
    mainLayout -> addWidget(displayArea);

    setLayout(mainLayout);

    setWindowTitle("Eye data detector");
}

Dialog::~Dialog()
{

}

void Dialog::changeSelectedFile(const QString &text)
{
    std::string a = text.toStdString();
    std::string fileName = chooseFileBox -> currentText().toStdString();
    chooseFileButton -> setEnabled(true);

    //here goes the code to select the file and generate corresponding data
}

void Dialog::submitClicked()
{
    displayArea->setReadOnly(true);
    displayArea->setText( *data );
}

QString* Dialog::generateData(string fileName)
{
    QString* theString = new QString();
    //theString->append("Filename:");
    //generate the saccade vector;
    //ScanParser* theData = new Scanparser(fileName);
    //SaccadeDetector* theDetector = new SaccadeDetector(theData) ;
    //vector<Saccade>* theVector = theDetector->getSaccades();

    return theString;
}

