#ifndef RENAMER_H
#define RENAMER_H

#include <QObject>

class Renamer : public QObject
{
    Q_OBJECT
public:
    explicit Renamer(QObject *parent = 0);

signals:
    void renamedFile(QString file);
    void error(QString title, QString description);
    void finished(QString title, QString description);

public slots:
    void startRenamer(QString folder_name);
};

#endif // RENAMER_H
