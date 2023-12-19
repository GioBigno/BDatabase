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
    void connect(const QString username, const QString password, const QString hostName, const QString DatabaseName);
    //start connection by reading credentials from config file
    void connect(const QString filePath);
    //closes the connection
    void disconnect();
    //state of the connection
    bool isConnected();
    //executes a query
    bool execute(const QString queryStr);

public:
    explicit BDatabase(QObject *parent = nullptr);
    ~BDatabase() override;

private:
};

#endif // BDATABASE_H
