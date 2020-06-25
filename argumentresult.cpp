//Name: Gilles Kepnang

#include "argumentresult.h"

ArgumentResult::ArgumentResult(QString name)
{
    m_name = name;
}

void ArgumentResult::set(QString value)
{
    if (m_values.size())
    {
        while (m_values.size()) m_values.pop_back();
    }
    m_values+=value;
}

void ArgumentResult::append(QString value)
{
    if (!m_values.size())   //Empty StringList
        set(value);
    else
        m_values.append(value);
}

QString ArgumentResult::get()
{                                   //Gets first value
    return m_values.at(0);
}

int ArgumentResult::toInt()
{
    bool ok;
    int dec = get().toInt(&ok,10);
    if (ok) return dec;
    else
    {
        qDebug() << "Error: number cannot be converted to an int";
        return -999999;
    }
}

double ArgumentResult::toDouble()
{
    bool ok;
    double dub = get().toInt(&ok);
    if (ok) return dub;
    else
    {
        qDebug() << "Error: number cannot be converted to an double";
        return -999999.9999;
    }
}

bool ArgumentResult::toBool()
{
    QString flag = get();
    if (!(QString::compare(flag,"true",Qt::CaseInsensitive)))
        return true;
    else return false;
}

QStringList ArgumentResult::getList()
{
    return m_values;
}

int ArgumentResult::count()
{
    return m_values.size();
}

QString& ArgumentResult::operator [](int n)
{
    return m_values[n];
}
