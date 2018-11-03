#include "Veiculo.h"

Veiculo::Veiculo(const unsigned int &idV,const string &matricula,const int &capacDeposito,const string &tipoComb,const float &precoComb, const float &consumoPerc)
: idV(idV), matricula(matricula), capacDeposito(capacDeposito), tipoComb(tipoComb), precoComb(precoComb), consumoPerc(consumoPerc) {}

float Veiculo::calcGasto()//assumindo que consumoPerc sao os km que anda
{
	return precoComb*consumoPerc;
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


