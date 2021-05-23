#ifndef MATRIX
#define MATRIX
#include<iostream>
#include<cstdlib>
#include<iomanip>
using namespace std;
using namespace std;


class matrix
{
public:
	matrix() //����������ʱ�������������ֱ�Ӹ�ֵ�����Ժ���и�ֵ
	{
		data = 0;
		col = 0;
		row = 0;
		rank = 0;
	}
	matrix(int m, int n) //����һ��Ĭ��ֵΪ0�ľ��� MxN
	{
		data = new double[m * n];
		row = m;
		col = n;
		for (int i = 0; i < m * n; i++)
		{
			data[i] = 0.0;
		}
	}
	matrix(int m, int n, int type) //����һ�����ֵ�ľ��� MxN
	{
		data = new double[m * n];
		row = m;
		col = n;
		for (int i = 0; i < m * n; i++)
		{
			data[i] = float(rand() % (999999 - 0 + 1)) / 100000;
		}
	}
	matrix(int m, int n, double* dat)
	{
		data = new double[m * n];
		row = m;
		col = n;
		memcpy(data, dat, m * n * sizeof(double));
	}
	matrix(const matrix& c)
	{
		int need_space = c.row * c.col;
		data = new double[need_space];
		memcpy(data, c.data, need_space * sizeof(double));//���ｫ������������ݸ���
		col = c.col;
		row = c.row;
		rank = c.rank;
	}

	~matrix()
	{
		delete [](this->data);
	}


	int get_row() { return row; }
	int get_col() { return col; }

	double get_matrix_value(int i, int j);
	double set_matrix_value(int i, int j, double value);
	double get_matrix_value_safe(int i, int j);
	void set_matrix_value_safe(int i, int j, double value);
	matrix get_matrix(int type, int k);//��ȡһ�л�һ�о���
	matrix get_matrix(int i_b, int j_b, int i_e, int j_e);//��ȡ����(i_b, j_b) -> (i_e, j_e)
	int output_matrix();// �������ȫ������
	int output_matrix(int type, int k);//�������һ�л�һ�о���
	int output_matrix(int i_b, int j_b, int i_e, int j_e);//�����������(i_b, j_b) -> (i_e, j_e)
	friend matrix hadamard(matrix a, matrix b);
	matrix get_matrix_T();
	void set_col(int tcol, matrix tmat);
	double* get_data_address()
	{
		return data;
	}
	matrix operator *(matrix b);
	matrix operator + (matrix &b);
	matrix operator - (matrix b);
	double& operator[](int i)
	{
		return data[i];
	}
	friend matrix operator*(double a, matrix b);
	friend matrix operator+(matrix a, double b);
	void operator = (matrix b);
	double* get_data_add()
	{
		return data;
	}



	double* data;
	int col;
	int row;
	int rank;
};

matrix m_0;
void matrix::operator= (matrix b)
{
	if (this == &b) return;
	int needspace = b.row * b.col;
	int nowspace = this->row * this->col;
	if (needspace != nowspace )
	{
		delete [](this->data);
		data = new double[needspace];
	}
	memcpy(this->data, b.data, needspace * sizeof(double));//���ｫ������������ݸ���
	col = b.col;
	row = b.row;
	rank = b.rank;
}

double matrix::get_matrix_value(int i, int j) //���ؾ���Ԫ�� double ����ȫ �����
{
	if (i > row) return 0;
	if (j > col) return 0;
	return *(data + col * (i - 1) + (j - 1));
}
double matrix::set_matrix_value(int i, int j, double value)
{
	if (i > row) return 0;
	if (j > col) return 0;
	*(data + col * (i - 1) + (j - 1)) = value;
	return value;
}
double matrix::get_matrix_value_safe(int i, int j) //���ؾ���Ԫ�� double ��ȫ �������
{
	return *(data + col * (i - 1) + (j - 1));
}
void matrix::set_matrix_value_safe(int i, int j, double value)
{
	*(data + col * (i - 1) + (j - 1)) = value;
}

matrix matrix::operator*(matrix b) //�������˷�������matrix����
{
	if (col != b.row)
	{
		return m_0;
	}
	matrix new_matrix(this->row, b.get_col());
	for (int i = 1; i <= row; i++) //��i�� j��
	{
		for (int j = 1; j <= b.col; j++)
		{
			double result = 0;
			for (int s = 1; s <= col; s++)//û�γ˷���Ҫs�Σ������������
			{
				double temp = get_matrix_value_safe(i, s) * b.get_matrix_value_safe(s, j); //����һ��ʼtemp����Ϊ��int �ҵ������ɴ�ӣ����˰���ŷ���
				if (temp < 0.00000001) temp = 0.0;  //����ӣ���Ȼ��ʹ��������ʧ����ӣ����˺ܳ�ʱ����ҵ�
				result += temp;
			}
			new_matrix.set_matrix_value_safe(i, j, result);
		}
	}
	return new_matrix;
}

matrix matrix::get_matrix(int type, int k)//��ȡһ�л�һ�о���
{
	return matrix();
}
matrix matrix::get_matrix(int i_b, int j_b, int i_e, int j_e)//��ȡ����(i_b, j_b) -> (i_e, j_e)
{
	return matrix();
}
int matrix::output_matrix()// �������ȫ������
{
	for (int i = 1; i <= row; i++)
	{
		for (int j = 1; j <= col; j++)
		{
			cout << setw(6) << setprecision(4) << get_matrix_value_safe(i, j) << " ";
		}
		cout << endl;
	}
	return 1;
}
int matrix::output_matrix(int type, int k)//�������һ�л�һ�о���
{
	return 0;
}
int matrix::output_matrix(int i_b, int j_b, int i_e, int j_e)//�����������(i_b, j_b) -> (i_e, j_e)
{
	return 0;
}

matrix matrix::operator + (matrix& b)
{
	if (col != b.col || row != b.row)
	{
		return m_0;
	}
	matrix new_matrix(row, col);
	for (int i = 0; i < row * col; i++)
	{
		*((new_matrix.data)+i) = *(data+i) + *((b.data)+i);
	}
	return new_matrix;

}
matrix operator+(matrix a, double b)
{
	int num = a.row * a.col;
	double* new_data = new double[num];
	for (int i = 0; i < num; i++)
	{
		new_data[i] = (a.data)[i] + b;
	}
	return matrix(a.row, a.col, new_data);
}

matrix matrix::operator - (matrix b)
{
	if (col != b.col || row != b.row)
	{
		return m_0;
	}
	matrix new_matrix(row, col);
	for (int i = 0; i < row * col; i++)
	{
		new_matrix.data[i] = data[i] - b.data[i];
	}
	return new_matrix;
}

matrix hadamard(matrix a, matrix b) //�˴����������� ���������ӦԪ�����
{
	if ((a.col != b.col) || (a.row != b.row))
	{
		return m_0;
	}
	matrix new_matrix(a.row, a.col);
	for (int i = 0; i < a.row*a.col; i++)
	{
		double temp = a.data[i] * b.data[i];
		if (temp < 0.000000001) temp = 0;
		new_matrix.data[i] = temp;
	}
	return new_matrix;
}

matrix matrix::get_matrix_T()
{
	int num = 0;
	double* new_data = new double[row * col];
	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < row; j++)
		{
			new_data[num] = this->get_matrix_value(j + 1, i + 1);
			num++;
		}
	}
	return matrix(col, row, new_data);
}
matrix operator*(double a, matrix b)
{
	int new_num = b.get_row() * b.get_col();
	double* new_data = new double[new_num];
	for (int i = 0; i < new_num; i++)
	{
		new_data[i] = a * (b.data)[i];
	}
	return matrix(b.get_row(), b.get_col(), new_data);
}
void matrix::set_col(int tcol, matrix tmat)
{
	if (tmat.col != 1 && tmat.col != 0) cout << "set_col != 1" << endl;
	for (int i = 0; i < row; i++)
	{
		this->set_matrix_value(i + 1, tcol, tmat.get_matrix_value(i + 1, 1));
	}
}


#endif