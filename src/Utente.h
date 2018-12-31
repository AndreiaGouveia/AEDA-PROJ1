#include <vector>
#include <string>
#include <sstream>
#include <ostream>

using namespace std;

/**
 * @class Utente
 *
 * @ingroup Utente
 *
 * @brief Classe para instanciar utentes
 *
 * Esta classe agrupa todas as caracteristicas de um utente.
 * Permite definir os clientes da empresa de transportes e
 * operar sobre alguns dos aspectos mais importantes, como por exemplo:
 * verificar quais as zonas onde o cliente habita e tem escola,
 * verificar se um cliente e utente ou funcionario,
 * encontrar o numero de telemovel do cliente para o poder contactar, etc.
 * Da classe Utente derivam a classe Crianca e a classe Funcionario.
 */
class Utente {
protected:
	unsigned cod_escola; ///< Codigo da escola frequentada pelo utente
	const string nome; ///< Nome do utente
	const string data_nascimento; ///< Data de nascimento do utente (Nota: nao e controlado o input)
	const string BI; ///< BI do utente (Nota: nao ha BI's repetidos)
	const unsigned int numUtente; ///< Numero de identificacao interna do utente
	unsigned int zonaHabitacao; ///< Zona onde o utente habita
	unsigned int zonaEscola; ///< Zona da escola do utente
public:
	static unsigned int ult_numUtente; ///< Membro estatico que guarda qual o numero de identificacao do ultimo utente registado
	/**
	 * @brief Construtor da classe Utente
	 *
	 * @param nome	Nome do utente
	 * @param data_nasc	Data de nascimento
	 * @param BI	BI do utente
	 * @param zonaHabit Zona de habitacao do utente
	 * @param zonaEsc	Zona da escola do utente
	 */
	Utente(const string &nome, const string &data_nasc, const string &BI,const unsigned int &zonaHabit, const unsigned int &zonaEsc);
	virtual ~Utente() {}
	/**
	 * @brief Permite acesso ao codigo da escola frequentada pelo utente
	 *
	 * @return codigo da escola
	 */
	unsigned getCodEscola();
	/**
	 * @brief Permite acesso ao nome do utente
	 *
	 * @return nome do utente
	*/
	string getNome() const;
	/**
	 * @brief Permite acesso a data de nascimento do utente
	 *
	 * @return data de nascimento do utente
	*/
	string getData_Nasc() const;
	/**
	 * @brief Permite acesso ao BI do utente
	 *
	 * @return BI do utente
	*/
	string getBI() const;
	/**
	 * @brief Devolve o numero de identificacao interna do utente
	 *
	 * @return Numero do utente
	*/
	unsigned int getNumUtente() const;
	/**
	 * @brief Devolve a zona onde o utente habita
	 *
	 * @return Zona de habitacao
	*/
	unsigned int getZonaHabitacao();
	/**
	 * @brief Devolve a zona da escola do utente
	 *
	 * @return Zona da Escola
	*/
	unsigned int getZonaEscola();
	/**
	 * @brief Altera a zona de habitacao do utente
	 *
	 * @param zona Nova zona de habitacao
	*/
	void setZonaHabitacao(unsigned int zona);
	/**
	 * @brief Altera a zona da escola do utente
	 *
	 * @param zona Nova zona de escola
	*/
	void setZonaEscola(unsigned int zona);
	/**
	 * @brief Altera o codigo da escola do utente
	 *
	 * @param codigo da nova escola
	*/
	void setCodEscola(unsigned codigo);
	virtual unsigned int getContacto() const = 0;
	virtual void setContacto(unsigned int cont) = 0;
	virtual string getNomeEE() const {return "";}
	virtual bool getDocente(){return false;}
	/**
	 * @brief Organiza a informacao do utente para ser guardada em ficheiro
	 *
	 * @return string com toda a informacao do utente (atributos separados por tabs)
	*/
	virtual string getInfo() const;
	friend ostream& operator<<(ostream &out, const Utente &utente);
	bool operator==(const Utente &ut);
};

/**
 * @class Funcionario
 *
 * @ingroup Utente
 *
 * @brief Classe para instanciar funcionarios
 *
 * Para alem das caracteristicas de um utente normal,
 * o funcionario pode ou nao ser docente e tem um numero de telemovel associado.
 */
class Funcionario: public Utente {
private:
	const bool docente; ///< Indica se o funcionario e docente (true) ou nao (false)
	unsigned int contacto; ///< Contacto do funcionario
public:
	/**
	 * @brief Construtor da classe Funcionario
	 *
	 * @param nome	Nome do funcionario
	 * @param data_nasc	Data de nascimento
	 * @param BI	BI do funcionario
	 * @param zonaHabit Zona de habitacao do funcionario
	 * @param zonaEsc	Zona da escola do funcionario
	 * @param docente	True se o funcionario � docente, False caso contrario
	 * @param contacto	Contacto do funcionario
	*/
	Funcionario(const string &nome, const string &data_nasc, const string &BI, const unsigned int &zonaHabit, const unsigned int &zonaEsc, const bool &docente, const unsigned int &contacto);
	/**
	 * @brief Permite acesso ao estatuto do funcionario na escola
	 *
	 * @return true se o funcionario for docente, falso caso contrario
	*/
	bool getDocente();
	/**
	 * @brief Permite acesso ao contacto do funcionario
	 *
	 * @return contacto do funcionario (unsigned int)
	*/
	unsigned int getContacto() const;
	/**
	 * @brief Altera o contacto do funcionario
	 *
	 * @param cont Novo contacto do funcionario
	*/
	void setContacto(unsigned int cont);
	/**
	 * @brief Organiza a informacao do funcionario para ser guardada em ficheiro
	 *
	 * @return string com toda a informacao do funcionario (atributos separados por tabs)
	*/
	string getInfo() const;
	friend ostream& operator<<(ostream &out, const Funcionario &utente);
};

/**
 * @class Crianca
 *
 * @ingroup Utente
 *
 * @brief Classe para instanciar criancas
 *
 * Para alem das caracteristicas de um utente normal,
 * a crianca tem associados o nome do Encarregado de Educacao e o contacto deste.
 */
class Crianca: public Utente {
private:
	const string nomeEE; ///< Nome do encarregado de educacao da crianca
	unsigned int contactoEE; ///< Contacto do encarregado de educacao da crianca
public:
	/**
	 * @brief Construtor da classe Crianca
	 *
	 * @param nome	Nome da crianca
	 * @param data_nasc	Data de nascimento
	 * @param BI	BI da crianca
	 * @param zonaHabit Zona de habitacao da crianca
	 * @param zonaEsc	Zona da escola da crianca
	 * @param nomeEE	Nome do Encarregado de Educacao
	 * @param contactoEE	Contacto do Encarregado de Educacao
	*/
	Crianca(const string &nome, const string &data_nasc, const string &BI, const unsigned int &zonaHabit, const unsigned int &zonaEsc, const string & nomeEE, const unsigned int &contactoEE);
	/**
	 * @brief Permite acesso ao nome do Encarregado de Educacao da crianca
	 *
	 * @return string com o nome do encarregado de educacao
	*/
	string getNomeEE() const;
	/**
	 * @brief Permite acesso ao contacto do Encarregado de Educacao da crianca
	 *
	 * @return contacto do encarregado de educacao (unsigned int)
	*/
	unsigned int getContacto() const;
	/**
	 * @brief Altera o contacto do Encarregado de Educacao da crianca
	 *
	 * @param cont Novo contacto do Encarregado de Educacao
	*/
	void setContacto(unsigned int cont);
	/**
	 * @brief Organiza a informacao da crianca para ser guardada em ficheiro
	 *
	 * @return string com toda a informacao da crianca (atributos separados por tabs)
	*/
	string getInfo() const;
	friend ostream& operator<<(ostream &out, const Crianca &utente);
};
