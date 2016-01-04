#include <matrix.h>

int main()
{
    ifstream input("input.txt");
    matrix myMatrix(input);
    myMatrix.printArray();
    myMatrix.findSolve();
    return 0;
}
