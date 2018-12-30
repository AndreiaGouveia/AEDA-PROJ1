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
	this->false;
}
Motorista::Motorista(string nome,bool atual): nome(nome),atual(atual)
{

}

Motorista::Motorista(string nome,bool atual,list <pair <string,unsigned>> veiculos): nome(nome),atual(atual)
{
	this->veiculos=veiculos;
}

string Motorista::getNome()
{
	return this->nome;
}

bool Motorista::getAtual()
{
	return this->atual;
}

list <pair <string,unsigned>> Motorista::getVeiculos()
{
	return this->veiculos;
}

void Motorista::inserirVeiculo(string matricula , unsigned id)
{
	list<pair<string , unsigned>>::iterator it;
	pair <string,unsigned> veiculo= make_pair(matricula,id);
	it=find(veiculos.begin(),veiculos.end(),veiculo);

	if(it==veiculos.end())//se nao existir
	{
		veiculos.push_back(veiculo);
	}
}

void Motorista::inserirVeiculos(list <pair<string , unsigned>> v)
{
	list<pair<string , unsigned>>::iterator it=v.begin();
	while(it!=v.end())
	{
		inserirVeiculo((*it).first,(*it).second);
	}
}

void Motorista::setAtual(bool atual)
{
	this->atual=atual;
}

void Motorista::removerVeiculo(unsigned id)
{
	list<pair <string,unsigned>>::iterator it;
	pair <string,unsigned> veiculo= make_pair("",id);
	it=find(veiculos.begin(),veiculos.end(),veiculo);

		if(it!=veiculos.end())//se existir
		{
			veiculos.erase(it);
		}
}

void Motorista::removerVeiculo(string matricula)
{
	list<pair <string,unsigned>>::iterator it;
	pair <string,unsigned> veiculo= make_pair(matricula,0);
	it=find(veiculos.begin(),veiculos.end(),veiculo);

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

void Motorista::contratar(string matricula,unsigned id)
{
	this->atual=true;

	list<pair <string,unsigned>>::iterator it;
	pair <string,unsigned> veiculo= make_pair(matricula,id);
	it=find(veiculos.begin(),veiculos.end(),veiculo);

	if(it==veiculos.end())//se nao existir
	{
		veiculos.push_back(veiculo);
	}

}




