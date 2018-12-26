#include "Oficina.h"

Oficina::Oficina(std::string nom, int disp, double dist): nome(nom)
{
	this->disponibilidade = disp;
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

void Oficina::reparacao()
{
	this->disponibilidade++;
}

bool Oficina::operator <(const Oficina &right)
{
	return this->disponibilidade > right.disponibilidade;
}

ostream& operator <<(ostream& out, const Oficina &of)
{
	out << of.nome << '\t' << of.disponibilidade << '\t' << of.distancia << '\n';

	return out;
}
