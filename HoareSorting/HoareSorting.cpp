/*1.[10 баллов] Требуется реализовать алгоритм Хоара сортировки массива.Также, для проверки работы алгоритма требуется написать функцию проверки отсортированного массива на упорядоченность.

Исходные данные : массив целых чисел.

2.[10 баллов] Используя тестовые массивы, сгенерированные для лабораторной № 3, совершить хотя бы три запуска алгоритма на каждом тестовом массиве и вычислить среднее время работы алгоритма для каждого из массивов(экономьте своё время, реализовав вызов сортировок с помощью циклов, а не перезапуском программы или дублированием кода).Полученные данные в виде отчёта также приложите к ответу.

В репозитории отчёт оформить в виде релиза, вместо обычного добавления.*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <random>
#include <chrono>
#include <string>



std :: vector<int> generateRandomArray(size_t size, int minValue, int maxValue) {
    std :: vector<int> array(size);
    std :: srand(static_cast<unsigned int>(std :: time(0)));
    for (size_t i = 0; i < size; ++i) {
        array[i] = minValue + std :: rand() % (maxValue - minValue + 1);
    }

    return array;
}


bool isSorted(const std :: vector<int>& array) {
    for (size_t i = 1; i < array.size(); ++i) {
        if (array[i - 1] > array[i]) {
            return false;
        }
    }
    return true;
}


void HoareSorting(std :: vector<int>& array, int left, int right) {
    if (left >= right)
        return;

    int pivot = array[(left + right) / 2];
    int i = left;
    int j = right;

    while (i <= j) {
        while (array[i] < pivot) 
            i++;
        while (array[j] > pivot) 
            j--;
        if (i <= j) {
            std :: swap(array[i], array[j]);
            i++;
            j--;
        }
    }

    if (left < j)
        HoareSorting(array, left, j);
    if (i < right)
        HoareSorting(array, i, right);
}


void writeArrayToFile(const std::string& filename, const std::vector<int>& arr) {
    std::ofstream outFile(filename);
    for (size_t i = 0; i < arr.size(); ++i) {
        outFile << arr[i] << "  ";
    }
}



int main()
{
    for (int i = 10000; i <= 1000000; i *= 10)
        for (int j = 10; j <= 100000; j *= 100) {
            std :: vector<int> originalArray = generateRandomArray(i, -j, j);
            std::string filename = "array_" + std::to_string(i) + "_" + std::to_string(j) + ".txt";
            writeArrayToFile(filename, originalArray);


            int n = originalArray.size();
            double totalTime = 0.0;

            for (int run = 0; run < 3; ++run) {
                std :: vector<int> arrCopy = originalArray;
                auto start = std :: chrono :: high_resolution_clock :: now();

                HoareSorting(arrCopy, 0, n - 1);

                auto end = std :: chrono :: high_resolution_clock :: now();
                totalTime += std :: chrono :: duration<double>(end - start).count();

                if (!isSorted(arrCopy)) {
                    std :: cerr << "Error: array is not sorted correctly" << "\n";
                }
            }

            std :: cout << "For sorting on array of size " << i << " in range " << j << ": " << totalTime / 3.0 << " seconds" << "\n";
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
