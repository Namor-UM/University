/**
 * УСЛОВИЕ
 * В двумерном массиве C, состоящем из n*n целых чисел, вычислить:
 * - индексы наименьшего элемента;
 * - сумму квадратов отрицательных элементов;
 * - минимальное простое число среди элементов, расположенных в
 * верхнем левом и нижнем правом секторах матрицы.
 * Для заданной матрицы C(n*n) и матрицы того же типа и размерности B(n*n)
 * найти значение выражения A = (B^T + C)^2
 */


# include <iostream>
# include <cmath>
int size;

bool isThereSenseToCheckPrimes (int i, int j, int TheLeastPrime) {
    if (TheLeastPrime != 2) {
        if (((i < size/2) && (j < size/2)) || ((i >= size/2) && (j >= size/2))){
            return true;
        }
    }
    return false;
}


bool isAPrimeNumber(int number) {
    for (int i = 2; i < sqrt(number); i++) {
        if (number % 1 == 0) {
            return false;
        }
    }
    return true;
}


int main() {
    int value, SumOfSquaredNegativeElements, TheLeastPrime, TheLeastElement;
    bool IsThereAnyPrimeNumbers;
    int *IndexesOfTheLeastElement = new int[2];
    std::cout << "Введите размер квадратных матриц: ";
    std::cin >> size;
    std::cout << "\n";
    int **C = new int *[size];
    // Здесь происходит заполнение матрицы C и вычисление первых трёх пунктов условия.
    for (int i = 0; i < size; i++) {
        C[i] = new int[size];
        for (int j = 0; j < size; j++) {
            std::cout << "Введите значение элемента " << i + 1 << "-й строки " << j + 1 << "-го столбца матрицы C: ";
            std::cin >> value;
            C[i][j] = value;

            // Здесь осуществляется поиск наименьшего элемента в матрице.
            if (i == 0 && j == 0) {
                TheLeastElement = value;
                IndexesOfTheLeastElement[0] = 0;
                IndexesOfTheLeastElement[1] = 0;
            } else if (value < TheLeastElement) {
                TheLeastElement = value;
                IndexesOfTheLeastElement[0] = i;
                IndexesOfTheLeastElement[1] = j;
            }

            // Здесь осуществляется вычисление суммы квадратов всех отрицательных чисел.
            if (value < 0) {
                SumOfSquaredNegativeElements += value * value;
            }

            // Здесь осуществляется поиск наименьшего простого числа в вышеуказанном секторе.
            if ((value > 1) && (isThereSenseToCheckPrimes(i, j, TheLeastPrime)) && (isAPrimeNumber(value))) {
                if ((!IsThereAnyPrimeNumbers) || (value < TheLeastPrime)) {
                    TheLeastPrime = value;
                    IsThereAnyPrimeNumbers = true;
                }
            }
        }
    }


    // Здесь происходит создание и заполнение матрицы B.
    int **B = new int *[size];
    for (int i = 0; i < size; i++) {
        B[i] = new int[size];
        for (int j = 0; j < size; j++) {
            std::cout << "Введите значение элемента " << i+1 << "-й строки " << j+1 << "-го столбца матрицы B: ";
            std::cin >> value;
            B[i][j] = value;
        }
    }

    // Здесь происходит создание матрицы B^T.
    int **B_T = new int *[size];
    for (int i = 0; i < size; i++) {
        B_T[i] = new int[size];
        for (int j = 0; j < size; j++) {
            B_T[i][j] = B[j][i];
        }
    }


    // Здесь происходит создание матрицы B^T+C
    int **B_T_plus_C = new int *[size];
    for (int i = 0; i < size; i++) {
        B_T_plus_C[i] = new int[size];
        for (int j = 0; j < size; j++) {
            B_T_plus_C[i][j] = B_T[i][j] + C[i][j];
        }
    }


    // Здесь происходит создание матрицы A.
    int **A = new int *[size];
    for (int i = 0; i < size; i++) {
        A[i] = new int[size];
        for (int j = 0; j < size; j++) {
            value = 0;
            for (int k = 0; k < size; k++) {
                value += B_T_plus_C[k][j]*B_T_plus_C[i][k];
            }
            A[i][j] = value;
        }
    }


    /**
     * Здесь формируется отчёт о результатах всех вычислений
     */
    std::cout << "\nМатрица С:";
    for (int i = 0; i < size; i++) {
        std::cout << "\n";
        for (int j = 0; j < size; j++) {
            std::cout << C[i][j] << "\t\t";
        }
    }
    std::cout << "\nАдрес наименьшего элемента — ["<<IndexesOfTheLeastElement[0]<<", "<<IndexesOfTheLeastElement[1]<<"]\n";
    std::cout << "Сумма квадратов всех отрицательных элементов = " << SumOfSquaredNegativeElements<<std::endl;
    if (!IsThereAnyPrimeNumbers) {
        std::cout << "Ни одного простого числа в секторе не обнаружено!"  << std::endl;
    }
    else {
        std::cout << "Наименьшее простое число в секторе = " << TheLeastPrime << std::endl;
    }

    std::cout << "\nМатрица B:";
    for (int i = 0; i < size; i++) {
        std::cout << "\n";
        for (int j = 0; j < size; j++) {
            std::cout << B[i][j] << "\t\t";
        }
    }

    std::cout << "\n\nМатрица B_T:";
    for (int i = 0; i < size; i++) {
        std::cout << "\n";
        for (int j = 0; j < size; j++) {
            std::cout << B_T[i][j] << "\t\t";
        }
    }

    std::cout << "\n\nМатрица A:";
    for (int i = 0; i < size; i++) {
        std::cout << "\n";
        for (int j = 0; j < size; j++) {
            std::cout << A[i][j] << "\t\t";
        }
    }
}
