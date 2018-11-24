#include "Utente.h"
#include "Veiculo.h"
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>

class Empresa
{
private:
	string nome_empresa; ///< Nome da empresa
	vector <Utente *> utentes; ///< Listagem dos Utentes da Empresa
	vector <Veiculo *> veiculos; ///< Listagem dos Veiculos da Empresa
	float precoPessoa; ///< Preco por pessoa do aluguer de tranportes recreativos
	vector<vector<double>> precos_zona; ///< Matriz de precos dos passes de acordo com as zonas
	vector<double> lucrosMensais; ///< Registo dos lucros registados mensalmente
	vector<double> registoDiario; ///< registo do lucro/prejuizo diario do mes corrente
	map<unsigned int,double> tabelaPasses; ///< Tabela que guarda a correspondencia Utente -> valor do passe mensal
	map<unsigned int,unsigned int> tabelaPassageiros; ///< Tabela que guarda a correspondencia Utente -> veiculo ao qual foi alocado
public:
	/**
	 * @brief
	 */
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
	void adicionarZonaEscolar(unsigned int idV, unsigned int zona);	//TODO ZonaJaExiste
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
	void alocaUtentes();
	void alocaUt(unsigned int numUt);
	bool finalDia(float kmsZona);
	bool calculoMensal();
	void guardarInfo(ostream &f) const;
	void carregarInfo(ifstream &f);
	string showUtentes() const;
	string showVeiculos() const;
	string showMensal() const;
	string showDiario() const;
	friend ostream& operator <<(ostream& out,const Empresa &emp);
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
