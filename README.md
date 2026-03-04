# Тетерина Юлия ИТ-16
## Лабораторная работа №1
## Вариант 4

### Исправления по кодстайлу EpicGames:
1. Именование функций
 
Было: void insert_sort(...) - с маленькой буквы, snake_case

Стало: void InsertionSort(...) - с заглавной буквы, PascalCase

Было: int backpack(...) - с маленькой буквы, непонятное название

Стало: int SolveBackpack(...) - с заглавной буквы, понятное название

2. Именование параметров функций

Было: std::vector<int>& w, std::vector<int>& p - однобуквенные

Стало: std::vector<int>& Weights, std::vector<int>& Values - осмысленные, с заглавной

Было: int W, std::vector<int>& wt, std::vector<int>& val, int n

Стало: int MaxWeight, const std::vector<int>& Weights, const std::vector<int>& Values, int NumItems, std::vector<int>& SelectedItems

3. Именование локальных переменных

Было: int temp = i;

Стало: int Temp = i; - с заглавной буквы

Было: std::vector<std::vector<int>> dp(...)

Стало: std::vector<std::vector<int>> DP(...) - с заглавной буквы

Было: int n, W;

Стало: int NumItems = 0, MaxWeight = 0; - инициализация и осмысленные имена

4. Типы индексов в циклах

Было: for (int i = 1; i < w.size(); i++) - сравнение int с size_t

Стало: for (size_t i = 1; i < Weights.size(); ++i) - правильный тип size_t

Было: while (temp - 1 >= 0 && w[temp] < w[temp - 1]) - потенциальное переполнение

Стало: while (Temp - 1 >= 0 && Temp - 1 < static_cast<int>(Weights.size()) && Weights[Temp] < Weights[Temp - 1]) - явная проверка границ

5. Форматирование кода

Было: if (i == 0 || w == 0) dp[i][w] = 0; - оператор на той же строке

Стало:

if (i == 0 || w == 0) {  
    DP[i][w] = 0;  
} - фигурные скобки и оператор на новой строке

Было: dp[i][w] = std::max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]); - длинная строка

Стало: DP[i][w] = std::max(Values[i - 1] + DP[i - 1][w - Weights[i - 1]], DP[i - 1][w]); - форматирование с переносом

6. Добавление const для неизменяемых параметров

Было: int SolveBackpack(int MaxWeight, std::vector<int>& Weights, std::vector<int>& Values, ...)

Стало: int SolveBackpack(int MaxWeight, const std::vector<int>& Weights, const std::vector<int>& Values, ...) - добавлен const

7. Инициализация переменных

Было: int n, W; - неинициализированные переменные

Стало: int NumItems = 0, MaxWeight = 0; - инициализация при объявлении

8. Удаление ненужной сортировки

Было: Сортировка нарушала соответствие индексов оригинальным номерам артефактов

Стало: Убрали вызов InsertionSort перед решением задачи

9. Добавление восстановления ответа

Было: Функция возвращала только максимальную стоимость

Стало: Функция через параметр SelectedItems возвращает индексы выбранных предметов  

Добавлен код:  

int CurrentWeight = MaxWeight;  
for (int i = NumItems; i > 0; --i) {  
    if (DP[i][CurrentWeight] > DP[i - 1][CurrentWeight]) {  
        SelectedItems.push_back(i - 1);  
        CurrentWeight -= Weights[i - 1];  
    }  
}  

10. Исправление условия проверки выбранного предмета  

Было: if (DP[i][CurrentWeight] != DP[i - 1][CurrentWeight]) - некорректно  

Стало: if (DP[i][CurrentWeight] > DP[i - 1][CurrentWeight]) - правильно определяет, взяли ли предмет  

11. Подсчет суммарного веса

Было: не считался

Стало: добавлен подсчет TotalWeight по выбранным индексам

12. Сортировка индексов при выводе

Было: for (int Index : SelectedIndices) - вывод в порядке восстановления (обратном)

Стало: std::sort(SelectedIndices.begin(), SelectedIndices.end()) - вывод в порядке возрастания для удобства чтения результатов

13. Вывод номеров артефактов (1-based)
 
Было: << SelectedIndices[i] - вывод 0-based индексов

Стало: << SelectedIndices[i] + 1 - вывод 1-based номеров для пользователя

14. Форматирование вывода

Было: вывод без разделителей

Стало: добавлены запятые между номерами артефактов
