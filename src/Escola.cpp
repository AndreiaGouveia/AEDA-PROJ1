#include "Escola.h"

Escola::Escola(string nome, unsigned codigo, string nome_d, string morada_d, unsigned zona)
{
	this->nome = nome;
	this->codigo = codigo;
	this->nome_diretor = nome_d;
	this->morada_diretor = morada_d;
	this->zona = zona;
}

vector<Utente*> Escola::getUtentes() const
{
	return utentes;
}

string Escola::getNome() const
{
	return nome;
}

unsigned Escola::getCodigo() const
{
	return codigo;
}

unsigned Escola::getZona() const
{
	return zona;
}

pair<string,string> Escola::getDiretorInfo() const
{
	pair<string, string> par;
	par.first = this->nome_diretor;
	par.second = this->morada_diretor;

	return par;
}

void Escola::set_diretor(const string &nome, const string &morada)
{
	this->nome_diretor = nome;
	this->morada_diretor = morada;
}

void Escola::addUtente(Utente *ut)
{
	utentes.push_back(ut);
}

void Escola::removeUtente(Utente *ut)
{
	for(size_t i = 0; i < utentes.size(); i++)
	{
		if(utentes[i] == ut)
		{
			utentes.erase(utentes.begin() + i);

			break;
		}
	}
}

bool Escola::operator<(const Escola &esc) const
{
	if(this->getUtentes().size() == esc.getUtentes().size())
	{
		return this->getNome() < esc.getNome();
	}
	else return this->getUtentes().size() < esc.getUtentes().size();
}

ostream& operator <<(ostream& out,const Escola &esc)
{
	pair<string,string> diretor = esc.getDiretorInfo();

	out << esc.getNome() << '\t' << esc.getCodigo() << '\t'
	  << diretor.first << '\t' << diretor.second << '\t'
	  << esc.getZona();

	return out;
}


