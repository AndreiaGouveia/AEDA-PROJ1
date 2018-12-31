#include "BST.h"
#include "Utente.h"
#include "Exceptions.h"

class Escola
{
private:
	vector<Utente*> utentes;
	string nome;
	unsigned codigo;
	string nome_diretor;
	string morada_diretor;
	unsigned zona;
public:
	Escola(string nome, unsigned codigo, string nome_d,string morada_d, unsigned zona);
	string getNome();
	vector<Utente> & getUtentes();
	unsigned getZona();
	unsigned getCodigo();
	pair<string,string> getDiretorInfo();
	void addUtente(Utente *ut);
	void removeUtente(Utente *ut);
	bool operator<(Escola &esc);
};
