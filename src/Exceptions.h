#ifndef SRC_EXCEPTIONS_H_
#define SRC_EXCEPTIONS_H_

#include <string>
#include <sstream>

using namespace std;

class ZonaInexistente
{
	ostringstream msg;
public:
	ZonaInexistente(const unsigned int &z) { msg << "A zona " << z << " não existe."; }
	string getMsg() { return msg.str(); }
};

class ZonaJaExiste
{
	ostringstream msg;
public:
	ZonaJaExiste(const unsigned int &z) { msg << "A zona " << z << " já existe."; }
	string getMsg() { return msg.str(); }
};

class VeiculoNaoExistente
{
private:
	string msg;
public:
	VeiculoNaoExistente() { msg = "Veiculo não existente."; }
	string getMsg() { return msg; }
};

class VeiculoJaExiste
{
private:
	string msg;
public:
	VeiculoJaExiste(const string &matricula) { msg = "Veiculo de matricula " + matricula + " já se encontra registado"; }
	string getMsg() { return msg; }
};

class VeiculosInsuficientes
{
private:
	string msg;
public:
	VeiculosInsuficientes() { msg = "Não há veículos suficientes"; }
	string getMsg() { return msg; }
};

class VeiculoNaoEscolar
{
private:
	string msg;
public:
	VeiculoNaoEscolar() { msg = "O veículo não é escolar!"; }
	string getMsg() { return msg; }
};

class VeiculoNaoRecreativo
{
private:
	string msg;
public:
	VeiculoNaoRecreativo() { msg = "O veículo não é recreativo!"; }
	string getMsg() { return msg; }
};

class UtenteNaoExistente
{
private:
	string msg;
public:
	UtenteNaoExistente() { msg = "Veiculo não existente."; }
	string getMsg() { return msg; }
};

class UtenteJaExiste
{
private:
	string msg;
public:
	UtenteJaExiste(const string &numUtente) { msg = "O utente de número " + numUtente + " já se encontra registado"; }
	string getMsg() { return msg; }
};

class PrecoNaoDefinido
{
private:
	string msg;
public:
	PrecoNaoDefinido() { msg = "O preço por pessoa não está definido ainda."; }
	string getMsg() { return msg; }
};

#endif /* SRC_EXCEPTIONS_H_ */
