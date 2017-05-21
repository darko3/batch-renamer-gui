#ifndef RENAMER_H
#define RENAMER_H

#include <QObject>

class Renamer : public QObject
{
    Q_OBJECT
public:
    explicit Renamer(QObject *parent = 0);

signals:

public slots:
};

#endif // RENAMER_H