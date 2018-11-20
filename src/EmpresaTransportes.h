#include "Utente.h"
#include "Veiculo.h"
#include <iostream>
#include <sstream>
#include <fstream>

class Empresa
{
private:
	string nome_empresa;
	vector <Utente *> utentes;
	vector <Veiculo *> veiculos;
	vector<vector<double>> precos; //matriz de pre�os
	vector<double> lucrosMensais; //registo dos lucros
public:
	//cria empresa apenas com nome
	Empresa(string nome);
	//carrega empresa de um ficheiro .txt
	Empresa(ifstream &f);
	//cria empresa com todos os atributos especificados (exceto lucrosMensais) e carrega de um ficheiro a matrix de pre�os
	Empresa(string nome, vector <Utente *> vUt, vector <Veiculo *> vVeic, ifstream &fprecos);
	string getNome() const {return nome_empresa;}
	vector<Veiculo*> getVeiculos() const;
	vector<Utente*> getUtentes() const;
	vector<vector<double>> getPrecos() const;
	void setUtentes(vector <Utente *> vUt);
	void setVeiculos(vector <Veiculo *> vVeic);
	void setPrecos(istream &fprecos);
	void setPrecos(const vector<vector<double>> &vet);
	void adicionarVeiculo(Veiculo *vc);
	void adicionaruUtente(Utente *ut);
	void atualizarPrecos(double delta);
	void guardarInfo(ostream &f) const;
	void carregarInfo(ifstream &f);
	friend ostream& operator <<(const ostream& out,const Empresa &emp);
	//undone
	void atualizarPasses();
	void alocaUtentes();
	void calculoMensal();
	bool alugarTransRecreativo();
	void definirTrajecto(unsigned int idV);
	void calculoPasseMensal(unsigned int numUtente);
};
