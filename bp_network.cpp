#include<iostream>
#include"matrix.h"
#include"network.h"
#include"read_mnist.h"
using namespace std;


int main()
{
	int a[5] = { 784, 50, 50, 50, 10 };
	network bp(a, 4);
	read_mnist mnist;
	bp.network_compute(100, 3, mnist);
	mnist.get_new();
	bp.read(mnist.image.get_data_address(), 784, mnist.lable.get_data_address(), 10);
	bp.network_forward_progagation();
	cout << "-------" << endl;
	mnist.image.output_matrix();
	cout << "-------" << endl;
	bp.output(0);
	bp.output(1);






	return 0;
}