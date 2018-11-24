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

void validar_data(string &data_nasc)
{
	bool invalidOp = true;

	while(cin.fail() || invalidOp)
	{
		invalidOp = false;

		if(data_nasc.size() == 8)
			{
				for(size_t i = 0; i < data_nasc.size(); i++)
				{
					if((i + 1) % 3 && i < 6) //verificar se é '-'
						{
							if(data_nasc[i] != '-')
								{
									invalidOp = true;
									break;//sai do ciclo for
								}

						}
					else if(!isdigit(data_nasc[i]))
						{
							invalidOp = true;
							break;//sai do ciclo for
						}
				}
			}
		if(invalidOp)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << endl << " Inseriu uma data com o formato errado. Por favor insira uma data com este formato: DD-MM-AAAA" << endl;
			cin >> data_nasc;
		}
	}
}
