#include "Utente.h"
#include "Exceptions.h"

/**
 * @class Escola
 *
 * @ingroup Escola
 *
 * @brief Classe para instanciar escolas
 *
 * Esta classe agrupa todas as caracteristicas de uma escola.
 * Pertmite definir as escolas frequentadas pelos utentes da empresa de transportes,
 * operando sobre elas:
 * obter a zona onde se encontra,
 * obter e modificar o nome e morado do diretor
 * obter o codigo que a define,
 * obter e modificar o vetor de utentes (adicionar, remover e alterar)
 */

class Escola
{
private:
	vector<Utente*> utentes; ///< Vetor de apontadores para utentes que frequentam a escola e se encontram assinados ao serviço de transportes
	string nome; ///< Nome da escola
	unsigned codigo; ///< Codigo da escola
	string nome_diretor; ///< Nome do diretor da escola
	string morada_diretor; ///< Morada do diretor da escola
	unsigned zona; ///< Zona da escola
public:
	/**
	 * @brief Construtor da classe Escola
	 *
	 * @param nome	Nome da Escola
	 * @param codigo	Codigo da Escola
	 * @param nome_d	Nome do diretor
	 * @param morada_d	Morada do diretor
	 * @param zonaEsc	Zona da escola
	 */
	Escola(string nome, unsigned codigo, string nome_d, string morada_d, unsigned zona);
	/**
	 * @brief Devolve o nome da escola
	 *
	 * @return string A informação é devolvida numa string
	 */
	string getNome() const;
	/**
	 * @brief Devolve os utentes que frequentam a escola
	 *
	 * @return vector<Utente*> A informação é devolvida num vetor de apontador de utentes
	 */
	vector<Utente*> getUtentes() const;
	/**
	 * @brief Devolve a zona da escola
	 *
	 * @return unsigned A informação é devolvida num unsigned
	 */
	unsigned getZona() const;
	/**
	 * @brief Devolve o codigo da escola
	 *
	 * @return unsigned A informação é devolvida num unsigned
	 */
	unsigned getCodigo() const;
	/**
	 * @brief Devolve o nome e morada do diretor
	 *
	 * @return string A informação é devolvida num par de strings (primeiro o nome e segundo a morada)
	 */
	pair<string,string> getDiretorInfo() const;
	/**
	 * @brief Altera as informações do diretor da escola
	 *
	 * @param nome Nome do diretor
	 * @param morada Morada do diretor
	 */
	void set_diretor(const string &nome, const string &morada);
	/**
	 * @brief Adiciona um utente ao vetor de utentes
	 *
	 * @param ut Apontador para o Utente a ser adicionado
	 */
	void addUtente(Utente *ut);
	/**
	 * @brief Remove um utente ao vetor de utentes
	 *
	 * @param ut Apontador para o Utente a ser removido
	 */
	void removeUtente(Utente *ut);
	/**
	 * @brief Compara duas escolas, assinalando qual é a menor
	 *
	 * @return bool A funçao retorna 1 se a primeira escola for menor que a segunda, e 0 caso contrario
	 */
	bool operator<(const Escola &esc) const;
	friend ostream& operator <<(ostream& out,const Escola &esc);
};
