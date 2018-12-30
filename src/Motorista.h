/*
 * Motorista.h
 *
 *  Created on: 28/12/2018
 *      Author: pc
 */

#ifndef SRC_MOTORISTA_H_
#define SRC_MOTORISTA_H_

#include <string>
#include <list>
#include <iostream>
#include "Veiculo.h"

using namespace std;
/*A empresa mantém um registo de todos os seus motoristas (trabalhadores atuais ou angos da empresa)
numa tabela de dispersão. A manutenção do registo de motoristas antigos da empresa jusfica-se porque,
no caso de necessidade de contratação de um motorista, a empresa tem como preferência a contratação de
trabalhadores já conhecidos. O motorista deve estar associado aos transportes que realiza (se é um
trabalhador atual da empresa).
 * */
//assumir que todos os veiculos teem motorista
//ver se ha motoristas disponiveis para tal veiculo(ou seja que nao tenham esse veiculo) se nao contrata um novo
class Motorista
{

private:
	bool atual;
	string nome;
	list <pair <string,unsigned>>  veiculos;

public:
	/**
	* @brief Construtor da classe Motorista
	*
	* @param nome	Nome do Motorista
	* @param atual	Se o motorista esta empregado ou nao
	* @param veiculos	Veiculos/transportes associados ao condutor
	*/
	Motorista(string nome,bool atual);
	Motorista(string nome,bool atual,list <pair <string,unsigned>> veiculos);
	/**
	* @brief Permite acesso ao nome do Motorista
	*
	* @return nome do Motorista
	*/
	string getNome();
	/**
	* @brief Permite saber se o motorista esta contratado ou nao
	*
	* @return true -> se esta contratado
	* @return false -> se nao estiver contratado
	*/
	bool getAtual();
	/**
	* @brief Permite aceder aos veiculos/transportes associados ao condutor
	*
	* @return lista de veiculos associados ao motorista
	*/
	list <pair <string,unsigned>> getVeiculos();
	/**
	* @brief Permite inserir novos veiculos/transportes associando-os ao condutor
	*
	* @return se esta contratado ou nao
	*/
	void inserirVeiculo(string matricula , unsigned id);
	/**
	* @brief Permite inserir novos veiculos/transportes associando-os ao condutor
	*
	* @return se esta contratado ou nao
	*/
	void inserirVeiculos(list <pair<string , unsigned>> v);
	/**
	* @brief Permite modificar o estado do contracto
	*
	* @return void
	*/
	void setAtual(bool atual);
	/**
	 * @brief Permite remover veiculos/transportes associados ao condutor atravez do id do veiculo
	*
	* @return void
	*/
	void removerVeiculo(unsigned id);
	/**
	 * @brief Permite remover veiculos/transportes associados ao condutor atravez da matricula do veiculo
	 *
	 * @return void
	 */
	void removerVeiculo(string matricula);
	/**
	 * @brief Permite despedir um funcionaro, mudando o atual e eliminando os elementos da lista
	 *
	 * @return se esta contratado ou nao
	 */
	void despedir();
	/**
	 * @brief Permite contratar um funcionario ja existente, mudando o atual para true
	 *
	 * @return void
	 */
	void contratar(string matricula,unsigned id);

};



#endif /* SRC_MOTORISTA_H_ */
