/*
 * Motorista.h
 *
 *  Created on: 28/12/2018
 *      Author: pc
 */

#ifndef SRC_MOTORISTA_H_
#define SRC_MOTORISTA_H_

#include <string>
#include <vector>
#include <iostream>
#include "Veiculo.h"

using namespace std;
/*A empresa mantém um registo de todos os seus motoristas (trabalhadores atuais ou angos da empresa)
numa tabela de dispersão. A manutenção do registo de motoristas antigos da empresa jusfica-se porque,
no caso de necessidade de contratação de um motorista, a empresa tem como preferência a contratação de
trabalhadores já conhecidos. O motorista deve estar associado aos transportes que realiza (se é um
trabalhador atual da empresa).
 * */

class Motorista
{

private:
	bool atual;
	string nome;
	vector <Veiculo> veiculos;

public:
	/**
		 * @brief Construtor da classe Motorista
		 *
		 * @param nome	Nome do Motorista
		 * @param atual	Se o motorista esta empregado ou nao
		 * @param veiculos	Veiculos/transportes associados ao condutor
	*/
	Motorista(string nome,bool atual);
	Motorista(string nome,bool atual,vector<Veiculo> veiculos);
	/**
		 * @brief Permite acesso ao nome do Motorista
		 *
		 * @return nome do Motorista
		*/
	string getNome();
	/**
			 * @brief Permite saber se o motorista esta contratado ou nao
			 *
			 * @return se esta contratado ou nao
			*/
	bool getAtual();
	/**
				 * @brief Permite aceder aos veiculos/transportes associados ao condutor
				 *
				 * @return se esta contratado ou nao
				*/
	vector <Veiculo> getVeiculos();
	/**
					 * @brief Permite inserir novos veiculos/transportes associados ao condutor
					 *
					 * @return se esta contratado ou nao
					*/
	void inserirVeiculo(Veiculo *veiculo);
	/**
						 * @brief Permite modificar o estado do contracto
						 *
						 * @return void
						*/
	void setAtual(bool atual);
	/**
						 * @brief Permite remover veiculos/transportes associados ao condutor
						 *
						 * @return se esta contratado ou nao
						*/
	void removerVeiculo(Veiculo *veiculo);
	/**
						 * @brief Permite despedir um funcionaro, mudando o atual e dando clear ao vetor
						 *
						 * @return se esta contratado ou nao
						*/
	void despedir();
	/**
						 * @brief Permite contratar um funcionario ja existente, mudando o atual para true
						 *
						 * @return void
						*/
	void contratar();
	/**
						 * @brief ermite contratar um funcionario ja existente, mudando o atual para true e inserindo um veiculo
						 *
						 * @return void
						*/
	void contratar(Veiculo *veiculo);


};



#endif /* SRC_MOTORISTA_H_ */
