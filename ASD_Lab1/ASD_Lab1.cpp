/*1. [10 баллов] Требуется реализовать точное (методом перебора) решение задачи коммивояжёра.

Исходные данные: количество городов, матрица стоимостей маршрутов, начальный город.
Формат ввода/вывода не важен.

Также требуется провести эксперименты, оценить рост объёма вычислений с увеличением числа городов и выяснить, при каком числе городов получение результата является затруднительным (ввиду переполнения и/или слишком долгого времени выполнения). Для упрощения данной процедуры рекомендуется реализовать функцию, которая будет заполнять матрицу случайными значениями.

2. [10 баллов] Требуется реализовать эвристическое решение задачи коммивояжёра. Допускается использование любой из эвристик - как из тех, что были представлены в лекции, так и любых других.

Исходные данные: количество городов, матрица стоимостей маршрутов, начальный город.
Формат ввода/вывода не важен.

Также требуется провести эксперименты, оценить качество работы эвристического алгоритма в сравнении с точным и приложить результат в виде отчёта к ответу. Примерный формат отчёта:
- наилучшее (и наихудшее для той же матрицы - для его получения просто немного модифицируйте исходный алгоритм) решения, полученные с помощью точного алгоритма;
- время работы точного алгоритма;
- решение, полученное с помощью эвристического алгоритма (для этой же матрицы стоимостей);
- время работы эвристического алгоритма;
- процент, характеризующий качество решения, полученного эвристическим алгоритмом (где 0% означает, что решение совпало с наихудшим, 100% - с наилучшим);
Требуется собрать подобные отчёты для матриц различных размерностей (3-4 различных, например: 4х4, 6х6, 8х8, 10х10). Для каждой размерности следует провести как минимум 3-4 запуска на случайных данных. Дополнительно можно поэкспериментировать с разбросом стоимостей в матрице.
Эти параметры (размерность матрицы и разброс стоимостей) также следует указать в отчёте.
Для измерения времени можете воспользоваться библиотекой chrono из 11 стандарта С++.*/



#include <iostream>
#include <climits>
#include <cstdlib>
#include <chrono>



int** createDistanceMatrix(int size) {
    int** distanceMatrix = new int* [size];
    for (int i = 0; i < size; ++i) {
        distanceMatrix[i] = new int[size];
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i != j) {
                distanceMatrix[i][j] = rand() % 10 + 1;
            }
            else {
                distanceMatrix[i][j] = 0;
            }
        }
    }

    return distanceMatrix;
}


void printDistanceMatrix(int** distanceMatrix, int size) {
    std::cout << "Distance matrix: \n";
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << distanceMatrix[i][j] << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}


int calculatePathCost(int** distanceMatrix, int* path, int size) {
    int cost = 0;
    for (int i = 0; i < size - 1; ++i) {
        cost += distanceMatrix[path[i]][path[i + 1]];
    }
    cost += distanceMatrix[path[size - 1]][path[0]];
    return cost;
}



bool nextPermutation(int* array, int size) {
    int k = -1;
    for (int i = 0; i < size - 1; ++i) {
        if (array[i] < array[i + 1]) {
            k = i;
        }
    }

    if (k == -1) {
        return false;
    }

    int l = -1;
    for (int i = k + 1; i < size; ++i) {
        if (array[k] < array[i]) {
            l = i;
        }
    }

    int temp = array[k];
    array[k] = array[l];
    array[l] = temp;

    for (int left = k + 1, right = size - 1; left < right; ++left, --right) {
        temp = array[left];
        array[left] = array[right];
        array[right] = temp;
    }

    return true;
}


int greedyAlgorithm(int** distanceMatrix, int size, int startCity, int* path) {
    bool* visited = new bool[size]();
    visited[startCity] = true;
    path[0] = startCity;

    int currentCity = startCity;
    int totalCost = 0;

    for (int i = 1; i < size; ++i) {
        int nextCity = -1;
        int minCost = INT_MAX;

        for (int j = 0; j < size; ++j) {
            if (!visited[j] && distanceMatrix[currentCity][j] < minCost) {
                minCost = distanceMatrix[currentCity][j];
                nextCity = j;
            }
        }

        path[i] = nextCity;
        visited[nextCity] = true;
        totalCost += minCost;
        currentCity = nextCity;
    }

    totalCost += distanceMatrix[currentCity][startCity];

    delete[] visited;

    return totalCost;
}


void findBestAndWorstPaths(int** distanceMatrix, int size, int startCity, int* cities, int* bestPath, int* worstPath, int& exactSolutionCost, int& worstSolutionCost) {
    do {
        int* fullPath = new int[size];
        fullPath[0] = startCity;

        for (int i = 0; i < size - 1; ++i) {
            fullPath[i + 1] = cities[i];
        }

        int currentCost = calculatePathCost(distanceMatrix, fullPath, size);
        if (currentCost < exactSolutionCost) {
            exactSolutionCost = currentCost;
            for (int i = 0; i < size; ++i) {
                bestPath[i] = fullPath[i];
            }
        }
        if (currentCost > worstSolutionCost) {
            worstSolutionCost = currentCost;
            for (int i = 0; i < size; ++i) {
                worstPath[i] = fullPath[i];
            }
        }

        delete[] fullPath;
    } while (nextPermutation(cities, size - 1));
}


void generateReport(int size) {
    int** distanceMatrix = createDistanceMatrix(size);
    printDistanceMatrix(distanceMatrix, size);

    int startCity = rand() % size;

    int* cities = new int[size - 1];
    for (int i = 0, j = 0; i < size; ++i) {
        if (i != startCity) {
            cities[j++] = i;
        }
    }

    int exactSolutionCost = INT_MAX;
    int worstSolutionCost = 0;

    int* bestPath = new int[size];
    int* worstPath = new int[size];

    auto startTimeExact = std::chrono::high_resolution_clock::now();

    findBestAndWorstPaths(distanceMatrix, size, startCity, cities, bestPath, worstPath, exactSolutionCost, worstSolutionCost);

    auto endTimeExact = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> timeExact = endTimeExact - startTimeExact;

    auto startTimeGreedy = std::chrono::high_resolution_clock::now();

    int* greedyPath = new int[size];
    int greedySolutionCost = greedyAlgorithm(distanceMatrix, size, startCity, greedyPath);

    auto endTimeGreedy = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> timeGreedy = endTimeGreedy - startTimeGreedy;

    double qualityGreedySolution = (1.0 - static_cast<double>(greedySolutionCost - exactSolutionCost) / (worstSolutionCost - exactSolutionCost)) * 100.0;

    std::cout << "Size matrix: " << size << "x" << size << "\n";
    std::cout << "Start city: " << startCity << "\n";

    std::cout << "Exact solution cost: " << exactSolutionCost << "\n";
    std::cout << "Exact path: ";
    for (int i = 0; i < size; ++i) {
        std::cout << bestPath[i] << " ";
    }
    std::cout << "\n";

    std::cout << "Worst solution cost: " << worstSolutionCost << "\n";
    std::cout << "Worst path: ";
    for (int i = 0; i < size; ++i) {
        std::cout << worstPath[i] << " ";
    }
    std::cout << "\n";

    std::cout << "Exact solution time: " << timeExact.count() << " seconds\n";

    std::cout << "Greedy solution cost: " << greedySolutionCost << "\n";
    std::cout << "Greedy path: ";
    for (int i = 0; i < size; ++i) {
        std::cout << greedyPath[i] << " ";
    }
    std::cout << "\n";

    std::cout << "Greedy solution time: " << timeGreedy.count() << " seconds\n";
    std::cout << "Quality of greedy solution: " << qualityGreedySolution << "%\n";

    delete[] bestPath;
    delete[] worstPath;
    delete[] greedyPath;
    delete[] cities;

    for (int i = 0; i < size; ++i) {
        delete[] distanceMatrix[i];
    }
    delete[] distanceMatrix;
}


int main() {
    srand(time(0));
    for (int size = 3; size <= 10; ++size) {
        generateReport(size);
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
