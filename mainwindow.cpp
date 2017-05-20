#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authordialog.h"

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>


QString folder_name;

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
    folder_name = QFileDialog::getExistingDirectory(this, tr("Open Folder"), "/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    return folder_name;
}

void MainWindow::on_openFolderButton_clicked()
{
    // Display an open folder dialog if the "Open Folder" button was pressed
    folder_name = selectFolder();
    if(folder_name != "") {
        ui->log->appendPlainText("Selected folder: \"" + folder_name + "\"");
    }
}

void MainWindow::on_renameButton_clicked()
{
    // Scan the selected directory and start renaming files in the directory
    if(folder_name == "") {
        // Show a messagebox telling the user that no folder was selected
        QMessageBox::critical(this, "No folder selected",
                              "You must select a folder before continuing.");
    } else {
        // Create a QDir object
        QDir dir(folder_name);
        // if a folder was selected, check if the folder exists
        if(dir.exists()) {
            // if the folder selected exists, start the rename process
            QMessageBox::information(this, "Folder exists",
                                  "The folder you selected exists. Folder selected: " + folder_name);
        } else {
            // if the folder selected doesn't exist, inform the user about it with a messagebox
            QMessageBox::critical(this, "Folder doesn't exist",
                                  "The folder you selected does not exist. Please select a valid folder.");
        }
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
