#include "print_console.h"
#include "print_ostream.h"

void print_console(int** A, int** B, int** B_T, int** C,
                   int* IndexesOfTheLeastElement, int SumOfSquaredNegativeElements, int TheLeastPrime, int size,
                   bool IsThereAnyPrimeNumbers)
{
    std::cout << "\nМатрица С:";
    print_matrix_ostream(std::cout, C, size);
    std::cout << "\nАдрес наименьшего элемента — ["<<IndexesOfTheLeastElement[0]<<", "<<IndexesOfTheLeastElement[1]<<"]\n";
    std::cout << "Сумма квадратов всех отрицательных элементов = " << SumOfSquaredNegativeElements<<std::endl;
    if (!IsThereAnyPrimeNumbers) {
        std::cout << "Ни одного простого числа в секторе не обнаружено!"  << std::endl;
    }
    else {
        std::cout << "Наименьшее простое число в секторе = " << TheLeastPrime << std::endl;
    }

    std::cout << "\nМатрица B:";
    print_matrix_ostream(std::cout, B, size);

    std::cout << "\n\nМатрица B_T:";
    print_matrix_ostream(std::cout, B_T, size);

    std::cout << "\n\nМатрица A:";
    print_matrix_ostream(std::cout, A, size);
}