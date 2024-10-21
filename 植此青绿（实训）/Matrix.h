#pragma once
#include<iostream>
#include<vector>
#include<map>
class Matrix
{
	friend std::ostream& operator<<(std::ostream&, const Matrix*);
	friend std::istream& operator>>(std::istream&, Matrix*);
public:
	Matrix();
	void fillMatrix(int,int,int,int);
	~Matrix();
	Matrix operator+(Matrix*);
	Matrix operator-(Matrix*);
	Matrix operator+=(Matrix*);
	Matrix operator-=(Matrix*);
	void copyMatrix(Matrix*);
	void printMatrix()const;
	bool operator==(Matrix*);
	bool operator!=(Matrix*);
	//把矩阵重新设置为零矩阵
	void setMatrixToZero();
public:
	int arr[6][6];
};
