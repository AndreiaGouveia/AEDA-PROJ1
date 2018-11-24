#include "EmpresaTransportes.h"
#include "Input_handler.h"
#include <iomanip>
#include <istream>


void adicicionar_utente(Empresa &empresa)
{
	//TIRAR INFO COMUM A TODOS OS UTENTES
	string nome, data_nasc, BI;
	unsigned int zonaHabit;
	unsigned int zonaEsc;

	//NOME
	cout << "Qual o nome do novo utente?" << endl;
//	cin.getline(&nome, 10000, '\n');

	//DATA DE NASCIMENTO
	cout << endl << "Qual a data de nascimento do utente?" << endl;
	cin >> data_nasc;
	validar_data(data_nasc);

	//BI
	cout << endl << "Qual o BI?" << endl;
	cin >> BI;
//	allNumbers(BI);

	//ZONA DE HABITACAO
	cout << endl << "Qual a zona onde a habitacao se encontra?" << endl;
	cin >> zonaHabit;

	//ZONA DA ESCOLA
	cout << endl << "Qual a zona onde a escola se encontra?" << endl;
	cin >> zonaEsc;
}

void alterar_utente(Empresa &empresa)
{

}

void remover_utente(Empresa &empresa)
{

}

void adicicionar_veiculo(Empresa &empresa)
{

}

void alterar_veiculo(Empresa &empresa)
{

}

void remover_veiculo(Empresa &empresa)
{

}

void alterar_precoZonas(Empresa &empresa)
{

}

void alugar_recreativo(Empresa &empresa)
{

}

void mostrar_utentes(const Empresa &empresa)
{
	cout << empresa.showUtentes();
}

void mostrar_veiculos(const Empresa &empresa)
{
	cout << empresa.showVeiculos();
}

void mostrar_lucros_mensais(const Empresa &empresa)
{
	cout << empresa.showMensal();
}

void mostrar_registo_diario(const Empresa &empresa)
{
	cout << empresa.showDiario();
}

void mostrar_precos(const Empresa &empresa)
{
	cout << empresa.showPrecos();
}

void trabalhar_empresa(Empresa &empresa)
{
	bool end = false;

	do
	{
		cout << "-------------" << empresa.getNome() << "------------" << endl
			 << "Qual o proximo passo?   " << endl
			 << "1. Adicicionar utente" << endl
			 << "2. Alterar informacoes de um utente" << endl
			 << "3. Remover utente" << endl
			 << "4. Adicionar veiculo" << endl
			 << "5. Alterar zona atravessada por um veiculo"
			 << "6. Remover veiculo" << endl
			 << "7. Alterar preco das zonas" << endl
			 << "8. Alugar recreativo" << endl
			 << "9. Mostrar a lista de utentes" << endl
			 << "10. Mostrar a lista de veiculos" << endl
			 << "11. Mostrar os lucros mensais deste ano" << endl
			 << "12. Mostrar os balancos diarios deste mes" << endl
			 << "13. Mostrar a matriz de precos por zona" << endl
			 << "14. Sair" << endl;

		switch(respostaNumeros(1, 14))
		{
		case 1:
			adicicionar_utente(empresa);
			break;
		case 2:
			alterar_utente(empresa);
			break;
		case 3:
			remover_utente(empresa);
			break;
		case 4:
			adicicionar_veiculo(empresa);
			break;
		case 5:
			alterar_veiculo(empresa);
			break;
		case 6:
			remover_veiculo(empresa);
			break;
		case 7:
			alterar_precoZonas(empresa);
			break;
		case 8:
			alugar_recreativo(empresa);
			break;
		case 9:
			mostrar_utentes(empresa);
			break;
		case 10:
			mostrar_veiculos(empresa);
			break;
		case 11:
			mostrar_lucros_mensais(empresa);
			break;
		case 12:
			mostrar_registo_diario(empresa);
			break;
		case 13:
			mostrar_precos(empresa);
			break;
		case 14:
			end = true;
			break;
		}
	}while(!end);
}

Empresa criar_empresa()
{
	string nome_empresa;

	cout << "Como se chama a empresa?  ";
	cin >> nome_empresa;

	if(cin.eof())
	{
		Empresa empresa("Nao criada");

		return empresa;
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
		precos_zona.push_back(vector<double>(zonas));
		for(int j = 0; j <= i; j++)
		{
			cout<<"Qual o preco entre a zona "<< i + 1<<" e "<< j + 1 <<"?  ";
			cin >> preco;

			checkingOnlyCinFail(preco);

			precos_zona[i][j] = preco;

			if(i != j)
				precos_zona[j][i] = preco;
		}
	}

	empresa.setPrecos(precos_zona);//Agora a empresa tem os precos

	trabalhar_empresa(empresa);

	return empresa;
}

Empresa continuar_empresa()
{
	ifstream ficheiro;
	string nome_ficheiro;

	cout << endl << "Qual o nome do ficheiro que quer abrir (nao coloque extensao .txt)? (Ctrl + Z para sair)  " << endl;

	if(file_handler(nome_ficheiro, ficheiro))
	{
		Empresa empresa(ficheiro);

		trabalhar_empresa(empresa);

		return empresa;
	}
	else
	{
		Empresa empresa("Nao criada");

		return empresa;
	}
}

void sair(Empresa &empresa)
{
	cout << "Deseja salvar o progresso?  ";

	if(respostaS_N() == 'S')
	{
		ofstream ficheiro;
		string nome_ficheiro;

		nome_ficheiro = nome_ficheiro + ".txt";

		ficheiro.open(nome_ficheiro);

		ficheiro << empresa;

		ficheiro.close();

		cout << "==================================================" << endl << endl
		     << "Os dados da empresa foram guardados com sucesso em:" << endl
			 << nome_ficheiro << endl << endl
			 << "===================================================" << endl << endl;
	}
}

void iniciar()
{
	cout << "==============================" << endl
		 << "=== Empresa de Transportes ===" << endl
		 << "==============================" << endl << endl;

	bool end = false;

	do
	{
		cout << "Que deseja fazer?" << endl
			 << "1. Criar uma nova empresa" << endl
			 << "2. Aceder a uma empresa ja existente" << endl
			 << "3. Sair" << endl;

		switch(respostaNumeros(1, 3))
		{
		case 1:
		{
			Empresa emp = criar_empresa();

			if(emp.getNome() == "Nao criada")
			{
				break;
			}

			sair(emp);

			break;
		}
		case 2:
		{
			Empresa emp = continuar_empresa();

			if(emp.getNome() == "Nao criada")
			{
				break;
			}

			sair(emp);

			break;
		}
		case 3:
			end = true;
			break;
		}
	}while(!end);
}

int main()
{
	iniciar();

	cout << "Ate a proxima :)" << endl;

	system("pause");

	return 0;
}
