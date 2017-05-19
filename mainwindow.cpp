#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authordialog.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::selectFolder()
{
    QString folder_name = QFileDialog::getExistingDirectory(this, tr("Open Folder"), "/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    return folder_name;
}

void MainWindow::on_openFolderButton_clicked()
{
    // Display an open folder dialog if the "Open Folder" button was pressed
    QString folder_name = selectFolder();
    if(folder_name != "") {
        ui->log->appendPlainText("Selected folder: \"" + folder_name + "\"");
    }
}

void MainWindow::on_actionAuthor_triggered()
{
    // Display a dialog with author information if author button was pressed
    AuthorDialog authorDialog;
    authorDialog.setModal(true);
    authorDialog.exec();
}

void MainWindow::on_actionOpen_Folder_triggered()
{
    on_openFolderButton_clicked();
}

void MainWindow::on_actionExit_triggered()
{
    // Exit the program if the exit action button was pressed
    MainWindow::close();
}
