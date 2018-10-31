#include <vector>
#include <string>

using namespace std;

class Utente
{
private:
	const string nome;
	unsigned int idade;
	const string BI;
	unsigned int numUtente;
	unsigned int zonaHabitacao;
	unsigned int zonaEscola;
public:
	Utente(const string nome,unsigned int idade,const string BI,unsigned int numUtente,unsigned int zonaHabitacao,unsigned int zonaEscola);
	string getNome();
	string getBI();
	unsigned int getNumUtente();
	unsigned int getZonaHabitacao();
	unsigned int getZonaEscola();
	unsigned int setZonaHabitacao();
	unsigned int setZonaEscola();
	virtual unsigned int getContacto();
};

class Funcionario:public Utente
{
private:
	bool docente;
	unsigned int contacto;
public:
	Funcionario(const string nome,unsigned int idade,const string BI,unsigned int numUtente,unsigned int zonaHabitacao,unsigned int zonaEscola,bool docente,unsigned int contacto);
	bool getDocente();
	unsigned int getContacto();
};

class Crianca:public Utente
{
private:
	const string nomeEE;
	unsigned int contactoEE;
public:
	Crianca(const string nome,unsigned int idade,const string BI,unsigned int numUtente,unsigned int zonaHabitacao,unsigned int zonaEscola,const string nomeEE,unsigned int contactoEE);
	string getNomeEE();
	unsigned int getContacto();
};
