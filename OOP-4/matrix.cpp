#include "matrix.h"

bool isThereSenseToCheckPrimes (int i, int j, int TheLeastPrime, int size) {
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


std::vector<int> new_vector_of_elements(int size, const std::string& matrix_name){
    std::vector<int> vector_of_elements;
    int element;
    for(int i = 0; i < size*size; i++){
        std::cout << "Введите значение элемента " << (i / size) + 1 << "-й строки " <<
        (i % size) + 1 << "-го столбца матрицы " << matrix_name << ": ";
        std::cin >> element;
        vector_of_elements.push_back(element);
    }
    return vector_of_elements;
}


void build_matrix(int**& matrix, std::vector<int> vector_of_elements, int size){
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
        for (int j = 0; j < size; j++) {
            matrix[i][j] = vector_of_elements[i*size+j];
        }
    }
}


void analyze_matrix_C(int**& C, bool& IsThereAnyPrimeNumbers, int& TheLeastPrime,
                              int*& IndexesOfTheLeastElement, int& SumOfSquaredNegativeElements, int size){
    int value, TheLeastElement;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // Здесь осуществляется поиск наименьшего элемента в матрице.
            value = C[i][j];
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
            if ((value > 1) && (isThereSenseToCheckPrimes(i, j, TheLeastPrime, size)) && (isAPrimeNumber(value))) {
                if ((!IsThereAnyPrimeNumbers) || (value < TheLeastPrime)) {
                    TheLeastPrime = value;
                    IsThereAnyPrimeNumbers = true;
                }
            }
        }
    }
}


void build_B_type_matrixes(int**& B, int**& C, int**& B_T, int**& B_T_plus_C, int size)
{
    for (int i = 0; i < size; i++) {
        B_T[i] = new int[size];
        for (int j = 0; j < size; j++) {
            B_T[i][j] = B[j][i];
        }
    }
    for (int i = 0; i < size; i++) {
        B_T_plus_C[i] = new int[size];
        for (int j = 0; j < size; j++) {
            B_T_plus_C[i][j] = B_T[i][j] + C[i][j];
        }
    }
}


void build_matrix_A(int**& A, int** B_T_plus_C, int size)
{
    int value;
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
}