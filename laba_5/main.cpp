#include <treemap.h>

int main()
{
    TreeMap myTreeMap;
    int size;
    cout << "size insert = ";
    cin >> size;
    string st;
    int value;
    cout << "\nkey and value  \n";
    for(int i = 0; i < size; i++)
    {
        cin >> st;
        cin >> value;
        myTreeMap.insert(st,value);
    }
    myTreeMap.printMap();

    cout << "find value of key ";
    cin >> st;
    cout << myTreeMap.findKey(st);

    int del;
    cout << "size delete = ";
    cin >> del;
    cout << "\nkey to del \n";
    for (int i = 0; i < del; i++)
    {
        cin >> st;
        myTreeMap.deleteKey(st);
        cout << "\n";
        myTreeMap.printMap();
    }
    return 0;
}
