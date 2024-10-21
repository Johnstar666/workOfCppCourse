#include"Matrix.h"
#include<iostream>
using namespace std;
ostream& operator<<(ostream& output, const Matrix* m)
{
	//output << m.a << " " << m.b << "\n" << m.c << " " << m.d;
	cout << "�������Ϊ��" << endl;
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
	//��ʼ������Ϊ6*6�������
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
	//������Ԫ��,���ԣ�x��y��Ϊ���Ͻǣ���x1��y1��Ϊ���½ǵľ����а�����Ԫ��ȫ����һ
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
	cout << "�������Ϊ��" << endl;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			cout << arr[i][j] << " ";
			if ((j==5))cout << endl;
		}
	}

}
//�жϾ����Ƿ����
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
//�жϾ����Ƿ����
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
////�Ѿ�����������Ϊ�����
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

Matrix Matrix::operator+(Matrix*m)//����λ��Ԫ�����
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

