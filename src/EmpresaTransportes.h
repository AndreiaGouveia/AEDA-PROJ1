#include "Veiculo.h"
#include "Escola.h"
#include "Oficina.h"
#include "Motorista.h"
#include "BST.h"
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <string>
#include <utility>

struct motoristaHash
{
	int operator() (const  Motorista & mt) const
	{
		return mt.getNome().length() + mt.getVeiculos().size(); //tamanho do nome e nr de veiculos que tem

	}

	bool operator()(const Motorista &mt1 ,const  Motorista &mt2)const
	{
		return mt1.getNome()==mt2.getNome(); //se tiverem nomes iguais
	}
};

typedef unordered_set<Motorista, motoristaHash, motoristaHash> tabHMotorista;

/**
 * @class Empresa
 *
 * @brief Classe que representa uma empresa de transportes
 *
 * A classe reune algumas informacoes importantes sobre a empresa, tais como
 * o seu nome, a frota de veiculos, a lista de utentes e os lucros obtidos.
 * Permite gerir o que acontece na empresa atraves de variadissimos metodos que fornecem
 * as abstracoes necessarias para proporcionar uma gestao intuitiva e simples.
 * Todas as informacoes da empresa podem ser guardadas em ficeiro de texo para mais tarde
 * serem carregadas e alteradas como necessario.
 */
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
	priority_queue<Oficina> oficinas; ///< Fila de oficinas ordenada pelo menor tempo de espera
	tabHMotorista motoristas; ///< Tabela de dispersao que contem os motoristas da empresa
	BST<Escola> escolas; ///< Árvore Binária ordenada pelo numero de alunos e funcionarios de cada escola que utilizam esta rede de transportes

public:
	/**
	 * @brief Construtor simples da classe Empresa
	 * Usado para criar uma Empresa de raiz
	 *
	 * @param nome Nome da empresa
	 */
	Empresa(string nome);
	/**
	 * @brief Construtor a partir de ficheiro da classe Empresa
	 * Usado para carregar uma Empresa previamente gravado num ficheiro
	 *
	 * @param f Ficheiro de texto em que se encontra um empresa guardada
	*/
	Empresa(ifstream &f);
	/**
	 * @brief Construtor completo da classe Empresa
	 *
	 * @param nome	Nome da empresa
	 * @param vUt	Vetor de utentes da empresa
	 * @param vVeic	Vetor de veiculos da empresa
	 * @param precoPessoa Valor do preco do aluguer por pessoa
	 * @param fprecos Ficheiro contendo a matrix de precos dos passes a ser carregada
	*/
	Empresa(string nome, vector <Utente *> vUt, vector <Veiculo *> vVeic, unsigned int precoPessoa, ifstream &fprecos);
	/**
	 * @brief Permite acesso ao nome da empresa
	 *
	 * @return String com o nome da empresa
	*/
	string getNome() const {return nome_empresa;}
	/**
	 * @brief Permite acesso a listagem de veiculos da empresa
	 *
	 * @return Vector de apontadores para os veiculos da empresa
	*/
	vector<Veiculo*> getVeiculos() const;
	/**
	 * @brief Permite acesso a listagem de utentes da empresa
	 *
	 * @return Vector de apontadores para os utentes da empresa
	*/
	vector<Utente*> getUtentes() const;
	/**
	 * @brief Permite acesso ao preco de aluguer por pessoa definido pela empresa
	 *
	 * @return Preco por pessoa
	*/
	unsigned int getPrecoPessoa() const;
	/**
	 * @brief Permite acesso a matrix de precos de passes por zona usada na empresa
	 *
	 * @return Matrix(vector<vector<double>> de precos
	*/
	vector<vector<double>> getPrecos() const;
	/**
	 * @brief Altera a listagem de utentes da empresa para uma nova
	 *
	 * @param vUt Nova listagem (vector) a ser usada
	 */
	void setUtentes(vector <Utente *> vUt);
	/**
	 * @brief Altera a listagem de veiculos da empresa para uma nova
	 *
	 * @param vVeic Nova listagem (vector) a ser usada
	*/
	void setVeiculos(vector <Veiculo *> vVeic);
	/**
	 * @brief Altera o preco de aluguer por pessoa
	 *
	 * @param precoP Novo preco por pessoa
	*/
	void setPrecoPessoa(unsigned int precoP);
	/**
	 * @brief Carrega de um ficheiro a matriz de precos dos passes
	 *
	 * @param fprecos Ficheiro de texto contendo a matrix dos precos
	*/
	void setPrecos(istream &fprecos);
	/**
	 * @brief Altera a matriz de precos empresa para uma nova
	 *
	 * @param vet Nova matriz (vector<vector<double>>) a ser usada
	*/
	void setPrecos(const vector<vector<double>> &vet);
	/**
	 * @brief Adiciona um Veiculo a listagem ja existente na empresa
	 *
	 * @param vc Veiculo a ser adicionado
	 *
	 * Se o veiculo ja existir lanca uma excecao do tipo VeiculoJaExiste
	*/
	void adicionarVeiculo(Veiculo *vc);
	/**
	 * @brief Adiciona um Utente a listagem ja existente na empresa
	 *
	 * @param ut Utente a ser adicionado
	 *
	 * Se o utente ja existir lanca uma excecao do tipo UtenteJaExiste
	*/
	void adicionarUtente(Utente *ut);
	/**
	 * @brief Remove o Veiculo especificado da listagem ja existente na empresa
	 *
	 * @param id Numero de identificacao do veiculo a remover
	 *
	 * Se o veiculo nao existir lanca uma excecao do tipo VeiculoNaoExistente
	*/
	void removerVeiculo(unsigned int id);
	/**
	 * @brief Remove o Veiculo especificado da listagem ja existente na empresa
	 *
	 * @param matricula Numero de identificacao do veiculo a remover
	 *
	 * Se o veiculo nao existir lanca uma excecao do tipo VeiculoNaoExistente
	*/
	void removerVeiculo(string matricula);
	/**
	 * @brief Remove o Utente especificado da listagem ja existente na empresa
	 *
	 * @param numUt NNumero de identificacao do utente
	 *
	 * Se o utente nao existir lanca uma excecao do tipo UtenteNaoExistente
	*/
	void removerUtente(unsigned int numUt);
	/**
	 * @brief Remove o Utente especificado da listagem ja existente na empresa
	 *
	 * @param BI BI do utente a remover
	 *
	 * Se o utente nao existir lanca uma excecao do tipo UtenteNaoExistente
	*/
	void removerUtente(string BI);
	/**
	 * @brief Adiciona ao transporte escolar especificaddo uma zona
	 *
	 * @param idV Numero de identificacao do veiculo a alterar
	 * @param zona Zona a ser adicionada
	 *
	 * Se o veiculo for um transporte recreativo lanca uma excecao do tipo VeiculoNaoEscolar
	 * Se o veiculo nao existir lanca uma excecao do tipo VeiculoNaoExistente
	*/
	void adicionarZonaEscolar(unsigned int idV, unsigned int zona);
	/**
	 * @brief Remove do transporte escolar especificaddo uma zona
	 *
	 * @param idV Numero de identificacao do veiculo a alterar
	 * @param zona Zona a ser removida
	 *
	 * Se o veiculo for um transporte recreativo lanca uma excecao do tipo VeiculoNaoEscolar
	 * Se o veiculo nao existir lanca uma excecao do tipo VeiculoNaoExistente
	 * Se a zona ja existir lanca uma excecao do tipo ZonaJaExistente
	*/
	void removerZonaEscolar(unsigned int idV, unsigned int zona);
	/**
	 * @brief Modifica a zona de habitacao do utente especificado
	 *
	 * @param numUtente Numero de identificacao do utente a alterar
	 * @param zona Nova zona de habitacao
	 *
	 * Se o utente nao existir lanca uma excecao do tipo UtenteNaoExistente
	 * Se a zona nao existir lanca uma excecao do tipo ZonaNaoExistente
	*/
	void alterarZonaHab(unsigned int numUtente, unsigned int zona);
	/**
	 * @brief Modifica a zona da escola do utente especificado
	 *
	 * @param numUtente Numero de identificacao do utente a alterar
	 * @param zona Nova zona da escola
	 *
	 * Se o utente nao existir lanca uma excecao do tipo UtenteNaoExistente
	*/
	void alterarZonaEsc(unsigned int numUtente, unsigned int zona);
	/**
	 * @brief Substitui o contacto do utente especificado
	 * Caso o utente seja um funcinario substitui o seu contacto,
	 * caso seja crianca substitui o contacto do Encarregado de Educacao
	 *
	 * @param numUtente Numero de identificacao do utente a alterar
	 * @param cont Novo contacto
	 *
	 * Se o utente nao existir lanca uma excecao do tipo UtenteNaoExistente
	*/
	void alterarContacto(unsigned int numUtente, unsigned int cont);
	/**
	 * @brief Devolve o contacto do utente especificado
	 * Caso o utente seja um funcinario devolve o seu contacto,
	 * caso seja crianca devolve o contacto do Encarregado de Educacao
	 *
	 * @param numUtente Numero de identificacao do utente a alterar
	 *
	 * @return Contacto do funcinario ou contacto do EE da crianca
	 *
	 * Se o utente nao existir lanca uma excecao do tipo UtenteNaoExistente
	*/
	unsigned int getContacto(unsigned int numUtente);
	/**
	 * @brief Devolve o contacto do utente especificado
	 * Caso o utente seja um funcinario devolve o seu contacto,
	 * caso seja crianca devolve o contacto do Encarregado de Educacao
	 *
	 * @param BI BI do utente a alterar
	 *
	 * @return Contacto do funcinario ou contacto do EE da crianca
	 *
	 * Se o utente nao existir lanca uma excecao do tipo UtenteNaoExistente
	*/
	unsigned int getContacto(string BI);
	/**
	 * @brief Calcula o valor do passe mensal do utente especificado
	 * Determina quais as zonas de habitacao e de escola do utente
	 * e usa-as para aceder a matrix de precos e devolver o valor do passe.
	 *
	 * @param numUtente Numero do utente
	 *
	 * @return Valor do passe mensal
	 *
	 * Se o utente nao existir lanca uma excecao do tipo UtenteNaoExistente
	*/
	double calculoPasseMensal(unsigned int numUtente);
	/**
	 * @brief Estabelece a correspondecia entre todos os utentes e os valores dos passes mensais
	 * Recorre ao metodo calculoPasseMensal() para calcular individualmente o valor do passe para
	 * cada utente e guarda essa correspondencia na tabelaPasses.
	*/
	void atualizarPasses();
	/**
	 * @brief Atualiza todos os precos na matrix de precos por zona
	 *
	 * @param delta Variacao global dos precos (todos os precos variam da mesma forma)
	*/
	void atualizarPrecos(double delta);
	/**
	 * @brief Calcula o preco do aluguer do transporte recreativo especificado.
	 * Baseia-se no preco de aluguer por pessoa e na capcidade do veiculo para fazer o calculo.
	 *
	 * @param idV Numero de identificacao do transporte recreativo a alugar
	 *
	 * @return Preco do aluguer do veiculo por um dia
	 *
	 * Se o veiculo nao existir lanca uma excecao do tipo VeiculoNaoExistente
	 * Se o idV se referir a um transporte escolar lanca uma excecao do tipo VeiculoNaoRecreativo
	 * Se o precoPessoa ainda nao tiver sido definido (i.e. se tiver o valor -1)
	 * lanca uma excecao do tipo PrecoNaoDefinido
	*/
	double calcularAluguer(unsigned int idV);
	/**
	 * @brief Verifica quais os transportes recreativos disponiveis para alugar.
	 * Devolve informacao relativa a todos os recreativos disponiveis (Id, Capacidade, Preco).
	 *
	 * @param capacidade Capacidade do veiculo pretendida
	 *
	 * @return String contendo a informacao de quais os
	 * transportes recreativos disponiveis bem como o custo do seu aluguer,
	 *
	 * Lanca as mesmas excecoes que o metodo calcularAluguer()
	*/
	string verificaDispRecreativo(unsigned int capacidade);
	/**
	 * @brief Aluga o trasnporte recreativo especificado por um dia
	 *
	 * @param idV Numero de identificacao do veiculo
	 *
	 * Se o veiculo for um transporte escolar lanca uma excecao do tipo VeiculoNaoRecreativo
	 * Se o veiculo nao existir lanca uma excecao do tipo VeiculoNaoExistente
	*/
	void alugaRecreativo(unsigned int idV);
	/**
	 * @brief Processa a alocacao de passageiros para os transportes escolares.
	 * A cada utente faz corresponder o veiculo (sempre um transporte escolar) que tem de usar.
	 * Nao o faz com nenhum criterio especifico, apenas vai por ordem crescente de numero de
	 * identificacao de utente e de veiculo
	 * O resultado da alocacao e uma tabela de corresnpondencias entre Utentes e Veiculos, i.e. a tabelaPassageiros
	 * Se nao existirem veiculos suficientes para todos os utentes lanca uma excecao do tipo VeiculosInsuficientes
	*/
	void alocaUtentes();
	/**
	 * @brief Aloca apenas o utente especificado a um transporte escolar
	 * O resultado da alocacao e guardado na tabelaPassageiros
	 *
	 * @param numUt Numero de identificacao do utente
	 *
	 * @return numero de identificacao do veiculo ao qual o utente foi atribuido
	 *
	 * Se nao existirem veiculos suficientes para todos os utentes lanca uma excecao do tipo VeiculosInsuficientes
	 * Se o utente nao existir lanca uma excecao do tipo UtenteNaoExistente
	*/
	unsigned int alocaUt(unsigned int numUt);
	/**
	 * @brief Processa o final de um dia na empresa
	 * Calcula todos os gastos de todos os veiculos, bem como os ganhos com o aluguer de recreativos
	 * e guarda a informacao sobre o balanco do dia no vetor registoDiario. Para alem disso, todos os
	 * trasnportes recreativos alugados passam a estar livres para o dia seguinte, dando assim inicio a um novo dia.
	 *
	 * @param kmsZona Media de kms percorridos em cada zona pelos transportes escolares
	 *
	 * @return true se foi bem sucedido a guardar os valores no registoDiario,
	 * false caso o registoDiario esteja cheio (com 31 valores)
	*/
	bool finalDia(float kmsZona);
	/**
	 * @brief Processa o calculo do lucro mensal na empresa
	 * Tendo em conta os balancos diarios e os valores dos passes mensais,
	 * calcula o lucro tirado no final do mes, dando assim inicio a um novo mes.
	 * Os lucros sao guardados no vetor lucrosMensais e quando se insere o 12o valor
	 * a funcao da inicio a um novo ano civil, mostrando no ecra os valores do lucro
	 * do ano que passou e limpando o vetor lucrosMensais para o proximo ano.
	 *
	 * @return true se o vetor lucrosMensais estiver cheio (o que representa o fim do ano), false caso contrario
	*/
	bool calculoMensal();
	/**
	 * @brief Envia toda a informacao da empresa para a ostream especificada.
	 * Usando um ficheiro, a funcao guarda a informacao nesse ficheiro
	 *
	 * @param f Ostream para onde sera escrita a informacao
	*/
	void guardarInfo(ostream &f) const;
	/**
	 * @brief Carrega toda a informacao da empresa a partir de um ficheiro de texto.
	 *
	 * @param f Ficheiro de texto onde sera guardada a informacao
	*/
	void carregarInfo(ifstream &f);
	/**
	 * @brief Devolve a informacao dos utentes da empresa
	 *
	 * @return String contendo a informacao organizada e legivel
	*/
	string showUtentes() const;
	/**
	 * @brief Devolve informacao dos veiculos da empresa
	 *
	 * @return String contendo a informacao organizada e legivel
	*/
	string showVeiculos() const;
	/**
	 * @brief Devolve a informacao da tabela dos valores dos passes da empresa
	 *
	 * @return String contendo a informacao organizada e legivel
	*/
	string showTabPasses() const;
	/**
	 * @brief Devolve a informacao da tabela de alocacao dos passageiros da empresa
	 *
	 * @return String contendo a informacao organizada e legivel
	*/
	string showTabPassag() const;
	/**
	 * @brief Devolve a informacao dos lucros mensais da empresa
	 *
	 * @return String contendo a informacao organizada e legivel
	*/
	string showMensal() const;
	/**
	 * @brief Devolve a informacao dos balancos diarios da empresa
	 *
	 * @return String contendo a informacao organizada e legivel
	*/
	string showDiario() const;
	/**
	 * @brief Devolve a informacao dos precos por zona da empresa
	 *
	 * @return String contendo a informacao organizada e legivel
	*/
	string showPrecos() const;
//==========================================================================
	/**
	 * @brief Verifica se a oficina especificada existe na fila de oficinas
	 *
	 * @return true -> existe
	 * @return false -> nao existe
	*/
	bool checkOficina(const Oficina& ofc);
	/**
	 * @brief Insere uma oficina na fila de oficinas
	 *
	 * @return true -> a oficina foi inserida com sucesso
	 * @return false -> a oficina ja existia e nao foi inserida
	*/
	bool insertOficina(const Oficina& ofc);
	/**
	 * @brief Remove uma oficina na fila de oficinas
	 *
	 * @return true -> a oficina foi removida com sucesso
	 * @return false -> a oficina nao existe
	*/
	bool removeOficina(const Oficina& ofc);
	/**
	 * @brief Escolhe qual a oficina em que o veiculo especificado deve fazer as reparacoes.
	 * A excolha depende da distancia maxima a garagem passada como argumento e da disponibilidade das oficinas.
	 *
	 * @param id Identificacao do veiculo a reparar
	 * @param dist_max Distancia maxima entre a oficina e a garagem pretendida
	 *
	 * @return Oficina escolhida para a reparacao
	*/
	Oficina repararVeiculo(unsigned int id, double dist_max);
	friend ostream& operator <<(ostream& out,const Empresa &emp);
//==========================================================================
	/**
	 * @brief Contata um novo motorista colocando-o na lista de dispersao, o atual assume se como true, pois e um novo motorista
	 *
	 * @param nome Nome do motorista a contratar
	 * @param veiculo Veiculo associado ao motorista
	 *
	 * @return true -> foi inserido na tabela com sucesso
	 * @return false -> nao foi inserido na tabela com sucesso
	*/
	bool contratarNovoMotorista(string nome,list<pair<string , unsigned >> veiculos);
	/**
	* @brief Coloca um motorista antigo na tabela de dispers�o, assume se que o valor do atual seja false
	*
	* @param nome Nome do motorista
	*
	* @return true -> foi inserido na tabela com sucesso
	* @return false -> nao foi inserido na tabela com sucesso
	*/
	bool inserirAntigoMotorista(string nome);
	/**
	* @brief Insere um novo veiculo num motorista ja existente
	*
	* @param nome Nome do motorista
	* @param veiculo Veiculo a inserir
	*
	* @return true -> o veiculo foi inserido com sucesso
	* @return false -> o veiculo ja pertencia ao motorista
	*/
	bool inserirVeiculo(string nome, string matricula, unsigned id);
	/**
	* @brief Insere uma lista de veiculos num motorista ja existente
	*
	* @param nome Nome do motorista
	* @param veiculos Lista de veiculos a inserir
	*
	* @return true -> os veiculos foram inseridos com sucesso
	* @return false -> os veiculos nao foram inseridos com sucesso
	*/
	bool inserirVeiculos(string nome, list<pair<string , unsigned>> veiculos);
	/**
	* @brief Insere um novo veiculo num motorista ja existente atravez da matricula e id do veiculo
	*
	* @param nome Nome do motorista
	* @param veiculo Veiculo a inserir
	*
	* @return true -> o veiculo foi inserido com sucesso
	* @return false -> o veiculo nao foi removido com sucesso
	*/
	bool removerVeiculo(string nome, string matricula,unsigned id);
	/**
	* @brief Remove um motorista da tabela de motoristas
	*
	* @param nome Nome do motorista a remover
	*
	* @return true -> Se o motorista foi removido com sucesso
	* @return false -> Se o motorista nao foi removido com sucesso
	*/
	bool removerMotorista(string nome);
	/**
	* @brief Apresenta na consola todos os motoristas e o seu estado de contratacao
	*
	* @return true -> se existir motoristas na tabela
	* @return false -> se nao existir motoristas na tabela
	*/
	bool mostrar_nome_motoristas();
	/**
	* @brief Vai adicionar um veiculo no primeiro motorista disponivel
	*
	* @return true -> se incluiu o veiculo num motorista ja existente na tabela
	* @return false -> se sera necessario contratar um novo motorista
	*/
	bool averiguar_motoristas(string matricula, unsigned id);

//==========================================================================
	pair<bool, Escola> verificaEscola(unsigned codigo);
	void adicionaEscola(Escola &esc);
	vector<Utente*> removeEscola(Escola &esc);
	pair<bool, Escola> encontraEscolaUtente(Utente &ut);
	bool InsereUtenteEscola(unsigned codigo, Utente *ut);
	bool RemoveUtenteEscola(Utente *ut);
	string getEscolasZona(unsigned zona);
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
