#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <ostream>

using namespace std;

class Veiculo {
protected:
	const unsigned int idV; ///< Identificacao interna do veiculo
	const string matricula; ///< Matricula do veiculo (Nota: nao ha matriculas repetidas)
	float consumo100km; ///< Volume medio de Litros consumidos por 100 kms
	float precoComb; ///< Preco do combustivel usado no veiculo
public:
	static unsigned int numVeiculos; ///< Membro estatico que guarda qual o numero de identificacao do ultimo veiculo registado
	Veiculo(const string &matricula, float consumo100km, float precoComb);
	virtual ~Veiculo() {}
	unsigned int getId() const;
	string getMatricula() const;
	float getConsumo() const;
	float getPreco() const;
	virtual unsigned int getLugsLivres() const {return 0;}
	virtual vector<unsigned int> getZonas() const {return vector<unsigned int>();}
	virtual void adicionarZona(unsigned int zona) {}
	virtual void removerZona(unsigned int zona) {}
	virtual bool getEstado() const {return false;} //retorno irrelevante
	virtual void setEstado(bool alugado) {}
	virtual unsigned int getCapacidade() const {return 0;}
	virtual bool existeZona(unsigned int zona) {return false;}
	virtual float calcGasto(float kms) const = 0;
	virtual bool cheio() const {return false;}
	virtual void aumentaLug() {}
	virtual void reduzLug() {}
	virtual string getInfo() const;
	friend ostream& operator <<(ostream& out, const Veiculo& veic);
};

class Escolar: public Veiculo {
private:
	const unsigned int lugTotais; ///< Capacidade do Trasnporte Escolar (Nota: usado apenas na inicializacao do objeto)
	unsigned int lugaresLivres; ///< Numero de lugares livres no transporte escolar
	vector<unsigned int> zonasAtravessadas; ///< Listagem das zonas em que o transporte escolar passa
public:
	Escolar(const string &matricula, float consumo100km, float precoComb, unsigned int capacidade, const vector<unsigned int>& zonasAtravessadas);
	unsigned int getLugsLivres() const;
	vector<unsigned int> getZonas() const;
	void adicionarZona(unsigned int zona);
	void removerZona(unsigned int zona);
	bool existeZona(unsigned int zona);
	float calcGasto(float kms) const;
	bool cheio() const;
	void aumentaLug();
	void reduzLug();
	string getInfo() const;
	friend ostream& operator <<(ostream& out, const Escolar& veic);
};

class Recreativo: public Veiculo {
private:
	const unsigned int capacidade; ///< Capacidade do transporte recreativo (Nota: nao pode ser alterada depois de inicializada)
	bool alugado; ///< Estado de aluguer do transporte recreativo: alugado->true; livre->false
public:
	Recreativo(const string &matricula, float consumo100km, float precoComb, unsigned int cap, bool alugado);
	unsigned int getCapacidade() const;
	bool getEstado() const;
	void setEstado(bool alugado);
	float calcGasto(float kms) const;
	string getInfo() const;
	friend ostream& operator <<(ostream& out, const Recreativo& veic);
};
