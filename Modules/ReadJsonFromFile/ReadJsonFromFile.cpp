#include "ReadJsonFromFile.h"
#include <QQmlEngine>
#include <QThread>
#include <QFile>
#include <QJsonDocument>

static ReadJsonFromFile* s_instance = nullptr;

QObject* ReadJsonFromFile::singletonProvider(QQmlEngine *qmlEngine, QJSEngine *)
{
    if(!s_instance){
        s_instance = new ReadJsonFromFile(qmlEngine);
    }
    return s_instance;
}

ReadJsonFromFile::ReadJsonFromFile(QObject *parent)
{
    qDebug() << metaObject()->className() << __FUNCTION__ << thread();

}

ReadJsonFromFile::~ReadJsonFromFile()
{
    qDebug() << metaObject()->className() << __FUNCTION__ << thread();
}

void ReadJsonFromFile::initJsonDataFromFiles(const QStringList &pathFileList)
{
    qDebug() << metaObject()->className() << __FUNCTION__ << pathFileList << thread();

    combineJsonObj2JsonArrayFromFile(pathFileList);
}

//void ReadJsonFromFile::filterEmployeeData(int filterOption1, int filterOption2)
//{
//    qDebug() << metaObject()->className() << __FUNCTION__ << thread();
//    if(m_EmployeeDataJsonArray.isEmpty()){
//        qWarning() << "No data to be filtered!";
//        return;
//    }

//    switch (filterOption1) {
//    case JsonEnums::FilOpt1_PositionLevel:
//        filterDataBasedOnPositionLevel(filterOption2+1);
//        break;
//    case JsonEnums::FilOpt1_JobTitle:
//        filterDataBasedOnJobTitle(filterOption2);
//        break;
//    case JsonEnums::FilOpt1_EmploymentStatus:
//        filterDataBasedOnEmploymentStatus(filterOption2);
//        break;
//    case JsonEnums::FilOpt1_Department:
//        filterDataBasedOnDepartment(filterOption2);
//        break;
//    default: break;
//    }
//}

void ReadJsonFromFile::filterEmployeeData(const QString& filterOption1, const QString& filterOption2)
{
    qDebug() << metaObject()->className() << __FUNCTION__ << thread();
    if(m_EmployeeDataJsonArray.isEmpty()){
        qWarning() << "No data to be filtered!";
        return;
    }

    filterDataBasedOn(filterOption1, filterOption2);
}


QJsonArray ReadJsonFromFile::getEmployeeDataJsonArray() const
{
    return m_EmployeeDataJsonArray;
}

QJsonArray ReadJsonFromFile::getEmployeeNameJsonArray() const
{
    return m_EmployeeNameJsonArray;
}

QJsonArray ReadJsonFromFile::getEmployeeDataJsonArrayFiltered() const
{
    return m_EmployeeDataJsonArrayFiltered;
}

void ReadJsonFromFile::combineJsonObj2JsonArrayFromFile(const QStringList &pathFileList)
{
    qDebug() << metaObject()->className() << __FUNCTION__ << pathFileList << thread();
    QStringList pathList = pathFileList;
    QJsonArray jsonArray;
    for(short i=0; i<pathList.length(); i++){
        QString path = pathList.at(i);
        QJsonObject jsonObj = getJsonObjFromFile(path);
        jsonArray.append(jsonObj);
    }
    if(m_EmployeeDataJsonArray != jsonArray){
        m_EmployeeDataJsonArray = jsonArray;
        emit sEmployeeDataJsonArrayChanged(jsonArray);
    }
}

void ReadJsonFromFile::filterDataBasedOn(const QString &filterOption1, const QString &filterOption2)
{
    qDebug() << metaObject()->className() << __FUNCTION__ << filterOption1 << filterOption2 << thread();
    QJsonArray jsonArrDataFiltered;

    for(int i=0; i<m_EmployeeDataJsonArray.size(); i++){
        QJsonObject jsonObj = m_EmployeeDataJsonArray.at(i).toObject();
        QJsonArray jsonObjArrEmployee = jsonObj.value("employee").toArray();
        //        qDebug() << i << jsonObjArrEmployee.size();

        if(filterOption1 == "department"){
            if(jsonObj.value("department").toString() == filterOption2){
                jsonArrDataFiltered = jsonObjArrEmployee;
                break;
            }
        }
        else
        {
        for(int j=0; j<jsonObjArrEmployee.size(); j++){
                QJsonObject jsonObjJsonArrEmployee = jsonObjArrEmployee.at(j).toObject();

                if(jsonObjJsonArrEmployee.value(filterOption1).toString() == filterOption2){
                    QJsonObject jsonObjTemp;
                    jsonObjTemp.insert("name", jsonObjJsonArrEmployee.value("name"));
                    jsonObjTemp.insert("job_title", jsonObjJsonArrEmployee.value("job_title"));
                    jsonObjTemp.insert("position_level", jsonObjJsonArrEmployee.value("position_level"));
                    jsonObjTemp.insert("employment_status", jsonObjJsonArrEmployee.value("employment_status"));
                    jsonObjTemp.insert("department", jsonObj.value("department"));

                    jsonArrDataFiltered.append(jsonObjTemp);
                }

            }
        }
    }

    setEmployeeDataJsonArrayFiltered(jsonArrDataFiltered);
}

QJsonArray ReadJsonFromFile::filterEmployeeName()
{

}

void ReadJsonFromFile::setEmployeeDataJsonArrayFiltered(QJsonArray value)
{
    if(m_EmployeeDataJsonArrayFiltered == value) return;
    m_EmployeeDataJsonArrayFiltered = value;
    emit sEmployeeDataJsonArrayFilteredChanged(value);
}

void ReadJsonFromFile::setEmployeeNameJsonArray(QJsonArray value)
{
    if(m_EmployeeNameJsonArray == value) return;
    m_EmployeeNameJsonArray = value;
    emit sEmployeeNameJsonArrayChanged(value);
}

QJsonObject ReadJsonFromFile::getJsonObjFromFile(const QString &filePath)
{
    qDebug() << metaObject()->className() << __FUNCTION__ << filePath << thread();

    QString jsonStr;
    QFile jsonFile(filePath);
    QByteArray jsonData;
    QJsonObject object;

    if(jsonFile.exists())
    {
        if(jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)){
            jsonData = jsonFile.readAll();
            jsonStr = jsonData;
            jsonFile.close();
        }
        else{
            qDebug() << "JSon file can't be opened!";
        }

        if(jsonData.isEmpty() == true){
            qDebug() << "Need to fill JSON data";
        }

        // Assign the json text to a JSON object
        QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData);
        if(jsonDocument.isObject() == false){
            qDebug() << "It is not a JSON object";
        }
        // Then get the main JSON object and get the datas in it
        object = jsonDocument.object();
    }//
    else{
        qDebug() << "Json file is unavailable";
    }

    return object;
}
