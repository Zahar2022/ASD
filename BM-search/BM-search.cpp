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


int Boyer_Moore_Search(const vector<char>& s, const vector<char>& p) {

    vector<int> TAB(256, 0);
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
            return i - m + 1;
        }
    }

    return -1;
}



vector<int> Boyer_Moore_All(const vector<char>& s, const vector<char>& p) {
    vector<int> TAB(256, 0);
    vector<int> index;
    vector<int> a = { -1 };
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
        if (j == -1) { // если все символы совпали
            index.push_back(i - m + 1); // сохраняем индекс вхождения
            i += 1; // продолжаем поиск со следующей позиции
        }
    }
    return index;
   
}


vector<int> FindAll(const vector<char>& s, const vector<char>& p, int left, int right) {
    vector<int> index;
    int n = right - left + 1;
    int m = strlen(p.data());

    if (n < m || left < 0 || right >= strlen(s.data())) {
        return index;
    }


    vector<int> TAB(256, m);
    for (int i = 0; i < m - 1; i++) {
        TAB[p[i]] = m - 1 - i;
    }

    int i = left + m - 1; 
    while (i < right + 1) {
        int k = i;
        int j = m - 1;

        while (j >= 0 && k < n + left) {
            if (s[k] == p[j]) {
                k--;
                j--;
            }
            else {
                i += TAB[s[k]];
                break;
            }
        }
        if (j == -1) {
            index.push_back(k + 1);
            i+=1;
        }
    }


    return index;
}


int main() {

    setlocale(LC_ALL, "Russian");

    vector<char> s(100);
    vector<char> p(100);

    cout << "Enter a sentence: ";
    cin.getline(s.data(), s.size());
    cout << "Enter a word: ";
    cin.getline(p.data(), p.size());

 
    int  result = Boyer_Moore_Search(s, p);
    cout << "Index of first occurance: " << result << endl;

    vector<int> ind1 = Boyer_Moore_All(s, p);
    cout << "All occurrences: ";
    for (int index1 : ind1) {
        cout << index1 << " ";
    }
    cout << endl;

    vector<int> ind2 = FindAll(s, p, 17, 91);
    cout << "All occurances in defined range: ";
    for (int index2 : ind2) {
        cout << index2 << " ";
    }
    cout << endl;

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
