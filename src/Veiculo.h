#include <vector>
#include <string>
#include <algorithm>
#include <ostream>

using namespace std;

<<<<<<< HEAD
class Veiculo {
protected:
	static unsigned int numVeiculos;
	const unsigned int idV;
	const string matricula;
	float consumo100km;
	float precoComb;
=======
class Veiculo
{
private:
	    static unsigned int numVeiculos;
	    const unsigned int idV;
		const string matricula;
		const int capacDeposito;
		//const string tipoComb; -> � desnecessario, por isso vamos poupar uma variavel
		float precoComb;
		float consumoPerc;
		//int numero; -> a ideia de numVeiculos � ser o idV de cada veiculo adicionado
		vector <unsigned int> zonasAtravessadas;

>>>>>>> d11e361ba0b279aeb9e6cb7309fdc18226a3bbdc
public:
	Veiculo(const string &matricula, float consumo100km, float precoComb);
	virtual ~Veiculo() {}
	virtual float calcGasto(float kms) const = 0;
	unsigned int getId() const;
	string getMatricula() const;
};

class Escolar: public Veiculo {
private:
	unsigned int lugaresLivres;
	vector<unsigned int> zonasAtravessadas;
public:
	Escolar(const string &matricula, float consumo100km, float precoComb, unsigned int capacidade, const vector<unsigned int>& zonasAtravessadas);
	void adicionarZona(unsigned int zona);
	void removerZona(unsigned int zona);
	float calcGasto(float kms) const;
	friend ostream& operator <<(ostream& out, const Escolar& veic);
};

<<<<<<< HEAD
class Recreativo: public Veiculo {
=======
class	TransporteActividadeRecreativa:public Veiculo
{
>>>>>>> d11e361ba0b279aeb9e6cb7309fdc18226a3bbdc
private:
	const unsigned int capacidade;
	bool alugado;
public:
	Recreativo(const string &matricula, float consumo100km, float precoComb, unsigned int cap, bool alugado);
	unsigned int getCapacidade() const;
	bool getEstado() const;
	void setEstado(bool alugado);
	float calcGasto(float kms) const;
	friend ostream& operator <<(ostream& out, const Recreativo& veic);
};
