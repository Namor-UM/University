#include <iostream>
#include <string>


const std::string operators = "+-*/";
const std::string numbers = "0123456789";
const std::string brackets = "()";


bool is_expression_typed_correctly(std::string expression){
    int amount_of_unpaired_brackets = 0;
    bool is_there_any_numbers = false;
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
        else if (brackets.find(expression[i]) != std::string::npos){                                                                             // Если i-тый символ — скобка, то...
            if(expression[i] == '(')
                amount_of_unpaired_brackets++;
            else
                amount_of_unpaired_brackets--;
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
     * Предполагается, что функция будет рекурсивной.
     * Алгоритм.
     * 1. Ищем скобки!
     *    Если найдена открывающая скобка, то ищем закрывающую, пока "баланс скобок" не станет равным нулю.
     *    После нахождения рекурсивно вызываем RPN отрезка выражения между этими скобками.
     *    Пара скобок заменяется на знаки "=".
     * 2. Ищем операторы умножения и деления!
     *    Если найден такой оператор, то:
     *    — если соседствует с цифрами, то выделяем отрезок от первой цифры левого операнда до последней цифры правого операнда.
     *    — если соседствует со знаками "=", то выделяем отрезок от левого "=" левого операнда до правого "=" правого операнда.
     *    — если только левый сосед — знак "=", то выделяем отрезок от левого "=" левого операнда до последней цифры правого операнда.
     *    — если только правый сосед — знак "=", то выделяем отрезок от первой цифры левого операнда до правого "=" правого операнда.
     *    Ограждаем отрезок знаками "=".
     *    После каждого операнда ставим пробел.
     *    Если на отрезке есть знаки "=", не считая границы, то беспробельно удаляем их.
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
        if(expression[count] == '('){
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
            reverse_polish_notation(buffer);
            expression.erase(left_border, right_border-left_border+1);
            std::cout << expression.length() << std::endl;
            expression.insert(left_border, "=" + buffer + "=");
            left_border = -1;
        }
        count++;
    }

    // 2. Ищем операторы умножения и деления!
    count = 0;
    is_operator_available_to_transform = true;
    //std::cout << "Ищем операторы умножения и деления!\n" << std::endl;
    while(count < expression.length()){
        buffer = "";
        //std::cout << "count = " << count << std::endl;
        //std::cout << "expression = " << expression << std::endl;
        //std::cout << "is_operator_available_to_transform = " << is_operator_available_to_transform << std::endl;
        //std::cout << std::endl;
        if(expression[count] == '='){
            is_operator_available_to_transform = not(is_operator_available_to_transform);
        }
        if(((expression[count] == '*') or (expression[count] == '/')) and (is_operator_available_to_transform)){
            if(expression[count-1] == '='){
                subcount = count-2;
                while(expression[subcount] != '='){
                    subcount--;
                }
                left_border = subcount;
            }
            else{
                subcount = count-1;
                while((operators.find(expression[subcount]) == std::string::npos) and (subcount > 0)){
                    subcount--;
                }
                if(subcount == 0){
                    subcount--;
                }
                left_border = subcount+1;
            }
            if(expression[count+1] == '='){
                subcount = count+2;
                while(expression[subcount] != '='){
                    subcount++;
                }
                right_border = subcount;
            }
            else{
                subcount = count+1;
                while((operators.find(expression[subcount]) == std::string::npos) and (subcount < expression.length())){
                    subcount++;
                }
                right_border = subcount-1;
            }
            expression.insert(left_border, "=");
            left_border++;
            right_border++;
            count++;
            if(right_border+1 == expression.length()){
                expression.push_back('=');
            }
            else{
                expression.insert(right_border+1, "=");
            }
            expression.insert(count, " ");
            right_border++;
            count++;
            expression.insert(right_border+1, " ");
            right_border++;

            for(int i = left_border; i <= right_border; i++){
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
            for(int i = count+1; i <= right_border; i++){
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
    //std::cout << "Ищем операторы сложения и вычитания!\n" << std::endl;
    while(count < expression.length()){
        buffer = "";
        //std::cout << "count = " << count << std::endl;
        //std::cout << "expression = " << expression << std::endl;
        //std::cout << "is_operator_available_to_transform = " << is_operator_available_to_transform << std::endl;
        //std::cout << std::endl;
        if(expression[count] == '='){
            is_operator_available_to_transform = not(is_operator_available_to_transform);
        }
        if(((expression[count] == '+') or (expression[count] == '-')) and (is_operator_available_to_transform)){
            if(expression[count-1] == '='){
                subcount = count-2;
                while(expression[subcount] != '='){
                    subcount--;
                }
                left_border = subcount;
            }
            else{
                subcount = count-1;
                while((operators.find(expression[subcount]) == std::string::npos) and (subcount > 0)){
                    subcount--;
                }
                if(subcount == 0){
                    subcount--;
                }
                left_border = subcount+1;
            }
            if(expression[count+1] == '='){
                subcount = count+2;
                while(expression[subcount] != '='){
                    subcount++;
                }
                right_border = subcount;
            }
            else{
                subcount = count+1;
                while((operators.find(expression[subcount]) == std::string::npos) and (subcount < expression.length())){
                    subcount++;
                }
                right_border = subcount-1;
            }
            expression.insert(left_border, "=");
            left_border++;
            right_border++;
            count++;
            if(right_border+1 == expression.length()){
                expression.push_back('=');
            }
            else{
                expression.insert(right_border+1, "=");
            }
            expression.insert(count, " ");
            right_border++;
            count++;
            expression.insert(right_border+1, " ");
            right_border++;

            for(int i = left_border; i <= right_border; i++){
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
            for(int i = count+1; i <= right_border; i++){
                buffer += expression[i];
            }
            expression.erase(count+1, right_border-count);
            expression.insert(count, buffer);
            count += buffer.length();
        }
        count++;
    }

    // 4. Удаляем оставшуюся пару знаков "="!
    expression.pop_back();
    expression.erase(0, 1);
}


int main() {
    setlocale(LC_ALL, "ru");
    std::string expression;

    // 1. Считываем строку.
    std::cout << "Наберите выражение без пробелов: ";
    std::cin >> expression;

    // 2. Проверим выражение на правильность ввода.
    if(!is_expression_typed_correctly(expression)){
        std::cout << "\nВыражение набрано неправильно!\n";
        return 0;
    }
    std::cout << "\nВыражение набрано правильно!\n";

    // 3. Преобразуем его в обратную польскую запись.
    reverse_polish_notation(expression);

    std::cout << expression;
}
