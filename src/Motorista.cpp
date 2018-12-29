/*
 * Motorista.cpp
 *
 *  Created on: 28/12/2018
 *      Author: pc
 */
#include "Motorista.h"
#include <algorithm>

Motorista::Motorista(string nome,bool atual): nome(nome),atual(atual)
{

}

Motorista::Motorista(string nome,bool atual,vector<Veiculo> veiculos): nome(nome),atual(atual)
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

vector <Veiculo> Motorista::getVeiculos()
{
	return this->veiculos;
}

void Motorista::inserirVeiculo(Veiculo *veiculo)
{
	vector<Veiculo>::iterator it;
	it=find(veiculos.begin(),veiculos.end(),*veiculo);

	if(it==veiculos.end())//se nao existir
	{
		veiculos.push_back(*veiculo);
	}
}

void Motorista::setAtual(bool atual)
{
	this->atual=atual;
}

void Motorista::removerVeiculo(Veiculo *veiculo)
{
	vector<Veiculo>::iterator it;
	it=find(veiculos.begin(),veiculos.end(),*veiculo);

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

void Motorista::contratar()
{
	this->atual=true;
}

void Motorista::contratar(Veiculo *veiculo)
{
	this->atual=true;
	veiculos.push_back(*veiculo);
}



