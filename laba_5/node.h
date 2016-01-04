#ifndef NODE
#define NODE

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class myPair
{
    string key;
    int value;
    friend class element;
public:
    myPair(){key = ""; value = 0;}
    myPair(string newString,int newValue){key = newString; value = newValue;}
    ~myPair(){}
    int getValue(){return value;}
    string getKey(){return key;}
};

class element
{
public:
    element(myPair newValue){value = newValue;parent=NULL;left=NULL;right=NULL;}
    element(){parent=NULL;left=NULL;right=NULL;}
    myPair getValue(){return value;}
    int getColor(){return color;}
    element* getLeft(){return left;}
    element* getRight(){return right;}
    element* getParent(){return parent;}
    void setLeft(element * temp){left = temp;}
    void setRight(element * temp){right = temp;}
    void setParent(element * temp){parent = temp;}
    void setColor(int col){color = col;}
    void setValue(myPair val){value = val;}
    ~element(){}
private:
    myPair value;
    int color;
    element *parent;
    element *left;
    element *right;
};

#endif // NODE

