#include "Input_handler.h"


char respostaS_N()
{
	char resposta;

	do
	{
		if(resposta == 's' || resposta == 'S')
		{
			return 'S';
		}
		else if(resposta == 'n' || resposta == 'N')
		{
			return 'N';
		}
		else if (cin.eof())
		{
			return 'E';
		}
		else if(cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << endl << " Opcao invalida, por favor, volte a inserir uma opcao valida (S (sim), N (nao) ou Ctrl + Z para sair)" << endl;
			cin >> resposta;
		}
	}while(true);

	return false;
}

int respostaNumeros(const int &min, const int &max)
{
	int resposta;

	do
	{
		cin >> resposta;

		if(resposta >= min && resposta <= max)
		{
			return resposta;
		}
		else if(cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << endl << " Opcao invalida, por favor, insira um número entre " << min << " e " << max << ". (" << max << " -> sair)   ";
		}
	}while(true);
}

bool file_handler(string &nome_ficheiro, ifstream &ficheiro)
{
	do
	{
		cin >> nome_ficheiro;

		if(cin.eof())
		{
			return false;
		}

		nome_ficheiro = nome_ficheiro + ".txt";

		ficheiro.open(nome_ficheiro);

		if(ficheiro.is_open()) //verificar se o ficheiro existe
		{

			return true;
		}
		else
		{
			cout << "O nome do ficheiro nao existe, insira um ficheiro de texto, sem extensão. (Ctrl + Z para sair)  "<<endl;
		}

	}while(true);
}


