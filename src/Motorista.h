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
	Motorista(string nome,bool atual);
	Motorista(string nome,bool atual,vector<Veiculo> veiculos);
	string getNome();
	bool getAtual();
	vector <Veiculo> getVeiculos();
	void inserirVeiculo(Veiculo *veiculo);
	void setAtual(bool atual);
	void removerVeiculo(Veiculo *veiculo);
	void despedir();


};



#endif /* SRC_MOTORISTA_H_ */
