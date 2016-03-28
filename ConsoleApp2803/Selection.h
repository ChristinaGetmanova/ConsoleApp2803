#pragma once
#include "Population.h"
#include "Genotype.h"
#include <random>
#include <functional>
#include <algorithm>

using namespace std;

class Selection
{
private:
	Selection();

	template<typename ValueType>
	static bool cmp(Genotype<ValueType>, Genotype<ValueType>);

	//��������� �����������
	template <typename ValueType>
	static void s_panmixia(Population<ValueType>&);

	//����� ����������� ������ ������
	template <typename ValueType>
	static void s_inbreeding(Population<ValueType>&);

	//����� ����������� ��������� ������
	template <typename ValueType>
	static void s_outbreeding(Population<ValueType>&);

	//��������� ����� (������� t ������ �� ��������� -> �� ��� ������)
	template <typename ValueType>
	static void s_tournament(Population<ValueType>&);

	//����������� ������ �������� ������� �����������������
	template <typename ValueType>
	static void s_roulette_wheel(Population<ValueType>&);

public:
	//��������� ����������� (�������� ������ ���������)
	template<typename ValueType>
	static function<void(Population<ValueType>&)> panmixia()
	{
		return [](Population<ValueType>& p) { s_panmixia(p); };
	}

	//����� ����������� ������ ������
	template<typename ValueType>
	static function<void(Population<ValueType>&)> inbreeding()
	{
		return [](Population<ValueType>& p) { s_inbreeding(p); };
	}

	//����� ����������� ��������� ������
	template<typename ValueType>
	static function<void(Population<ValueType>&)>outbreeding()
	{
		return [](Population<ValueType>& p) { s_outbreeding(p); };
	}

	//��������� ����� (������� t ������ �� ��������� -> �� ��� ������)
	template<typename ValueType>
	static function<void(Population<ValueType>&)> tournament()
	{
		return [](Population<ValueType>& p) { s_tournament(p); };
	}

	//����������� ������ �������� ������� �����������������
	template<typename ValueType>
	static function<void(Population<ValueType>&)> roulette_wheel()
	{
		return [](Population<ValueType>& p) { s_roulette_wheel(p); };
	}
};

template<typename ValueType>
bool Selection::cmp(Genotype<ValueType> g1, Genotype<ValueType> g2)
{
	return (g1.get_fitness() < g2.get_fitness());
}

template<typename ValueType>
void Selection::s_panmixia(Population<ValueType>& p)
{
	random_device rd;
	mt19937 generator(rd());
	uniform_int_distribution<> uniform_population(0, p.number_of_genotype);
	auto t = uniform_population(generator),
		tt = uniform_population(generator);
	//������� ���� �� ��������
	if (t != tt)
	{
		p.parent = &p.population[t];
		p._parent = &p.population[tt];
	}
	p.parent_vector->push_back(*p.parent);
	p.parent_vector->push_back(*p._parent);
}

template<typename ValueType>
void Selection::s_inbreeding(Population<ValueType>& p)
{
	sort(p.population->begin(), p.population->end(),
		[](Genotype<ValueType>* g1, Genotype<ValueType>* g2) {return (g1->get_fitness() < g2->get_fitness()); });
	random_device rd;

	mt19937 generator(rd());
	uniform_int_distribution<> uniform_population(0, p.number_of_genotype - 1);
	auto t = uniform_population(generator);
	p.parent = p.population->at(t);
	if (t != p.population->size() - 1)
		p._parent = p.population->at(t + 1);
	else p._parent = p.population->at(t - 1);

	p.parent_vector->push_back(p.parent);
	p.parent_vector->push_back(p._parent);
}

template<typename ValueType>
void Selection::s_outbreeding(Population<ValueType>&)
{
}

template<typename ValueType>
void Selection::s_tournament(Population<ValueType>& p)
{
	random_device rd;
	mt19937 generator(rd());
	uniform_int_distribution<> uniform_population(0, p.number_of_genotype);
	vector<Genotype<ValueType>> rand_genotype;
	vector<Genotype<ValueType>> mas;
	int t = 0.2*p.number_of_genotype;

	for (size_t i = 0; i < p.number_of_genotype; i++)
	{
		for (size_t k = 0; k < t; k++)
			rand_genotype.push_back(p.population[uniform_population(generator)]);

		sort(p.population.begin(), p.population.end(), cmp);
		mas.push_back(rand_genotype[0]);
	}

	uniform_int_distribution<> distr(0, mas.size());
	p.parent = &mas[distr(generator)];
	p._parent = &mas[distr(generator)];
	p.parent_vector->push_back(*p.parent);
	p.parent_vector->push_back(*p._parent);
}

template<typename ValueType>
inline void Selection::s_roulette_wheel(Population<ValueType>&)
{
}
