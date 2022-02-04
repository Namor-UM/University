#include <iostream>
#include <random>
#include <thread>
#include <vector>

// Здесь регулируются параметры массива. size - размер массива, a и b - нижняя и верхняя границы генерации случайных целых чисел для массива.
const int size = 100;
const int a = 1;
const int b = 5;

int array_of_data[size];
std::vector<int> vector_of_sums;
int result = 0;


void parse_array_of_data(int number_of_thread){
    int number_of_summand;
    int amount_of_summands = size/std::thread::hardware_concurrency();
    if(size%std::thread::hardware_concurrency() != 0)
        amount_of_summands++;

    for(int i = 0; i < amount_of_summands; i++){
        number_of_summand = i*std::thread::hardware_concurrency() + number_of_thread;
        if(number_of_summand < size)
            vector_of_sums[number_of_thread] += array_of_data[number_of_summand];
    }

}


int main() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(a, b);

    int amount_of_threads = std::thread::hardware_concurrency();
    int array_of_sums[amount_of_threads];

    auto * array_of_additional_threads = new std::thread [amount_of_threads];

    // 1. Генерация массива из size элементов и их вывод в консоль.
    std::cout << "Слагаемые: " << std::endl;
    for (int i = 0; i < size; i++) {
        array_of_data[i] = 1;
        std::cout << array_of_data[i] << " ";
        if (i % 24 == 23) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;


    // 2. Разбиение данных массива на обработку по потокам.
    for (int i = 0; i < amount_of_threads-1; i++) {
        vector_of_sums.push_back(0);
        array_of_additional_threads[i] = std::thread(parse_array_of_data, i);
    }

    vector_of_sums.push_back(0);
    parse_array_of_data(amount_of_threads-1);

    for (int i = 0; i < amount_of_threads-1; i++) {
        array_of_additional_threads[i].join();
    }

    for(int summand : vector_of_sums){
        std::cout << "Сумма потока = " << summand << std::endl;
        result += summand;
    }

    std::cout << "Сумма: " << result;
}


