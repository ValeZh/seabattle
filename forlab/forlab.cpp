// forlab.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "realize.cpp"
#include <iostream>
using namespace std;

//направление сортировки


int main(int argc, char** argv)
{
    int* arr;
    int size;

    cout << "n = ";
    cin >> size;

    arr = new int[size];
    arr = fillArray(arr, size);

    arr = bubbleSort(arr, size, ASC);

    printArray(arr, size);

    delete arr;
    cout << endl;
    system("pause");
    return 0;
}

