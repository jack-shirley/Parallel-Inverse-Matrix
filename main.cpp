#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include <omp.h>
#include <string>
#include <time.h>

using namespace std;

void printMatrix(vector<vector<float>> matrix)
{
    int asdf = matrix[0].size();
    int asdf2 = matrix[1].size();
    int asdf3 = matrix[2].size();
    for (int i = 0; i < matrix[0].size(); i++)
    {
        for (int j = 0; j < matrix[0].size(); j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

vector<vector<float>> combine(vector<vector<float>> tl_matrix, vector<vector<float>> tr_matrix, vector<vector<float>> bl_matrix, vector<vector<float>> br_matrix)
{
    vector<vector<float>> matrix;
    vector<float> temp;

    for (int i = 0; i < tl_matrix[0].size(); i++)
    {
        for (int j = 0; j < tl_matrix[0].size(); j++)
        {
            temp.push_back(tl_matrix[i][j]);
        }
        for (int j = 0; j < tr_matrix[0].size(); j++)
        {
            temp.push_back(tr_matrix[i][j]);
        }
        matrix.push_back(temp);
        temp.clear();
    }

    for (int i = 0; i < bl_matrix[0].size(); i++)
    {
        for (int j = 0; j < bl_matrix[0].size(); j++)
        {
            temp.push_back(bl_matrix[i][j]);
        }
        for (int j = 0; j < br_matrix[0].size(); j++)
        {
            temp.push_back(br_matrix[i][j]);
        }
        matrix.push_back(temp);
        temp.clear();
    }
    return matrix;
}

vector<vector<float>> getSection(vector<vector<float>> matrix, int base_x, int base_y, int n_x, int n_y)
{
    vector<vector<float>> matrix_section;
    vector<float> temp;
    for (int i = base_x; i < n_x; i++)
    {
        for (int j = base_y; j < n_y; j++)
        {
            temp.push_back(matrix[i][j]);
        }
        matrix_section.push_back(temp);
        temp.clear();
    }
    return matrix_section;
}

vector<vector<float>> turnNegative(vector<vector<float>> matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix.size(); j++)
        {
            matrix[i][j] = matrix[i][j] * -1;
        }
    }
    return matrix;
}

vector<vector<float>> makeZeros(vector<vector<float>> matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix.size(); j++)
        {
            matrix[i][j] = matrix[i][j] * 0;
        }
        cout << endl;
    }
    return matrix;
}

vector<vector<float>> multiplyNumByMatrix(vector<vector<float>> matrix, float num)
{
    for (int i = 0; i < matrix[0].size(); i++)
    {
        for (int j = 0; j < matrix[0].size(); j++)
        {
            matrix[i][j] = num * matrix[i][j];
        }
    }
    return matrix;
}

vector<vector<float>> mulitplyMatrices(vector<vector<float>> matrix1, vector<vector<float>> matrix2)
{
    vector<vector<float>> matrix = matrix1;
    vector<float> temp;
    int n = matrix1[0].size();

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = 0;
            for (int k = 0; k < n; k++)
            {
                matrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return matrix;
}

vector<vector<float>> getDetSection(vector<vector<float>> matrix, int row, int col)
{
    vector<vector<float>> matrix_section;
    vector<float> temp;

    for (int x = 0; x < matrix[0].size(); x++)
    {
        for (int y = 0; y < matrix[0].size(); y++)
        {
            if (x == row)
            {
                continue;
            }
            else if (y == col)
            {
                continue;
            }
            else
            {
                temp.push_back(matrix[x][y]);
            }
        }
        if (temp.size() > 0)
        {
            matrix_section.push_back(temp);
            temp.clear();
        }
    }
    return matrix_section;
}

vector<vector<float>> transposeMatrix(vector<vector<float>> matrix)
{
    vector<vector<float>> transpose = matrix;

    for (int i = 0; i < matrix[0].size(); i++)
    {
        for (int j = 0; j < matrix[0].size(); j++)
        {
            transpose[j][i] = matrix[i][j];
        }
        cout << endl;
    }

    return transpose;
}

vector<vector<float>> applySigns(vector<vector<float>> matrix)
{
    int counter = 0;
    if (matrix[0].size() % 2 == 0)
    { //even size n
        for (int i = 0; i < matrix[0].size(); i++)
        {
            for (int j = 0; j < matrix[0].size(); j++)
            {
                if (counter % 2 == 0)
                {
                    counter++;
                    continue;
                }
                else
                {
                    matrix[i][j] = -1 * matrix[i][j];
                    counter++;
                }
            }
            counter++;
        }
    }
    else
    { //odd n

        for (int i = 0; i < matrix[0].size(); i++)
        {
            for (int j = 0; j < matrix[0].size(); j++)
            {
                if (counter % 2 == 0)
                {
                    counter++;
                    continue;
                }
                else
                {
                    matrix[i][j] = -1 * matrix[i][j];
                    counter++;
                }
            }
        }
    }
    return matrix;
}

float getDet(vector<vector<float>> matrix)
{
    float det = 0;
    int counter = 0; //counter for keeping track of + or -

    //base case is 2x2 matrix
    if (matrix[0].size() == 2)
    {
        return ((matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]));
    }
    else //recursively breakdown the matrix to find the determinant
    {
        for (int col = 0; col < matrix.size(); col++)
        {
            if (counter % 2 == 0)
            {
                det += matrix[0][col] * getDet(getDetSection(matrix, 0, col));
                counter++;
            }
            else
            {
                det += -1 * (matrix[0][col] * getDet(getDetSection(matrix, 0, col)));
                counter++;
            }
        }
    }

    return det;
}

vector<vector<float>> getAdjMatrix(vector<vector<float>> matrix)
{
    {
        vector<vector<float>> adj_matrix;
        vector<float> temp;
        int counter = 0;

        for (int i = 0; i < matrix[0].size(); i++)
        {
            for (int j = 0; j < matrix[0].size(); j++)
            {
                temp.push_back(getDet(getDetSection(matrix, i, j)));
            }
            adj_matrix.push_back(temp);
            temp.clear();
        }

        adj_matrix = transposeMatrix(adj_matrix);
        adj_matrix = applySigns(adj_matrix);

        return adj_matrix;
    }
}

vector<vector<float>> inverse(vector<vector<float>> matrix)
{
    vector<vector<float>> inv_matrix = matrix;
    inv_matrix = multiplyNumByMatrix(getAdjMatrix(matrix), 1 / getDet(matrix));
    return inv_matrix;
}

vector<vector<float>> computeInverse(vector<vector<float>> matrix)
{
    int n = matrix[0].size();
    if (n < 16)
    {
        //inverse of matrix ... inverse(matrix);
        return inverse(matrix);
    }
    else
    {
        int nl = round(n / 2);

        cout << "nl is: " << nl << '\n';

        vector<vector<float>> inv_matrix_tl = computeInverse(getSection(matrix, 0, 0, nl, nl)); //paralellize?

        vector<vector<float>> inv_matrix_br = computeInverse(getSection(matrix, nl, nl, n, n)); //parallelize?
        vector<vector<float>> inv_matrix_tr = getSection(matrix, 0, nl, nl, n);
        inv_matrix_tr = mulitplyMatrices(mulitplyMatrices(turnNegative(inv_matrix_tl), inv_matrix_tr), inv_matrix_br);
        vector<vector<float>> inv_matrix_bl;
        vector<float> temp;
        //create matrix of random value with size nxn
        for (int i = 0; i < nl; i++)
        {
            for (int j = 0; j < nl; j++)
            {
                temp.push_back(0);
            }
            inv_matrix_bl.push_back(temp);
            temp.clear();
        }
        //combine matricies
        matrix = combine(inv_matrix_tl, inv_matrix_tr, inv_matrix_bl, inv_matrix_br);
    }
    return matrix;
}

void rinverse(int n)
{

    vector<vector<float>> matrix;
    vector<float> temp;

    srand(time(NULL));

    //create matrix of random value with size nxn
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            temp.push_back((float)rand() / (RAND_MAX));
        }

        matrix.push_back(temp);
        temp.clear();
    }

    //set values to 0 below diagonal
    for (int x = 0; x < matrix[0].size(); x++)
    {
        for (int y = x + 1; y < matrix[0].size(); y++)
        {
            matrix[y][x] = 0;
        }
    }

    printMatrix(matrix);
    cout << '\n';
    printMatrix(computeInverse(matrix));
}

int main()
{
    clock_t tStart = clock();
    rinverse(20);
    printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
    return 0;
}