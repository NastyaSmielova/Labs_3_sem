#ifndef TREEMAP
#define TREEMAP

#include <node.h>

class TreeMap
{
    element *head;

public:
    TreeMap();
    ~TreeMap();
    void insert(string,int);
    int findKey(string);
    int deleteKey(string);
    void printMap();
private:
    void leftRotate(element*);
    void rightRotate(element*);
    element* treeInsert(myPair);
    int treeSearch(element*,string);
    element* findElement(element*,string);
    element* treeDelete(element*);
    element* treeNext(element*);
    element* minTree(element*);
    void fixTree(element*);
    void print(element*);

};


#endif // TREEMAP

