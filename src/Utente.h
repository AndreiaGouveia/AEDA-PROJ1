#include <vector>
#include <string>

using namespace std;

class Utente
{
private:
	const string nome;
	const string data_nascimento;
	const string BI;
	unsigned int numUtente;
	unsigned int zonaHabitacao;
	unsigned int zonaEscola;

	static unsigned int ult_numUtente;
public:
	Utente(const string &nome, const string &data_nasc, const string &BI, const unsigned int &zonaHabit, const unsigned int &zonaEsc);
	virtual ~Utente() {}
	string getNome();
	string getData_Nasc();
	string getBI();
	unsigned int getNumUtente();
	unsigned int getZonaHabitacao();
	unsigned int getZonaEscola();
	void setZonaHabitacao(unsigned int zona);
	void setZonaEscola(unsigned int zona);
	virtual unsigned int getContacto() const = 0;
};

class Funcionario : public Utente
{
private:
	const bool docente;
	unsigned int contacto;
public:
	Funcionario(const string &nome, const string &data_nasc, const string &BI, const unsigned int &zonaHabit, const unsigned int &zonaEsc, const bool &docente, const unsigned int &contacto);
	bool getDocente();
	unsigned int getContacto() const;
	friend ostream& operator<< (ostream &out, const Funcionario &utente);
};

class Crianca : public Utente
{
private:
	const string nomeEE;
	unsigned int contactoEE;
public:
	Crianca(const string &nome, const string &data_nasc, const string &BI, const unsigned int &zonaHabit, const unsigned int &zonaEsc, const string & nomeEE, const unsigned int &contactoEE);
	string getNomeEE();
	unsigned int getContacto() const;
	friend ostream& operator<< (ostream &out, const Crianca &utente);
};
