#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
    this->path = QFileDialog::getOpenFileName();
    if(!path.isEmpty()) {
        QFile file(this->path);
        QString line;
        ui->textEdit->clear();
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream stream(&file);
            while (!stream.atEnd()){
                line = stream.readLine();
                ui->textEdit->setText(ui->textEdit->toPlainText() + line + "\n");
            }
        }
        file.close();
    }
}

void MainWindow::on_actionExit_triggered()
{
    exit(0);
}


void MainWindow::on_actionSave_triggered()
{
    if(!this->path.isEmpty())
    {
        QFile file(this->path);
        QString text;

        text = ui->textEdit->toPlainText();
        if(file.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QTextStream stream(&file);
            stream << text;
        }
    }
    else
    {
        QMessageBox msgBox;

        msgBox.setText("No file is opened! You should use the Save As option.");
        msgBox.setStandardButtons(QMessageBox::Close);
        msgBox.setDefaultButton(QMessageBox::Close);
        msgBox.exec();
    }
}


void MainWindow::on_actionSave_As_triggered()
{
    this->path = QFileDialog::getSaveFileName();
    QFile file(this->path);
    QString text;

    text = ui->textEdit->toPlainText();
    if(file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << text;
    }
}


void MainWindow::on_actionClose_triggered()
{
    ui->textEdit->clear();
    this->path = "";
}

