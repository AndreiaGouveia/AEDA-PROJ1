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
 * As oficinas s�o caracterizadas pelo seu nome, disponibilidade e distancia � garagem da Empresa.
 * A disponibilidade � o n�mero de dias que faltam at� a oficina estar livre.
 * De entre estes atributos o que se pode alterar � a disponibilidade, sendo que sempre que um ve�culo
 * � enviado para repara��es este ficar� 1 dia na oficina.
 */
class Oficina
{
	const string nome; ///< Nome da oficina (constante)
	int disponibilidade; ///< Disponibilidade da oficina (n�mero de dias que faltam at� a oficina estar livre)
	double distancia; ///< Distancia da oficina � garagem da Empresa
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
