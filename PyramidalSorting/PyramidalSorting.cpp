// PyramidalSorting.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*1. [10 баллов] Требуется реализовать алгоритм пирамидальной сортировки массива. Также, для проверки работы алгоритма требуется написать функцию проверки отсортированного массива на упорядоченность.

Исходные данные: массив целых чисел.

2. [10 баллов] Используя тестовые массивы, сгенерированные для лабораторной № 4, совершить хотя бы три запуска алгоритма на каждом тестовом массиве и вычислить среднее время работы алгоритма для каждого из массивов (экономьте своё время, реализовав вызов сортировок с помощью циклов, а не перезапуском программы или дублированием кода). Полученные данные в виде отчёта также приложите к ответу.

В репозитории отчёт оформить в виде релиза, вместо обычного добавления*/


#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>
#include <chrono>
#include <functional>
#include <algorithm>



void BinaryHeap(std::vector<int>& arr, int size, int i)
{
    int highest = i;
    int leftChild = 2 * i + 1; 
    int rightChild = 2 * i + 2;
    
    if (leftChild < size && arr[leftChild] > arr[highest])
        highest = leftChild;

    if (rightChild < size && arr[rightChild] > arr[highest])
        highest = rightChild;

    if (highest != i)
    {
        std :: swap(arr[i], arr[highest]);
        BinaryHeap(arr, size, highest);
    }
}


void PyramidalSorting(std::vector<int>& arr){
    int size = arr.size();
    for (int i = size / 2 - 1; i >= 0; --i)
        BinaryHeap(arr, size, i);

    for (int i = size - 1; i >= 0; --i)
    {
        std :: swap(arr[0], arr[i]);

        BinaryHeap(arr, i, 0);
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


std::vector<int> generateRandomArr(int size, int minValue, int maxValue) {
    std :: vector<int> array(size);
    std :: srand(static_cast<unsigned int>(std::time(0)));
    for (int  i = 0; i < size; ++i) {
        array[i] = minValue + std::rand() % (maxValue - minValue + 1);
    }

    return array;
}


int main()
{
    for (int i = 10000; i <= 1000000; i *= 10)
        for (int j = 10; j <= 100000; j *= 100) {
            std::vector<int> originalArray = generateRandomArr(i, -j, j);

            double totalTime = 0.0;

            for (int run = 0; run < 3; ++run) {
                std::vector<int> arrCopy = originalArray;

                auto start = std::chrono::high_resolution_clock::now();
                PyramidalSorting(arrCopy);
                auto end = std::chrono::high_resolution_clock::now();

                totalTime += std::chrono::duration<double>(end - start).count();

                if (!isSorted(arrCopy)) {
                    std::cerr << "Error: array is not sorted correctly" << "\n";
                }
            }
            std::cout << "For sorting on array of size " << i << " in range " << j << ": " << totalTime / 3.0 << " seconds" << "\n";
        }
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
