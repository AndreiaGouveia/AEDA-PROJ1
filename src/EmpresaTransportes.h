#include "Utente.h"
#include "Veiculo.h"
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>

class Empresa
{
private:
	string nome_empresa;
	vector <Utente *> utentes;
	vector <Veiculo *> veiculos;
	vector<vector<double>> precos; //matriz de precos dos passes de acordo com as zonas
	vector<double> lucrosMensais; //registo dos lucros
	map<unsigned int,double> tabelaPasses;
public:
	//cria empresa apenas com nome
	Empresa(string nome);
	//carrega empresa de um ficheiro .txt
	Empresa(ifstream &f);
	//cria empresa com todos os atributos especificados (exceto lucrosMensais) e carrega de um ficheiro a matrix de preï¿½os
	Empresa(string nome, vector <Utente *> vUt, vector <Veiculo *> vVeic, ifstream &fprecos);
	string getNome() const {return nome_empresa;}
	vector<Veiculo*> getVeiculos() const;
	vector<Utente*> getUtentes() const;
	vector<vector<double>> getPrecos() const;
	void setUtentes(vector <Utente *> vUt);
	void setVeiculos(vector <Veiculo *> vVeic);
	void setPrecos(istream &fprecos);
	void setPrecos(const vector<vector<double>> &vet);
	void adicionarVeiculo(Veiculo *vc); //TODO Adicionar exceçao
	void adicionaruUtente(Utente *ut); //TODO adicionar exceçao
	void atualizarPrecos(double delta);
	void guardarInfo(ostream &f) const;
	void carregarInfo(ifstream &f);
	friend ostream& operator <<(const ostream& out,const Empresa &emp);
	//undone
	void removerVeiculo(unsigned int id);
	void removerVeiculo(string matricula);
	void atualizarPasses();
	void alocaUtentes();
	void calculoMensal();
	bool alugarTransRecreativo();
	void definirTrajecto(unsigned int idV);
	void calculoPasseMensal(unsigned int numUtente);
};
