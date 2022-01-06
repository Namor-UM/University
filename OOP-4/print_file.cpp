#include "print_file.h"
#include "print_ostream.h"
#include <iostream>
#include <fstream>
#include <string>

void print_matrix(int** A, int** B, int** B_T, int** C,
                  int* IndexesOfTheLeastElement, int SumOfSquaredNegativeElements, int TheLeastPrime, int size,
                  bool IsThereAnyPrimeNumbers) {
    std::ofstream fout("matrix.txt");

    fout << "\nМатрица С:";
    print_matrix_ostream(fout, C, size);
    fout << "\nАдрес наименьшего элемента — [" << IndexesOfTheLeastElement[0] << ", " << IndexesOfTheLeastElement[1]
         << "]\n";
    fout << "Сумма квадратов всех отрицательных элементов = " << SumOfSquaredNegativeElements << "\n";
    if (!IsThereAnyPrimeNumbers) {
        fout << "Ни одного простого числа в секторе не обнаружено!\n";
    } else {
        fout << "Наименьшее простое число в секторе = " << TheLeastPrime << "\n";
    }

    fout << "\nМатрица B:";
    print_matrix_ostream(fout, B, size);

    fout << "\n\nМатрица B_T:";
    print_matrix_ostream(fout, B_T, size);

    fout << "\n\nМатрица A:";
    print_matrix_ostream(fout, A, size);

    fout.close();
}