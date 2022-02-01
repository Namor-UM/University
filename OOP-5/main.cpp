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


#include <iostream>
//#include "print_console.h"
#include "matrix.h"
#include <vector>


int main() {
    int size, TheLeastPrime;
    bool IsThereAnyPrimeNumbers;
    int *IndexesOfTheLeastElement = new int[2];
    int SumOfSquaredNegativeElements = 0;
    std::cout << "Введите размер квадратных матриц: ";
    std::cin >> size;
    std::cout << "\n";
    int **C = new int *[size];

    // Здесь происходит заполнение матрицы C и вычисление первых трёх пунктов условия.

    std::vector<int> vector_of_elements = new_vector_of_elements(size, "C");

    build_matrix(C, vector_of_elements, size);
    analyze_matrix_C(C, IsThereAnyPrimeNumbers, TheLeastPrime, IndexesOfTheLeastElement,
                             SumOfSquaredNegativeElements, size);

    // Здесь происходит создание матриц B, B^T, B^T+C.
    int **B = new int *[size];
    int **B_T = new int *[size];
    int **B_T_plus_C = new int *[size];
    vector_of_elements.clear();
    vector_of_elements = new_vector_of_elements(size, "B");
    build_matrix(B, vector_of_elements, size);
    build_B_type_matrixes(B, C, B_T, B_T_plus_C, size);


    // Здесь происходит создание матрицы A.
    int **A = new int *[size];
    build_matrix_A(A, B_T_plus_C, size);


    /**
     * Здесь формируется отчёт о результатах всех вычислений
     */
    //print_matrix(A, B, B_T, C,
    //             IndexesOfTheLeastElement, SumOfSquaredNegativeElements, TheLeastPrime, size, IsThereAnyPrimeNumbers);
}