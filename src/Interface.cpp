#include "EmpresaTransportes.h"
#include "Input_handler.h"
#include <iomanip>


void adicicionar_utente()
{

}

void alterar_utente()
{

}

void remover_utente()
{

}

void adicicionar_veiculo()
{

}

void alterar_veiculo()
{

}

void remover_veiculo()
{

}

void alterar_precoZonas()
{

}

void alugar_recreativo()
{

}

void trabalhar_empresa(const Empresa &empresa)
{
	bool end = false;

	do
	{
		cout << "--------------------------------"
			 << "Qual o proximo passo?   " << endl
			 << "1. Adicicionar utente" << endl
			 << "2. Alterar informacoes de um utente" << endl
			 << "3. Remover utente" << endl
			 << "4. Adicionar veiculo" << endl
			 << "5. Alterar zona atravessada por um veiculo"
			 << "6. Remover veiculo" << endl
			 << "7. Alterar preco das zonas" << endl
			 << "8. Alugar recreativo" << endl
			 << "9. Sair" << endl;

		switch(respostaNumeros(1, 9))
		{
		case 1:
			adicicionar_utente();
			break;
		case 2:
			alterar_utente();
			break;
		case 3:
			remover_utente();
			break;
		case 4:
			adicicionar_veiculo();
			break;
		case 5:
			alterar_veiculo();
			break;
		case 6:
			remover_veiculo();
			break;
		case 7:
			alterar_precoZonas();
			break;
		case 8:
			alugar_recreativo();
			break;
		case 9:
			end = true;
			break;
		}
	}while(!end);
}

Empresa* criar_empresa()
{
	string nome_empresa;

	cout << "Como se chama a empresa?  ";
	cin >> nome_empresa;

	if(cin.eof())
	{
		Empresa empresa("Nao criada");

		Empresa *emp = &empresa;

		return emp;
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

	Empresa *emp = &empresa;

	return emp;
}

Empresa* continuar_empresa()
{
	ifstream ficheiro;
	string nome_ficheiro;

	cout << endl << "Qual o nome do ficheiro que quer abrir (não coloque extensao .txt)? (Ctrl + Z para sair)  " << endl;

	if(file_handler(nome_ficheiro, ficheiro))
	{
		Empresa empresa(ficheiro);

		trabalhar_empresa(empresa);

		Empresa *emp = &empresa;

		return emp;
	}
	else
	{
		Empresa empresa("Nao criada");

		Empresa *emp = &empresa;

		return emp;
	}
}

void sair(Empresa *empresa)
{
	cout << "Deseja salvar o progresso?  ";

	if(respostaS_N() == 'S')
	{
		empresa->guardarInfo();
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
			Empresa *emp = criar_empresa();

			if(emp->getNome() == "Nao criada")
			{
				break;
			}

			sair(emp);

			break;
		}
		case 2:
		{
			Empresa *emp = continuar_empresa();

			if(emp->getNome() == "Nao criada")
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
