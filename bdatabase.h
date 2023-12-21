#ifndef BDATABASE_H
#define BDATABASE_H

#include "qqmlintegration.h"
#include <QObject>
#include <QSqlDatabase>

#include <QMetaType>
#include <QVariantMap>

Q_DECLARE_METATYPE(QVariantMap)

class BDatabase : public QObject{
    Q_OBJECT
    QML_ELEMENT
    Q_DISABLE_COPY(BDatabase)

signals:
    void numberChanged();

public slots:
    void connect(const QString username, const QString password, const QString hostName, const QString DatabaseName);
    void connect(const QString filePath);
    void disconnect();
    bool isConnected();
    QList<QVariantMap> execute(const QString queryStr);

public:
    explicit BDatabase(QObject *parent = nullptr);
    ~BDatabase() override;

private:
};

#endif // BDATABASE_H
