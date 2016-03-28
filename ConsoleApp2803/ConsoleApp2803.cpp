// ConsoleApp2803.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Read_File.h"
#include "Genotype.h"
#include "Population.h"
#include "Selection.h"
#include "Recombination.h"
#include "Mutation.h"
#include "Select_In_Population.h"
#include <algorithm>
#include <random>
#include "Source.h"
#include <fstream>
#include <functional>
#include "Fit_Fun.h"

using namespace std;

//class Genotype2 : public Genotype<int> //источником данных в этом классе будет массив (это конкретная реализация)
//{
//public:
//	Genotype2(double** mas, int number) : Genotype(number, mas)
//	{
//		Distr distribution(1, _number_of_genes);
//		genotype = new vector<Gene<int>>();
//		for (size_t i = 0; i < _number_of_genes; i++)
//		{
//			Gene<int> g;
//			g.get_gene()->push_back(distribution());
//			genotype->push_back(move(g));
//		}
//		Genotype<int>::get_fitness();
//	}
//
//	//конструктор копирования
//	Genotype2(const Genotype2& other) : Genotype<int>(other._number_of_genes, other._fitness)
//	{
//		if (this != &other)
//		{
//			auto lenght = other.genotype->size();
//			genotype = new vector<Gene<int>>(lenght);
//			copy(other.genotype->begin(), other.genotype->end(), genotype->begin());
//
//			matrix = other.matrix;
//		}
//	}
//
//	//конструктор перемещения для ускорения обработки данных в векторах,
//	//основнополагающие типы также должны поддерживать этот конструктор
//	Genotype2(Genotype2&& other)
//	{
//		genotype = new vector<Gene<int>>(move(*other.genotype));
//
//		_number_of_genes = other._number_of_genes;
//		_fitness = other._fitness;
//		matrix = other.matrix;
//		other.matrix = nullptr;
//		other.genotype = nullptr;
//	}
//
//private:
//	//double** matrix;
//	static const int line_in_genes = 1;
//	static const int column_in_genes = 3;
//
//	//класс для получения равномерного распределения без повторений
//	class Distr
//	{
//		random_device rd;
//		mt19937 generator;
//		uniform_int_distribution<> distrib;
//
//		int a, b;
//		vector<int> chisla;
//
//	public:
//		Distr(int a, int b) : a(a), b(b)
//		{
//			generator = mt19937(rd());
//			distrib = uniform_int_distribution<>(a, b);
//		}
//
//		int operator() () {
//			while (true)
//			{
//				auto temp = distrib(generator);
//				if (!binary_search(chisla.begin(), chisla.end(), temp))
//				{
//					chisla.push_back(temp);
//					return temp;
//				}
//				/*if (find(chisla.begin(), chisla.end(), temp) == chisla.end())
//				{
//				chisla.push_back(temp);
//				return temp;
//				}*/
//			}
//		}
//	};
//
//	bool checked(Gene<int> gene)
//	{
//		/*auto val = find(genotype.begin(), genotype.end(), number);
//		auto v = genotype.end() - 1;*/
//		if (find(genotype->begin(), genotype->end(), gene) == genotype->end())
//			return true;
//		return false;
//	}
//
//	double count_fitness()
//	{
//		int n_l, n_c;
//		double fitness = 0;
//		for (auto& gen : *genotype)
//		{
//			for (auto item : *gen.get_gene())
//			{
//				int num_of_gene = --item;
//				n_l = line_in_genes * (num_of_gene / 159);
//				n_c = column_in_genes * (num_of_gene % 159);
//
//				for (size_t i = n_c; i < n_c + column_in_genes; i++)
//					fitness += matrix[n_l][i];
//			}
//		}
//		return fitness;
//	}
//};


//class Fit_fun
//{
//public:
//	template<typename ValueType>
//	static function<double(Genotype<ValueType>&)> get_count()
//	{
//		return[](Genotype<ValueType>& temp) {return _count(temp); };
//	}
//
//	template<typename ValueType>
//	static  function<void(Genotype<ValueType>&)> get_create()
//	{
//		return [](Genotype<ValueType>& temp) {_create(temp); };
//	}
//
//private:
//
//	static const int line_in_genes = 1;
//	static const int column_in_genes = 3;
//	template<typename ValueType>
//	static double _count(Genotype<ValueType>& g)
//	{
//		int n_l, n_c;
//		double fitness = 0;
//		auto matr = Source::get_source();
//		for (auto& gen : *g.genotype)
//		{
//			for (auto item : *gen.get_gene())
//			{
//				int num_of_gene = --item;
//				n_l = line_in_genes * (num_of_gene / 159);
//				n_c = column_in_genes * (num_of_gene % 159);
//
//				for (size_t i = n_c; i < n_c + column_in_genes; i++)
//				{
//					fitness += matr[n_l][i];
//				}
//			}
//		}
//		return fitness;
//	}
//
//	template<typename ValueType>
//	static void _create(Genotype<ValueType>& gg)
//	{
//		Distr distribution(1, gg._number_of_genes);
//		gg.genotype = new vector<Gene<int>>();
//		for (size_t i = 0; i < gg._number_of_genes; i++)
//		{
//			Gene<int> g;
//			g.get_gene()->push_back(distribution());
//			gg.genotype->push_back(move(g));
//		}
//	}
//
//	class Distr
//	{
//		random_device rd;
//		mt19937 generator;
//		uniform_int_distribution<> distrib;
//
//		int a, b;
//		vector<int> chisla;
//
//	public:
//		Distr(int a, int b) : a(a), b(b)
//		{
//			generator = mt19937(rd());
//			distrib = uniform_int_distribution<>(a, b);
//		}
//
//		int operator() () {
//			while (true)
//			{
//				auto temp = distrib(generator);
//				if (!binary_search(chisla.begin(), chisla.end(), temp))
//				{
//					chisla.push_back(temp);
//					return temp;
//				}
//			}
//		}
//	};
//};

int main()
{
	vector<Genotype<int>*>* vec = new vector<Genotype<int>*>();
	auto temp_count = Fit_Fun::get_count<int>();
	auto temp_create = Fit_Fun::get_create<int>();
	for (size_t i = 0; i < 100; i++)
	{
		auto g = new Genotype<int>(7807, temp_create, temp_count);
		vec->push_back(g);
		/*auto g = new Genotype2(matrix, 7807);
		vec->push_back(g);*/
		//Genotype2 g(matrix, 7807);//Сам класс Genotype2 нужен для реализации логики формирования и загрузки данных
		//vec->push_back(dynamic_cast<Genotype<int>&>(g));//динамическое приведение для того, чтобы передать в конструктор класса Population2, все данные уже готовы для работы в популяции
	}

	auto temp_s = Selection::inbreeding<int>();
	auto temp_r = Recombination::discrete<int>();
	auto temp_m = nullptr;
	auto temp_sp = Select_In_Population::elite<int>();

	Population<int> p(100, vec, temp_s, temp_r, temp_m, temp_sp);

	for (size_t i = 0; i < 500; i++)
	{
		for (size_t j = 0; j < 50; j++)
		{
			p.select();
			p.recom();
		}
		//p.mut(); добавить удаление динамической памяти - утечка и рассмотреть операцию сортировки в новых родителях, чем больше итераций, тем больше времени
		p.select_in_population();
	}

	return 0;
}


