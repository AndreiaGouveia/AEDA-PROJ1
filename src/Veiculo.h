#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <ostream>
#include "Exceptions.h"

using namespace std;

/**
 * @class Veiculo
 *
 * @ingroup Veiculo
 *
 * @brief Classe para instanciar veiculos
 *
 * Esta classe agrupa todas as caracteristicas de um veiculo.
 * Permite definir os tracos gerais de um veiculo usado pela Empresa,
 * i.e. matricula, identificacao, consumo e preco de combustivel.
 * Com base nesta classe e nas suas derivadas (Escolar e Recreativo)
 * e possivel executar operacoes como alugar um transporte recreativo,
 * calcular o gasto no percurso efetuado, definir as zonas por onde o transporte escolar passa, etc.
 */
class Veiculo {
protected:
	const unsigned int idV; ///< Identificacao interna do veiculo
	const string matricula; ///< Matricula do veiculo (Nota: nao ha matriculas repetidas)
	float consumo100km; ///< Volume medio de Litros consumidos por 100 kms
	float precoComb; ///< Preco do combustivel usado no veiculo
	bool emReparacao; ///< Estado de reparacao do veiculo (se esta ou nao a ser reparado neste momento)
public:
	static unsigned int numVeiculos; ///< Membro estatico que guarda qual o numero de identificacao do ultimo veiculo registado
	/**
	 * @brief Construtor da classe Veiculo
	 *
	 * @param matricula	Matricula do veiculo
	 * @param consumo100km	Consumo em Litros por cada 100 kms
	 * @param precoComb	Preco do combustivel usado no veiculo
	*/
	Veiculo(const string &matricula, float consumo100km, float precoComb);
	virtual ~Veiculo() {}
	/**
	 * @brief Permite acesso ao identificador interno do veiculo
	 *
	 * @return identificacao do veiculo
	*/
	unsigned int getId() const;
	/**
	 * @brief Permite acesso a matricula do veiculo
	 *
	 * @return matricula do veiculo
	*/
	string getMatricula() const;
	/**
	 * @brief Permite acesso consumo em Litros por 100 kms do veiculo
	 *
	 * @return consumo100km do veiculo
	*/
	float getConsumo() const;
	/**
	 * @brief Permite acesso ao preco do combustivel usado no veiculo
	 *
	 * @return preco do combustivel do veiculo
	*/
	float getPreco() const;
	virtual unsigned int getLugsLivres() const {return 0;}
	virtual vector<unsigned int> getZonas() const {return vector<unsigned int>();}
	virtual void adicionarZona(unsigned int zona) {}
	virtual void removerZona(unsigned int zona) {}
	virtual bool getEstado() const {return false;}
	virtual void setEstado(bool alugado) {}
	virtual unsigned int getCapacidade() const {return 0;}
	virtual bool existeZona(unsigned int zona) {return false;}
	virtual float calcGasto(float kms) const = 0;
	virtual bool cheio() const {return false;}
	virtual void aumentaLug() {}
	virtual void reduzLug() {}
	/**
	 * @brief Organiza a informacao do veiculo para ser guardada em ficheiro
	 *
	 * @return string com toda a informacao do veiculo (atributos separados por tabs)
	*/
	virtual string getInfo() const;
//============================================================================
	/**
	 * @brief Devolve o estado de reparacao do veiculo
	 *
	 * @return true -> o veiculo esta em oficina a ser reparado
	 * @return false -> o veiculo esta disponivel
	 */
	bool getReparacao() const;
	/**
	 * @brief Altera o estado de reparacao do veiculo
	 *
	 * @param rep Novo estado (true-> veiculo em oficina, false-> veiculo saiu da oficina)
	 */
	void setReparacao(bool rep);
	friend ostream& operator <<(ostream& out, const Veiculo& veic);
};

/**
 * @class Escolar
 *
 * @ingroup Veiculo
 *
 * @brief Classe para instanciar transportes escolares
 *
 * Os transportes escolares sao os responsaveis por levar os utentes de
 * casa ate a escola e vice-versa. Por isso cada transporte recreativo possui
 * uma listagem das zonas que atravessa previamente definida para poder levar utentes.
 */
class Escolar: public Veiculo {
private:
	const unsigned int lugTotais; ///< Capacidade do Trasnporte Escolar (Nota: usado apenas na inicializacao do objeto)
	unsigned int lugaresLivres; ///< Numero de lugares livres no transporte escolar
	vector<unsigned int> zonasAtravessadas; ///< Listagem das zonas em que o transporte escolar passa
public:
	/**
	 * @brief Construtor da classe Escolar
	 *
	 * @param matricula	Matricula do trasnporte escolar
	 * @param consumo100km	Consumo em Litros por cada 100 kms
	 * @param precoComb	Preco do combustivel usado no trasnporte escolar
	 * @param capacidade Capacidade total do trasnporte escolar (Inicializa tanto lugTotais como lugaresLivres)
	 * @param zonasAtravessadas Vetor das zonas por onde o trasnporte escolar passa (por omissao e inicializado um vector vazio)
	*/
	Escolar(const string &matricula, float consumo100km, float precoComb, unsigned int capacidade, const vector<unsigned int>& zonasAtravessadas);
	/**
	 * @brief Permite acesso aos lugares livres no transporte escolar
	 *
	 * @return lugares livres no transporte escolar
	*/
	unsigned int getLugsLivres() const;
	/**
	 * @brief Permite acesso as zonas atravessadas pelo transporte escolar
	 *
	 * @return vector das zonas atravessadas pelo transporte escolar
	*/
	vector<unsigned int> getZonas() const;
	/**
	 * @brief Adiciona zona ao vetor de zonas atravessadas pelo transporte escolar
	 *
	 * @param zona Zona a ser adicionada
	 *
	 * Se a zona ja existir lanca uma excecao do tipo ZonaJaExistente
	*/
	void adicionarZona(unsigned int zona);
	/**
	 * @brief Remove a zona do vetor de zonas atravessadas pelo transporte escolar
	 *
	 * @param zona Zona a ser removida
	 *
	 * Se a zona nao existir lanca uma excecao do tipo ZonaNaoExistente
	*/
	void removerZona(unsigned int zona);
	/**
	 * @brief Verifica se o transporte escolar passa pela zona indicada
	 *
	 * @param zona Zona na qual se pretende verificar a passagem
	 *
	 * @return true se a zona existe no vetor de zonas atravessadas, false caso contrario
	*/
	bool existeZona(unsigned int zona);
	/**
	 * @brief Calcula o gasto de combustivel do transporte escolar ao fim de um dia.
	 * Tendo em conta que realiza duas viagens por dia e o numero de zonas atravessadas,
	 * o calculo é 2 * numero de zonas atravessadas * kms por zona * consumo por 100km /100.
	 *
	 * @param kms Media dos kms percorridos por zona atravessada
	 *
	 * @return Gasto diario
	*/
	float calcGasto(float kms) const;
	/**
	 * @brief Verifica se o transporte escolar esta cheio
	 *
	 * @return true se ja nao houver lugares vazios, false caso contrario
	*/
	bool cheio() const;
	/**
	 * @brief Aumenta o numero de lugares vazios em 1
	*/
	void aumentaLug();
	/**
	 * @brief Reduz o numero de lugares vazios em 1
	*/
	void reduzLug();
	/**
	 * @brief Organiza a informacao do transporte escolar para ser guardada em ficheiro
	 *
	 * @return string com toda a informacao do transporte escolar (atributos separados por tabs)
	*/
	string getInfo() const;
	friend ostream& operator <<(ostream& out, const Escolar& veic);
};

/**
 * @class Recreativo
 *
 * @ingroup Veiculo
 *
 * @brief Classe para instanciar transportes de atividades recreativas
 *
 * Veiculos especiais que se podem alugar por um dia.
 * O preco do aluguer depende da capacidade do transporte recreativo (atributo constante).
 * Caso ele tenha sido alugado para o dia, e tambem importante calcular o gasto correspondente.
 */
class Recreativo: public Veiculo {
private:
	const unsigned int capacidade; ///< Capacidade do transporte recreativo (Nota: nao pode ser alterada depois de inicializada)
	bool alugado; ///< Estado de aluguer do transporte recreativo: alugado->true; livre->false
public:
	/**
	 * @brief Construtor da classe Recreativo
	 *
	 * @param matricula	Matricula do trasnporte recreativo
	 * @param consumo100km	Consumo em Litros por cada 100 kms
	 * @param precoComb	Preco do combustivel usado no trasnporte recreativo
	 * @param cap Capacidade do trasnporte recreativo
	 * @param alugado Estado de aluguer do transporte recreativo (true->alugado, false->livre). Por omissao e false.
	*/
	Recreativo(const string &matricula, float consumo100km, float precoComb, unsigned int cap, bool alugado);
	/**
	 * @brief Permite acesso a capacidade do transporte recreativo
	 *
	 * @return capacidade do transporte recreativo
	*/
	unsigned int getCapacidade() const;
	/**
	 * @brief Permite acesso ao estado de aluguer do transporte recreativo
	 *
	 * @return true se o transporte recreativo estiver alugado, false caso contrario
	*/
	bool getEstado() const;
	/**
	 * @brief Altera o estado de aluguer do veiculo recreativo
	 *
	 * @param alugado Estado de aluguer do veiculo (true->alugado, false->livre)
	*/
	void setEstado(bool alugado);
	/**
	 * @brief Calcula o gasto de combustivel do transporte recreativo ao fim de uma viagem.
	 * O gasto depende dos kms percorridos na viagem e do consumo por 100km do veiculo.
	 *
	 * @param kms Kms percorridos durante a viagem
	 *
	 * @return Gasto na viagem
	*/
	float calcGasto(float kms) const;
	/**
	 * @brief Organiza a informacao do transporte recreativo para ser guardada em ficheiro
	 *
	 * @return string com toda a informacao do transporte recreativo (atributos separados por tabs)
	*/
	string getInfo() const;
	friend ostream& operator <<(ostream& out, const Recreativo& veic);
};
