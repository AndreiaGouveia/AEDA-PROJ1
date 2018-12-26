#ifndef SRC_OFICINA_H_
#define SRC_OFICINA_H_

#include <iostream>
#include <string>

using namespace std;

/**
 * @class Oficina
 *
 * @brief Classe para instanciar oficinas
 *
 * Esta classe permite criar e trabalhar com oficinas.
 * As oficinas são caracterizadas pelo seu nome, disponibilidade e distancia à garagem da Empresa.
 * A disponibilidade é o número de dias que faltam até a oficina estar livre.
 * De entre estes atributos o que se pode alterar é a disponibilidade, sendo que sempre que um veículo
 * é enviado para reparações este ficará 1 dia na oficina.
 */
class Oficina
{
	const string nome; ///< Nome da oficina (constante)
	int disponibilidade; ///< Disponibilidade da oficina (número de dias que faltam até a oficina estar livre)
	double distancia; ///< Distancia da oficina à garagem da Empresa
public:
	Oficina(string nom = "", int disp = 0, double dist = 0);
	string getNome() const;
	int getDisp() const;
	double getDist() const;
	void reparacao();
	bool operator <(const Oficina &right);
	friend ostream& operator <<(ostream& out, const Oficina &of);
};

#endif
