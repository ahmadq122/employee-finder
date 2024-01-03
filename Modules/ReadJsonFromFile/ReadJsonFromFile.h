#pragma once

#include <QObject>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

/// Support Singleton mechanism
class QQmlEngine;
class QJSEngine;

class ReadJsonFromFile : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QJsonArray pEmployeeDataJsonArray READ getEmployeeDataJsonArray NOTIFY sEmployeeDataJsonArrayChanged)
    Q_PROPERTY(QJsonArray pEmployeeNameJsonArray READ getEmployeeNameJsonArray NOTIFY sEmployeeNameJsonArrayChanged)
    Q_PROPERTY(QJsonArray pEmployeeDataJsonArrayFiltered READ getEmployeeDataJsonArrayFiltered NOTIFY sEmployeeDataJsonArrayFilteredChanged)

public:
    static QObject* singletonProvider(QQmlEngine *qmlEngine, QJSEngine *);
    explicit ReadJsonFromFile(QObject *parent = nullptr);
    ~ReadJsonFromFile();

    QJsonArray getEmployeeDataJsonArray() const;
    QJsonArray getEmployeeNameJsonArray() const;
    QJsonArray getEmployeeDataJsonArrayFiltered() const;

public slots:
    void initJsonDataFromFiles(const QStringList &pathFileList);
    void filterEmployeeData(const QString& filterOption1, const QString& filterOption2);

signals:
    void sEmployeeDataJsonArrayChanged(QJsonArray value);
    void sEmployeeNameJsonArrayChanged(QJsonArray value);
    void sEmployeeDataJsonArrayFilteredChanged(QJsonArray value);

private:
    void combineJsonObj2JsonArrayFromFile(const QStringList &pathFileList);

    void filterDataBasedOn(const QString& filterOption1, const QString& filterOption2);
    QJsonArray filterEmployeeName();

    void setEmployeeDataJsonArrayFiltered(QJsonArray value);
    void setEmployeeNameJsonArray(QJsonArray value);

    QJsonObject getJsonObjFromFile(const QString& filePath);
    QJsonArray m_EmployeeDataJsonArray;
    QJsonArray m_EmployeeNameJsonArray;
    QJsonArray m_EmployeeDataJsonArrayFiltered;
};

