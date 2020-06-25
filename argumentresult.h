//Name: Gilles Kepnang

#ifndef __ARGUMENTRESULT_H__
#define __ARGUMENTRESULT_H__

#include <QtCore>
#include <QDebug>

class ArgumentResult
{
public:
    ArgumentResult(QString name);
    
    void set(QString value);
    void append(QString value);
    
    QString get();
    int toInt();
    double toDouble();
    bool toBool();
    
    QStringList getList();
    int count();
    
    QString& operator[] (int n);
private:
    QString m_name;
    QStringList m_values;
};

#endif
