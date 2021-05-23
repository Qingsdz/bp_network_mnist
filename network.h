#ifndef NETWORK
#define NETWORK
#include<cmath>
#include"matrix.h"
#include"read_mnist.h"


class network
{
public:

	network(int* a, int a_num);
	void read(double* data, int num, double* correct_data, int correct_num);
	void read(matrix data, matrix correct_data);
	void network_forward_progagation();//正向传播
	void network_backward_progagation(double speed);//反向传播
	void network_compute(int n, int speed, read_mnist& data);//计算 包含正向传播与反向传播 包括了多个参数的计算 多次正向反向传播
	friend matrix sigmoid(matrix a);
	friend double sigmoid(double a);
	friend double OLS(matrix real, matrix a);
	friend matrix der_OLS(matrix real, matrix a);
	friend matrix der_sigmoid(matrix a);
	void output(int type);
	
	matrix* a;
	matrix* w;
	matrix* z;
	matrix* b;
	matrix* delta;
	int L;
};


network::network(int* ta, int num)
{
	L = num;
	a = new matrix[num + 2];
	w = new matrix[num + 1];
	z = new matrix[num + 1];
	b = new matrix[num + 1];
	delta = new matrix[num + 1];
	matrix* temp;
	for (int i = 0; i <= num; i++)
	{
		temp = new matrix(ta[i], 1, 0);
		a[i] = *temp;
		delete temp;
		if (i > 0)
		{
			temp = new matrix(ta[i], ta[i-1], 0);
			w[i] = *temp;
			delete temp;

			temp = new matrix(ta[i], 1, 0);
			b[i] = *temp;
			z[i] = *temp;
			delta[i] = *temp;
			delete temp;
		}
	}
	temp = new matrix(ta[num], 1, 0);
	a[num + 1] = *temp;
	delete temp;
}
double sigmoid(double a)
{
	return 1.0 / (1.0 + exp(-a));
}
matrix sigmoid(matrix a)
{
	int n = a.get_row();
	double* new_data = new double[n];
	for (int i = 0; i < n; i++)
	{
		new_data[i] = sigmoid(a.get_matrix_value(i+1, 1));
	}
	return matrix(n, 1, new_data);
}

double OLS(matrix real, matrix a)
{
	int n = a.get_row();
	double result = 0;
	double temp = 0;
	for (int i = 0; i < n; i++)
	{
		temp = (real.get_matrix_value(i + 1, 1) - a.get_matrix_value(i + 1, 1));
		result = result + temp * temp;
	}
	return result / 2;
}
matrix der_OLS(matrix real, matrix a)
{
	int n = a.get_row();
	double* data = new double[n];
	for (int i = 0; i < n; i++)
	{
		data[i] = -(real.get_matrix_value(i + 1, 1) - a.get_matrix_value(i + 1, 1));
	}
	return matrix(n, 1, data);
}
matrix der_sigmoid(matrix a)
{
	int n = a.get_row();
	double* data = new double[n];
	for (int i = 0; i < n; i++)
	{
		double fx = sigmoid(a.get_matrix_value(i + 1, 1));
		data[i] = fx * (1 - fx);
	}
	return matrix(n, 1, data);
}
void network::read(double* data, int num, double* correct_data, int correct_num)
{
	matrix mdata(num, 1, data);
	a[0] = mdata;
	matrix mcdata(correct_num, 1, correct_data);
	a[L + 1] = mcdata;
}
void network::read(matrix data, matrix correct_data)
{
	a[0] = data;
	a[L + 1] = correct_data;
}
void network::network_forward_progagation()
{
	for (int i = 1; i <= L; i++)
	{
		z[i] = w[i] * a[i - 1] + b[i];
		a[i] = sigmoid(z[i]);
	}
}
void network::network_backward_progagation(double speed)
{
	/*
	cout << "333333333333------------" << endl;
	der_OLS(a[L + 1], a[L]).output_matrix();
	cout << "-----" << endl;
	der_sigmoid(z[L]).output_matrix();
	cout << "333333333333-----" << endl;
	*/
	delta[L] = hadamard(der_OLS(a[L + 1], a[L]), der_sigmoid(z[L]));
	b[L] = b[L] - speed * delta[L];
	w[L] = w[L] - speed * delta[L] * a[L-1].get_matrix_T();
	for (int i = L - 1; i >= 1; i--)
	{
		/*
		cout << i << "-----" << endl;
		delta[i + 1].output_matrix();
		cout << "-------" << endl;
		w[i + 1].output_matrix();
		(w[i + 1].get_matrix_T()).output_matrix();
		cout << "-----" << endl;
		(w[i + 1].get_matrix_T() * delta[i + 1]).output_matrix();
		cout << "-----" << endl;
		der_sigmoid(z[i]).output_matrix();
		cout << "-----" << endl;
		*/
		delta[i] = hadamard(w[i + 1].get_matrix_T() * delta[i + 1], der_sigmoid(z[i]));
		/*
		delta[i].output_matrix();
		cout << i << "-----" << endl;
		*/
		b[i] = b[i] - speed * delta[i];
		w[i] = w[i] - speed * delta[i] * a[i - 1].get_matrix_T();
	}
}
void network::output(int type)
{
	if (type == 0)
	{
		int max_row = 0;
		for (int i = 0; i <= L; i++)
		{
			if (max_row < a[i].get_row())
			{
				max_row = a[i].get_row();
			}
		}
		cout << "-----a-----" << endl;
		matrix out(max_row, L + 2);
		for (int i = 0; i < L + 2; i++)
		{
			out.set_col(i + 1, a[i]);
		}
		out.output_matrix();
		cout << "--------b--------" << endl;
		matrix out1(max_row, L + 1);
		for (int i = 0; i < L + 1; i++)
		{
			out1.set_col(i + 1, b[i]);
		}
		out1.output_matrix();
		cout << "--------z--------" << endl;
		for (int i = 0; i < L + 1; i++)
		{
			out1.set_col(i + 1, z[i]);
		}
		out1.output_matrix();
		cout << "------delta------" << endl;
		for (int i = 0; i < L + 1; i++)
		{
			out1.set_col(i + 1, delta[i]);
		}
		out1.output_matrix();
		for (int i = 1; i <= L; i++)
		{
			cout << "-------w" << i << "-------" << endl;
			w[i].output_matrix();
		}
		cout << "######end#######" << endl;
	}
	else if (type == 1)
	{
		cout << "@---result---@" << endl;
		a[L].output_matrix();
		cout << "end---result---end" << endl;
	}
	else if (type == 3)
	{
		cout << OLS(a[L], a[L + 1]) << " ";
	}
}
void network::network_compute(int n, int speed, read_mnist& data)
{
	for (int i = 0; i < n; i++)
	{
		data.get_new();
		read(data.image.get_data_address(), 784, data.lable.get_data_address(), 10);
		network_forward_progagation();
		output(3);
		network_backward_progagation(speed);
	}
}




#endif // NETWORK

