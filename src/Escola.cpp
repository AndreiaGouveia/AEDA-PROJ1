#include "Escola.h"

Escola::Escola(string nome, unsigned codigo, string nome_d,string morada_d, unsigned zona)
{
	this->nome = nome;
	this->codigo = codigo;
	this->nome_diretor = nome_d;
	this->morada_diretor = morada_d;
	this->zona = zona;
}

vector<Utente> & Escola::getUtentes()
{
	return utentes;
}

string Escola::getNome()
{
	return nome;
}

unsigned Escola::getCodigo()
{
	return codigo;
}

unsigned Escola::getZona()
{
	return zona;
}

pair<string,string> Escola::getDiretorInfo()
{
	pair<string, string> par;
	par.first = this->nome_diretor;
	par.second = this->morada_diretor;

	return par;
}

void Escola::addUtente(Utente *ut)
{
	utentes.push_back(ut);
}

void Escola::removeUtente(Utente *ut)
{
	for(size_t i = 0; i < utentes.size(); i++)
	{
		if(*utentes[i] == *ut)
		{
			utentes.erase(utentes.begin() + i);

			break;
		}
	}
}

bool Escola::operator<(Escola &esc)
{
	if(this->getUtentes().size() == esc.getUtentes().size())
	{
		return this->getNome() < esc.getNome();
	}
	else return this->getUtentes().size() < esc.getUtentes().size();
}

