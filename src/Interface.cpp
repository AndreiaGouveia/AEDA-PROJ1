#include "EmpresaTransportes.h"
#include "Input_handler.h"
#include <iomanip>



void trabalhar_empresa(const Empresa &empresa)
{
	cout << "--------------------------------"
		 << "Que area pretende alterar?   ";
}

void criar_empresa()
{
	string nome_empresa;

	cout << "Como se chama a empresa?  ";
	cin >> nome_empresa;

	if(cin.eof())
	{
		return;
	}

	Empresa empresa(nome_empresa);

	int zonas;
	double preco;
	vector < vector < double > > precos_zona;

	cout << "Quantas zonas?  ";
	cin >> zonas;

	checkingOnlyCinFail(zonas);

	for(int i = 0; i < zonas; i++)
	{
		for(int j = 0; j <= i; j++)
		{
			cout<<"Qual o preco entre a zona "<< i + 1<<" e "<< j + 1 <<"?  ";
			cin >> preco;

			checkingOnlyCinFail(preco);

			precos_zona[i][j] = preco;
		}
	}

	empresa.setPrecos(precos_zona);//Agora a empresa tem os precos

	trabalhar_empresa(empresa);
}

void continuar_empresa()
{
	ifstream ficheiro;
	string nome_ficheiro;

	cout << endl << "Qual o nome do ficheiro que quer abrir (não coloque extensao .txt)? (Ctrl + Z para sair)  " << endl;

	if(file_handler(nome_ficheiro, ficheiro))
	{
		Empresa empresa(ficheiro);

		trabalhar_empresa(empresa);
	}
	else return;
}

void primeiras_opcoes()
{
	cout << "==============================" << endl
		 << "=== Empresa de Transportes ===" << endl
		 << "==============================" << endl << endl;

	cout << "Que deseja fazer?" << endl
		 << "1. Criar uma nova empresa" << endl
		 << "2. Aceder a uma empresa ja existente" << endl
		 << "3. Sair" << endl;

	int resposta;
	bool end = false;

	while(!end)
	{
		resposta = respostaNumeros(1, 3);

		switch(resposta)
		{
		case 1:
			criar_empresa();
			break;
		case 2:
			continuar_empresa();
			break;
		case 3:
			end = true;
			break;
		}
	}
}

int main()
{
	primeiras_opcoes();

	return 0;
}
