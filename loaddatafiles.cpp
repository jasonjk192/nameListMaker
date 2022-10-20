#include "loaddatafiles.h"

//////////////////////////
/// Tree for Name List ///
//////////////////////////

LoadTree::LoadTree(QWidget *parent)
    : QMainWindow{parent}
{}

bool LoadTree::LoadData(QString* nameListFileString)
{
    std::vector<QString> keys;
    keys.push_back("START");
    TreeItem* currentNode = root.InsertKey("START");
    bool ignoreSpace = false, isSingularValue = false;
    QString word = "";
    int depth = 0;
    for(int idx=0;idx<nameListFileString->size();idx++)
    {
        QChar c = nameListFileString->at(idx);
        if(c == "#")
        {
            idx = nameListFileString->indexOf("\n",idx);
            continue;
        }
        else if(c=='\"')
        {
            ignoreSpace = !ignoreSpace;
            word.append(c);
        }
        else if(c.isLetterOrNumber() || c=='_' || c=='%')
            word.append(c);
        else if(word.length()>0 && (c==' '||c=='\t'||c=='\n'||c=='\r'||c=='\f'))
        {
            if(ignoreSpace)
                word.append(c);
            else
            {
                if(checkIfWordKey(nameListFileString,idx))
                {
                    currentNode = root.InsertKey(word,keys.back());
                    keys.push_back(word);
                    if(debugToConsole) HelperFunctions::printLine(HelperFunctions::generateSpace(depth)+word,"green");
                }
                else if(checkIfWordValue(nameListFileString,idx))
                {
                    root.InsertKey(word,keys.back(),currentNode);
                    if(debugToConsole) HelperFunctions::printLine(HelperFunctions::generateSpace(depth)+word,"cyan");
                    if(isSingularValue)
                    {
                        if(debugToConsole) HelperFunctions::printLine(HelperFunctions::generateSpace(depth)+keys.back(),"red");
                        depth--;
                        isSingularValue = false;
                        keys.pop_back();
                    }
                }
                word.clear();
            }
        }
        else if(c=='{')
        {
            if(debugToConsole) HelperFunctions::printLine(HelperFunctions::generateSpace(depth)+keys.back(),"yellow");
            ++depth;
        }
        else if(c=='=')
        {
            for(int i=idx+1;nameListFileString->at(i)!='{';i++)
            {
                QChar c0 = nameListFileString->at(i);
                if(c0.isLetterOrNumber()||c0=='_'||c0=='\"')
                {
                    depth++;
                    idx=i-1;
                    isSingularValue = true;
                    break;
                }
            }
        }
        else if(c=='}')
        {
            if(debugToConsole) HelperFunctions::printLine(HelperFunctions::generateSpace(depth)+keys.back(),"red");
            keys.pop_back();
            --depth;
        }
    }
    if(keys.size()>1)
    {
        HelperFunctions::printLine("Error in reading data", "red");
        root = TreeItem();
        return false;
    }
    root = *root.children[0];
    return true;
}

bool LoadTree::checkIfWordKey(QString* word, int idx)
{
    for(int i=idx;;i++)
    {
        QChar c = word->at(i);
        if(c.isLetterOrNumber()||c=='_'||c=='\"'||c=='}') return false;
        else if(c=='=') return true;
    }
    return false;
}

bool LoadTree::checkIfWordValue(QString* word, int idx)
{
    for(int i=idx;;i++)
    {
        QChar c = word->at(i);
        if(c.isLetterOrNumber()||c=='_'||c=='\"'||c=='}') return true;
        else if(c=='=') return false;
    }
    return false;
}

////////////////////////////////////////
/// Dictionary for Localization Keys ///
////////////////////////////////////////

LoadDict::LoadDict(QWidget *parent)
    : QMainWindow{parent}
{}

bool LoadDict::LoadData(QString *localListFileString)
{
    QTextStream in(localListFileString);
    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();
        if(line.contains("l_english") || line.startsWith("#") || line.isEmpty()) continue;
        int findColon = line.indexOf(':');
        int findQuote = line.indexOf('\"');
        if(findColon>line.size() || findQuote>line.size())
            continue;
        QString tag = line.mid(0,findColon);
        QString name = line.mid(findQuote).remove('\"');
        keyPair[tag]=name;
    }
    if(debugToConsole)
        for(auto k:keyPair)
            HelperFunctions::printLine(k.first,k.second,"green");
    return true;
}
