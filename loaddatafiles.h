///////////////////////////////////////////////////////////////
///     Relevant data structures for information storage    ///
/// Tree for name list and Dictionary for localization keys ///
///////////////////////////////////////////////////////////////

#ifndef LOADDATAFILES_H
#define LOADDATAFILES_H

#include <QMainWindow>
#include <QAbstractItemModel>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include <helperFunctions.h>

class TreeItem
{
public:
    QString key;
    TreeItem* parent;
    std::vector<TreeItem*> children;

    // From current node, search for node with given key through all its children
    TreeItem* SearchKey(QString k)
    {
        if(this->key==k) return this;
        for(auto child:this->children)
        {
            TreeItem* temp = SearchKey(child,k);
            if(temp!=nullptr) return temp;
        }
        return nullptr;
    }

    // From root node, search for node with given key through all its children
    // Basically this node can search for other nodes in different branches of the tree
    // This function is kinda overkill over here and may be better suited in LoadTree
    TreeItem* SearchKey(TreeItem* root, QString k)
    {
        if(root==nullptr) return nullptr;
        if(root->key == k) return root;
        if(root->children.size()==0) return nullptr;
        for(auto child:root->children)
        {
            TreeItem* temp = SearchKey(child,k);
            if(temp!=nullptr) return temp;
        }
        return nullptr;
    }

    // Overkill function (can insert a key anywhere given the parent key)
    // Probably suited for LoadTree too
    TreeItem* InsertKey(QString k, QString parentKey, TreeItem* currentNode = nullptr)
    {
        TreeItem* parentNode = parent==nullptr?SearchKey(currentNode==nullptr?this:currentNode, parentKey):parent;
        if(parentNode==nullptr) {qWarning()<<"\033[31mWARNING: Null Parent\033[0m";return nullptr;}
        if(parentNode->key == k) {qInfo()<<"\033[33mINFO: Key Exists\033[0m";return this;}
        for(auto child: parentNode->children) if(child->key == k) return child;
        TreeItem* node = new TreeItem;
        node->key = k;
        node->parent = parentNode;
        parentNode->children.push_back(node);
        return node;
    }

    // If current node has no key then it will get the current key (useful for root node)
    // Else it will insert this key as a child into the current node
    TreeItem* InsertKey(QString k)
    {
        if(this->key.isEmpty())
        {
            this->key = k;
            this->parent = nullptr;
            if(this->children.size()>0) this->children.clear();
            return this;
        }
        else
        {
            TreeItem* node = new TreeItem;
            node->key = k;
            node->parent = this;
            this->children.push_back(node);
            return node;
        }
    }

    // Removes a child node of the current node
    void RemoveChildKey(QString childKey)
    {
        int idx=0;
        for( ;idx<children.size();idx++)
            if(children[idx]->key==childKey)
                break;
        if(idx<children.size())
            children.erase(children.begin()+idx);
        else
            HelperFunctions::printLine("WARNING: Cannot remove a key that does not exist","red");
    }

    // Remove the current node
    void RemoveKey()
    {
        this->children.clear();
        this->key.clear();
        if(parent!=nullptr)
            parent->RemoveChildKey(this->key);
    }

    // Search for node with given key in all descendents of current node (A bit overkill)
    void RemoveKeyInChildren(QString k)
    {
        if(this->key==k)
        {
            RemoveKey();
            return;
        }
        TreeItem* node = SearchKey(k);
        if(node!=nullptr)
        {
            //vec.erase(vec.begin() + index);
            TreeItem* parent = node->parent;
            parent->RemoveChildKey(k);
        }
        else
            HelperFunctions::printLine("WARNING: Key is non-existent in children","red");
    }

    // Ease of access of children of current node using their key
    TreeItem* operator[](QString k)
    {
        for(auto child:children)
            if(child->key==k)
                return child;
        return nullptr;
    }

    // Returns child of current node at the given index, else returns null pointer
    TreeItem* operator[](int index)
    {
        if(index>=0 && index<children.size())
            return children[index];
        return nullptr;
    }

};


// Holds relevant data and functions for data loading and tree access
class LoadTree : public QMainWindow
{
    Q_OBJECT
public:
    explicit LoadTree(QWidget *parent = nullptr);

    /// \brief Loads in name list data into a tree structure
    /// \param Pointer to the string object
    /// \return true if data is loaded successfully else false if data is not of correct format
    bool LoadData(QString* nameListFileString);

public:
    TreeItem root;

private:

    // Looks ahead for '=' which determines word is a key
    bool checkIfWordKey(QString* word, int idx);
    // Inverse of the above
    bool checkIfWordValue(QString* word, int idx);

    bool debugToConsole = false;

signals:

};

// Holds relevant data and functions for data loading and dictionary access
class LoadDict : public QMainWindow
{
    Q_OBJECT
public:
    explicit LoadDict(QWidget *parent = nullptr);

    /// \brief Loads in localization data into a dictianary (key-value pair)
    /// \param Pointer to the string object
    /// \return true if data is loaded successfully else false if data is not of correct format
    bool LoadData(QString* localListFileString);

public:
    std::map<QString, QString> keyPair;

private:
    bool debugToConsole = false;

signals:

};

#endif // LOADDATAFILES_H
