#pragma once
#pragma once
#ifndef MATRIX
#define MATRIX

#include <iostream>
#include <string>
#include "Vec3.h"

class MatError {};

class MatNonInvertable : MatError {};
class MatSingular : MatError {};
class MatInvalidOp : MatError {};

class Matrix
{
public:
	float** a = nullptr;
	int n = 0;
	int m = 0;

	Matrix() {}
	Matrix(int n, int m);
	Matrix(float* data[], int n, int m);
	Matrix(const Matrix& A);

	void create(float* data[], int n, int m);
	void clear();
	void makeEmpty(int n, int m);
	void makeIdentity();

	void invert();
	void print();
	void println();

	Matrix operator*(Matrix& A);
	void operator=(Matrix A);

	~Matrix();
};

#endif