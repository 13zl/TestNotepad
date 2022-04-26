#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void Init();

private slots:
    void newDocument(); // new - key word
    void Open();
    void Save();
    void SaveAs();
    void About();

private:
    Ui::MainWindow *ui;

    QString currentFilePathName;
    QString currentFileName;
};
#endif // MAINWINDOW_H
