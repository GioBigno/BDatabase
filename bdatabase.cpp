#include "bdatabase.h"

#include <QPainter>
#include <QQmlEngine>
#include <QSettings>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariantMap>
#include <QVariant>

#include <QDebug>

BDatabase::BDatabase(QObject *parent):
    QObject(parent)
{
    qDebug() << "costruttore";
}

BDatabase::~BDatabase(){
    qDebug() << "distruttore";
}

BDatabase::DbType BDatabase::databaseType(){
    return m_databaseType;
}

void BDatabase::setDatabaseType(const DbType t){

    if(m_databaseType == t)
        return;

    m_databaseType = t;
    emit databaseTypeChanged();
}

void BDatabase::connect(const QString username, const QString password, const QString hostName, const QString DatabaseName){

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setUserName(username);
    db.setPassword(password);
    db.setHostName(hostName);
    db.setDatabaseName(DatabaseName);

    if(!db.open()){
        qmlEngine(this)->throwError(tr("invalid database credentials"));
    }
}

void BDatabase::connect(const QString filePath){

    qDebug()<<"connecting...";

    switch(m_databaseType){
        case QPSQL: {
            QSettings settings(filePath, QSettings::IniFormat);

            settings.beginGroup("database");
            const QString username = settings.value("username").toString();
            const QString password = settings.value("password").toString();
            const QString host = settings.value("host").toString();
            const QString database = settings.value("database").toString();
            settings.endGroup();

            connect(username, password, host, database);
        }
        break;
        case QSQLITE: {
            QSqlDatabase db = QSqlDatabase::addDatabase(DbTypeToString(DbType::QSQLITE));
            db.setDatabaseName(filePath);

            if(!db.open()){
                qmlEngine(this)->throwError(tr("invalid database file path"));
            }
        }
    }

    qDebug()<<"connected";
}

void BDatabase::disconnect(){
    QSqlDatabase::database().close();
}

bool BDatabase::isConnected(){
    return QSqlDatabase::database().isOpen();
}

QList<QVariantMap> BDatabase::execute(const QString queryStr){

    QSqlQuery query(QSqlDatabase::database());
    QList<QVariantMap> resultList;

    if(!query.exec(queryStr)){
        qDebug() << "Error executing query:" << query.lastError().text();
        return resultList;
    }

    while (query.next()) {

        QVariantMap row;
        for (int i = 0; i < query.record().count(); ++i) {
            QString columnName = query.record().fieldName(i);
            QVariant value = query.value(i);

            qDebug() << "valore: " << value;

            row.insert(columnName, value);
        }
        resultList.append(row);

    }

    return resultList;
}

const QString BDatabase::DbTypeToString(const DbType dbType) const{
    switch (dbType) {
    case QPSQL:
        return "QPSQL";
    case QSQLITE:
        return "QSQLITE";
    default:
        return "Unknown";
    }
}
