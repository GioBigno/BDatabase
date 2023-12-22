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

    Q_PROPERTY(DbType databaseType READ databaseType WRITE setDatabaseType NOTIFY databaseTypeChanged REQUIRED)

signals:
    void databaseTypeChanged();

public:
    explicit BDatabase(QObject *parent = nullptr);
    ~BDatabase() override;

    enum DbType{
        QPSQL,
        QSQLITE
    };

    Q_ENUM(DbType)

public slots:
    DbType databaseType();
    void setDatabaseType(const DbType t);
    void connect(const QString username, const QString password, const QString hostName, const QString DatabaseName);
    void connect(const QString filePath);
    void disconnect();
    bool isConnected();
    QList<QVariantMap> execute(const QString queryStr);

private:
    DbType m_databaseType;

    const QString DbTypeToString(const DbType dbType) const;

};

#endif // BDATABASE_H
