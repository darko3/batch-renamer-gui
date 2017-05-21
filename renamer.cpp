#include "renamer.h"

#include <QDir>
#include <QThread>

Renamer::Renamer(QObject *parent) : QObject(parent)
{

}

void Renamer::startRenamer(QString folder_name)
{
    // Create a QDir object
    QDir dir(folder_name);

    // Filter to display only files
    dir.setFilter(QDir::Files);

    // File counter
    int file_count = 0;

    // if a folder was selected, check if the folder exists
    if(dir.exists()) {
        // if the folder selected exists, start the rename process
        foreach (QFileInfo file, dir.entryInfoList()) {
            // Emit a signal to the main thread telling that a file was renamed
            emit renamedFile(file.absoluteFilePath());

            // Add 1 to the file counter
            file_count += 1;
        }
    } else {
        // if the folder selected doesn't exist, inform the user about it with a messagebox
        emit error("Folder doesn't exist",
                   "The folder you selected does not exist. Please select a valid folder.");
    }
    emit finished("Successfully renamed " + QString::number(file_count) + " files. " + QString::number(dir.count()),
                  "Successfully finished renaming " + QString::number(file_count) + " files.");
}
