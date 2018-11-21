#include "Utente.h"


////////////////////////////////////////////////////////////////
//////////////////////Utente////////////////////////////////////
////////////////////////////////////////////////////////////////
unsigned int Utente::ult_numUtente = 0;

Utente::Utente(const string &nome, const string &data_nasc, const string &BI, const unsigned int &zonaHabit, const unsigned int &zonaEsc)
: nome(nome), data_nascimento(data_nasc), BI(BI), numUtente(++ult_numUtente), zonaHabitacao(zonaHabit), zonaEscola(zonaEsc){}

string Utente::getNome()
{
	return nome;
}

string Utente::getData_Nasc()
{
	return data_nascimento;
}

string Utente::getBI()
{
	return BI;
}

unsigned int Utente::getNumUtente()
{
	return numUtente;
}

unsigned int Utente::getZonaHabitacao()
{
	return zonaHabitacao;
}

unsigned int Utente::getZonaEscola()
{
	return zonaEscola;
}

void Utente::setZonaHabitacao(unsigned int zona)
{
	zonaHabitacao = zona;
}

void Utente::setZonaEscola(unsigned int zona)
{
	zonaEscola = zona;
}

string Utente::getInfo() const
{
	ostringstream out;

	out << nome << '\t' << data_nascimento << '\t' << BI << '\t'
			<< numUtente << '\t' << zonaHabitacao << '\t' << zonaEscola;

	return out.str();
}

////////////////////////////////////////////////////////////////
//////////////////////Funcionario///////////////////////////////
////////////////////////////////////////////////////////////////

Funcionario::Funcionario(const string &nome, const string &data_nasc, const string &BI, const unsigned int &zonaHabit, const unsigned int &zonaEsc, const bool &docente, const unsigned int &contacto)
: Utente(nome, data_nasc, BI, zonaHabit, zonaEsc), docente(docente), contacto(contacto) {}

bool Funcionario::getDocente()
{
	return docente;
}
unsigned int Funcionario::getContacto() const
{
	return contacto;
}

string Funcionario::getInfo() const
{
	ostringstream out;

	out << Utente::getInfo() << '\t';

	if(docente)
	{
		out << "docente" << '\t';
	}
	else
	{
		out << "funcionario(a)" << '\t';
	}

	out << contacto;

	return out.str();
}

////////////////////////////////////////////////////////////////
//////////////////////Crianca///////////////////////////////////
////////////////////////////////////////////////////////////////

Crianca::Crianca(const string &nome, const string &data_nasc, const string &BI, const unsigned int &zonaHabit, const unsigned int &zonaEsc, const string & nomeEE, const unsigned int &contactoEE)
: Utente(nome, data_nasc, BI, zonaHabit, zonaEsc), nomeEE(nomeEE), contactoEE(contactoEE) {}

string Crianca::getNomeEE()
{
	return nomeEE;
}

unsigned int Crianca::getContacto() const
{
	return contactoEE;
}

string Crianca::getInfo() const
{
	ostringstream out;

	out << Utente::getInfo() << '\t' << nomeEE << '\t' << contactoEE;

	return out.str();
}

////////////////////////////
/////OPERADORES/////////////
////////////////////////////

ostream& operator<< (ostream &out, const Utente &utente)
{
	out << utente.getInfo();

	return out;
}

ostream& operator<< (ostream &out, const Funcionario &utente)
{
	out << utente.getInfo();

	return out;
}

ostream& operator<< (ostream &out, const Crianca &utente)
{
	out << utente.getInfo();

	return out;
}
