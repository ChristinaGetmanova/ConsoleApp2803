#pragma once
#include <vector>
#include "Genotype.h"
#include <functional>

using namespace std;

template<typename ValueType> class Population
{
private:
	int number_of_genotype;//����� ���������
	bool die_notigkeit_der_mutation;

	Genotype<ValueType>* parent, *_parent;//�����, ������� ����� ����������
	Genotype<ValueType>* child, *_child;// ����, ������� ���������� ��� ����������� 
	vector<Genotype<ValueType>*>* parent_vector;
	vector<Genotype<ValueType>*>* childrn_vector;

	//������� �������� ���������
	function<void(Population<ValueType>&)> selection;

	//������� ������������ (���������������)
	function<void(Population<ValueType>&)> recombination;

	//������� �������
	function<void(Population<ValueType>&)> mutation;

	//������� ������ ������ � ����� ���������
	function<void(Population<ValueType>&)> sampling;

protected:
	//Population(const int, vector<Genotype<ValueType>>&&, function<void(Population<ValueType>&)>);
	vector<Genotype<ValueType>*>* population;

public:

	Population(const int number, vector<Genotype<ValueType>*>* gene, function<void(Population<ValueType>&)> select_function,
		function<void(Population<ValueType>&)> rec_function, function<void(Population<ValueType>&)> mut_function,
		function<void(Population<ValueType>&)> samp_function);

	//������-������ ��� ��������� ������� � ��������� ���������� ��������� � ��������� ������ ������ � ������� � ��������� ������
	friend class Selection;
	friend class Recombination;
	friend class Mutation;
	friend class Select_In_Population;

	void select()
	{
		selection(*this);
	}

	void mut()
	{
		mutation(*this);
	}

	void recom()
	{
		recombination(*this);
	}

	void select_in_population()
	{
		sampling(*this);
		/*delete childrn_vector;
		delete parent_vector;

		parent_vector = new vector<Genotype<ValueType>*>();
		childrn_vector = new vector<Genotype<ValueType>*>();*/
	}
	Population() : number_of_genotype(0), die_notigkeit_der_mutation(false) {};
	virtual ~Population() {};
};

template<typename ValueType>
Population<ValueType>::Population(const int number, vector<Genotype<ValueType>*>* gene,
	function<void(Population<ValueType>&)> select_function,
	function<void(Population<ValueType>&)> rec_function, 
	function<void(Population<ValueType>&)> mut_function,
	function<void(Population<ValueType>&)> samp_function): die_notigkeit_der_mutation(false)
{
	number_of_genotype = number;
	population = new vector<Genotype<ValueType>*>(move(*gene));
	selection = select_function;
	recombination = rec_function;
	mutation = mut_function;
	sampling = samp_function;

	
	parent = new Genotype<ValueType>();
	_parent = new Genotype<ValueType>();

	parent_vector = new vector<Genotype<ValueType>*>();
	childrn_vector = new vector<Genotype<ValueType>*>();
}
