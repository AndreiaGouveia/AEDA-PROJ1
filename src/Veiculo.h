#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <ostream>

using namespace std;

class Veiculo {
protected:
	static unsigned int numVeiculos;
	const unsigned int idV;
	const string matricula;
	float consumo100km;
	float precoComb;
public:
	Veiculo(const string &matricula, float consumo100km, float precoComb);
	virtual ~Veiculo() {}
	virtual float calcGasto(float kms) const = 0;
	unsigned int getId() const;
	string getMatricula() const;
	virtual string getInfo() const;
	virtual void adicionarZona(unsigned int zona) {}
	virtual void removerZona(unsigned int zona) {}
	virtual bool getEstado() const {return false;} //retorno irrelevante
	virtual void setEstado(bool alugado) {}
	virtual unsigned int getCapacidade() {return 0;}
	virtual bool existeZona(unsigned int zona) {return false;}
	virtual bool cheio() const {return false;}
	virtual void aumentaLug() {}
	virtual void reduzLug() {}
	friend ostream& operator <<(ostream& out, const Veiculo& veic);
};

class Escolar: public Veiculo {
private:
	const unsigned int lugTotais;
	unsigned int lugaresLivres;
	vector<unsigned int> zonasAtravessadas;
public:
	Escolar(const string &matricula, float consumo100km, float precoComb, unsigned int capacidade, const vector<unsigned int>& zonasAtravessadas);
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
