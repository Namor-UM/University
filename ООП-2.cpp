#include <iostream>

/**
 * НАЗНАЧЕНИЕ ФУНКЦИИ
 * Рекурсивная функция возвращает количество цифр amount в числе target.
 * В начале рекурсии amount = 0.
**/

int CalculateAmountOfChars(int target, int amount=0) {
    amount += 1;
    if (target/10 == 0) {
        return amount;
    }
    return CalculateAmountOfChars(target/10, amount);
}

/**
 * УСЛОВИЕ
 * Поступает последовательность целых положительных чисел, 0 — конец
 * последовательности. Определить, в каком из чисел больше всего цифр.
 *
 * МОЁ ЗАМЕЧАНИЕ
 * Если было передано более одного числа с максимальным количеством цифр,
 * то программа возвращает первое из них.
 */

int main() {
    int newNumber = 1;
    int MaxAmountOfChars = 0;
    int Winner, AmountOfChars;
    while (newNumber > 0) {
        std::cin >> newNumber;
        AmountOfChars = CalculateAmountOfChars(newNumber);
        if (AmountOfChars > MaxAmountOfChars) {
            Winner = newNumber;
            MaxAmountOfChars = AmountOfChars;
        }
    }
    std::cout << "Число с наибольшим кол-вом цифр: " << Winner;
    return 0;
}
