// BM-search.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/*Требуется реализовать алгоритм Бойера - Мура поиска подстроки в строке.

Исходные данные : строка с текстом, искомая подстрока.Для упрощения работы с памятью используйте класс std::string.
1.[10 баллов] Реализовать функцию получения индекса первого вхождения подстроки в тексте.Эта функция не должна использовать консольный ввод - вывод.
2.[5 баллов] Реализовать функцию получения индексов всех вхождений подстроки в тексте.Эта функция не должна использовать консольный ввод - вывод, для упрощения работы с памятью используйте класс std::vector<int>.
3.[10 баллов] Реализовать функцию получения индексов вхождений подстроки в тексте в заданном диапазоне(индексы начала и конца поиска в тексте).Эта функция не должна использовать консольный ввод - вывод, для упрощения работы с памятью используйте класс std::vector<int>.
Для примера работы последней функции рассмотрим следующий текст длины 92 :
    "std::move_iterator is an iterator adaptor which behaves exactly like the underlying iterator"
    Предположим, что требуется найти подстроку "tor" длины 3.
    Поиск во всём тексте :
findAll(0, 91), ответ : [15, 30, 38, 89]
Поиск в подстроке "r is an iterator adaptor which behaves exactly like the underlying iterator" :
    findAll(17, 91), ответ : [30, 38, 89]
    Поиск в подстроке "rator ad" :
    findAll(28, 36), ответ : [30]*/


#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;


string Boyer_Moore_Search(const vector<char>& s, const vector<char>& p) {

    vector<int> TAB(256, 0); // Таблица сдвигов инициализируется нулями
    int n = strlen(s.data());
    int m = strlen(p.data());


    for (int i = 0; i < 256; i++) {
        TAB[i] = m;
    }
    for (int i = 0; i < m - 1; i++) {
        TAB[p[i]] = m - 1 - i;
    }

    int i = m - 1;
    int j;

    while (i < n) {
        int k = i;
        j = m - 1;

        while (j >= 0) {
            if (s[k] == p[j]) {
                k--;
                j--;
            }
            else {
                i = k + TAB[s[k]];
                break;
            }
        }
        if (j == -1) { 
            return "Found\nIndex: " + to_string(i - m + 1);
        }
    }

    return "Not found";
}



vector<int> Boyer_Moore_All(const vector<char>& s, const vector<char>& p) {
    vector<int> TAB(256, 0);
    vector<int> index;
    int n = strlen(s.data());
    int m = strlen(p.data());

   
    for (int i = 0; i < 256; i++) {
        TAB[i] = m;
    }
    for (int i = 0; i < m - 1; i++) {
        TAB[p[i]] = m - 1 - i;
    }

    int i = m - 1;
    int j;

    while (i < n) {
        int k = i;
        j = m - 1;

        while (j >= 0) {
            if (s[k] == p[j]) {
                k--;
                j--;
            }
            else {
                i = k + TAB[s[k]];
                break;
            }
        }
        if (j == -1) { // Если все символы совпали
            index.push_back(i - m + 1); // Сохраняем индекс вхождения
            i += 1; // Продолжаем поиск с следующей позиции
        }
    }

    return index;
}


int main() {

    setlocale(LC_ALL, "Russian");

    vector<char> s(80);
    vector<char> p(40);

    cout << "Enter a sentence: ";
    cin.getline(s.data(), s.size());
    cout << "Enter a word: ";
    cin.getline(p.data(), p.size());

 
    string result = Boyer_Moore_Search(s, p);
    cout << result << endl;

    vector<int> ind = Boyer_Moore_All(s, p);
    cout << "All occurrences: ";
    for (int index : ind) {
        cout << index << " ";
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
