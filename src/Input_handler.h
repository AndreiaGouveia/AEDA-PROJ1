#ifndef SRC_INPUT_HANDLER_H_
#define SRC_INPUT_HANDLER_H_

#include <iostream>
#include <fstream>

using namespace std;


char respostaS_N();
int respostaNumeros(const int &min, const int &max);
bool file_handler(string &nome_ficheiro, ifstream &ficheiro);
void allNumbers(string &answer, const int &n);
void validar_data(string &data_nasc);
void validar_matricula(string &matricula);

template <class T>
void checkCinFail(T &answer)
{
	cin >> answer;

	while(cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl << " Inseriu uma resposta invalida." << endl;
		cin >> answer;
	}
}


#endif /* SRC_INPUT_HANDLER_H_ */
