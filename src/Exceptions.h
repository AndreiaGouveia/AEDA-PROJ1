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
	UtenteJaExiste(const string &numUtente) { msg = "O utente de número " + numUtente + " já se encontra registado"; };
};

#endif /* SRC_EXCEPTIONS_H_ */
