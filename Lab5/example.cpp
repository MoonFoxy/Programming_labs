/*степень матрицы*/
#include <iostream>
#include <iomanip>
using namespace std;

int **CreateArray (int N)
{   int i,j;
    int **arr = new int*[N];
    for (i = 0; i<N; i++)
        arr[i] = new int[N];

    for (i = 0; i<N; i++)
        for (j = 0; j<N; j++)
            arr[i][j] = 0;

    return arr;
}

void DeleteArray (int **arr, int N)
{   for (int i = 0; i<N; i++)
        delete [] arr[i];
    delete [] arr;
}

void FillRandom (int **arr, int N, int bottom, int top)
{   if (top <= bottom)
    {   cout << "Wrong limits";
        return;
    }

    int i,j;
    for (i = 0; i<N; i++)
        for (j = 0; j<N; j++)
            arr[i][j] = rand()% (top-bottom) + bottom + 1;
}

void PrintArray (int **arr, int N)
{   int i,j;
    for (i = 0; i<N; i++)
    {   for (j = 0; j<N; j++)
            cout << setw(16) << arr[i][j];
        cout << '\n';
    }
    cout << '\n';
}

void PowArray (int **res, int **arr, int N, int pow)
{   int i, j, k, p = 1;
    int **temp = CreateArray (N);

    for (i = 0; i<N; i++)
            for (j = 0; j<N; j++)
                res[i][j] = arr[i][j];

    while (++p <= pow)
    {   for (i = 0; i<N; i++)
            for (j = 0; j<N; j++)
                for (k = 0; k<N; k++)
                    temp[i][j] += res[i][k] * arr[k][j];

        for (i = 0; i<N; i++)
            for (j = 0; j<N; j++)
            {   res[i][j] = temp[i][j];
                temp[i][j] = 0;
            }
    }
    DeleteArray (temp, N);
}


int main()
{   setlocale (LC_CTYPE, "Russian");
    srand ((unsigned int) time (NULL));

    int N, p, **arr, **res;

    cout << "Размерность матрицы N = ";
    cin >> N;

    arr = CreateArray (N);
    FillRandom (arr, N, 1, 9);
    PrintArray (arr, N);

    cout << "\n\nСтепень, в которую матрица возводится P = ";
    cin >> p;

    res = CreateArray (N);

    PowArray (res, arr, N, p);
    PrintArray (res, N);

    DeleteArray (res, N);
    DeleteArray (arr, N);

    cin.sync();
    cin.get();
    return 0;
}
