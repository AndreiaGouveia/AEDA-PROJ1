/*
 * Motorista.cpp
 *
 *  Created on: 28/12/2018
 *      Author: pc
 */
#include "Motorista.h"
#include <algorithm>

Motorista::Motorista(string nome):nome(nome)
{
	this->atual=false;
}
Motorista::Motorista(string nome,bool atual): nome(nome),atual(atual)
{

}

Motorista::Motorista(string nome,bool atual,list <unsigned> veiculos): nome(nome),atual(atual)
{
	this->veiculos=veiculos;
}

string Motorista::getNome() const
{
	return this->nome;
}

bool Motorista::getAtual()
{
	return this->atual;
}

list <unsigned> Motorista::getVeiculos() const
{
	return this->veiculos;
}

void Motorista::inserirVeiculo(unsigned id)
{
	list<unsigned>::iterator it;

	it=find(veiculos.begin(),veiculos.end(),id);

	if(it==veiculos.end())//se nao existir
	{
		veiculos.push_back(id);
		it++;
	}
}

void Motorista::inserirVeiculos(list <unsigned> v)
{
	list<unsigned>::iterator it=v.begin();

	while(it!=v.end())
	{
		inserirVeiculo(*it);
		it++;
	}
}

void Motorista::setAtual(bool atual)
{
	this->atual=atual;
}

void Motorista::removerVeiculo(unsigned id)
{
	//meter um return false
	if(veiculos.empty())
		return ;

	list<unsigned>::iterator it;

	it=find(veiculos.begin(),veiculos.end(),id);

		if(it!=veiculos.end())//se existir
		{
			veiculos.erase(it);
		}
}


void Motorista::despedir()
{
	this->atual=false;

	this->veiculos.clear();
}

void Motorista::contratar(unsigned id)
{
	this->atual=true;

	list<unsigned>::iterator it;

	it=find(veiculos.begin(),veiculos.end(),id);

	if(it==veiculos.end())//se nao existir
	{
		veiculos.push_back(id);
	}

}

int Motorista::nr_veiculos_por_inserir()
{
	return 5 - veiculos.size();
}

void Motorista::mostrar_veiculos()
{
	if(veiculos.empty())
		cout<<"Nao tem veiculos associados"<<endl;

	list<unsigned>::iterator it=veiculos.begin();

	while(it!=veiculos.end())
	{
		cout<<"id: "<<*it<<endl;
		it++;
	}
}

bool Motorista::operator==(Motorista &m1)
	{
		return this->nome==m1.getNome();
	}
