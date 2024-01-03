#include "WordFrquency.h"
#include <QQmlEngine>
#include <QThread>
#include <QFile>

static WordFrequency* s_instance = nullptr;

QObject* WordFrequency::singletonProvider(QQmlEngine *qmlEngine, QJSEngine *)
{
    if(!s_instance){
        s_instance = new WordFrequency(qmlEngine);
    }
    return s_instance;
}

QVariantList WordFrequency::getWordFrequency() const
{
    return m_WordFrequency;
}

int WordFrequency::getWordCount() const
{
    return m_WordCount;
}

bool WordFrequency::availableStrInList(const QString &str, const QStringList &list)
{
    for (int i=0; i<list.length(); i++){
        if(str == list.at(i))
            return true;
    }
    return false;
}

int WordFrequency::countStrInList(const QString &str, const QStringList &list)
{
    int count = 0;
    for (int i=0; i<list.length(); i++){
        if(str == list.at(i))
            count++;
    }
    return count;
}

WordFrequency::WordFrequency(QObject *parent)
{
    qDebug() << metaObject()->className() << __FUNCTION__ << thread();

}

WordFrequency::~WordFrequency()
{
    qDebug() << metaObject()->className() << __FUNCTION__ << thread();
}

void WordFrequency::performWordFrequency(const QString &pathFile)
{
    qDebug() << metaObject()->className() << __FUNCTION__ << pathFile << thread();
    QVariantList list;

    QFile textStream(pathFile);

    if(textStream.exists()){
        //qDebug() << "File is available";
        QStringList strList;
        if(textStream.open(QIODevice::ReadOnly)){
            QByteArray fileData;
            fileData = textStream.readAll();
            QString textStreamStr = fileData;

            /// Filter the string
            textStreamStr.replace("\n", " ");
            textStreamStr.replace("\r", " ");
            textStreamStr.replace("  ", " ");
            qDebug() << textStreamStr;

            strList = textStreamStr.split(" ");

            // Calculate word count
            int count = strList.length();
            qDebug() << "word count" << count;
            if(m_WordCount != count){
                m_WordCount = count;
                emit sWordCountChanged(count);
            }

            QStringList wordList;
            QStringList wordCountList;

            for(int i=0; i<count; i++){
                QString tempStr = strList.at(i);
                if(!availableStrInList(tempStr, wordList)){
                    wordList << tempStr;
                    wordCountList << QString::number(countStrInList(tempStr, strList));
                }
            }
            qDebug() << wordList;
            qDebug() << wordCountList;

            QVariantList combineList;
            if(wordList.length() == wordCountList.length()){
                for(int i=0; i<wordList.length(); i++){
                    QStringList tempStrList;
                    QString temp = wordList.at(i);
                    tempStrList << temp;
                    temp = wordCountList.at(i);
                    tempStrList << temp;
                    combineList << tempStrList;
                }

                qDebug() << combineList;
                list = combineList;
            }
            else
                qDebug() << "Invalid";
        }
        else{
            qDebug() << "File cannot be opened";
        }
    }
    else{
        qDebug() << "File is not available";
        return;
    }

    if(m_WordFrequency != list){
        m_WordFrequency = list;
        emit sWordFrequencyChanged(list);
    }
}
