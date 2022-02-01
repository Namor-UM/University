#include "print_ostream.h"

void print_matrix_ostream(std::ostream& Out, int** Matrix, int size)
{
    for (int i = 0; i < size; i++) {
        Out << "\n";
        for (int j = 0; j < size; j++) {
            Out << Matrix[i][j] << "\t\t";
        }
    }
    Out << "\n";
}
