#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAuthor_triggered();
    void on_openFolderButton_clicked();

    void on_actionOpen_Folder_triggered();

    void on_actionExit_triggered();
    QString selectFolder();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
