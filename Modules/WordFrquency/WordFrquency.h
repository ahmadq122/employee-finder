#pragma once

#include <QObject>
#include <QDebug>

/// Support Singleton mechanism
class QQmlEngine;
class QJSEngine;

class WordFrequency : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList pWordFrequency READ getWordFrequency NOTIFY sWordFrequencyChanged)
    Q_PROPERTY(int pWordCount READ getWordCount NOTIFY sWordCountChanged)

public:
    explicit WordFrequency(QObject *parent = nullptr);
    ~WordFrequency();

    static QObject* singletonProvider(QQmlEngine *qmlEngine, QJSEngine *);

    QVariantList getWordFrequency() const;
    int getWordCount() const;

     bool availableStrInList(const QString &str, const QStringList &list);
     int countStrInList(const QString &str, const QStringList &list);

public slots:
    void performWordFrequency(const QString &pathFile);

signals:
    void sWordFrequencyChanged(QVariantList value);
    void sWordCountChanged(int value);

private:
    QVariantList m_WordFrequency;
    int m_WordCount = 0;

};

