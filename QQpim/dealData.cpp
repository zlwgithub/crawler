#include "dealData.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>
#include <iostream>
#include <qstring.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>


dealData::dealData()
{
}

dealData::~dealData()
{
}


QSqlDatabase database;

bool openDatabase() {

    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("ContactDataBase.db");
        database.setUserName("root");
        database.setPassword("123456");
    }
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        qDebug() << "open success";

    }
    return true;
}


bool dealData::dealJson(QString filepath)
{
    
    openDatabase();
    QSqlQuery sql_query;
    int id = 0;
    
    //判断路径以及是否正常打开
    if (filepath.isEmpty())
        return false;
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    //读取数据后关闭文件
    const QByteArray raw_data = file.readAll();
    file.close();

    //解析为Json文档
    QJsonParseError json_error;
    QJsonDocument json_doc = QJsonDocument::fromJson(raw_data, &json_error);

    //是否正常解析Json数据
    if (json_doc.isNull() || json_doc.isEmpty() || json_error.error != QJsonParseError::NoError)
        return false;

    //解析文档中的Object
    const QJsonObject json_obj = json_doc.object();
    QJsonValue vacrds = json_obj.value("vacrds");
    QJsonArray vacrdsArray = vacrds.toArray();
    for (int i = 0; i < vacrdsArray.size(); i++) {
        QJsonValue valueChild = vacrdsArray.at(i);
        QJsonObject vchild = valueChild.toObject();
        QJsonValue vcard = vchild.value("vcard");
        QJsonObject vcardChild = vcard.toObject();
        QJsonValue FN = vcardChild.value("FN");
        QJsonValue tel = vcardChild.value("TEL");
        QJsonArray FNArray = FN.toArray();
        QJsonArray telArray = tel.toArray();
        QString cName;
        QString phone;


        for (int j = 0; j < FNArray.size(); j++)
        {
            QJsonValue FNValue = FNArray.at(j);
            QJsonObject FNOj = FNValue.toObject();
            QJsonValue name = FNOj.value("VALUE");
            qDebug() << name.toString();
            cName = name.toString();
        }
        
        for (int k = 0; k < telArray.size(); k++) {
            QJsonValue telValue = telArray.at(k);
            QJsonObject telOj = telValue.toObject();
            QJsonValue tel = telOj.value("VALUE");
            qDebug() << tel.toString();
            phone = tel.toString();
        }

        QString insert_sql = "insert into contact values (?, ?, ?)";
        sql_query.prepare(insert_sql);
        sql_query.addBindValue(id);
        sql_query.addBindValue(cName);
        sql_query.addBindValue(phone);
        if (!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }
        else
        {
            qDebug() << "inserted success!";
        }
        qDebug() << id;
        id++;

    }
    database.close();
}

bool dealData::dealJsonStringContact(QString jsonString)
{
    openDatabase();
    QSqlQuery sql_query;
    

    //解析为Json文档
    QJsonParseError json_error;
    QJsonDocument json_doc = QJsonDocument::fromJson(jsonString.toUtf8(), &json_error);

    //是否正常解析Json数据
    if (json_doc.isNull() || json_doc.isEmpty() || json_error.error != QJsonParseError::NoError)
        return false;

    //解析文档中的Object
    const QJsonObject json_obj = json_doc.object();
    QJsonValue vacrds = json_obj.value("vacrds");
    QJsonArray vacrdsArray = vacrds.toArray();
    for (int i = 0; i < vacrdsArray.size(); i++) {
        QJsonValue valueChild = vacrdsArray.at(i);
        QJsonObject vchild = valueChild.toObject();
        QJsonValue vcard = vchild.value("vcard");
        QJsonObject vcardChild = vcard.toObject();
        QJsonValue FN = vcardChild.value("FN");
        QJsonValue tel = vcardChild.value("TEL");
        QJsonArray FNArray = FN.toArray();
        QJsonArray telArray = tel.toArray();
        QString cName;
        QString phone;


        for (int j = 0; j < FNArray.size(); j++)
        {
            QJsonValue FNValue = FNArray.at(j);
            QJsonObject FNOj = FNValue.toObject();
            QJsonValue name = FNOj.value("VALUE");
            qDebug() << name.toString();
            cName = name.toString();
        }

        for (int k = 0; k < telArray.size(); k++) {
            QJsonValue telValue = telArray.at(k);
            QJsonObject telOj = telValue.toObject();
            QJsonValue tel = telOj.value("VALUE");
            qDebug() << tel.toString();
            phone = tel.toString();
        }
        


        QString insert_sql = "insert into contact values (?, ?)";
        sql_query.prepare(insert_sql);
        /*sql_query.addBindValue(id);*/
        sql_query.addBindValue(cName);
        sql_query.addBindValue(phone);
        if (!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
            return false;
        }
        else
        {
            /*return true;*/
            qDebug() << "inserted success!";
        }
        /*qDebug() << id;
        id++;*/

    }
    database.close();
    return true;
}

bool dealData::dealJsonTel(QString filepath)
{
    openDatabase();
    QSqlQuery sql_query;
    int id = 0;
    //判断路径以及是否正常打开
    if (filepath.isEmpty())
        return false;
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    //读取数据后关闭文件
    const QByteArray raw_data = file.readAll();
    file.close();

    //解析为Json文档
    QJsonParseError json_error;
    QJsonDocument json_doc = QJsonDocument::fromJson(raw_data, &json_error);

    //是否正常解析Json数据
    if (json_doc.isNull() || json_doc.isEmpty() || json_error.error != QJsonParseError::NoError)
        return false;

    //解析文档中的Object
    const QJsonObject json_obj = json_doc.object();
    QJsonValue root = json_obj.value("info");
    QJsonObject info = root.toObject();

    QJsonValue pageCount = info.value("pageCount");
    qDebug() << pageCount.toInt();


    QJsonValue sub1 = info.value("VCALLLOG");
    QJsonArray vcalllogArray = sub1.toArray();
    QString nameValue;
    QString phoneValue;
    QString dateValue;
    QString timeValue;
    for (int i = 0; i < vcalllogArray.size(); i++) {
        QJsonValue sub2 = vcalllogArray.at(i);
        QJsonObject sub3 = sub2.toObject();
        QJsonValue N = sub3.value("N");
        QJsonArray NArray = N.toArray();
        QJsonObject sub4 = NArray[0].toObject();
        QJsonValue name = sub4.value("VALUE");
        qDebug() << name.toString();
        nameValue = name.toString();

        QJsonArray telArray = sub3.value("TEL").toArray();
        QJsonObject sub5 = telArray[0].toObject();
        QJsonValue phone = sub5.value("VALUE");
        qDebug() << phone.toString();
        phoneValue = phone.toString();

        QJsonArray dateArray = sub3.value("STARTTIME").toArray();
        QJsonObject sub6 = dateArray[0].toObject();
        QJsonValue date = sub6.value("VALUE");
        qDebug() << date.toString();
        dateValue = date.toString();
        

        QJsonValue time = sub3.value("lasttime");
        qDebug() << time.toString();
        timeValue = time.toString();


        QString insert_sql = "insert into callLog values (?, ?, ?, ?, ?)";
        sql_query.prepare(insert_sql);
        sql_query.addBindValue(id);
        sql_query.addBindValue(nameValue);
        sql_query.addBindValue(phoneValue);
        sql_query.addBindValue(dateValue);
        sql_query.addBindValue(timeValue);
        if (!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }
        else
        {
            qDebug() << "inserted success!";
        }
        qDebug() << id;
        id++;

    
    }
    database.close();
    return false;
}

bool dealData::dealJsonStringTel(QString jsonString)
{
    openDatabase();
    QSqlQuery sql_query;
    
    //解析为Json文档
    QJsonParseError json_error;
    QJsonDocument json_doc = QJsonDocument::fromJson(jsonString.toUtf8(), &json_error);

    //是否正常解析Json数据
    if (json_doc.isNull() || json_doc.isEmpty() || json_error.error != QJsonParseError::NoError)
        return false;

    //解析文档中的Object
    const QJsonObject json_obj = json_doc.object();
    QJsonValue root = json_obj.value("info");
    QJsonObject info = root.toObject();

    QJsonValue pageCount = info.value("pageCount");
    qDebug() << pageCount.toInt();


    QJsonValue sub1 = info.value("VCALLLOG");
    QJsonArray vcalllogArray = sub1.toArray();
    QString nameValue;
    QString phoneValue;
    QString dateValue;
    QString timeValue;
    for (int i = 0; i < vcalllogArray.size(); i++) {
        QJsonValue sub2 = vcalllogArray.at(i);
        QJsonObject sub3 = sub2.toObject();
        QJsonValue N = sub3.value("N");
        QJsonArray NArray = N.toArray();
        QJsonObject sub4 = NArray[0].toObject();
        QJsonValue name = sub4.value("VALUE");
        qDebug() << name.toString();
        nameValue = name.toString();

        QJsonArray telArray = sub3.value("TEL").toArray();
        QJsonObject sub5 = telArray[0].toObject();
        QJsonValue phone = sub5.value("VALUE");
        qDebug() << phone.toString();
        phoneValue = phone.toString();

        QJsonArray dateArray = sub3.value("STARTTIME").toArray();
        QJsonObject sub6 = dateArray[0].toObject();
        QJsonValue date = sub6.value("VALUE");
        qDebug() << date.toString();
        dateValue = date.toString();


        QJsonValue time = sub3.value("lasttime");
        qDebug() << time.toString();
        timeValue = time.toString();


        QString insert_sql = "insert into callLog values ( ?, ?, ?, ?)";
        sql_query.prepare(insert_sql);
        //sql_query.addBindValue(NULL);
        sql_query.addBindValue(nameValue);
        sql_query.addBindValue(phoneValue);
        sql_query.addBindValue(dateValue);
        sql_query.addBindValue(timeValue);
        if (!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }
        else
        {
            qDebug() << "inserted success!";
        }
       


    }
    database.close();
    return false;


    return false;
}




bool dealData::dealDataBaseContact() {

    openDatabase();
    QSqlQuery sql_query;
    QString create_sql = "create table if not exists contact (name varchar(30), phone varchar(30))";
    sql_query.prepare(create_sql);
    if (!sql_query.exec())
    {
        qDebug() << "Error: Fail to create table." << sql_query.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }

    QString selectCount_sql = "select count(*) from contact";
    sql_query.prepare(selectCount_sql);
    sql_query.exec();
    sql_query.next();
    int count = sql_query.value(0).toInt();
    qDebug() << count;
    if (count > 0) {
        QString del_seq = "delete from contact";
        sql_query.prepare(del_seq);
        sql_query.exec();
    }


    //QString del_seq = "delete from contact";
    
    database.close();
    return true;
}

bool dealData::dealDataBaseTel()
{
    openDatabase();
    QSqlQuery sql_query;
    QString create_sql = "create table if not exists callLog (name varchar(30), phone varchar(30),telDate varchar(30),telTime varchar(30))";
    sql_query.prepare(create_sql);
    if (!sql_query.exec())
    {
        qDebug() << "Error: Fail to create table." << sql_query.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }

    QString selectCount_sql = "select count(*) from callLog";
    sql_query.prepare(selectCount_sql);
    sql_query.exec();
    sql_query.next();
    int count = sql_query.value(0).toInt();
    qDebug() << count;
    if (count > 0) {
        QString del_seq = "delete from callLog";
        sql_query.prepare(del_seq);
        sql_query.exec();
    }



    database.close();
    return true;
}




bool CreateDataBase()
{
    QSqlDatabase database;
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("MyDataBase.db");
        database.setUserName("root");
        database.setPassword("123456");
    }
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        qDebug() << "open success";
        QSqlQuery sql_query;
        QString create_sql = "create table contact (id int primary key, name varchar(30), phone varchar(30))";
        sql_query.prepare(create_sql);
        if (!sql_query.exec())
        {
            qDebug() << "Error: Fail to create table." << sql_query.lastError();
        }
        else
        {
            qDebug() << "Table created!";
        }
        //关闭数据库
        database.close();
    }
    return true;
}


