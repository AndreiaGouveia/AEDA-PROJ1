#include "Input_handler.h"


char respostaS_N()
{
	char resposta;

	cin >> resposta;

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
			cout << endl << " Opcao invalida, por favor, insira um numero entre " << min << " e " << max << ".  ";
		}
		else
			cout << endl << " Opcao invalida, por favor, insira um numero entre " << min << " e " << max << ".  ";
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
			cout << "O ficheiro nao existe, insira o nome do ficheiro de texto, sem extensao. (Ctrl + Z para sair)  "<<endl;
		}

	}while(true);
}

void allNumbers(string &answer, const int &n)//checks if in a string there are only numbers
{
	bool invalidAnswer;

	do
	{
		cin >>answer;

		invalidAnswer = false;

		for (size_t i = 0; i < answer.size(); i++)
		{
			if(isalpha(answer[i]))
			{
				invalidAnswer = true;
				break;
			}
		}

		if(invalidAnswer)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << endl << " Inseriu uma resposta invalida.Tem de ser composto por " << n << "digitos." << endl;
		}
		else break;
	}while(true);
}

void validar_data(string &data_nasc)
{
	bool invalidOp = true;

	while(cin.fail() || invalidOp)
	{
		cin >> data_nasc;

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
		}
	}
}

void validar_matricula(string &matricula)
{
	bool invalida;

	while(true)
	{
		cin >> matricula;

		if(matricula.size() == 8 || matricula[2] == '-' || matricula[5] == '-')
		{
			int cnt_letras = 0;

			for(size_t i = 0; i < 8; i++)
			{
				if(isalpha(matricula[i]))
				{
					cnt_letras++;
				}
			}

			if(cnt_letras == 2)
			{
				return;
			}

			invalida = true;
		}
		else invalida = true;

		if(invalida)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << endl << " Inseriu uma matricula errada. Tem de ter duas letras maiusculas e estar sobre o formato: AB-CD-FG" << endl;
		}
	}
}

