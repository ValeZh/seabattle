#pragma once


#include <iostream>
using namespace std;

void swapElements(int& element1, int& element2);
bool isSorted(int a, int b, SortOrder sortOrder);
int* bubbleSort(int* array, int n, SortOrder sortOrder);
int* fillArray(int* arr, int n);
void printArray(int* arr, int n);