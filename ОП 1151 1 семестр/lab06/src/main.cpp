#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

// ============================
// Генератор случайных чисел
// ============================

double generateRandom(double min, double max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(min, max);
    return dist(gen);
}

// ============================
// Заполнение массива
// ============================

void fillRandom(std::vector<double>& arr, double min, double max)
{
    for (double& value : arr)
    {
        value = generateRandom(min, max);
    }
}

// ============================
// Сортировка массива (методом выбора)
// ============================

void selectionSort(std::vector<double>& arr)
{
    int n = arr.size();
    int minIndex;

    for (int i = 0; i < n - 1; i+=2) 
    {

        minIndex = i;
        if (arr[i] > 0 && i % 2 == 0) {
            for (int j = i + 2; j < n; j+=2)
        {
            if (arr[j] > 0 && j % 2 == 0 && arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }

        std::swap(arr[i], arr[minIndex]);
        } 
    }
}

// ============================
// Вывод массива (с индексами)
// ============================

void printArray(const std::vector<double>& arr)
{
    for (size_t i = 0; i < arr.size(); ++i)
    {
        std::cout << "[" << i + 1 << "] "
                  << std::setw(8) << std::fixed << std::setprecision(2)
                  << arr[i] << "\n";
    }
}

// ============================
// main
// ============================

int main()
{
    const int size = 22;

    std::vector<double> arr(size);

    fillRandom(arr, -100.0, 100.0);

    std::cout << "Original array:\n";
    printArray(arr);

    selectionSort(arr);

    std::cout << "\nSorted array:\n";
    printArray(arr);

    return 0;
}