#include "Utente.h"
#include "Veiculo.h"

class EmpresaTrans
{
private:
	vector <Utente *> utentes;
	vector <Veiculo *> veiculos;
	vector<vector<float>> precos;
	vector<float>lucrosMensais;
public:
	void alocaUtentes();
	void calculoMensal();
	bool alugarTransRecreativo();
	void definirTrajecto(unsigned int idV);
	void adicionarVeiculo(Veiculo *vc);
	void adicionaruUtente(Utente *ut);
	void guardarInfo(const ofstream &f);
	void carregarInfo(const ifstream &f);
	vector<Veiculo*> getVeiculos();
	vector<Utente*> getUtentes();
	void calculoPasseMensal(unsigned int numUtente);
	void atualizarPasses();
	void atualizarPrecos(float delta);
};
