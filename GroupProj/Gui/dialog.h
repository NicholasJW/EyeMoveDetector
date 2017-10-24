/*
dialog.h

Created On: November 15th
Author: Nicholas Wan
*/
#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <string>
using namespace std;


//class QLabel;
//class QComboBox;
//class QTextEdit;
//class QPushButton;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();
    QString* generateData(string fileName);

signals:
    void fileSelected(const QString &str);

private slots:
    void changeSelectedFile(const QString &text);
    void submitClicked();

private:
    QString *data;
    QLabel *fileLabel;
    QComboBox *chooseFileBox;
    QPushButton *chooseFileButton;
    QTextEdit *displayArea;

};

#endif // DIALOG_H
