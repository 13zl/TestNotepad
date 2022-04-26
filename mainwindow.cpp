#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::newDocument);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::Open);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::Save);
    connect(ui->actionSaveAs, &QAction::triggered, this, &MainWindow::SaveAs);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::About);

    Init();
}

void MainWindow::newDocument()
{
    currentFilePathName.clear();
    ui->textEdit->setText(QString());
}

void MainWindow::Init()
{
    QString fileName = ":/hello";
    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::Open()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    currentFilePathName = fileName;

    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::information(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::Save()
{
    QString fileName;

// If we don't have a filename from before, get one.
    if (currentFilePathName.isEmpty())
    {
        fileName = QFileDialog::getSaveFileName(this, "Save");
        currentFilePathName = fileName;
    }
    else
    {
        fileName = currentFilePathName;
    }

    QFile file(fileName);

    if(!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void MainWindow::SaveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    currentFilePathName = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void MainWindow::About()
{
    QMessageBox::information(this, "About Notepad", " Notepad\n version 25.04.2022\n Test task!");
}

MainWindow::~MainWindow()
{
    delete ui;
}
