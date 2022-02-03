#include "base64.h"
#include <cmath>
#include <string>
#include <iostream>


std::string base64_string = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


bool is_string_base64_encoded(std::string input, int& equality_sign_count){
    int equality_sign_position[2] = {0, 0};
    if((input.empty()) or (input.length() % 4 != 0)) {
        return false;
    }
    for(int i = 0; i < input.length(); i++){
        if(base64_string.find(input[i]) == std::string::npos){
            if((input[i] == '=') and (equality_sign_count < 2)){
                equality_sign_position[equality_sign_count] = i;
                equality_sign_count++;
            }
            else {
                return false;
            }
        }
    }
    for(int i = 0; i < equality_sign_count; i++){
        if(equality_sign_position[i] != input.length() - (equality_sign_count - i)){
            return false;
        }

    }
    return true;
}


std::string dec_to_bin(int number, int size){
    int mod;
    int char_count = 0;
    std::string result;
    while(number > 0){
        mod = number % 2;
        number /= 2;
        result.insert(0, 1, (char) (48+mod));
        char_count++;
    }
    while(result.length() < size){
        result.insert(0, 1, '0');
        char_count++;
    }
    return result;
}


int bin_to_dec(std::string bin, int size){
    int result = 0;
    for(int i = 0; i < size; i++){
        if(bin[i] == '1'){
            result += pow(2, size-i-1);
        }
    }
    return result;
}


std::string encode_parse_buffer_24(std::string buffer_24){
    std::string buffer_6, result;
    for(int i = 0; i < 4; i++){
        buffer_6 = "";
        for(int j = 0; j < 6;j++){
            buffer_6 += buffer_24[i*6 + j];
        }
        if(buffer_6 != "000000"){
            result += base64_string[bin_to_dec(buffer_6, 6)];
        }
        else{
            result += "=";
        }
    }
    return result;
}


std::string encode(const std::string& input){
    unsigned long amount_of_buffer_24_rewrites;
    std::string buffer_string, buffer_24, result;
    result = "";

    if(input.empty())                                                                   // 0. Если в строке 0 элементов, то возвращаем пустую строку.
        return "";

    for(char letter : input){                                                           // 1. Получаем ASCII-код каждого символа, переводим в двоичный вид и записываем в промежуточную строку.
        buffer_string += dec_to_bin((int) letter, 8);
    }

    while(buffer_string.length() % 3 != 0){                                             // 2. Дополняем строку подстроками "00000000", подставляемыми вместо битов, недостающих для буфера-24.
        buffer_string += "00000000";
    }

    amount_of_buffer_24_rewrites = buffer_string.length()/24;                           // 2.1. Считаем количество обновлений буфера-24.
    for(int i = 0; i < amount_of_buffer_24_rewrites; i++){
        buffer_24 = "";                                                                 // 3. Выгружаем в буфер-24 некоторые 24 символа промежуточной строки.
        for(int j = 0; j < 24; j++){
            buffer_24 += buffer_string[i*24 + j];
        }
        result += encode_parse_buffer_24(buffer_24);                           // 4. Прибавляем к итоговой строке символы, закодированные на основе данных буфера-24.

    }
    return result;                                                                      // 5. Возвращаем итоговую строку.
}


std::string decode(const std::string& input){
    unsigned long amount_of_buffer_8_rewrites;
    int equality_sign_count = 0;
    std::string buffer_string, buffer_8, result;
    result = "";

    if(!is_string_base64_encoded(input, equality_sign_count)){                // 0. Если строка не имеет вид закодированной в base64, то программа вызывает исключение.
        throw std::invalid_argument("Эта строка не закодирована в base64");
    }

    for(char letter : input){                                                           // 1. Получаем base64-индекс каждого символа, переводим в двоичный код и записываем в промежуточную строку.
        if(base64_string.find(letter) != std::string::npos) {
            buffer_string += dec_to_bin(base64_string.find(letter), 6);
        }
        else{
            buffer_string += "000000";
        }
    }

    for(int i = 0; i < equality_sign_count*8; i++){                                     // 2. Удаляем из хвоста нули, добавленные в процессе кодирования в base64.
        buffer_string.pop_back();
    }

    amount_of_buffer_8_rewrites = buffer_string.length()/8;                           // 2.1. Считаем количество обновлений буфера-8.

    for(int i = 0; i < amount_of_buffer_8_rewrites; i++) {
        buffer_8 = "";                                                                 // 3. Выгружаем в буфер-8 некоторые 8 символа промежуточной строки.
        for (int j = 0; j < 8; j++) {
            buffer_8 += buffer_string[i * 8 + j];
        }
        result += (char) bin_to_dec(buffer_8, 8);                           // 4. Прибавляем к итоговой строке символ, раскодированный на основе данных буфера-8.
    }

    return result;                                                               // 5. Возвращаем итоговую строку.
}