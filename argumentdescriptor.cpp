//Name: Gilles Kepnang

#include "argumentparser.h"
#include "argumentdescriptor.h"

//////////////////////////////////////////////////////////////////
/*              ArgumentDescriptor Class                        */
ArgumentDescriptor::ArgumentDescriptor(QString name1, QString name2)
{
    m_name1 = name1;
    m_name2 = name2;
    m_multiplicity = 1;
    if (m_name1.contains("--")) m_name1.remove(0,2);
    else if (m_name1.contains("-")) m_name1.remove(0,1);
    m_destName = m_name1;
}

ArgumentDescriptor& ArgumentDescriptor::setDest(QString destName)
{
    m_destName = destName;
    return *this;
}

ArgumentDescriptor& ArgumentDescriptor::setRequired(bool required)
{
    m_required = required;
    return *this;
}

ArgumentDescriptor& ArgumentDescriptor::setDefault(QString value)
{
    m_default = value;
    return *this;
}

bool ArgumentDescriptor::isOption()
{
    if (m_name1.contains("-") || m_name2.contains("-"))
        return true;
    else return false;
}

void ArgumentDescriptor::handle(QStringList &list, bool reverse)
{
    int argc = list.size();
    bool l_form(false), s_form(false);
    QStringList splitter;
    if (argc == 2)
    {
        l_form = (list[1].contains("--"));
        s_form = (list[1].contains("-"));
        if (l_form)  //long form
        {
            splitter = list[1].split('=');
            list = splitter;
            if (splitter.size() >= getMultiplicity())
                list.append("true");
            else list.append("false");
        }
        else if (!l_form && s_form) //short form
        {
            QString substr = list[1];
            substr.remove(0,2);
            list[1].remove(0,2);
            list.append(substr);
            if (list.size() >= getMultiplicity())
                list.append("true");
            else list.append("false");
            list.append("true");
        }
        else list.append("false");
    }
    else if (argc == 3)
    {
        l_form = (list[1].contains("--"));
        s_form = (list[1].contains("-"));
        if (l_form)  //long form
        {
            splitter = list[1].split('-', QString::KeepEmptyParts);
            splitter.append(list[2]);
            list = splitter;
            if (splitter.size() >= getMultiplicity())
                list.append("true");
            else list.append("false");
        }
        else if (!l_form && s_form) //short form
        {
            splitter = list[1].split('-', QString::KeepEmptyParts);
            splitter.append(list[2]);
            list = splitter;
            if (splitter.size() >= getMultiplicity())
                list.append("true");
            else list.append("false");
        }
        else list.append("false");
    }
    else if (argc > 3)
    {
        l_form = (list[2].contains("--"));
        s_form = (list[2].contains("-"));
        if (l_form || (!l_form && s_form))
            list.append("true");
        else list.append("false");
    }
    else
    {
        list.append("false");
    }

    if (list.at(list.size()-1) ==  "true")
    {
        QStringList sl;
        for (int i=0; i < list.size(); i++)
        {
            if (list[i] == m_name1 || list[i] == m_name2)
                sl.append(list[i]);
        }
        qDebug() << sl;
        process(sl);
    }

    return;
}

void ArgumentDescriptor::setParent(ArgumentParser *parent)
{
    m_parent = parent;
}

int ArgumentDescriptor::getMultiplicity()
{
    return m_multiplicity;
}
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
/*              ArgumentStore Class                             */
ArgumentStore::ArgumentStore(QString name1, QString name2):ArgumentDescriptor(name1,name2)
{   }

void ArgumentStore::process(QStringList &args)
{
    (*m_parent) [m_destName].set(args[0]);
    for (int i = 1; i < args.size(); i++)
        (*m_parent) [m_destName].append(args[i]);
}
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
/*              ArgumentStoreConst Class                        */
ArgumentStoreConst::ArgumentStoreConst(QString name1, QString name2):ArgumentStore(name1,name2)
{   }

void ArgumentStoreConst::setConst(QString constVal)
{
    m_constVal = constVal;
}

void ArgumentStoreConst::process(QStringList &args)
{
    (*m_parent) [m_destName].set(m_constVal);
}
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
/*              ArgumentStoreTrue Class                         */
ArgumentStoreTrue::ArgumentStoreTrue(QString name1, QString name2):ArgumentStoreConst(name1,name2)
{
    setConst("true");
}
//////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
/*              ArgumentStoreFalse Class                         */
ArgumentStoreFalse::ArgumentStoreFalse(QString name1, QString name2):ArgumentStoreConst(name1,name2)
{
    setConst("false");
}
///////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
/*              ArgumentAppend Class                         */
ArgumentAppend::ArgumentAppend(QString name1, QString name2):ArgumentDescriptor(name1,name2)
{   }

void ArgumentAppend::process(QStringList &args)
{
    for (int i = 0; i < args.size(); i++)
        (*m_parent) [m_destName].append(args[i]);
}

//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
/*              ArgumentAppendConst Class                         */
ArgumentAppendConst::ArgumentAppendConst(QString name1, QString name2):ArgumentAppend(name1,name2)
{   }

void ArgumentAppendConst::setConst(QString constVal)
{
    m_constVal = constVal;
}

void ArgumentAppendConst::process(QStringList &args)
{
    for (int i = 0; i < args.size(); i++)
        (*m_parent) [m_destName].append(m_constVal);
}
//////////////////////////////////////////////////////////////////
