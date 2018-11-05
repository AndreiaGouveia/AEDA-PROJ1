#include <vector>
#include <string>

using namespace std;

class Veiculo
{
private:
	    static unsigned int numVeiculos;
	    const unsigned int idV;
		const string matricula;
		const int capacDeposito;
		const string tipoComb;
		float precoComb;
		float consumoPerc;
		int numero;
		vector <unsigned int> zonasAtravessadas;

public:
		Veiculo(const unsigned int &idV,const string &matricula,const int &capacDeposito,const string &tipoComb,const float &precoComb, const float &consumoPerc);
		float calcGasto();
		void adicionarZona(unsigned int zona);
		void removerZona(unsigned int zona);
};

class	TransporteEscolar : public Veiculo
{
private:
	unsigned int lotacao;
	unsigned int lugaresLivres;
public:
	TransporteEscolar(const unsigned int idV,const string matricula,const int capacDeposito,const string tipoComb,float precoComb,float consumoPerc,unsigned int lotacao,unsigned int lugaresLivres);

};
class	TransporteActividadeRecreativa:public Veiculo
{
private:
	bool alugado;
	const unsigned int capacidade;
public:
	TransporteActividadeRecreativa(const unsigned int idV,const string matricula,const int capacDeposito,const string tipoComb,float precoComb,float consumoPerc,bool alugado,const unsigned int capacidade);
};
