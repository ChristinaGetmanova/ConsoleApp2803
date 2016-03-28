#pragma once
#include "Read_File.h"
#include <string.h>
#include <fstream>
using namespace std;

struct Matrix
{
	double** matrix;
} matr;

class Source
{

	Source()
	{
	}

public:

	static double** get_source()
	{
		string file_name = "matrix.txt";
		Read_File *file = new Read_File(file_name);

		const int line = file->get_line();
		const int column = file->get_column();

		if (matr.matrix == nullptr)
		{
			matr.matrix = new double*[line];
			for (int i = 0; i < line; i++)
				matr.matrix[i] = new double[column];

			double value;
			for (int i = 0; i < line; i++)
				for (int j = 0; j < column; j++)
				{
					*(file->get_file()) >> value;
					matr.matrix[i][j] = value;
				}
		}


		return matr.matrix;
	}
	~Source()
	{
	}
};


