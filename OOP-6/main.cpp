#include <iostream>
#include "base64.h"

int main() {
    setlocale(LC_ALL, "ru");
    std::string operand = "Monty Python's Flying Circus";

    operand = encode(operand);
    std::cout << "Закодировано: " << operand << std::endl;

    operand = decode(operand);
    std::cout << "Раскодировано: " << operand << std::endl;
    return 0;
}
