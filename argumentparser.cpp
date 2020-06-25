//Name: Gilles Kepnang

#include "argumentparser.h"

//////////////////////////////////////////////////////////////////////////
/*              ArgumentParser class                                    */
ArgumentParser::ArgumentParser()
{}

void ArgumentParser::setDescription(QString description)
{
    m_description = description;
}


void ArgumentParser::printHelp(QTextStream *outputStream)
{
    if (outputStream == NULL)
        qDebug() << m_description;
    else
        (*outputStream) << m_description;
}

///////////////////////////addArg_* functions///////////////////////////
ArgumentStore& ArgumentParser::addArg_store(QString name1, QString name2)
{
    ArgumentStore *asptr = new ArgumentStore(name1,name2);
    asptr ->setParent(this);
    if (asptr->isOption())
        m_optionArgs.append(asptr);
    else
        m_positionalArgs.append(asptr);
    return *asptr;
}

ArgumentStoreConst& ArgumentParser::addArg_storeConst(QString name1, QString constVal)
{
    ArgumentStoreConst *ascptr = new ArgumentStoreConst(name1,constVal);
    ascptr->setParent(this);
    if (ascptr->isOption())
        m_optionArgs.append(ascptr);
    else
        m_positionalArgs.append(ascptr);
    return *ascptr;
}

ArgumentStoreConst& ArgumentParser::addArg_storeConst(QString name1, QString name2, QString constVal)
{
    ArgumentStoreConst *ascptr = new ArgumentStoreConst(name1, name2);
    ascptr->setConst(constVal);
    ascptr->setParent(this);
    if (ascptr->isOption())
        m_optionArgs.append(ascptr);
    else
        m_positionalArgs.append(ascptr);
    return *ascptr;
}

ArgumentStoreTrue& ArgumentParser::addArg_storeTrue(QString name1, QString name2)
{
    ArgumentStoreTrue *astptr = new ArgumentStoreTrue(name1, name2);
    astptr->setParent(this);
    if (astptr->isOption())
        m_optionArgs.append(astptr);
    else
        m_positionalArgs.append(astptr);
    return *astptr;
}

ArgumentStoreFalse& ArgumentParser::addArg_storeFalse(QString name1, QString name2)
{
    ArgumentStoreFalse *asfptr = new ArgumentStoreFalse(name1, name2);
    asfptr->setParent(this);
    if (asfptr->isOption())
        m_optionArgs.append(asfptr);
    else
        m_positionalArgs.append(asfptr);
    return *asfptr;
}

ArgumentAppend& ArgumentParser::addArg_append(QString name1, QString name2)
{
    ArgumentAppend *aaptr = new ArgumentAppend(name1, name2);
    aaptr->setParent(this);
    if (aaptr->isOption())
        m_optionArgs.append(aaptr);
    else
        m_positionalArgs.append(aaptr);
    return *aaptr;
}

ArgumentAppendConst& ArgumentParser::addArg_appendConst(QString name1, QString constVal)
{
    ArgumentAppendConst *aacptr = new ArgumentAppendConst(name1, constVal);
    aacptr->setParent(this);
    if (aacptr->isOption())
        m_optionArgs.append(aacptr);
    else
        m_positionalArgs.append(aacptr);
    return *aacptr;
}

ArgumentAppendConst& ArgumentParser::addArg_appendConst(QString name1, QString name2, QString constVal)
{
    ArgumentAppendConst *aacptr = new ArgumentAppendConst(name1, name2);
    aacptr->setConst(constVal);
    aacptr->setParent(this);
    if (aacptr->isOption())
        m_optionArgs.append(aacptr);
    else
        m_positionalArgs.append(aacptr);
    return *aacptr;
}
/////////////////////////////////////////////////////////////////////////////////////////

///////////////////////Parsing Arguments/////////////////////////////////////////////////
bool ArgumentParser::parseArgs(int argc, char**argv)
{                                           //Receive from command line
    QStringList list;
    for (int i=0; i<argc; i++)
    {
        list.append(argv[i]);
    }
    return parseArgs(list);

}

bool ArgumentParser::parseArgs(QStringList args)
{                                           //Pass as QStringList
    int i = 0;
    for (i=0; i < m_optionArgs.size(); i++)
    {
        m_optionArgs[i]->handle(args,0);
        if ((args.at(args.size()-1)) == "true") break;
    }
    for (i=0; i < m_positionalArgs.size(); i++)
    {
        m_positionalArgs[i]->handle(args,0);
        if ((args.at(args.size()-1)) == "true") break;
    }
    if ((args.at(args.size()-1)) == "false")
        return false;
    else return true;
}

ArgumentResult& ArgumentParser::operator [](QString name)
{                                               //Points to appropriate object in list
    ArgumentResult *arptr;
    if (m_results.contains(name))
        arptr = m_results.value(name);
    else
    {
        arptr = new ArgumentResult(name);
        m_results.insert(name,arptr);
    }
    return *arptr;
}

/////////////////////////////////////////////////////////////////////////////
