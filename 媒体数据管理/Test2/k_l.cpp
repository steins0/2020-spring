// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include <Dense>
#include <Eigenvalues>
#include <map>
using namespace Eigen;

#define inputfile "E://cpp//homewrok//ColorHistogram.txt" 
#define outputfile "E://cpp//homewrok//zerocentered.txt"
#define outputfile2 "E://cpp//homewrok//cov.txt"
#define outputfile3 "E://cpp//homewrok//D.txt"
#define outputfile4 "E://cpp//homewrok//V.txt"

using namespace std;

double variance(double *a, double n)//求方差
{
	double total = 0;
	for (int i = 0; i < n; i++)
	{
		total += a[i];
	}
	return total / n;
}


double cov(double **a, int x, int y, double ex, double ey)
{
	double sum = 0;
	double temp1, temp2;
	for (int i = 0; i < 68040; i++)
	{
		temp1 = a[i][x] - ex;
		temp2 = a[i][y] - ey;
		sum = sum + temp1 * temp2;
	}
	return sum / 68039;
}

void sortmat(MatrixXd a, int *sort)
{
	double temp = 0;
	int temps = 0;
	for (int p = 0; p < 32; p++)
	{
		for (int q = 0; q < 31; q++)
		{
			if (a(q, q) < a(q+1, q+1))
			{
				temp = a(q, q);
				a(q + 1, q + 1) = a(q, q);
				a(q, q)= a(q + 1, q + 1);
				temps = sort[q];
				sort[q] = sort[q + 1];
				sort[q + 1] = temps;
			}
		}
	}
}
int main(int argc, char const *argv[])
{
	fstream file1, file2, file3, file4, file5;
	file1.open(inputfile, ios::in);
	if (!file1)
	{
		cout << "file1 open error" << endl;
	}
	file2.open(outputfile, ios::out);
	if (!file2)
	{
		cout << "file2 open error" << endl;
	}
	file3.open(outputfile2, ios::out);
	if (!file3)
	{
		cout << "file3 open error" << endl;
	}
	file4.open(outputfile3, ios::out);
	if (!file4)
	{
		cout << "file4 open error" << endl;
	}
	file5.open(outputfile4, ios::out);
	if (!file5)
	{
		cout << "file5 open error" << endl;
	}

	int temp,sort[32];
	memset(sort, 0, 32);
	/*int data[68040][32];
	int data2[32][68040];*/
	//int (*data)[32] = new int [68040][32];
	double **data = new double *[68040];
	for (int i = 0; i < 68040; i++)data[i] = new double[32];
	MatrixXd input(68040, 32);
	double **tempdata = new double *[32];
	for (int i = 0; i < 32; i++)tempdata[i] = new double[68040];
	double **covdata = new double *[32];
	for (int i = 0; i < 32; i++)covdata[i] = new double[32];

	double var[32];
	MatrixXd mat(32, 32);

	for (int p = 0; p < 68040; p++)
	{
		if (p == 0)cout << "yes" << endl;
		file1 >> temp;
		for (int q = 0; q < 32; q++)
		{
			file1 >> data[p][q];
			tempdata[q][p] = data[p][q];
			input(p,q)= data[p][q];
		}
	}
	cout << "input success" << endl;

	for (int i = 0; i < 32; i++)
	{
		var[i] = variance(tempdata[i], 68040);
	}
	cout << "var success" << endl;

	for (int p = 0; p < 32; p++)
	{
		for (int q = 0; q < 68040; q++)
		{
			data[q][p] = data[q][p] - var[p];
		}
	}
	cout << "zero success" << endl;
	
	for (int p = 0; p < 68040; p++)
	{
		if (p == 0)cout << "yes" << endl;
		file2 << p << " ";
		for (int q = 0; q < 32; q++)
		{
			file2 << data[p][q] << " ";
		}
		file2 << endl;
	}
	cout << "out1 success" << endl;
	
	file1.close();
	file2.close();

	for (int p = 0; p < 32; p++)
	{
		for (int q = 0; q < 32; q++)
		{
			if (p == q) {
				covdata[p][q] = cov(data, p, q, var[p], var[q]);
				mat(p, q) = covdata[p][q];
			}
			else
			{
				covdata[p][q] = cov(data, p, q, var[p], var[q]);
				covdata[q][p] = covdata[p][q];
				mat(p,q) = covdata[p][q];
				mat(q,p) = covdata[p][q];

			}
		}
	}
	
	for (int p = 0; p < 32; p++)
	{
		if (p == 0)cout << "yes 2" << endl;
		for (int q = 0; q < 32; q++)
		{
			file3 << covdata[p][q] << " ";
		}
		file3 << endl;
		sort[p] = p;
	}
	cout << "out2 success" << endl;
	file3.close();
	
	EigenSolver<MatrixXd> es(mat);
	MatrixXd D = es.pseudoEigenvalueMatrix();
	MatrixXd V = es.pseudoEigenvectors();
	sortmat(D, sort);
	for (int i = 0; i < 32; i++)
	{
		cout << sort[i] << " ";
	}
	
	MatrixXd mattemp(32,12);
	for (int i = 0; i < 12; i++)
	{
		for (int p = 0; p < 32; p++)
		{
			mattemp(p, i) = V(p, sort[i]);
		}
	}
	MatrixXd result = input * mattemp;
	//mattemp.dot(input);
	//cout << result;
	ofstream fout("E://cpp//homewrok//result.txt");
	fout << result;
	fout.close();
	//cout << D << endl << V << endl;
	for (int p = 0; p < 32; p++)
	{
		for (int q = 0; q < 32; q++)
		{
			file4 << D(p, q) << " ";
			file5 << V(p, q) << " ";
		}
		file4 << endl;
		file5 << endl;
	}
	file4.close();
	file5.close();
	return 0;
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
