#pragma once
#include "random"
#include "algorithm"
#include "functional"
#include "Genotype.h"
#include "Source.h"

using namespace std;
class Fit_Fun
{

public:
	template<typename ValueType>
	static function<double(Genotype<ValueType>&)> get_count()
	{
		return[](Genotype<ValueType>& temp) {return _count(temp); };
	}

	template<typename ValueType>
	static  function<void(Genotype<ValueType>&)> get_create()
	{
		return [](Genotype<ValueType>& temp) {_create(temp); };
	}

private:

	static const int line_in_genes = 1;
	static const int column_in_genes = 3;
	template<typename ValueType>
	static double _count(Genotype<ValueType>& g)
	{
		int n_l, n_c;
		double fitness = 0;
		auto matr = Source::get_source();
		for (auto& gen : *g.genotype)
		{
			for (auto item : *gen.get_gene())
			{
				int num_of_gene = --item;
				n_l = line_in_genes * (num_of_gene / 159);
				n_c = column_in_genes * (num_of_gene % 159);

				for (size_t i = n_c; i < n_c + column_in_genes; i++)
				{
					fitness += matr[n_l][i];
				}
			}
		}
		return fitness;
	}

	template<typename ValueType>
	static void _create(Genotype<ValueType>& gg)
	{
		Distr distribution(1, gg._number_of_genes);
		gg.genotype = new vector<Gene<int>>();
		for (size_t i = 0; i < gg._number_of_genes; i++)
		{
			Gene<int> g;
			g.get_gene()->push_back(distribution());
			gg.genotype->push_back(move(g));
		}
	}

	class Distr
	{
		random_device rd;
		mt19937 generator;
		uniform_int_distribution<> distrib;

		int a, b;
		vector<int> chisla;

	public:
		Distr(int a, int b) : a(a), b(b)
		{
			generator = mt19937(rd());
			distrib = uniform_int_distribution<>(a, b);
		}

		int operator() () {
			while (true)
			{
				auto temp = distrib(generator);
				if (!binary_search(chisla.begin(), chisla.end(), temp))
				{
					chisla.push_back(temp);
					return temp;
				}
			}
		}
	};
};

