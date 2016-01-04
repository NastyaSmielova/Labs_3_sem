#include <treemap.h>

// red = 1
// black = 0;

//create tree
TreeMap::TreeMap()
{
    head = NULL;
}

//destroy tree
TreeMap::~TreeMap()
{
    while(head) treeDelete(head);
}

//make left rotate of the tree
void TreeMap::leftRotate(element *myElement)
{
    element* temp = myElement->getRight();
    myElement->setRight(temp->getLeft());

    if (temp->getLeft() != NULL) temp->getLeft()->setParent( myElement);

    temp->setParent(myElement->getParent());

    if (myElement->getParent()== NULL) head = temp;
    else
    {
        if (myElement == myElement->getParent()->getLeft())
            myElement->getParent()->setLeft(temp);
        else myElement->getParent()->setRight(temp);
    }
    temp->setLeft(myElement);
    myElement->setParent(temp);
}

//make right rotate of the tree
void TreeMap::rightRotate(element *myElement)
{
    element* temp = myElement->getLeft();
    myElement->setLeft(temp->getRight());

    if (temp->getRight() != NULL) temp->getRight()->setParent( myElement);

    temp->setParent(myElement->getParent());

    if (myElement->getParent() == NULL) head  = temp;
    else
    {
        if (myElement == myElement->getParent()->getRight())
            myElement->getParent()->setRight(temp);
        else myElement->getParent()->setLeft(temp);
    }
    temp->setRight(myElement);
    myElement->setParent(temp);

}

//this function compare two elements by their keys
bool compare(myPair first, myPair second)
{
    bool ans = first.getKey() > second.getKey();
    return ans;
}

//create new element to insert to the tree
element* TreeMap::treeInsert(myPair newPair)
{
    element *newElement = new element(newPair);
    element *temp = NULL;
    element *curr = head;

    while (curr != NULL)
    {
        temp = curr;
        if (compare(curr->getValue(), newElement->getValue())) curr = curr->getLeft();
        else curr = curr->getRight();
    }

    newElement->setParent(temp);
    if (temp == NULL) head  = newElement;
    else
    {
        if (compare(temp->getValue(),newElement->getValue())) temp->setLeft(newElement);
        else temp->setRight(newElement);
    }
    return newElement;
}

//print elements
//key, value and color
void TreeMap::print(element* curr)
{
    if (curr)
    {
        print(curr->getLeft());
        cout <<" " << curr->getValue().getKey() << " -> " << curr->getValue().getValue() << " " << curr->getColor()<<"\n";
        print(curr->getRight());
    }
}


//call function to print all elements
//begins from the head of the tree
void TreeMap::printMap()
{
    print(head);
}



//find element with the lowest key
element* TreeMap::minTree(element* current)
{
    while (current->getLeft())
        current = current->getLeft();
    return current;
}

//find the element with next value in the tree
element* TreeMap::treeNext(element* current)
{
    if (current)
    {
        if (current->getRight() != NULL) return minTree(current->getRight());
        element* temp = current->getParent();
        while(temp && current == temp->getRight())
        {
            current = temp;
            temp = temp->getParent();
        }
        return temp;
    }
    return NULL;
}


//this function fix the the tree
//because after deleting element tree can have one problem:
//one red element may have red son
//and it is problem for a red black tree
//here we solve all 8 cases that can be after deleting
void TreeMap::fixTree(element * current)
{
   while ( current != head && current->getColor() == 0)
    {
        if (current->getParent()->getLeft() == current)
        {

            element* temp = current->getParent()->getRight();
            if (temp && temp->getColor() == 1)
            {
                temp->setColor(0);
                current->getParent()->setColor(1);
                leftRotate(current->getParent());
                temp = current->getParent()->getRight();
            }
            if (temp->getLeft() && temp->getRight() && temp->getLeft()->getColor() == 0 && temp->getRight()->getColor() == 0)
            {
                temp->setColor(1);
                current = current->getParent();
            }
            else
            {
                if (temp && temp->getRight() && temp->getRight()->getColor() ==  0)
                {
                    if (temp->getLeft())temp->getLeft()->setColor(0);
                    temp->setColor(1);
                    rightRotate(temp);
                    temp = current->getParent()->getRight();
                }
                temp->setColor(current->getParent()->getColor());
                current->getParent()->setColor(0);
                temp->getRight()->setColor(0);
                leftRotate(current->getParent());
                current = head;

            }
        }
        else
        {
            element* temp = current->getParent()->getLeft();
            if (temp && temp->getColor() == 1)
            {
                temp->setColor(0);
                current->getParent()->setColor(1);
                rightRotate(current->getParent());
                temp = current->getParent()->getLeft();
            }
            if (temp->getLeft() && temp->getRight() && temp->getRight()->getColor() == 0 && temp->getLeft()->getColor() == 0)
            {
                temp->setColor(1);
                current = current->getParent();
            }
            else
            {
                if (temp->getLeft() &&  temp->getLeft()->getColor() ==  0)
                {
                    temp->getRight()->setColor(0);
                    temp->setColor(1);
                    leftRotate(temp);
                    temp = current->getParent()->getLeft();
                }
                temp->setColor(current->getParent()->getColor());
                current->getParent()->setColor(0);
                temp->getLeft()->setColor(0);
                rightRotate(current->getParent());
                current = head;
            }
        }
    }
    current->setColor(0);
}

//delete element from the tree
//if we have problem with RB tree after deleting we call function to fix proble of the colors
element* TreeMap::treeDelete(element* elementToDeleting)
{
    element* temp;

    if (elementToDeleting->getLeft() == NULL || elementToDeleting->getRight() == NULL) temp = elementToDeleting;
    else temp = treeNext(elementToDeleting);

    element* next = NULL;
    if (temp->getLeft()) next = temp->getLeft();
    else if (temp->getRight())next = temp->getRight();

    if (next && temp) next->setParent(temp->getParent());

    if (temp->getParent() == NULL) head = next;
    else
    {
        if (temp == temp->getParent()->getLeft()) temp->getParent()->setLeft(next);
        else temp->getParent()->setRight(next);
    }
    if (temp != elementToDeleting)
        elementToDeleting->setValue(temp->getValue());

    if (temp && next && temp->getColor() == 0) fixTree(next);
    return temp;

}


//delete element by its key
//delete it if it exists and tell its value
int TreeMap::deleteKey(string myString)
{
    element* elementToDeleting = findElement(head,myString);
     if (elementToDeleting)
     {
         int value = elementToDeleting->getValue().getValue();
         cout << value << "   ";
         delete (treeDelete(elementToDeleting));
         return value;
     }
    return 0;
}

//add new element to the tree
//firstly we add node as to binary tree and then we can brake one role of the RB tree
//red parent can have a red son we can have 4 cases of relation this node its parent and ankle
void TreeMap::insert(string st, int value)
{
    myPair tempPair(st,value);
    element *newElement = treeInsert(tempPair);

    newElement->setColor(1);
    element *temp = new element();

    while (newElement != head && newElement->getParent()->getColor() == 1)
    {
        if (newElement->getParent() == newElement->getParent()->getParent()->getLeft())
        {
            temp = newElement->getParent()->getParent()->getRight();
            if (temp && temp->getColor() == 1)
            {
                newElement->getParent()->setColor(0);
                temp->setColor(0);
                newElement->getParent()->getParent()->setColor(1);
                newElement = newElement->getParent()->getParent();
            }
            else
            {
                if (newElement == newElement->getParent()->getRight())
                {
                    newElement = newElement->getParent();
                    leftRotate(newElement);
                }
                newElement->getParent()->setColor(0);
                newElement->getParent()->getParent()->setColor(1);
                rightRotate(newElement->getParent()->getParent());
            }
        }
        else
        {
            temp = newElement->getParent()->getParent()->getLeft();
            if (temp && temp->getColor() == 1)
            {
                newElement->getParent()->setColor(0);
                temp->setColor(0);
                newElement->getParent()->getParent()->setColor(1);
                newElement = newElement->getParent()->getParent();
            }
            else
            {
                if (newElement == newElement->getParent()->getLeft())
                {
                    newElement = newElement->getParent();
                    rightRotate(newElement);
                }
                newElement->getParent()->setColor(0);
                newElement->getParent()->getParent()->setColor(1);
                leftRotate(newElement->getParent()->getParent());
            }

        }
    }
    if (head) head->setColor(0);
}


//find the element by its key in the tree
element* TreeMap::findElement(element* current,string myString)
{
    if (current == NULL) return NULL;
    if(current->getValue().getKey()== myString) return current;
    myPair temp(myString,0);
    if (compare(current->getValue(),temp)) return findElement(current->getLeft(),myString);
    else return findElement(current->getRight(),myString);
}



//call the function to find element by its key
//return the value
int TreeMap::findKey(string myString)
{
    element* result = findElement(head,myString);
    if (result == NULL) return 0;
    return result->getValue().getValue();
}
