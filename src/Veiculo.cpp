#include "Veiculo.h"

unsigned int Veiculo::numVeiculos=1;
Veiculo::Veiculo(const unsigned int &idV,const string &matricula,const int &capacDeposito,const string &tipoComb,const float &precoComb, const float &consumoPerc)
: idV(idV), matricula(matricula), capacDeposito(capacDeposito), tipoComb(tipoComb), precoComb(precoComb), consumoPerc(consumoPerc),numero(numVeiculos++) {}

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
TransporteEscolar::TransporteEscolar(const unsigned int idV,const string matricula,const int capacDeposito,const string tipoComb,float precoComb,float consumoPerc,unsigned int lotacao,unsigned int lugaresLivres):Veiculo(idV, matricula,capacDeposito,tipoComb,precoComb,consumoPerc)
{
	this->lotacao=lotacao;
	this->lugaresLivres=lugaresLivres;
}

////////////////////////////////////////////////////////////////
//////////////////Transporte  Recreativo////////////////////////
////////////////////////////////////////////////////////////////
TransporteActividadeRecreativa::TransporteActividadeRecreativa(const unsigned int idV,const string matricula,const int capacDeposito,const string tipoComb,float precoComb,float consumoPerc,bool alugado,const unsigned int capacidade):Veiculo(idV, matricula,capacDeposito,tipoComb,precoComb,consumoPerc),capacidade(capacidade)
{	this->alugado=alugado;
}

