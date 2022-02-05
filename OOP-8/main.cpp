#include <iostream>
#include <string>
#include <cmath>


const std::string operators = "+-*/";
const std::string numbers = "0123456789";
const std::string brackets = "()";


bool is_expression_typed_correctly(std::string expression){
    int amount_of_unpaired_brackets = 0;
    bool is_there_any_numbers = false;
    if(expression.empty()){                                                                                                                     // Если это пустая строка, то выражение записано неправильно.
        return false;
    }
    for(int i = 0; i < expression.length(); i++){
        if (operators.find(expression[i]) != std::string::npos) {                                                                               // Если i-тый символ — оператор, то...
            if ((i == 0) or (i == expression.length()-1)) {                                                                                     // Если оператор стоит в начале или в конце строки, то выражение записано неправильно.
                return false;
            }
            if (((numbers.find(expression[i-1]) == std::string::npos) and (brackets.find(expression[i-1]) == std::string::npos))          // Если оператор не соседствует справа и слева с числами или скобками, то выражение записано неправильно.
            or ((numbers.find(expression[i+1]) == std::string::npos)) and (brackets.find(expression[i+1]) == std::string::npos)) {
                return false;
            }
        }
        else if (numbers.find(expression[i]) != std::string::npos) {                                                                             // Если i-тый символ — цифра, то...
            is_there_any_numbers = true;
            if (i != 0) {
                if (expression[i - 1] == ')') {                                                                                                  // Если левым соседом цифры является закрывающая скобка, то выражение записано неправильно.
                    return false;
                }
            }
            if(i != expression.length()-1) {
                if (expression[i + 1] == '(') {                                                                                                  // Если правым соседом цифры является открывающая скобка, то выражение записано неправильно.
                    return false;
                }
            }
        }
        else if (brackets.find(expression[i]) != std::string::npos){                                                                             // Если i-тый символ = '(', то баланс скобок увеличиваем на единицу.
            if(expression[i] == '(') {
                amount_of_unpaired_brackets++;
                if((expression[i-1] == ')' or (expression[i+1] == ')'))){                                                                        // Если в выражении имеются конструкции вида (...)(...) или ...()..., то выражение записано неправильно.
                    return false;
                }
            }
            else
                amount_of_unpaired_brackets--;                                                                                                   // // Если i-тый символ = ')', то баланс скобок уменьшаем на единицу.
            if(amount_of_unpaired_brackets < 0)                                                                                                  // Если в какой-то момент закрывающих скобок больше, чем открывающих, то выражение записано неправильно.
                return false;
        }
        else {
            return false;
        }
    }
    if((amount_of_unpaired_brackets != 0) or !(is_there_any_numbers))
        return false;
    return true;

}


/*
     * Алгоритм преобразования выражения в обратную польскую запись.
     * 1. Ищем скобки!
     *    Если найдена открывающая скобка, то ищем закрывающую, пока "баланс скобок" не станет равным нулю.
     *    После нахождения рекурсивно вызываем RPN отрезка выражения между этими скобками.
     *    Пара скобок заменяется на знаки "=".
     * 2. Ищем операторы умножения и деления!
     *    Если найден такой оператор, то:
     *    — если оператор в качестве соседа слева имеет знак "=", то левая граница = индекс следующего знака "=".
     *    — если оператор в качестве соседа слева имеет число, то левая граница = индекс цифры самого старшего разряда числа слева.
     *    — если оператор в качестве соседа справа имеет знак "=", то правая граница = индекс следующего знака "=".
     *    — если оператор в качестве соседа справа имеет число, то правая граница = индекс цифры самого младшего разряда числа справа.
     *    Ограждаем отрезок знаками "=".
     *    После каждого операнда ставим пробел.
     *    Беспробельно удаляем все знаки "=" на отрезке, не считая границы.
     *    Меняем местами правый операнд, считая пробел, и оператор.
     * 3. Ищем операторы сложения и вычитания!
     *    На этом этапе проделываем те же действия, что и на прошлом.
     * 4. Удаляем оставшуюся пару знаков "="!
     */
void reverse_polish_notation(std::string& expression){
    int count = 0;
    int subcount;
    int left_border = -1;
    int right_border;
    int amount_of_unpaired_brackets = 0;
    bool is_operator_available_to_transform;
    std::string buffer;

    // 1. Ищем скобки!
    while(count < expression.length()){
        if(expression[count] == '('){                                                                                       // Если найдена открывающая скобка, то ищем закрывающую, пока "баланс скобок" не станет равным нулю.
            if (left_border == -1){
                left_border = count;
            }
            amount_of_unpaired_brackets++;
        } else if(expression[count] == ')'){
            amount_of_unpaired_brackets--;
        }
        if((left_border != -1) and (amount_of_unpaired_brackets == 0)){
            right_border = count;
            buffer = "";
            for(int i = left_border+1; i < right_border; i++){
                buffer += expression[i];
            }
            reverse_polish_notation(buffer);                                                                            // После нахождения закрывающей скобки рекурсивно вызываем RPN отрезка выражения между этими скобками.
            expression.erase(left_border, right_border-left_border+1);                                                  // Выражение в скобках заменяется на результат рекурсивно вызванной RPN.
            expression.insert(left_border, "=" + buffer + "=");                                                        // Пара скобок заменяется на знаки "=".
            left_border = -1;
        }
        count++;
    }

    // 2. Ищем операторы умножения и деления!
    count = 0;
    is_operator_available_to_transform = true;
    while(count < expression.length()){
        buffer = "";
        if(expression[count] == '='){
            is_operator_available_to_transform = not(is_operator_available_to_transform);
        }
        if(((expression[count] == '*') or (expression[count] == '/')) and (is_operator_available_to_transform)){            // Если найден такой оператор, то:
            if(expression[count-1] == '='){                                                                                 // — если оператор в качестве соседа слева имеет знак "=", то левая граница = индекс следующего знака "=".
                subcount = count-2;
                while(expression[subcount] != '='){
                    subcount--;
                }
                left_border = subcount;
            }
            else{                                                                                                           // — если оператор в качестве соседа слева имеет число, то левая граница = индекс цифры самого старшего разряда числа слева.
                subcount = count-1;
                while((operators.find(expression[subcount]) == std::string::npos) and (subcount > 0)){
                    subcount--;
                }
                if(subcount == 0){
                    subcount--;
                }
                left_border = subcount+1;
            }
            if(expression[count+1] == '='){                                                                                 // — если оператор в качестве соседа справа имеет знак "=", то правая граница = индекс следующего знака "=".
                subcount = count+2;
                while(expression[subcount] != '='){
                    subcount++;
                }
                right_border = subcount;
            }
            else{                                                                                                           // — если оператор в качестве соседа справа имеет число, то правая граница = индекс цифры самого младшего разряда числа справа.
                subcount = count+1;
                while((operators.find(expression[subcount]) == std::string::npos) and (subcount < expression.length())){
                    subcount++;
                }
                right_border = subcount-1;
            }

            expression.insert(left_border, "=");                                                                         // Ограждаем отрезок знаками "=".
            left_border++;
            right_border++;
            count++;
            if(right_border+1 == expression.length()){
                expression.push_back('=');
            }
            else{
                expression.insert(right_border+1, "=");
            }

            expression.insert(count, " ");                                                                               // После каждого операнда ставим пробел.
            right_border++;
            count++;
            expression.insert(right_border+1, " ");
            right_border++;

            for(int i = left_border; i <= right_border; i++){                                                               // Беспробельно удаляем все знаки "=" на отрезке, не считая границы.
                if(expression[i] == '='){
                    expression.erase(i, 1);
                    if(i == left_border){
                        left_border--;
                    }
                    if(i <= count){
                        count--;
                    }
                    right_border--;
                    i--;
                }
            }

            for(int i = count+1; i <= right_border; i++){                                                                   // Меняем местами правый операнд, считая пробел, и оператор.
                buffer += expression[i];
            }
            expression.erase(count+1, right_border-count);
            expression.insert(count, buffer);
            count += buffer.length();
        }
        count++;
    }

    // 3. Ищем операторы сложения и вычитания!
    count = 0;
    is_operator_available_to_transform = true;
    while(count < expression.length()){
        buffer = "";
        if(expression[count] == '='){
            is_operator_available_to_transform = not(is_operator_available_to_transform);
        }
        if(((expression[count] == '+') or (expression[count] == '-')) and (is_operator_available_to_transform)){            // Если найден такой оператор, то:
            if(expression[count-1] == '='){                                                                                 // — если оператор в качестве соседа слева имеет знак "=", то левая граница = индекс следующего знака "=".
                subcount = count-2;
                while(expression[subcount] != '='){
                    subcount--;
                }
                left_border = subcount;
            }
            else{                                                                                                           // — если оператор в качестве соседа слева имеет число, то левая граница = индекс цифры самого старшего разряда числа слева.
                subcount = count-1;
                while((operators.find(expression[subcount]) == std::string::npos) and (subcount > 0)){
                    subcount--;
                }
                if(subcount == 0){
                    subcount--;
                }
                left_border = subcount+1;
            }
            if(expression[count+1] == '='){                                                                                 // — если оператор в качестве соседа справа имеет знак "=", то правая граница = индекс следующего знака "=".
                subcount = count+2;
                while(expression[subcount] != '='){
                    subcount++;
                }
                right_border = subcount;
            }
            else{                                                                                                           // — если оператор в качестве соседа справа имеет число, то правая граница = индекс цифры самого младшего разряда числа справа.
                subcount = count+1;
                while((operators.find(expression[subcount]) == std::string::npos) and (subcount < expression.length())){
                    subcount++;
                }
                right_border = subcount-1;
            }

            expression.insert(left_border, "=");                                                                         // Ограждаем отрезок знаками "=".
            left_border++;
            right_border++;
            count++;
            if(right_border+1 == expression.length()){
                expression.push_back('=');
            }
            else{
                expression.insert(right_border+1, "=");
            }

            expression.insert(count, " ");                                                                               // После каждого операнда ставим пробел.
            right_border++;
            count++;
            expression.insert(right_border+1, " ");
            right_border++;

            for(int i = left_border; i <= right_border; i++){                                                               // Беспробельно удаляем все знаки "=" на отрезке, не считая границы.
                if(expression[i] == '='){
                    expression.erase(i, 1);
                    if(i == left_border){
                        left_border--;
                    }
                    if(i <= count){
                        count--;
                    }
                    right_border--;
                    i--;
                }
            }

            for(int i = count+1; i <= right_border; i++){                                                                   // Меняем местами правый операнд, считая пробел, и оператор.
                buffer += expression[i];
            }
            expression.erase(count+1, right_border-count);
            expression.insert(count, buffer);
            count += buffer.length();
        }
        count++;
    }

    // 4. Удаляем оставшуюся пару знаков "="!
    if(expression[0] == '='){
        expression.pop_back();
        expression.erase(0, 1);
    }
}


float operation_result(float operand_1, float operand_2, char operation){
    switch(operation){
        case '+':
            return operand_1 + operand_2;
        case '-':
            return operand_1 - operand_2;
        case '*':
            return operand_1 * operand_2;
        case '/':
            return operand_1 / operand_2;
        default:
            throw std::invalid_argument("Такой операции не определено!");
    }
}


/*
 * Алгоритм вычисления выражения в обратной польской записи.
 * 1. Создаём два массива под два операнда каждый!
 * 2. Обходим выражение!
 *    Если встречаем операнд, то...
 *    — если первый массив не заполнен целиком, то записываем операнд в первый массив.
 *    — иначе записываем операнд во второй массив.
 *    Если встречаем оператор, то...
 *    — если второй массив заполнен целиком, то производим операцию над операндами второго массива;
 *      результат записываем в первую ячейку второго массива, а вторую — опустошаем.
 *    — если второй массив хранит только один элемент, то производим операцию над вторым операндом первого массива и операндом второго массива;
 *      результат записываем во вторую ячейку первого массива, а второй массив опустошаем.
 *    — иначе производим операцию над операндами первого массива;
 *      результат записываем в первую ячейку первого массива, а вторую — опустошаем.
 * 3. Возвращаем содержимое первой ячейки первого массива.
 */
float calculate_rpn_expression(const std::string& expression){
    std::string buffer;
    int count = 0;
    int left_border, right_border;

    float array1[2] = {NAN, NAN};                                                                               // 1. Создаём два массива под два операнда каждый!
    float array2[2] = {NAN, NAN};

    while(count < expression.length()){                                                                         // 2. Обходим выражение!
        if(numbers.find(expression[count]) != std::string::npos){                                               // Если встречаем операнд, то...
            left_border = count;
            while(expression[count+1] != ' '){
                count++;
            }
            right_border = count;
            buffer = "";
            for(int i = left_border; i <= right_border; i++){
                buffer += expression[i];
            }
            if(std::isnan(array1[1])){                                                                       // — если первый массив не заполнен целиком, то записываем операнд в первый массив.
                if(std::isnan(array1[0])){
                    array1[0] = std::stof(buffer);
                }
                else{
                    array1[1] = std::stof(buffer);
                }
            }
            else{                                                                                               // — иначе записываем операнд во второй массив.
                if(std::isnan(array2[0])){
                    array2[0] = std::stof(buffer);
                }
                else{
                    array2[1] = std::stof(buffer);
                }
            }
        }
        else if(operators.find(expression[count]) != std::string::npos){                                        // Если встречаем оператор, то...
            if(!std::isnan(array2[1])){                                                                      // — если второй массив заполнен целиком, то
                array2[0] = operation_result(array2[0], array2[1], expression[count]);      //   производим операцию над операндами второго массива;
                array2[1] = NAN;                                                                                //   результат записываем в первую ячейку второго массива, а вторую — опустошаем.
            }
            else if(!std::isnan(array2[0])){                                                                 //  — если второй массив хранит только один элемент, то
                array1[1] = operation_result(array1[1], array2[0], expression[count]);      //    производим операцию над вторым операндом первого массива и операндом второго массива;
                array2[0] = NAN;                                                                                //    результат записываем во вторую ячейку первого массива, а второй массив опустошаем.
            }
            else{                                                                                               // — иначе
                array1[0] = operation_result(array1[0], array1[1], expression[count]);      //   производим операцию над операндами первого массива;
                array1[1] = NAN;                                                                                //   результат записываем в первую ячейку первого массива, а вторую — опустошаем.
            }
        }
        count++;
    }
    return array1[0];                                                                                           // 3. Возвращаем содержимое первой ячейки первого массива.
}


int main() {
    setlocale(LC_ALL, "ru");
    std::string expression;
    float result;

    // 1. Считываем строку.
    std::cout << "Наберите выражение без пробелов: ";
    std::cin >> expression;

    // 2. Проверим выражение на правильность ввода.
    if(!is_expression_typed_correctly(expression)){
        std::cout << "\nВыражение набрано неправильно!\n";
        return 0;
    }

    // 3. Преобразуем его в обратную польскую запись.
    reverse_polish_notation(expression);
    std::cout << "\nВыражение приведено к следующему виду: ";
    std::cout << expression << std::endl;

    result = calculate_rpn_expression(expression);
    std::cout << "Результат вычислений = " << result << std::endl;
    return 0;
}
