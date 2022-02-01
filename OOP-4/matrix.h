#pragma once
#include <iostream>
#include <cmath>
#include <vector>

std::vector<int> new_vector_of_elements(int size, const std::string& matrix_name);

void build_matrix(int**& matrix, std::vector<int> vector_of_elements, int size);

void analyze_matrix_C(int**& C, bool& IsThereAnyPrimeNumbers, int& TheLeastPrime,
                              int*& IndexesOfTheLeastElement, int& SumOfSquaredNegativeElements, int size);

void build_B_type_matrixes(int**& B, int**& C, int**& B_T, int**& B_T_plus_C, int size);

void build_matrix_A(int**& A, int** B_T_plus_C, int size);