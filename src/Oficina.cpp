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

bool Oficina::operator <(const Oficina &right) const
{
	return this->disponibilidade > right.disponibilidade;
}

bool Oficina::operator ==(const Oficina& right) const
{
	return (this->nome == right.nome) &&
			(this->disponibilidade == right.disponibilidade) &&
			(this->distancia == right.distancia);
}

ostream& operator <<(ostream& out, const Oficina &of)
{
	out << of.getNome() << '\t' << of.getDisp() << '\t' << of.getDist() << '\n';

	return out;
}
