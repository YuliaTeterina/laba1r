// Археолог нашел N артефактов. Известны веса(сi) и ценности(di) артефактов. Нужно
// выбрать такое подмножество найденных вещей, чтобы суммарный их вес не превысил Z кг, а их
// общая ценность оказалась максимальной. Известно, что решение единственно. Укажите поряд-
// ковые номера вещей, которые нужно взять. Исходные данные находятся в текстовом файле, в
// первой строке указаны N и Z, а во второй строке значения весов(в кг), в третьей - ценность
// находок. Вывести так же суммарный вес и общую ценность результата.

#include <iostream>
#include <vector>
#include <algorithm>

// FIX_ME: Неправильное имя функции - должно быть с заглавной буквы согласно кодстайлу
// void insert_sort(std::vector<int>& w, std::vector<int>& p) {
void InsertionSort(std::vector<int>& Weights, std::vector<int>& Values) {
    // FIX_ME: Использование int для индекса - должен быть size_t
    // for (int i = 1; i < w.size(); i++) {
    for (size_t i = 1; i < Weights.size(); ++i) {
        int Temp = i;
        // FIX_ME: Сравнение int и size_t
        // while (temp - 1 >= 0 && w[temp] < w[temp - 1]) {
        while (Temp - 1 >= 0 && Temp - 1 < static_cast<int>(Weights.size()) && Weights[Temp] < Weights[Temp - 1]) {
            std::swap(Weights[Temp], Weights[Temp - 1]);
            std::swap(Values[Temp], Values[Temp - 1]);
            --Temp;
        }
    }
}

// FIX_ME: Неправильное имя функции
// int backpack(int W, std::vector<int>& wt, std::vector<int>& val, int n) {
int SolveBackpack(int MaxWeight, const std::vector<int>& Weights, const std::vector<int>& Values, int NumItems, std::vector<int>& SelectedItems) {
    // FIX_ME: Создание двумерного вектора каждый раз - неэффективно
    // std::vector<std::vector<int>> dp(n + 1, std::vector<int>(W + 1));
    std::vector<std::vector<int>> DP(NumItems + 1, std::vector<int>(MaxWeight + 1, 0));

    // Заполнение таблицы динамического программирования
    for (int i = 1; i <= NumItems; ++i) {
        for (int w = 1; w <= MaxWeight; ++w) {
            if (Weights[i - 1] <= w) {
                // Выбор между включением и исключением текущего предмета
                DP[i][w] = std::max(Values[i - 1] + DP[i - 1][w - Weights[i - 1]], DP[i - 1][w]);
            }
            else {
                // Текущий предмет не вмещается в рюкзак
                DP[i][w] = DP[i - 1][w];
            }
        }
    }

    // Восстановление ответа (какие предметы были взяты)
    int CurrentWeight = MaxWeight;
    for (int i = NumItems; i > 0; --i) {
        // FIX_ME: Неправильное условие для проверки, был ли взят предмет
        // if (DP[i][CurrentWeight] != DP[i - 1][CurrentWeight]) {
        if (DP[i][CurrentWeight] > DP[i - 1][CurrentWeight]) {
            SelectedItems.push_back(i - 1); // Добавляем индекс предмета (0-based)
            CurrentWeight -= Weights[i - 1];
        }
    }

    return DP[NumItems][MaxWeight];
}

int main() {
    setlocale(LC_ALL, "ru");

    int NumItems = 0;
    int MaxWeight = 0;

    do {
        std::cout << "Введите объем рюкзака (кг) > 0: ";
        std::cin >> MaxWeight;
    } while (MaxWeight <= 0);

    do {
        std::cout << "Введите количество артефактов > 0: ";
        std::cin >> NumItems;
    } while (NumItems <= 0);

    std::cout << "Введите параметры артефактов:\n";

    std::vector<int> Values(NumItems);
    std::vector<int> Weights(NumItems);

    for (int i = 0; i < NumItems; ++i) {
        std::cout << "Артефакт #" << i + 1 << ":\n";
        std::cout << "  Вес (кг): ";
        std::cin >> Weights[i];
        std::cout << "  Стоимость: ";
        std::cin >> Values[i];
    }

    // FIX_ME: Сортировка изменяет соответствие индексов оригинальным номерам
    // InsertionSort(Weights, Values);

    std::vector<int> SelectedIndices;
    int MaxValue = SolveBackpack(MaxWeight, Weights, Values, NumItems, SelectedIndices);

    std::cout << "\nРезультат:\n";
    std::cout << "Максимальная стоимость: " << MaxValue << "\n";

    // Подсчет суммарного веса выбранных предметов
    int TotalWeight = 0;
    for (int Index : SelectedIndices) {
        TotalWeight += Weights[Index];
    }

    std::cout << "Суммарный вес: " << TotalWeight << " кг\n";
    std::cout << "Выбраны артефакты с номерами: ";

    // FIX_ME: Вывод индексов должен быть в порядке возрастания
    // for (int Index : SelectedIndices) {
    std::sort(SelectedIndices.begin(), SelectedIndices.end());
    for (size_t i = 0; i < SelectedIndices.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << SelectedIndices[i] + 1; // +1 для вывода порядкового номера (1-based)
    }
    std::cout << "\n";

    return 0;
}