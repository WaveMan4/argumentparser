//Name: Gilles Kepnang

#ifndef __ARGUMENTDESCRIPTOR_H__
#define __ARGUMENTDESCRIPTOR_H__

#include <QtCore>
#include <QDebug>
class ArgumentParser;

class ArgumentDescriptor
{
public:
    // Required interface
    ArgumentDescriptor(QString name1, QString name2);
    
    ArgumentDescriptor& setDest(QString destName);
    ArgumentDescriptor& setRequired(bool required);
    
    ArgumentDescriptor& setFixedMultiplicity(int N);
    ArgumentDescriptor& setPlusMultiplicity();
    ArgumentDescriptor& setStarMultiplicity();
    
    ArgumentDescriptor& setDefault(QString value);

    // Implementation specific
    bool isOption();
    void handle(QStringList &list, bool reverse=false);
    virtual void process(QStringList &args) = 0;
    void setParent(ArgumentParser *parent);
    int getMultiplicity();
private:
    QString m_default;
    int m_multiplicity;
    bool m_required;
    QString m_name1;
    QString m_name2;
protected:
    QString m_destName;
    ArgumentParser *m_parent;
};

class ArgumentStore : public ArgumentDescriptor
{
public:
    ArgumentStore(QString name1, QString name2);
    virtual void process(QStringList &args);
};

class ArgumentStoreConst : public ArgumentStore
{
public:
    ArgumentStoreConst(QString name1, QString name2);
    void setConst(QString constVal);
    virtual void process(QStringList &args);
private:
    QString m_constVal;
};

class ArgumentStoreTrue : public ArgumentStoreConst
{
public:
    ArgumentStoreTrue(QString name1, QString name2);
};

class ArgumentStoreFalse : public ArgumentStoreConst
{
public:
    ArgumentStoreFalse(QString name1, QString name2);
};

class ArgumentAppend : public ArgumentDescriptor
{
public:
    ArgumentAppend(QString name1, QString name2);
    virtual void process(QStringList &args);
};

class ArgumentAppendConst : public ArgumentAppend
{
public:
    ArgumentAppendConst(QString name1, QString name2);
    void setConst(QString constVal);
    virtual void process(QStringList &args);
private:
    QString m_constVal;
};

#endif
