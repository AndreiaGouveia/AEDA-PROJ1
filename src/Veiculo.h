#include <vector>
#include <string>

using namespace std;

class Veiculo {
private:
	static unsigned int numVeiculos;
	const unsigned int idV;
	const string matricula;
	const int capacDeposito;
	//const string tipoComb; -> é desnecessario, por isso vamos poupar uma variavel
	float precoComb;
	float consumo100km;
	//int numero; -> a ideia de numVeiculos é ser o idV de cada veiculo adicionado
public:
	Veiculo(const string &matricula, const int &capacDeposito, const float &precoComb, const float &consumoPerc);
	virtual ~Veiculo() {
	}
	virtual float calcGasto() const = 0;
	unsigned int getId() const;
	string getMatricula() const;
};

class Escolar: public Veiculo {
private:
	unsigned int lotacao;
	unsigned int lugaresLivres;
	vector<unsigned int> zonasAtravessadas;
public:
	Escolar(const string matricula, const int capacDeposito, float precoComb, float consumoPerc, unsigned int lotacao, unsigned int lugaresLivres);
	void adicionarZona(unsigned int zona);
	void removerZona(unsigned int zona);
	float calcGasto() const;
	friend ostream& operator <<(ostream& out, const Escolar& veic);
};
class Recreativo: public Veiculo {
private:
	bool alugado;
	const unsigned int capacidade;
	float kmsPercorridos;
public:
	Recreativo(const string matricula, const int capacDeposito, float precoComb, float consumoPerc, bool alugado, const unsigned int capacidade);
	float calcGasto() const;
	friend ostream& operator <<(ostream& out, const Recreativo& veic);
};
