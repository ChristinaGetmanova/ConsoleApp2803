#pragma once
#include "vector"
#include "Gene.h"
#include <functional>

using namespace std;

template<typename ValueType> class Genotype
{
protected:
	int _number_of_genes;
	vector<Gene<ValueType>>* genotype;
	double _fitness;

	function<void(Genotype<ValueType>&)> creare_function;
	function<double(Genotype<ValueType>&)> count_function;

	void create()
	{
		creare_function(*this);
	}

public:
	Genotype() : _number_of_genes(0), _fitness(0) {};
	Genotype(function<double(Genotype<ValueType>&)> count_fun) : _number_of_genes(0), _fitness(0)
	{
		count_function = count_fun;
	}
	/*Genotype(const Genotype& other)
	{
		auto lenght = other.genotype.size();
		genotype = vector<Gene<int>>(lenght);
		copy(other.genotype.begin(), other.genotype.end(), genotype.begin());
	}

	Genotype(Genotype&& other)
	{
		genotype = vector<Gene<int>>(move(other.genotype));
		_number_of_genes = other._number_of_genes;
		_fitness = other._fitness;
	}*/

	Genotype(int number, function<void(Genotype<ValueType>&)> _create, function<double(Genotype<ValueType>&)> _count) :
		_number_of_genes(number), _fitness(0)
	{
		creare_function = _create;
		count_function = _count;

		create();
		count_fitness();
	}


	~Genotype() { };
	double get_fitness() const
	{
		return _fitness;
	}

	void count_fitness()
	{
		_fitness = count_function(*this);
	};

	vector<Gene<ValueType>>* get_genotype();
	int get_number_of_genes() const;

private:
	friend class Fit_Fun;
};

template<typename ValueType>
vector<Gene<ValueType>>* Genotype<ValueType>::get_genotype()
{
	if (genotype == nullptr)
		genotype = new vector<Gene<ValueType>>();
	return genotype;
}

template<typename ValueType>
int Genotype<ValueType>::get_number_of_genes() const
{
	return _number_of_genes;
}
