#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "EmpresaTransportes.h"
#include "Input_handler.h"
#include <iomanip>


void adicicionar_utente(Empresa &empresa)
{
	//TIRAR INFO COMUM A TODOS OS UTENTES
	string nome, data_nasc, BI;
	unsigned int zonaHabit;
	unsigned int zonaEsc;

	//NOME
	cout << "Qual o nome do novo utente?" << endl;
	readLine(nome);

	//DATA DE NASCIMENTO
	cout << endl << "Qual a data de nascimento do utente?" << endl;
	cin >> data_nasc;
	validar_data(data_nasc);

	//BI
	cout << endl << "Qual o BI?" << endl;
	allNumbers(BI, 8);

	//o numero de zonas e dado pela raiz quadrada do numero total de casos possiveis no vetor precos_zona, uma vez que o tamanha deste é dado por nº zonas*nº zonas
	int num_zonas = empresa.getPrecos().size();

	//ZONA DE HABITACAO
	cout << endl << "Qual a zona onde a habitacao se encontra?" << endl;
	zonaHabit = respostaNumeros(1, num_zonas);

	//ZONA DA ESCOLA
	cout << endl << "Qual a zona onde a escola se encontra?" << endl;
	zonaEsc = respostaNumeros(1, num_zonas);


	///DADOS ESPECIFICOS
	cout << "O utente é uma criança? (S/N)" << endl;

	char resposta = respostaS_N();

	if(resposta == 'S')
	{
		string nomeEE;
		unsigned int contactoEE;

		//NOME DO ENCARREGADO DE EDUCACAO
		cout << endl << "Qual o nome do encarregado de educacao?" << endl;
		readLine(nomeEE);

		//CONTACTO DO ENCARREGADO DE EDUCACAO
		cout << endl << "Qual o contacto do encarregado de educacao?" << endl;
		checkingOnlyCinFail(contactoEE);

		//ADICIONAR A CRIANCA AOS UTENTES
		Crianca c1(nome, data_nasc, BI, zonaHabit, zonaEsc, nomeEE, contactoEE);

		try
		{
			empresa.adicionarUtente(&c1);
		}
		catch (exception &UtenteJaExiste) {}
	}
	else if(resposta == 'N')
	{
		char resposta;
		bool docente;
		unsigned int contacto;

		//DOCENTE
		cout << "O funcionario que pretende adicionar e docente(S/N)?" << endl;

		resposta = respostaS_N();

		if(resposta == 'S')
		{
			docente = true;
		}
		else if(resposta == 'N')
		{
			docente = false;
		}
		else return;

		//CONTACTO DO FUNCIONARIO
		cout << "Qual o contacto do funcionario?" << endl;
		checkingOnlyCinFail(contacto);

		//ADICIONAR O FUNCIONARIO AOS UTENTES
		Funcionario f1(nome, data_nasc, BI, zonaHabit, zonaEsc, docente, contacto);

		try
		{
			empresa.adicionarUtente(&f1);
		}
		catch (exception &UtenteJaExiste) {}
	}
	else return;
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

void calcula_um_passe(Empresa &empresa)
{
	unsigned int id;

	cout << "Qual o numero do utente? ";
	cin >> id;

	cout << "O valor do passe mensal � " << empresa.calculoPasseMensal(id) << " euros";
}

void calcula_todos_passes(Empresa &empresa)
{
	cout << empresa.atualizarPasses();
}

void alocar_um_utente(Empresa &empresa)
{

}

void alocar_todos_utentes(Empresa &empresa)
{

}

void processar_dia(Empresa &empresa)
{

}

void processar_mes(Empresa &empresa)
{

}

void alugar_recreativo(Empresa &empresa)
{
	unsigned int cap_id;
	string info;

	cout << "Quer alugar o veiculo para quantas pessoas? ";
	cin >> cap_id;

	info = empresa.verificaDispRecreativo(cap_id);
	cout << info;

	if(info == "Nao existe nenhum veiculo disponivel com essa capacidade.\n")
	{
		return;
	}
	else
	{
		cout << endl << "Qual o ID do veiculo que pretende alugar? ";
		cin >> cap_id;

		try{
			empresa.alugaRecreativo(cap_id);
		}
		catch(VeiculoNaoRecreativo &e)
		{
			cout << e.getMsg() << endl;
			return;
		}
		catch(VeiculoNaoExistente &e)
		{
			cout << e.getMsg() << endl;
			return;
		}

		cout << "Veiculo alugado com sucesso para o resto do dia." << endl;
	}
}

void mostrar_utentes(const Empresa &empresa)
{
	cout << empresa.showUtentes();
}

void mostrar_veiculos(const Empresa &empresa)
{
	cout << empresa.showVeiculos();
}

void mostrar_tab_passes(const Empresa &empresa)
{
	cout << empresa.showTabPasses();
}

void mostrar_tab_alocacao(const Empresa &empresa)
{
	cout << empresa.showTabPassag();
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
			 << "8. Calcular o valor do passe mensal de um utente" << endl
			 << "9. Atualizar o valor dos passes mensais no registo" << endl
			 << "10. Alocar um utente para o transporte escolar" << endl
			 << "11. Alocar todos os utentes para os transportes escolares" << endl
			 << "12. Alugar recreativo" << endl
			 << "13. Processar o final do dia de hoje" << endl
			 << "14. Processar o final deste mes" << endl
			 << "15. Mostrar a lista de utentes" << endl
			 << "16. Mostrar a lista de veiculos" << endl
			 << "17. Mostrar a tabela do valor dos passes" << endl
			 << "18. Mostrar a tabela de alocacao de utentes por veiculo" << endl
			 << "19. Mostrar os lucros mensais deste ano" << endl
			 << "20. Mostrar os balancos diarios deste mes" << endl
			 << "21. Mostrar a matriz de precos por zona" << endl
			 << "22. Voltar" << endl;

		switch(respostaNumeros(1, 22))
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
			calcula_um_passe(empresa);
			break;
		case 9:
			calcula_todos_passes(empresa);
			break;
		case 10:
			alocar_um_utente(empresa);
			break;
		case 11:
			alocar_todos_utentes(empresa);
			break;
		case 12:
			alugar_recreativo(empresa);
			break;
		case 13:
			processar_dia(empresa);
			break;
		case 14:
			processar_mes(empresa);
			break;
		case 15:
			mostrar_utentes(empresa);
			break;
		case 16:
			mostrar_veiculos(empresa);
			break;
		case 17:
			mostrar_tab_passes(empresa);
			break;
		case 18:
			mostrar_tab_alocacao(empresa);
			break;
		case 19:
			mostrar_lucros_mensais(empresa);
			break;
		case 20:
			mostrar_registo_diario(empresa);
			break;
		case 21:
			mostrar_precos(empresa);
			break;
		case 22:
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
