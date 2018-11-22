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
	unsigned int precoPessoa; //preco por pessoa do aluguer de tranportes recreativos
	vector<vector<double>> precos; //matriz de precos dos passes de acordo com as zonas
	vector<double> lucrosMensais; //registo dos lucros
	vector<double> registoDiario; //registo do lucro/prejuizo diario
	map<unsigned int,double> tabelaPasses;
public:
	//cria empresa apenas com nome
	Empresa(string nome);
	//carrega empresa de um ficheiro .txt
	Empresa(ifstream &f);
	//cria empresa com todos os atributos especificados (exceto lucrosMensais) e carrega de um ficheiro a matrix de pre�os
	Empresa(string nome, vector <Utente *> vUt, vector <Veiculo *> vVeic, unsigned int precoPessoa, ifstream &fprecos);
	string getNome() const {return nome_empresa;}
	vector<Veiculo*> getVeiculos() const;
	vector<Utente*> getUtentes() const;
	unsigned int getPrecoPessoa() const;
	vector<vector<double>> getPrecos() const;
	void setUtentes(vector <Utente *> vUt);
	void setVeiculos(vector <Veiculo *> vVeic);
	void setPrecoPessoa(unsigned int precoP);
	void setPrecos(istream &fprecos);
	void setPrecos(const vector<vector<double>> &vet);
	void adicionarVeiculo(Veiculo *vc); 	//TODO VeiculoJaExistente
	void adicionarUtente(Utente *ut);		//TODO UtenteJaExistente
	void removerVeiculo(unsigned int id);	//TODO VeiculoNaoExistente
	void removerVeiculo(string matricula);	//TODO VeiculoNaoExistente
	void removerUtente(unsigned int numUt);	//TODO UtenteNaoExistente
	void removerUtente(string BI);			//TODO UtenteNaoExistente
	void adicionarZonaEscolar(unsigned int idV, unsigned int zona);	//TODO ZonaJaExistente
	void removerZonaEscolar(unsigned int idV, unsigned int zona);	//TODO ZonaNaoExistente
	void alterarZonaHab(unsigned int numUtente, unsigned int zona); //TODO UtenteNaoExistente
	void alterarZonaEsc(unsigned int numUtente, unsigned int zona);
	void alterarContacto(unsigned int numUtente, unsigned int cont);
	unsigned int getContacto(unsigned int numUtente);
	unsigned int getContacto(string BI);
	double calculoPasseMensal(unsigned int numUtente);
	void atualizarPasses();
	void atualizarPrecos(double delta);
	double calcularAluguer(unsigned int idV);
	string verificaDispRecreativo(unsigned int capacidade);
	bool alugaRecreativo(unsigned int idV);
	bool finalDia(float kmsZona);
	void calculoMensal();
	void guardarInfo(ostream &f) const; //TODO adicionar precoPessoa e registoDiario e kmsPercorridos
	void carregarInfo(ifstream &f);		//TODO adicionar precoPessoa e registoDiario e kmsPercorridos
	friend ostream& operator <<(const ostream& out,const Empresa &emp);
	//undone
	void alocaUtentes();
};

class CmpId
{
public:
	bool operator() (Veiculo* left, Veiculo* right)
	{
		return left->getId() < right->getId();
	}
	bool operator() (Utente* left, Utente* right)
	{
		return left->getNumUtente() < right->getNumUtente();
	}
};
