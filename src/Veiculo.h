#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <ostream>

using namespace std;

class Veiculo {
protected:
	const unsigned int idV;
	const string matricula;
	float consumo100km;
	float precoComb;
public:
	static unsigned int numVeiculos;
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
	const unsigned int lugTotais;
	unsigned int lugaresLivres;
	vector<unsigned int> zonasAtravessadas;
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
	const unsigned int capacidade;
	bool alugado;
public:
	Recreativo(const string &matricula, float consumo100km, float precoComb, unsigned int cap, bool alugado);
	unsigned int getCapacidade() const;
	bool getEstado() const;
	void setEstado(bool alugado);
	float calcGasto(float kms) const;
	string getInfo() const;
	friend ostream& operator <<(ostream& out, const Recreativo& veic);
};
