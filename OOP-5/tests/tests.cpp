#include "gtest/gtest.h"
#include "matrix.h"
#include <iostream>
#include <vector>


// Создание матрицы 3х3 с элементами 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16.
TEST(build_matrix, case_1){
    int size = 4;
    int **C = new int *[size];
    build_matrix(C, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}, size);

    // Проверка на правильное заполнение матрицы.
    for(int i = 0; i < 16; i++){
        EXPECT_EQ(C[i/size][i%size], i+1);
    }
}


// Анализ матрицы 3х3 с элементами 9, 0, 33, -5, -21, 3, 6, -2, 0.
TEST(analyze_matrix_C, case_1){
    int TheLeastPrimeInSector = 0;
    bool IsThereAnyPrimeNumbers = false;
    int *IndexesOfTheLeastElement = new int[2];
    int SumOfSquaredNegativeElements = 0;
    int size = 3;
    int **C = new int *[size];
    std::vector<int> vector_of_int = {9, 0, 33, -5, -21, 3, 6, -2, 0};

    build_matrix(C, vector_of_int, size);
    analyze_matrix_C(C, IsThereAnyPrimeNumbers, TheLeastPrimeInSector, IndexesOfTheLeastElement, SumOfSquaredNegativeElements, size);

    // Проверка на правильное заполнение матрицы.
    for(int i = 0; i < size*size; i++){
        EXPECT_EQ(C[i/size][i%size], vector_of_int[i]);
    }

    // Проверка на правильный анализ матрицы C.
    EXPECT_TRUE(IsThereAnyPrimeNumbers);
    EXPECT_EQ(TheLeastPrimeInSector, 3);
    EXPECT_EQ(IndexesOfTheLeastElement[0], 1);
    EXPECT_EQ(IndexesOfTheLeastElement[1], 1);
    EXPECT_EQ(SumOfSquaredNegativeElements, 470);
}


// Анализ матрицы 2х2 с элементами 6, 2, -5, 0
TEST(analyze_matrix_C, case_2){
    int TheLeastPrimeInSector = 0;
    bool IsThereAnyPrimeNumbers = false;
    int *IndexesOfTheLeastElement = new int[2];
    int SumOfSquaredNegativeElements = 0;
    int size = 2;
    int **C = new int *[size];
    std::vector<int> vector_of_int = {6, 2, 5, 0};

    build_matrix(C, vector_of_int, size);
    analyze_matrix_C(C, IsThereAnyPrimeNumbers, TheLeastPrimeInSector, IndexesOfTheLeastElement, SumOfSquaredNegativeElements, size);

    // Проверка на правильное заполнение матрицы.
    for(int i = 0; i < size*size; i++){
        EXPECT_EQ(C[i/size][i%size], vector_of_int[i]);
    }

    // Проверка на правильный анализ матрицы C.
    EXPECT_FALSE(IsThereAnyPrimeNumbers);
    EXPECT_EQ(TheLeastPrimeInSector, 0);
    EXPECT_EQ(IndexesOfTheLeastElement[0], 1);
    EXPECT_EQ(IndexesOfTheLeastElement[1], 1);
    EXPECT_EQ(SumOfSquaredNegativeElements, 0);
}


// Построение матрицы B_T транспонированием матрицы B и суммирование её с другой матрицей C. Размерность: 3х3.
// Элементы в матрице B: 1, 2, 3, 4, 5, 6, 7, 8, 9. Элементы в матрице C: -1, -4, -7, -2, -5, -8, -3, -6, -9.
TEST(build_B_type_matrixes, case_1){
    int size = 3;
    int **B = new int *[size];
    int **C = new int *[size];
    int **B_T = new int *[size];
    int **B_T_plus_C = new int *[size];
    std::vector<int> vectorB = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> vectorC = {-1, -4, -7, -2, -5, -8, -3, -6, -9};

    build_matrix(B, vectorB, size);
    build_matrix(C, vectorC, size);

    // Проверка на правильное заполнение матрицы.
    for(int i = 0; i < size*size; i++){
        EXPECT_EQ(B[i/size][i%size], vectorB[i]);
        EXPECT_EQ(C[i/size][i%size], vectorC[i]);
    }

    build_B_type_matrixes(B, C, B_T, B_T_plus_C, size);

    // Проверка на правильное заполнение транспонированной матрицы B_T, и суммы матриц B_T_plus_C.
    for(int i = 0; i < size*size; i++){
        EXPECT_EQ(B_T[i/size][i%size], vectorC[i]*(-1));
        EXPECT_EQ(B_T_plus_C[i/size][i%size], 0);
    }
}


// Построение матрицы B_T транспонированием матрицы B и суммирование её с другой матрицей C. Размерность: 3х3.
// Элементы в матрице B: 1, 2, 3, 4, 5, 6, 7, 8, 9. Элементы в матрице C: -1, -2, -3, -4, -5, -6, -7, -8, -9.
TEST(build_B_type_matrixes, case_2){
    int size = 3;
    int **B = new int *[size];
    int **C = new int *[size];
    int **B_T = new int *[size];
    int **B_T_plus_C = new int *[size];
    std::vector<int> vectorB = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> vectorC = {-1, -2, -3, -4, -5, -6, -7, -8, -9};

    build_matrix(B, vectorB, size);
    build_matrix(C, vectorC, size);

    // Проверка на правильное заполнение матрицы.
    for(int i = 0; i < size*size; i++){
        EXPECT_EQ(B[i/size][i%size], vectorB[i]);
        EXPECT_EQ(C[i/size][i%size], vectorC[i]);
    }

    build_B_type_matrixes(B, C, B_T, B_T_plus_C, size);

    // Проверка на правильное заполнение транспонированной матрицы B_T, и суммы матриц B_T_plus_C.
    for(int i = 0; i < size*size; i++){
        EXPECT_EQ(B_T[i/size][i%size], i/size+1+(i%size)*size);
        EXPECT_EQ(B_T_plus_C[i/size][i%size], (-2)*(i/size) + 2*(i%size));
    }
}


// Построение матрицы А путём произведения матрицы B на саму себя. Размерность: 3х3.
// Элементы в матрице B: -1, 1, 3, -3, -1, 1, -5, -3, -1.
TEST(build_matrix_A, case_1){
    int size = 3;
    int **A = new int *[size];
    int **B = new int *[size];
    std::vector<int> vectorB = {-1, 1, 3, -3, -1, 1, -5, -3, -1};

    build_matrix(B, vectorB, size);

    // Проверка на правильное заполнение матрицы.
    for(int i = 0; i < size*size; i++){
        EXPECT_EQ(B[i/size][i%size], vectorB[i]);
    }

    build_matrix_A(A, B, size);

    int list_result[9] = {-17, -11, -5, 1, -5, -11, 19, 1, -17};
    // Проверка на правильное заполнение матрицы A.
    for(int i = 0; i < size*size; i++){
        EXPECT_EQ(A[i/size][i%size], list_result[i]);
    }
}