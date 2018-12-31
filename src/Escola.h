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
	Escola(string nome, unsigned codigo, string nome_d, string morada_d, unsigned zona);
	string getNome() const;
	vector<Utente*> getUtentes() const;
	unsigned getZona() const;
	unsigned getCodigo() const;
	pair<string,string> getDiretorInfo() const;
	void addUtente(Utente *ut);
	void removeUtente(Utente *ut);
	bool operator<(const Escola &esc) const;
};
