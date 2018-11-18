#include "Veiculo.h"

unsigned int Veiculo::numVeiculos = 0;
Veiculo::Veiculo(const string &matricula,const int &capacDeposito,const float &precoComb, const float &consumoPerc)
: idV(++numVeiculos), matricula(matricula), capacDeposito(capacDeposito), precoComb(precoComb), consumoPerc(consumoPerc) {}

float Veiculo::calcGasto()//assumindo que consumoPerc sao os km que anda
{
	return precoComb*consumoPerc;
}

void Veiculo::adicionarZona(unsigned int zona)
{
	bool existe = false;
	for (int i = 0; i < zonasAtravessadas.size(); i++)
	{
		if (zonasAtravessadas[i] == zona)
		{
			existe = true;
			break;
		}
	}
	if (!existe)
		zonasAtravessadas.push_back(zona);
}
void Veiculo::removerZona(unsigned int zona)
{
	for (int i = 0; i < zonasAtravessadas.size(); i++)
	{
		if(zonasAtravessadas[i]==zona)
			zonasAtravessadas.erase(zonasAtravessadas.begin()+i);
	}
}
////////////////////////////////////////////////////////////////
//////////////////Transporte  Escolar///////////////////////////
////////////////////////////////////////////////////////////////
TransporteEscolar::TransporteEscolar(const string matricula,const int capacDeposito,float precoComb,float consumoPerc,unsigned int lotacao,unsigned int lugaresLivres):Veiculo(matricula,capacDeposito,precoComb,consumoPerc)
{
	this->lotacao=lotacao;
	this->lugaresLivres=lugaresLivres;
}

////////////////////////////////////////////////////////////////
//////////////////Transporte  Recreativo////////////////////////
////////////////////////////////////////////////////////////////
TransporteActividadeRecreativa::TransporteActividadeRecreativa(const string matricula,const int capacDeposito,float precoComb,float consumoPerc,bool alugado,const unsigned int capacidade):Veiculo(matricula,capacDeposito,precoComb,consumoPerc),capacidade(capacidade)
{	this->alugado=alugado;
}

