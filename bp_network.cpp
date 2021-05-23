#include<iostream>
#include"matrix.h"
#include"network.h"
#include"read_mnist.h"
using namespace std;


int main()
{
	int a[3] = { 784, 30, 10 };
	network bp(a, 2);
	read_mnist mnist;
	bp.network_compute(150, 1, mnist);
	mnist.get_new();
	bp.read(mnist.image.get_data_address(), 784, mnist.lable.get_data_address(), 10);
	bp.network_forward_progagation(); 
	cout << "-------" << endl;
	mnist.image.output_matrix();
	cout << "-------" << endl;
	bp.output(1);

	mnist.get_new();
	bp.read(mnist.image.get_data_address(), 784, mnist.lable.get_data_address(), 10);
	bp.network_forward_progagation();
	cout << "-------" << endl;
	mnist.image.output_matrix();
	cout << "-------" << endl;
	bp.output(1);






	return 0;
}