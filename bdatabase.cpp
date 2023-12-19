#include "bdatabase.h"

#include <QPainter>
#include <QQmlEngine>
#include <QSettings>

#include <QDebug>

BDatabase::BDatabase(QObject *parent):
    QObject(parent)
{
    qDebug() << "costruttore";
}

BDatabase::~BDatabase(){
    qDebug() << "distruttore";
}

void BDatabase::start(const QString username, const QString password, const QString hostName, const QString DatabaseName){
    qDebug()<<"starto";

    db = QSqlDatabase::addDatabase("QPSQL");
    db.setUserName(username);
    db.setPassword(password);
    db.setHostName(hostName);
    db.setDatabaseName(DatabaseName);

    if(!db.open()){
        qmlEngine(this)->throwError(tr("invalid database credentials"));
    }
}

void BDatabase::start(const QString filePath){

    QSettings settings(filePath, QSettings::IniFormat);

    settings.beginGroup("database");
    const QString username = settings.value("username").toString();
    const QString password = settings.value("password").toString();
    const QString host = settings.value("host").toString();
    const QString database = settings.value("database").toString();
    settings.endGroup();

    start(username, password, host, database);
}

