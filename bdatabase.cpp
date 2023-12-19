#include "bdatabase.h"

#include <QPainter>
#include <QQmlEngine>
#include <QSettings>
#include <QSqlQuery>
#include <QSqlError>

#include <QDebug>

BDatabase::BDatabase(QObject *parent):
    QObject(parent)
{
    qDebug() << "costruttore";
}

BDatabase::~BDatabase(){
    qDebug() << "distruttore";
}

void BDatabase::connect(const QString username, const QString password, const QString hostName, const QString DatabaseName){
    qDebug()<<"connecting...";

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setUserName(username);
    db.setPassword(password);
    db.setHostName(hostName);
    db.setDatabaseName(DatabaseName);

    if(!db.open()){
        qmlEngine(this)->throwError(tr("invalid database credentials"));
    }

    qDebug()<<"connected";
}

void BDatabase::connect(const QString filePath){

    QSettings settings(filePath, QSettings::IniFormat);

    settings.beginGroup("database");
    const QString username = settings.value("username").toString();
    const QString password = settings.value("password").toString();
    const QString host = settings.value("host").toString();
    const QString database = settings.value("database").toString();
    settings.endGroup();

    connect(username, password, host, database);
}

void BDatabase::disconnect(){
    QSqlDatabase::database().close();
}

bool BDatabase::isConnected(){
    return QSqlDatabase::database().isOpen();
}

bool BDatabase::execute(const QString queryStr){

    QSqlQuery query(QSqlDatabase::database());

    if(!query.exec(queryStr)){
        qDebug() << "Error executing query:" << query.lastError().text();
        return false;
    }

    //save the result

    return true;
}
