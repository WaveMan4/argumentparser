//Name: Gilles Kepnang

#ifndef __ARGUMENTPARSER_H__
#define __ARGUMENTPARSER_H__

#include <QtCore>
#include "argumentdescriptor.h"
#include "argumentresult.h"
#include <QDebug>
class ArgumentParser
{
public: 
    ArgumentParser();

    void setDescription(QString description);
    void printHelp(QTextStream *outputStream = NULL);

    ArgumentStore& addArg_store(QString name1, QString name2=QString());
    ArgumentStoreConst& addArg_storeConst(QString name1, QString constVal);
    ArgumentStoreConst& addArg_storeConst(QString name1, QString name2, QString constVal);
    ArgumentStoreTrue& addArg_storeTrue(QString name1, QString name2 = QString());
    ArgumentStoreFalse& addArg_storeFalse(QString name1, QString name2 = QString());
    ArgumentAppend& addArg_append(QString name1, QString name2 = QString());
    ArgumentAppendConst& addArg_appendConst(QString name1, QString constVal);
    ArgumentAppendConst& addArg_appendConst(QString name1, QString name2, QString constVal);

    bool parseArgs(int argc, char** argv);
    bool parseArgs(QStringList args);

    ArgumentResult& operator [] (QString name);
private:
    QString m_description;
    QMap<QString,ArgumentResult*> m_results;
    QList<ArgumentDescriptor*> m_optionArgs;
    QList<ArgumentDescriptor*> m_positionalArgs;
    QString m_error;
};

#endif
