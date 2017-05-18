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

void MainWindow::on_openFolderButton_clicked()
{
    // Display an open folder dialog if the "Open Folder" button was pressed
    QString folder_name = QFileDialog::getExistingDirectory(this, tr("Open Folder"), "/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->log->appendPlainText(folder_name);
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
    // Display an open folder dialog if the "Open Folder" action button was pressed
    QString folder_name = QFileDialog::getExistingDirectory(this, tr("Open Folder"), "/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->log->appendPlainText(folder_name);
}
