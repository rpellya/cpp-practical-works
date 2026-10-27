#pragma once
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <string>

int** allocateMatrix(int rows, int cols);

void freeMatrix(int**& matrix, int rows);

int* allocateVector(int size);

void freeVector(int*& vec);

int** copyMatrix(int** src, int rows, int cols);

bool areMatricesEqual(int** a, int** b, int rows, int cols);

int readInt(const std::string& prompt, int minValue = -2147483647, int maxValue = 2147483647);

void inputMatrixDimensions(int& rows, int& cols, const std::string& matrixName);

void inputMatrixElements(int** matrix, int rows, int cols, const std::string& matrixName);

void inputVector(int*& vec, int& size, const std::string& vectorName);

void inputVectorElements(int* vec, int size, const std::string& vectorName);

void printMatrix(int** matrix, int rows, int cols, const std::string& matrixName);

void printVector(const int* vec, int size, const std::string& vectorName);

bool canMultiply(int colsA, int rowsB);

int** multiplyMatrices(int** a, int rowsA, int colsA, int** b, int rowsB, int colsB);

void runEquivalencePartitioningTests();

#endif