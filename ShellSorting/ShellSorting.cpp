// ShellSorting.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


/*1. [10 баллов] Требуется реализовать алгоритм Шелла для сортировки массива. Также, для проверки работы алгоритма требуется написать функцию проверки отсортированного массива на упорядоченность.

Исходные данные: массив целых чисел.

2. [10 баллов] Дополнительно:
- выбрать три различных алгоритма выбора длины промежутков;
- сгенерировать 9 различных массивов, заполненных случайными значениями: (размером 10000, 100000 и 1000000 элементов, для каждого по три диапазона значений: -10/10, -1000/1000, -100000/100000). 
Обратите внимание на диапазон значений, выдаваемых функцией rand - при необходимости замените её другим ГСПЧ. Полученные массивы записать в файл и приложить к ответу (эти же выборки будут затем использоваться для других лабораторных);
- совершить хотя бы по три запуска каждого алгоритма выбора диапазона на каждом тестовом массиве и вычислить среднее время работы алгоритма для каждого из массивов (экономьте своё время, реализовав вызов сортировок с помощью циклов, а не перезапуском программы или дублированием кода). 
Полученные данные в виде отчёта также приложите к ответу.

В репозитории отчёт и файлы с данными оформить в виде релиза, вместо обычного добавления.*/


#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>
#include <chrono>
#include <functional>



void ShellDefault(std::vector<int>& arr) {
    int sizeArr = arr.size();
    int g = sizeArr / 2;

    while (g > 0) {
        for (int i = g; i < sizeArr; ++i) {
            for (int j = i; j >= g && arr[j] < arr[j - g]; j -= g) {
                std::swap(arr[j], arr[j - g]);
            }
        }
        g /= 2;
    }
}

 
void ShellKnuth(std::vector<int>& arr) {
    int sizeArr = arr.size();
    int g = 1;
    while (g < sizeArr / 3) {
        g = 3 * g + 1;
    }

    while (g >= 1) {
        for (int i = g; i < sizeArr; ++i) {
            for (int j = i; j >= g && arr[j] < arr[j - g]; j -= g) {
                std::swap(arr[j], arr[j - g]);
            }
        }
        g /= 3;
    }
}


void ShellHibbard(std::vector<int>& array) {
    int arraySize = array.size();
    int k = 1;
    int g = 1;

    while ((1 << k) - 1 < arraySize) {
        k++;
        g = (1 << k) - 1;
    }

    while (g >= 1) {
        for (int i = g; i < arraySize; ++i) {
            for (int j = i; j >= g && array[j] < array[j - g]; j -= g) {
                std::swap(array[j], array[j - g]);
            }
        }
        k--;
        g = (1 << k) - 1;
    }
}


bool isSorted(const std::vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; ++i) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}


std::vector<int> generateRandomArray(size_t size, int minValue, int maxValue) {
    std::vector<int> array(size);
    std::srand(static_cast<unsigned int>(std::time(0)));
    for (size_t i = 0; i < size; ++i) {
        array[i] = minValue + std::rand() % (maxValue - minValue + 1);
    }

    return array;
}




int main() {
    std::vector<std::string> sortingNames = {"Knuth", "Default", "Hibbard"};

    std::vector<std::function<void(std::vector<int>&)>> sortingAlgorithms = {
        ShellKnuth,
        ShellDefault,
        ShellHibbard
    };

    for (int i = 10000; i <= 1000000; i *= 10)
        for (int j = 10; j <= 100000; j *= 100) {
            std::vector<int> originalArray = generateRandomArray(i, -j, j);
            for (int index = 0; index < sortingAlgorithms.size(); ++index) {
                const auto& sortName = sortingNames[index];
                double totalTime = 0.0;
                for (int run = 0; run < 3; ++run) {
                    std::vector<int> arrCopy = originalArray;

                    auto start = std::chrono::high_resolution_clock::now();


                    sortingAlgorithms[index](arrCopy);

                    auto end = std::chrono::high_resolution_clock::now();
                    totalTime += std::chrono::duration<double>(end - start).count();

                    if (!isSorted(arrCopy)) {
                        std::cerr << "Error: array is not sorted correctly by " << sortName << "\n";
                    }
                }
                std::cout << sortName << " for size " << i << " in range " << j << ": " << totalTime / 3.0 << " seconds" << "\n";
            }
        }

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
