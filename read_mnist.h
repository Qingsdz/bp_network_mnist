#ifndef READ_MNIST
#define READ_MNIST
#include<iostream>
#include<fstream>
#include"matrix.h"
using namespace std;
const int output_number = 10;
class read_mnist
{
public:
	read_mnist();
	void get_new();
	void write_to_ppm();
	int ReversalInt(int nValue)
	{
		unsigned char cTemp1 = nValue & 255;
		unsigned char cTemp2 = (nValue >> 8) & 255;
		unsigned char cTemp3 = (nValue >> 16) & 255;
		unsigned char cTemp4 = (nValue >> 24) & 255;
		int nData = static_cast<int>(cTemp1) << 24;
		nData += static_cast<int>(cTemp2) << 16;
		nData += static_cast<int>(cTemp3) << 8;
		return nData + cTemp4;
	}

	int number;
	int row;
	int col;
	int magic;
	int total_pixel;
	matrix image;
	int int_lable;
	matrix lable;
	fstream fmnist;
	fstream flable;
	fstream foutput;
	unsigned char* char_image;
};

read_mnist::read_mnist()
{
	fmnist.open("D:/files/document/BPnetwork/mnist/train-images-idx3-ubyte", ios::in | ios::binary);//这里一定要家长binary，记住中间不能使用逗号，要用|，做运算
	if (!fmnist)
	{
		cout << "Error opening file.";
	}
	fmnist.read(reinterpret_cast<char*> (&magic), sizeof(magic));
	fmnist.read(reinterpret_cast<char*> (&number), sizeof(number));
	fmnist.read(reinterpret_cast<char*> (&row), sizeof(row));
	fmnist.read(reinterpret_cast<char*> (&col), sizeof(col));

	flable.open("D:/files/document/BPnetwork/mnist/train-labels-idx1-ubyte", ios::in | ios::binary);
	if (!flable)
	{
		cout << "Error opening file.";
	}
	flable.read(reinterpret_cast<char*> (&magic), sizeof(number));
	flable.read(reinterpret_cast<char*> (&number), sizeof(number));

	magic = ReversalInt(magic);
	number = ReversalInt(number);
	row = ReversalInt(row);
	col = ReversalInt(col);
	total_pixel = row * col;
	int_lable = 0;
	char_image = new unsigned char[total_pixel];
	matrix* temp = new matrix(output_number, 1);
	image = *temp;
	delete temp;
	temp = new matrix(output_number, 1);
	lable = *temp;
	delete temp;

}
void read_mnist::get_new()
{
	fmnist.read(reinterpret_cast<char*>(char_image), total_pixel);
	for (int i = 0; i < total_pixel; i++)
	{
		image[i] = double(char_image[i]) / 255.0;
	}

	flable.read(reinterpret_cast<char*>(&int_lable), 1);
	for (int i = 0; i < output_number; i++)
	{
		if (int_lable == i)
		{
			lable[i] = 1.0;
		}
		else
		{
			lable[i] = 0.0;
		}
	}
}
void read_mnist::write_to_ppm()
{
	
}
#endif
