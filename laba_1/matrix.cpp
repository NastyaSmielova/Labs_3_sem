#include <matrix.h>

//read number of unknown variables and then
//read matrix N*N
//and line of results
matrix::matrix(ifstream &input)
{
    input >> numberVariables;
    for (int i = 0; i < numberVariables; i++)
    {
        vector <double> line;
        for (int j = 0; j < numberVariables; j++)
        {
            double value;
            input >> value;
            line.push_back(value);
        }
        array.push_back(line);
        line.clear();
    }
    for (int i = 0; i < numberVariables; i++)
    {
        double value;
        input >> value;
        result.push_back(value);
    }
}

//makes empty all of vecotors
matrix::~matrix()
{
    array.~vector();
    result.~vector();
    permutation.~vector();
}


//prints our matirx
void matrix::printArray()
{
    for (int i = 0; i < numberVariables; i++)
    {
        for (int j = 0; j < numberVariables; j++)
            cout << array[i][j] << " ";
        cout << "\n";
    }
    cout << "\n";
}

//if want to find some matixes to present our array as P*Array = LU
// matix P is the matrix of permutation
// which contains pivotion element in each step in needed column
// L - it is the lower triangular matrix(elements don't equal 0 only under the main diagonal)
// U - an upper matrix(elements don't equal 0 only above main diagonal and on it)
// we call LUP to find if it is possible these matrixes
void matrix::findSolve()
{
    if (LUP())
    {
        solve();
        printAnswer();
    }
    else
    {
        cout << "no solution\n";
    }
}



// foud matrix of permutation, lower triangular and an upper matrixes if they exist
// they don't exist if our matix is undeterminated
// that means than at least one line is the linear transformation of other lines
int matrix::LUP()
{
    for (int i = 0; i < numberVariables; i++) permutation.push_back(i);
    for (int k = 0; k < numberVariables; k++)
    {
        double max = 0;
        int newK;
        for (int i = k; i < numberVariables; i++)
            if (fabs(array[i][k]) > max)
            {
                max  = fabs(array[i][k]);
                newK = i;
            }
        if (max == 0)
        {
            cout << "underdeterminated\n";
            return 0;
        }
        swap(permutation[k],permutation[newK]);

        for (int i = 0; i < numberVariables; i++) swap(array[k][i],array[newK][i]);

        for (int i = k + 1; i < numberVariables; i++)
        {
            array[i][k] = array[i][k] / array[k][k];
            for (int j = k + 1; j < numberVariables; j++)
                array[i][j] = (double)( array[i][j]- (double)array[i][k] * array[k][j]);
        }
    }
    return 1;
}



//here we use our triangulated matrix to find the answer
//we make forward substitytion(FS) and then back substitytion(BS) to find the answer
// if we can present matix A as PA=LU then we make BS to find y(auxiliaryMatrix)
// from formula Ly = PA
// and BS to find answer from  formula U * Answer = y
void matrix::solve()
{
    vector <double> auxiliaryMatrix;
    for (int i = 0; i < numberVariables; i++)
    {
        double sum = 0;
        for (int j = 0; j < i - 1; j++)
            sum += array[i][j] * auxiliaryMatrix[j];
        double newValue = result[permutation[i]] - sum;
        auxiliaryMatrix.push_back(newValue);
    }

    for (int i = 0; i < numberVariables; i++)answer.push_back(0);

    for (int i = numberVariables - 1; i >= 0; i--)
    {
        double sum = 0;
        for (int j = i + 1; j < numberVariables; j++)
            sum += array[i][j] * answer[j];
        double newValue = (auxiliaryMatrix[i] - sum) / array[i][i];
        answer[i] = newValue;
    }

}

//print founded answer
void matrix::printAnswer()
{
    cout << "Answer : \n";
    for (int i = 0; i < numberVariables; i++) printf("x%d = %.4f, ",i + 1,answer[i]);
    cout << "\n";

}
