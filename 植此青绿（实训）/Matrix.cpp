#include"Matrix.h"
#include<iostream>
using namespace std;
ostream& operator<<(ostream& output, const Matrix* m)
{
	//output << m.a << " " << m.b << "\n" << m.c << " " << m.d;
	cout << "这个矩阵为：" << endl;
	for (int i = 0; i < 36; i++)
	{
		output << m->arr[i] << " ";
		if ((i + 1) / (6.0f) == 0)cout << endl;
	}
	return output;
}
istream& operator>>(istream& input, Matrix* m)
{
	//input >> m.a >> m.b >> m.c >> m.d;
	
	return input;
}
Matrix::Matrix()
{
	//cout << "Matrix constructor works. " << endl;
	//初始化数组为6*6的零矩阵
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			this->arr[i][j] = 0;
		}
	}
}
Matrix::~Matrix()
{
	//cout << "Matrix destructor works." << endl;
}
void Matrix::fillMatrix(int x,int y,int x1,int y1)
{
	//填充矩阵元素,把以（x，y）为左上角，（x1，y1）为右下角的矩形中包含的元素全部加一
	for (int i = y; i <= y1; i++)
	{
		for (int j = x; j <= x1; j++)
		{
			this->arr[i][j]++;
		}
	}
}
void Matrix::printMatrix()const
{
	cout << "这个矩阵为：" << endl;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			cout << arr[i][j] << " ";
			if ((j==5))cout << endl;
		}
	}

}
//判断矩阵是否相等
bool Matrix::operator==(Matrix*m)
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (this->arr[i][j] != m->arr[i][j])
			{
				return false;
			}
		}
	}
	return true;
}
//判断矩阵是否不相等
bool Matrix::operator!=(Matrix*m)
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (this->arr[i][j] != m->arr[i][j])
			{
				return true;
			}
		}
	}
	return false;
}
////把矩阵重新设置为零矩阵
void Matrix::setMatrixToZero()
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			this->arr[i][j] = 0;
		}
	}
}

Matrix Matrix::operator+(Matrix*m)//各个位置元素相加
{

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			this->arr[i][j] += m->arr[i][j];
		}
	}
	return *this;
}
Matrix Matrix::operator-(Matrix* m)
{
	
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			this->arr[i][j] -= m->arr[i][j];
		}
	}
	return *this;
}


Matrix Matrix::operator+=(Matrix* m)
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			this->arr[i][j] += m->arr[i][j];
		}
	}
	return *this;
}
Matrix Matrix::operator-=(Matrix* m)
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			this->arr[i][j] -= m->arr[i][j];
		}
	}
	return *this;
}

void Matrix::copyMatrix(Matrix*m)
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			this->arr[i][j]=m->arr[i][j];
		}
	}
}

