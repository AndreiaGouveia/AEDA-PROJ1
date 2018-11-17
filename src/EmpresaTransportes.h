#include "Utente.h"
#include "Veiculo.h"
#include <iostream>
#include <fstream>

class Empresa
{
private:
	string nome_empresa;
	vector <Utente *> utentes;
	vector <Veiculo *> veiculos;
	vector<vector<double>> precos; //matriz de preços
	vector<double>lucrosMensais; //registo dos lucros
public:
	//cria empresa apenas com nome
	Empresa(string nome);
	//carrega empresa de um ficheiro .txt
	Empresa(ifstream &f);
	//cria empresa com todos os atributos especificados (exceto lucrosMensais) e carrega de um ficheiro a matrix de preços
	Empresa(string nome, vector <Utente *> vUt, vector <Veiculo *> vVeic, ifstream &fprecos);
	vector<Veiculo*> getVeiculos() const;
	vector<Utente*> getUtentes() const;
	vector<vector<double>> getPrecos() const;
	void setUtentes(vector <Utente *> vUt);
	void setVeiculos(vector <Veiculo *> vVeic);
	void setPrecos(ifstream &fprecos);
	void setPrecos(const vector<vector<double>> &vet);
	void adicionarVeiculo(Veiculo *vc);
	void adicionaruUtente(Utente *ut);
	void atualizarPrecos(double delta);
	void guardarInfo(ofstream &f);
	void carregarInfo(ifstream &f);
	//undone
	void atualizarPasses();
	void alocaUtentes();
	void calculoMensal();
	bool alugarTransRecreativo();
	void definirTrajecto(unsigned int idV);
	void calculoPasseMensal(unsigned int numUtente);
};
