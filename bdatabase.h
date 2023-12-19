#ifndef BDATABASE_H
#define BDATABASE_H

#include "qqmlintegration.h"
#include <QObject>
#include <QSqlDatabase>

class BDatabase : public QObject{
    Q_OBJECT
    QML_ELEMENT
    Q_DISABLE_COPY(BDatabase)

signals:
    void numberChanged();

public slots:
    //start connection by passing credentials
    void start(const QString username, const QString password, const QString hostName, const QString DatabaseName);
    //start connection by reading credentials from config file
    void start(const QString filePath);

public:
    explicit BDatabase(QObject *parent = nullptr);
    ~BDatabase() override;

private:
    QSqlDatabase db;
};

#endif // BDATABASE_H
