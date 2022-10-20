#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <QString>
#include <QStringList>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QDebug>

class HelperFunctions
{
public:

    // Creates a string list from body of data (redundant since tree is now used)
    static QStringList CreateStringList(QString *sectionBody)
    {
        QStringList qsl;
        if(sectionBody->size()==0)
            return qsl;
        QRegularExpression re;
        QRegularExpressionMatch match;
        QString sectionBodyNoQuotedWords = *sectionBody;
        re = QRegularExpression("\"([^\"]*)\"");
        match = re.match(sectionBody);
        while(match.hasMatch())
        {
            QString matchedString = match.captured(0);
            match = re.match(sectionBody, match.capturedEnd());
            qsl.append(matchedString.replace("\"",""));
            sectionBodyNoQuotedWords.remove(matchedString);
        }
        sectionBodyNoQuotedWords = sectionBodyNoQuotedWords.remove("\"").replace("\t"," ").replace("\r"," ").replace("\n"," ").trimmed();
        if(!sectionBodyNoQuotedWords.isEmpty())
        {
            QStringList words = sectionBodyNoQuotedWords.split(" ");
            for( int idx=words.size()-1 ; idx>=0 ; idx-- )
            {
                if(words[idx].size()==0)
                    words.removeAt(idx);
            }
            qsl.append(words);
        }
        return qsl;
    }

    // For debugging purpose (Console readability)
    static void printLine(QString str, QString otherText, QString color)
    {
        if(color.toLower().compare("red")==0) qDebug() << "\033[31m" << str << "\033[0m" << otherText;
        else if(color.toLower().compare("green")==0) qDebug() << "\033[32m" << str << "\033[0m" << otherText;
        else if(color.toLower().compare("yellow")==0) qDebug() << "\033[33m" << str << "\033[0m" << otherText;
        else if(color.toLower().compare("blue")==0) qDebug() << "\033[34m" << str << "\033[0m" << otherText;
        else if(color.toLower().compare("magenta")==0) qDebug() << "\033[35m" << str << "\033[0m" << otherText;
        else if(color.toLower().compare("cyan")==0) qDebug() << "\033[36m" << str << "\033[0m" << otherText;
        else if(color.toLower().compare("light gray")==0) qDebug() << "\033[37m" << str << "\033[0m" << otherText;
        else if(color.toLower().compare("bold")==0) qDebug() << "\033[1m" << str << "\033[0m" << otherText;
        else if(color.toLower().compare("underline")==0) qDebug() << "\033[24m" << str << "\033[0m" << otherText;
        else qDebug() << str << otherText;
    }

    static void printLine(QString str, QString color)
    {
        if(color.toLower().compare("red")==0) qDebug() << "\033[31m" << str << "\033[0m";
        else if(color.toLower().compare("green")==0) qDebug() << "\033[32m" << str << "\033[0m";
        else if(color.toLower().compare("yellow")==0) qDebug() << "\033[33m" << str << "\033[0m";
        else if(color.toLower().compare("blue")==0) qDebug() << "\033[34m" << str << "\033[0m";
        else if(color.toLower().compare("magenta")==0) qDebug() << "\033[35m" << str << "\033[0m";
        else if(color.toLower().compare("cyan")==0) qDebug() << "\033[36m" << str << "\033[0m";
        else if(color.toLower().compare("light gray")==0) qDebug() << "\033[37m" << str << "\033[0m";
        else if(color.toLower().compare("bold")==0) qDebug() << "\033[1m" << str << "\033[0m";
        else if(color.toLower().compare("underline")==0) qDebug() << "\033[24m" << str << "\033[0m";
        else qDebug() << str;
    }

    // For debugging purpose (Simulate tree)
    static QString generateSpace(int depth)
    {
        QString s;
        for(s="";depth>0;depth--)
            s.append("    ");
        return s;
    }
};

#endif // HELPERFUNCTIONS_H
