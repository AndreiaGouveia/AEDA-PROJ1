#ifndef SRC_EXCEPTIONS_H_
#define SRC_EXCEPTIONS_H_

#include <string>
#include <sstream>
#include <exception>

using namespace std;

class ZonaNaoExistente
{
	ostringstream msg;
public:
	ZonaNaoExistente(const unsigned int &z) { msg << "A zona " << z << " nao existe."; }
	string getMsg() { return msg.str(); }
};

class ZonaJaExistente
{
	ostringstream msg;
public:
	ZonaJaExistente(const unsigned int &z) { msg << "A zona " << z << " ja existe."; }
	string getMsg() { return msg.str(); }
};

class VeiculoNaoExistente
{
private:
	string msg;
public:
	VeiculoNaoExistente() { msg = "Veiculo nao existente."; }
	string getMsg() { return msg; }
};

class VeiculoJaExiste
{
private:
	string msg;
public:
	VeiculoJaExiste(const string &matricula) { msg = "Veiculo de matricula " + matricula + " ja se encontra registado"; }
	string getMsg() { return msg; }
};

class VeiculosInsuficientes
{
private:
	string msg;
public:
	VeiculosInsuficientes() { msg = "Nao ha veiculos suficientes"; }
	string getMsg() { return msg; }
};

class VeiculoNaoEscolar
{
private:
	string msg;
public:
	VeiculoNaoEscolar() { msg = "O veiculo nao e escolar!"; }
	string getMsg() { return msg; }
};

class VeiculoNaoRecreativo
{
private:
	string msg;
public:
	VeiculoNaoRecreativo() { msg = "O veiculo nao e recreativo!"; }
	string getMsg() { return msg; }
};

class UtenteNaoExistente
{
private:
	string msg;
public:
	UtenteNaoExistente() { msg = "Utente nao existente."; }
	string getMsg() { return msg; }
};

class UtenteJaExiste
{
private:
	string msg;
public:
	UtenteJaExiste(const string &numUtente) { msg = "O utente de numero " + numUtente + " ja se encontra registado"; }
	string getMsg() { return msg; }
};

class PrecoNaoDefinido
{
private:
	string msg;
public:
	PrecoNaoDefinido() { msg = "O preco por pessoa nao esta definido ainda."; }
	string getMsg() { return msg; }
};


#endif /* SRC_EXCEPTIONS_H_ */
