#ifndef MATRIX
#define MATRIX

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <cstdio>
#include <queue>

using namespace std;

class matrix
{
private:
    int numberVariables;
    vector <vector <double> > array;
    vector <int> permutation;
    vector <double> result;
    vector <double> answer;
    int LUP();
    void solve();
    void printAnswer();
public:
    matrix(ifstream &input);
    ~matrix();
    void printArray();
    void findSolve();
};



#endif // MATRIX

