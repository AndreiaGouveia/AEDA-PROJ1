#ifndef SRC_INPUT_HANDLER_H_
#define SRC_INPUT_HANDLER_H_

#include <iostream>
#include <fstream>

using namespace std;


char respostaY_N(char &resposta);
char respostaNumeros(const int &min, const int &max);
bool file_handler(string &nome_ficheiro, ifstream &ficheiro);


#endif /* SRC_INPUT_HANDLER_H_ */
