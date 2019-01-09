#include "Oficina.h"

Oficina::Oficina(std::string nom, double dist): nome(nom)
{
	this->disponibilidade = 0;
	this->distancia = dist;
}

std::string Oficina::getNome() const
{
	return nome;
}

int Oficina::getDisp() const
{
	return disponibilidade;
}

double Oficina::getDist() const
{
	return distancia;
}

queue<unsigned int> Oficina::getFila() const
{
	return filaEspera;
}

void Oficina::setDisp(int disp)
{
	this->disponibilidade = disp;
}

void Oficina::setDist(double dist)
{
	this->distancia = dist;
}

void Oficina::reparacao(unsigned int idV)
{
	this->disponibilidade++;
	filaEspera.push(idV);
}

unsigned int Oficina::fimReparacao()
{
	if(!filaEspera.empty()){
		unsigned int temp = filaEspera.front();
		filaEspera.pop();
		this->disponibilidade--;
		return temp;
	}

	return 0;
}

bool Oficina::operator <(const Oficina &right) const
{
	return this->disponibilidade > right.disponibilidade;
}

bool Oficina::operator ==(const Oficina& right) const
{
	return (this->nome == right.nome);
}

ostream& operator <<(ostream& out, const Oficina &of)
{
	queue<unsigned int> aux = of.filaEspera;

	out << of.getNome() << '\t' << of.getDisp() << '\t' << of.getDist();

	while (!aux.empty())
	{
		out << '\t' << aux.front();
		aux.pop();
	}

	return out;
}
