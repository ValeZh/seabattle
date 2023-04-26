
#include <iostream>
using namespace std;




enum SortOrder
{
    ASC,    //по возрастанию
    DESC    //по убыванию
};

//обмен элементов массива
void swapElements(int& element1, int& element2)
{
    int tempVar = element1;
    element1 = element2;
    element2 = tempVar;
}

//проверка правильности расположения элементов
bool isSorted(int a, int b, SortOrder sortOrder)
{
    if (sortOrder == ASC)
    {
        return a <= b;
    }
    else
    {
        return a >= b;
    }
}

//сортировка пузырьком
int* bubbleSort(int* array, int n, SortOrder sortOrder)
{
    bool swappedFlag = false;

    for (int i = 1; i < n; i++)
    {
        swappedFlag = false;

        for (int j = 0; j < n - i; j++)
        {
            if (!isSorted(array[j], array[j + 1], sortOrder))
            {
                swapElements(array[j], array[j + 1]);
                swappedFlag = true;
            }
        }

        //если обменов не было прерываем цикл
        if (!swappedFlag)
        {
            break;
        }
    }

    return array;
}

//заполнение массива с клавиатуры
int* fillArray(int* arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "arr[" << i << "] = ";
        cin >> arr[i];
    }

    return arr;
}

//вывод массива на экран
void printArray(int* arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
}