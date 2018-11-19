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
		//const string tipoComb; -> � desnecessario, por isso vamos poupar uma variavel
		float precoComb;
		float consumoPerc;
		//int numero; -> a ideia de numVeiculos � ser o idV de cada veiculo adicionado
		vector <unsigned int> zonasAtravessadas;

public:
		Veiculo(const string &matricula,const int &capacDeposito,const float &precoComb, const float &consumoPerc);
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
	TransporteEscolar(const string matricula,const int capacDeposito,float precoComb,float consumoPerc,unsigned int lotacao,unsigned int lugaresLivres);

};

class	TransporteActividadeRecreativa:public Veiculo
{
private:
	bool alugado;
	const unsigned int capacidade;
public:
	TransporteActividadeRecreativa(const string matricula,const int capacDeposito,float precoComb,float consumoPerc,bool alugado,const unsigned int capacidade);
};
