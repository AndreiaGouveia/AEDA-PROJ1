#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Veiculo {
private:
	static unsigned int numVeiculos;
	const unsigned int idV;
	const string matricula;
	int deposito;
	float consumo100km;
	float precoComb;
public:
	Veiculo(const string &matricula, int deposito, float consumo100km, float precoComb);
	virtual ~Veiculo() {}
	virtual float calcGasto() const = 0;
	unsigned int getId() const;
	string getMatricula() const;
};

class Escolar: public Veiculo {
private:
	unsigned int lugaresLivres;
	vector<unsigned int> zonasAtravessadas;
public:
	Escolar(const string &matricula, int deposito, float consumo100km, float precoComb, unsigned int capacidade, const vector<unsigned int>& zonasAtravessadas);
	void adicionarZona(unsigned int zona);
	void removerZona(unsigned int zona);
	float calcGasto(float kmsZona) const;
	friend ostream& operator <<(ostream& out, const Escolar& veic);
};

class Recreativo: public Veiculo {
private:
	const unsigned int capacidade;
	bool alugado;
	float kmsPercorridos;
public:
	Recreativo(const string &matricula, int deposito, float consumo100km, float precoComb, unsigned int cap, bool alugado);
	unsigned int getCapacidade() const;
	bool getEstado() const;
	void setEstado(bool alugado);
	void setKmsPercorridos(float kms);
	float calcGasto() const;
	friend ostream& operator <<(ostream& out, const Recreativo& veic);
};
