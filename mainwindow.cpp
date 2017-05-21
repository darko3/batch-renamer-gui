#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authordialog.h"
#include "renamer.h"

#include <QThread>
#include <QFileDialog>
#include <QMessageBox>
#include <QSignalMapper>


QString folder_name;
bool renameInProgress = false;

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
    QThread* thread = new QThread;
    Renamer* renamer = new Renamer();
    renamer->moveToThread(thread);

    connect(renamer, SIGNAL(renamedFile(QString)), this, SLOT(onFileRenamed(QString)));
    connect(renamer, SIGNAL(error(QString,QString)), this, SLOT(onError(QString,QString)));
    connect(renamer, SIGNAL(finished(QString,QString)), this, SLOT(onSuccess(QString,QString)));

    QSignalMapper* signalMapper = new QSignalMapper(this);
    connect(thread, SIGNAL(started()), signalMapper, SLOT(map()));

    signalMapper->setMapping(thread, folder_name);
    connect(signalMapper, SIGNAL(mapped(QString)), renamer, SLOT(startRenamer(QString)));

    if(renameInProgress) {
        // If the rename is in progress, ask the user if they would like to stop the rename process
        QMessageBox::StandardButton renameStopDialog;
        renameStopDialog = QMessageBox::question(this, "Rename in Progress",
                                                 "Are you sure you want to stop the rename process?",
                                                 QMessageBox::Yes | QMessageBox::No);
        if(renameStopDialog == QMessageBox::Yes) {
            // Stop the rename process if the yes button was clicked
            thread->terminate();
        } else {
            // Don't do anything if something else was clicked
        }
    } else {
        // Scan the selected directory and start renaming files in the directory
        if(folder_name == "") {
            // Show a messagebox telling the user that no folder was selected
            QMessageBox::critical(this, "No folder selected",
                                  "You must select a folder before continuing.");
        } else {
            renameInProgress = true;

            if(renameInProgress) {
                ui->renameButton->setText("Stop Renaming");
            }

            thread->start();
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

void MainWindow::onFileRenamed(QString file_name)
{
    ui->log->appendPlainText("Renamed file: " + file_name);
}

void MainWindow::onError(QString title, QString description)
{
    QMessageBox::critical(this, title, description);
}

void MainWindow::onSuccess(QString title, QString description)
{
    renameInProgress = false;
    if(!renameInProgress) {
        ui->renameButton->setText("Start Renaming");
    }

    QMessageBox::information(this, title, description);
}
