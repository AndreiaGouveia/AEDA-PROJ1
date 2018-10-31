#include <utente.h>
////////////////////////////////////////////////////////////////
//////////////////////Utente////////////////////////////////////
////////////////////////////////////////////////////////////////
Utente::Utente(const string nome,unsigned int idade,const string BI,unsigned int numUtente,unsigned int zonaHabitacao,unsigned int zonaEscola):nome(nome),BI(BI)
{
	this->idade=idade;
	this->numUtente=numUtente;
	this->zonaHabitacao=zonaHabitacao;
	this->zonaEscola=zonaEscola;
}

string Utente::getNome()
{
	return nome;
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

virtual unsigned int Utente::getContacto()
{}
////////////////////////////////////////////////////////////////
//////////////////////Funcionario///////////////////////////////
////////////////////////////////////////////////////////////////
Funcionario::Funcionario(const string nome,unsigned int idade,const string BI,unsigned int numUtente,unsigned int zonaHabitacao,unsigned int zonaEscola,bool docente,unsigned int contacto):Utente( nome, idade, BI, numUtente, zonaHabitacao, zonaEscola)
{
	this->docente=docente;
	this->contacto=contacto;
}
bool Funcionario::getDocente()
{
	return docente;
}
unsigned int Funcionario::getContacto()
{
	return contacto;
}
////////////////////////////////////////////////////////////////
//////////////////////Crianca///////////////////////////////////
////////////////////////////////////////////////////////////////
Crianca::Crianca(const string nome,unsigned int idade,const string BI,unsigned int numUtente,unsigned int zonaHabitacao,unsigned int zonaEscola,const string nomeEE,unsigned int contactoEE):Utente( nome, idade, BI, numUtente, zonaHabitacao, zonaEscola)
{
	this->nomeEE=nomeEE;
	this->contactoEE=contactoEE;
}
string Crianca::getNomeEE()
{
	return nomeEE;
}
unsigned int Crianca::getContacto()
{
	return contactoEE;
}
