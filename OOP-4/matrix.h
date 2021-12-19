#pragma once
#include <iostream>
#include <cmath>

void build_and_check_matrix_C(int**& C, bool& IsThereAnyPrimeNumbers, int& TheLeastPrime,
                              int*& IndexesOfTheLeastElement, int& SumOfSquaredNegativeElements, int size);

void build_B_type_matrixes(int**& B, int**& C, int**& B_T, int**& B_T_plus_C, int size);

void build_matrix_A(int**& A, int** B_T_plus_C, int size);