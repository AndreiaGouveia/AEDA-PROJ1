#include "Veiculo.h"

unsigned int Veiculo::numVeiculos = 0;

Veiculo::Veiculo(const string &matricula, int deposito, float consumo100km, float precoComb) : idV(++numVeiculos), matricula(matricula)
{
	this->deposito = deposito;
	this->consumo100km = consumo100km;
	this->precoComb = precoComb;
}

unsigned int Veiculo::getId() const
{
	return idV;
}

string Veiculo::getMatricula() const
{
	return matricula;
}

////////////////////////////////////////////////////////////////
//////////////////Transporte  Escolar///////////////////////////
////////////////////////////////////////////////////////////////
Escolar::Escolar(const string &matricula, int deposito, float consumo100km, float precoComb, unsigned int capacidade, const vector<unsigned int>& zonasAtravessadas = vector<unsigned int>()) :
		Veiculo(matricula, deposito, consumo100km, precoComb)
{
	lugaresLivres = capacidade;
	this->zonasAtravessadas = zonasAtravessadas;
}

void Escolar::adicionarZona(unsigned int zona)
{
	for(size_t i = 0; i < zonasAtravessadas; i++)
	{
		if(zonasAtravessadas[i] == zona)
			return;
	}

	zonasAtravessadas.push_back(zona);

	sort(zonasAtravessadas.begin(),zonasAtravessadas.end()); //o vector zonasAtravessadas
}

void Escolar::removerZona(unsigned int zona)
{
	vector<unsigned int>::iterator it = find(zonasAtravessadas.begin(), zonasAtravessadas.end(), zona);

	if(it == zonasAtravessadas.end())
		//throw ZonaInexistente(zona); //IMPLEMENTAR ZONAINEXISTENTE

	zonasAtravessadas.erase(it);
}

float Escolar::calcGasto(float kmsZona) const
{
	return zonasAtravessadas.size() * kmsZona * consumo100km / 100.0;
}

ostream& operator <<(ostream& out, const Escolar& veic)
{
	out << "Transporte Escolar" << '\t' << veic.idV << '\t' << veic.matricula << '\t'
			<< veic.deposito << '\t' << veic.consumo100km << '\t' << veic.precoComb << '\t'
			<< veic.lugaresLivres << '\t' << '{';

	for(size_t i = 0; i < veic.zonasAtravessadas.size(); i++)
	{
		if (i == veic.zonasAtravessadas.size() - 1)
			out << veic.zonasAtravessadas[i];
		else
			out << veic.zonasAtravessadas[i] << ',';
	}

	out << '}';

	return out;
}

////////////////////////////////////////////////////////////////
//////////////////Transporte  Recreativo////////////////////////
////////////////////////////////////////////////////////////////
Recreativo::Recreativo(const string &matricula, int deposito, float consumo100km, float precoComb, unsigned int cap, bool alugado) :
	Veiculo(matricula, deposito, consumo100km, precoComb)
{
	capacidade = cap;
	this->alugado=alugado;
	kmsPercorridos = 0;
}

unsigned int Recreativo::getCapacidade() const
{
	return capacidade;
}

bool Recreativo::getEstado() const
{
	return alugado;
}

void Recreativo::setEstado(bool alugado)
{
	this->alugado = alugado;
}

void Recreativo::setKmsPercorridos(float kms)
{
	kmsPercorridos = kms;
}

float Recreativo::calcGasto() const
{
	return
}
