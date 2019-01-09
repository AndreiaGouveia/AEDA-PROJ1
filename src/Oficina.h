#ifndef SRC_OFICINA_H_
#define SRC_OFICINA_H_

#include <iostream>
#include <string>
#include <queue>

using namespace std;

/**
 * @class Oficina
 *
 * @brief Classe para instanciar oficinas
 *
 * Esta classe permite criar e trabalhar com oficinas.
 * As oficinas sao caracterizadas pelo seu nome, disponibilidade e distancia a garagem da Empresa.
 * A disponibilidade e o numero de dias que faltam ate a oficina estar livre.
 * Sempre que um veiculo e enviado para reparacoes ele ficara 1 dia na oficina.
 */
class Oficina
{
	string nome; ///< Nome da oficina
	int disponibilidade; ///< Disponibilidade da oficina (numero de dias que faltam ate a oficina estar livre)
	double distancia; ///< Distancia da oficina a garagem da Empresa (em kms)
	queue<unsigned int> filaEspera; ///< Fila de espera onde são inseridos os veículos
public:
	/**
	 * @brief Construtor da classe Oficina
	 *
	 * @param nom	Nome da oficina
	 * @param dist	Distancia a garagem (por omissao e 0)
	*/
	Oficina(string nom = "", double dist = 0);
	/**
	 * @brief Retorna o nome da oficina
	 *
	 * @return Nome da oficina
	*/
	string getNome() const;
	/**
	 * @brief Retorna a disponibilidade da oficina
	 *
	 * @return Disponibilidade da oficina
	*/
	int getDisp() const;
	/**
	 * @brief Retorna a distancia da oficina a garagem da Empresa
	 *
	 * @return Distancia da oficina a garagem
	*/
	double getDist() const;
	/**
	 * @brief Retorna a fila de espera
	 *
	 * @return Fila com os identificadores dos veiculos em reparacao
	*/
	queue<unsigned int> getFila() const;
	/**
	 * @brief Altera a disponibilidade da oficina
	 *
	 * @param disp Nova disponibilidade da oficina
	*/
	void setDisp(int disp);
	/**
	 * @brief Altera a distancia da oficina
	 *
	 * @param dist Nova distancia da oficina
	*/
	void setDist(double dist);
	/**
	 * @brief Efetua a reparacao do veiculo. Esse veículo é adicionado à fila de espera.
	 * A disponibilidade da oficina aumenta em 1 dia
	 * (a reparacao de um veiculo demora sempre 1 dia)
	 *
	 * @param idV Identificacao do veiculo a ser reparado
	*/
	void reparacao(unsigned int idV);
	/**
	 * @brief Processa o final de uma reparacao (acontece ao final de cada dia)
	 *
	 * @return Identificacao do veiculo que acabou de ser reparado
	*/
	unsigned int fimReparacao();
	/**
	 * @brief Compara duas oficinas e verifica se a da esquerda e maior que a da direita.
	 * Permite ordenar as oficinas numa fila de prioridade em que o elemento do topo e o que
	 * possui menor numero de dias de espera (disponibilidade)
	 *
	 * @return true -> a oficina da esquerda e maior que a da direita
	 * @return false -> a oficina da direita e maior ou igual a da esquerda
	*/
	bool operator <(const Oficina& right) const;
	/**
	 * @brief Compara duas oficinas e verifica se sao iguais.
	 * Duas oficinas sao iguais se tiverem o mesmo nome.
	 *
	 * @return true -> as oficinas sao iguais
	 * @return false -> as oficinas sao diferentes
	*/
	bool operator ==(const Oficina& right) const;
	/**
	 * @brief Envia a informacao sobre uma oficina para uma ostream
	 *
	 * @return A propria ostream
	*/
	friend ostream& operator <<(ostream& out, const Oficina& of);
};

#endif
