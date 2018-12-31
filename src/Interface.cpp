#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "EmpresaTransportes.h"
#include "Input_handler.h"
#include <iomanip>

void inserir_escola(Empresa &empresa);

void inserir_utente_escola(Empresa &empresa, Utente *ut)
{
	unsigned codigo;

	while(true)
	{
		cout << "A que escola pretende associar o utente? (Ctrl + Z para ver lista de escolas/inserir nova escola)" << '\t';
		cin >> codigo;

		if(cin.eof())
		{
			char c;

			cout << "Pretende ver a lista de escolas ('v') ou inserir uma nova escola ('i')?" << '\t';
			cin >> c;

			if(c == 'v')
			{
				cout << empresa.getEscolasZona(ut->getZonaEscola()) << endl;
			}
			else if(c == 'i')
			{
				inserir_escola(empresa);
			}
			else continue;
		}
		else if(cin.fail())
		{
			cin.ignore(10000, '\n');
			cin.clear();
		}
		else
		{
			try
			{
				empresa.InsereUtenteEscola(codigo, ut);
			}
			catch(ZonasIncompativeis &z)
			{
				z.getMsg();
				continue;
			}
			catch(EscolaNaoExistente &e)
			{
				e.getMsg();
				continue;
			}

			return;
		}
	}
}

void remover_utente_escola(Empresa &empresa, Utente *ut)
{
	empresa.RemoveUtenteEscola(ut);

	cout << "Deverá agora associar o utente a uma nova escola." << endl;

	inserir_utente_escola(empresa, ut);
}

void mudar_escola_utente(Empresa &empresa, unsigned numUtente)
{
	vector<Utente*> aux = empresa.getUtentes();

	for(size_t i = 0; i < aux.size(); i++)
	{
		if(aux[i]->getNumUtente() == numUtente)
		{
			remover_utente_escola(empresa, aux[i]);
			inserir_utente_escola(empresa, aux[i]);
			break;
		}
	}
}

void adicicionar_utente(Empresa &empresa)
{
	//TIRAR INFO COMUM A TODOS OS UTENTES
	string nome, data_nasc, BI;
	unsigned int zonaHabit;
	unsigned int zonaEsc;

	//NOME
	cout << "Qual o nome do novo utente?" << endl;
	cin.ignore(1000,'\n');
	getline(cin,nome);

	//DATA DE NASCIMENTO
	cout << endl << "Qual a data de nascimento do utente?" << endl;
	validar_data(data_nasc);

	//BI
	cout << endl << "Qual o BI?" << endl;
	allNumbers(BI, 8);

	int num_zonas = empresa.getPrecos().size();

	//ZONA DE HABITACAO
	cout << endl << "Qual a zona onde a habitacao se encontra?" << endl;
	zonaHabit = respostaNumeros(1, num_zonas);

	//ZONA DA ESCOLA
	cout << endl << "Qual a zona onde a escola se encontra?" << endl;
	zonaEsc = respostaNumeros(1, num_zonas);


	///DADOS ESPECIFICOS
	cout << "O utente e uma crianca? (S/N)" << endl;

	char resposta = respostaS_N();

	if(resposta == 'S')
	{
		string nomeEE;
		unsigned int contactoEE;

		//NOME DO ENCARREGADO DE EDUCACAO
		cout << endl << "Qual o nome do encarregado de educacao?" << endl;
		cin.ignore(1000,'\n');
		getline(cin,nomeEE);

		//CONTACTO DO ENCARREGADO DE EDUCACAO
		cout << endl << "Qual o contacto do encarregado de educacao?" << endl;
		checkCinFail(contactoEE);

		//ADICIONAR A CRIANCA AOS UTENTES
		try
		{
			empresa.adicionarUtente(new Crianca(nome, data_nasc, BI, zonaHabit, zonaEsc, nomeEE, contactoEE));
		}
		catch (UtenteJaExiste &e)
		{
			cout << e.getMsg() << endl;
			return;
		}
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
		checkCinFail(contacto);

		try
		{
			empresa.adicionarUtente(new Funcionario(nome, data_nasc, BI, zonaHabit, zonaEsc, docente, contacto));
		}
		catch (UtenteJaExiste &e)
		{
			cout << e.getMsg() << endl;
			return;
		}
	}
	else return;
}

void alterar_utente(Empresa &empresa)
{
	while(true)
	{
		cout << "O que pretende alterar no utente?  " << endl
			 << "1. Contacto" << endl
			 << "2. Zona de habitacao" << endl
			 << "3. Zona escolar" << endl
			 << "4. Voltar" << endl;

		switch(respostaNumeros(1, 4))
		{
		case 1:
		{
			unsigned int numUtente, contacto;

			cout << "Qual o numero de utente?  ";
			checkCinFail(numUtente);

			cout << "Qual o novo contacto?  ";
			checkCinFail(contacto);


			try
			{
				empresa.alterarContacto(numUtente, contacto);
			}
			catch (UtenteNaoExistente &e)
			{
				cout << e.getMsg() << endl;
				return;
			}

			break;
		}
		case 2:
		{
			unsigned int numUtente, zonaHabit;

			cout << "Qual o numero de utente?  ";
			checkCinFail(numUtente);

			int num_zonas = empresa.getPrecos().size();

			cout << "Qual a nova zona de habitacao?  ";

			zonaHabit = respostaNumeros(1, num_zonas);

			try
			{
				empresa.alterarZonaHab(numUtente, zonaHabit);
			}
			catch (UtenteNaoExistente &e)
			{
				cout << e.getMsg() << endl;
				return;
			}

			break;
		}
		case 3:
		{
			unsigned int numUtente, zonaEsc;

			cout << "Qual o numero de utente?  ";
			checkCinFail(numUtente);

			int num_zonas = empresa.getPrecos().size();

			cout << "Qual a nova zona escolar?  ";

			zonaEsc = respostaNumeros(1, num_zonas);

			try
			{
				empresa.alterarZonaEsc(numUtente, zonaEsc);
			}
			catch (UtenteNaoExistente&e)
			{
				cout << e.getMsg() << endl;
				return;
			}

			mudar_escola_utente(empresa, numUtente);

			break;
		}
		case 4:
			return;
		}
	}
}

void remover_utente(Empresa &empresa)
{
	unsigned int numUtente;

	//Perguntar qual o numero de utente que pretende remover
	cout << endl << "Insira o numero do utente a remover.  " << endl;
	checkCinFail(numUtente);

	try
	{
		empresa.removerUtente(numUtente);
	}
	catch (UtenteNaoExistente &e)
	{
		cout << e.getMsg() << endl;
		return;
	}
}

void adicicionar_veiculo(Empresa &empresa)
{
	string matricula;
	float consumo100km;
	float precoComb;

	//RETIRAR DADOS COMUNS A TODOS OS VEICULOS

	//MATRICULA
	cout << endl << "Qual a matricula do veiculo que pretende adicionar?" << endl;
	validar_matricula(matricula);

	//CONSUMO 100 KM
	cout << endl << "Qual o consumo (em litros) por 100km?" << endl;

	checkCinFail(consumo100km);

	//PRECO COMBUSTIVEL
	cout << endl << "Qual o preco do combustivel que utiliza?" << endl;

	checkCinFail(precoComb);


	// ESPECIFICACAO DO VEICULO //

	char resposta;

	cout << "O veiculo que pretende adicionar e escolar?  " << endl;
	resposta = respostaS_N();

	if(resposta == 'S')
	{
		unsigned int capacidade;
		vector<unsigned int> zonasAtravessadas;
		unsigned int zona;
		unsigned int n = empresa.getPrecos().size();
		bool valido = false;

		//LUGARES LIVRES
		cout << endl << "Quantos lugares tem o veiculo?  " << endl;
		cin >> capacidade;

		//ZONAS ATRAVESSADAS
		cout << endl << "Quais sao as zonas que atravessa? (insira uma de cada vez e insira 0 quando tiver terminado)" << endl;

		while((zona = respostaNumeros(0,n)) != 0)
		{
			if(find(zonasAtravessadas.begin(), zonasAtravessadas.end(), zona) == zonasAtravessadas.end())
			{
				zonasAtravessadas.push_back(zona);
				valido = true;
			}
		}

		if(!valido)
		{
			cout << "Nao foi possivel construir o veiculo" << endl;
			return;
		}
		else
		{
			try
			{
				empresa.adicionarVeiculo(new Escolar(matricula, consumo100km, precoComb, capacidade, zonasAtravessadas));
			}
			catch(VeiculoJaExiste &e)
			{
				cout << e.getMsg() << endl;
				return;
			}
		}
	}
	else if(resposta == 'N')
	{
		int capacidade;
		bool alugado;
		char resp;

		//CAPACIDADE
		cout << endl << "Qual a capacidade do veiculo Recreativo?" << endl;
		checkCinFail(capacidade);

		//ALUGADOS
		cout << endl << "Esta alugado? (S/N)" << endl;

		resp = respostaS_N();

		if(resp == 'S')
		{
			alugado=true;
		}
		else if (resp == 'N')
		{
			alugado=false;
		}
		else
		{
			cout << "Nao foi possivel construir o veiculo" << endl;
			return;
		}

		try
		{
			empresa.adicionarVeiculo(new Recreativo(matricula,consumo100km,precoComb, capacidade,alugado));
		}
		catch(VeiculoJaExiste &e)
		{
			cout << e.getMsg() << endl;
			return;
		}
	}
	else return;
}

void alterar_veiculo(Empresa &empresa)
{
	while(true)
	{
		cout << "O que pretende alterar no veiculo?  " << endl
			 << "1. Adicionar uma zona" << endl
			 << "2. Remover uma zona" << endl
			 << "3. Voltar" << endl;

		switch(respostaNumeros(1, 3))
		{
		case 1:
		{
			unsigned int idV, zona;

			cout << "Qual o id do veiculo?  ";
			checkCinFail(idV);

			int num_zonas = empresa.getPrecos().size();

			cout << "Qual a nova zona?  ";

			zona = respostaNumeros(1, num_zonas);

			try
			{
				empresa.adicionarZonaEscolar(idV, zona);
			}
			catch (VeiculoNaoExistente &e)
			{
				cout << e.getMsg() << endl;
				return;
			}
			catch (ZonaJaExistente &e)
			{
				cout << e.getMsg() << endl;
				return;
			}

			break;
		}
		case 2:
		{
			unsigned int idV, zona;

			cout << "Qual o id do veiculo?  ";
			checkCinFail(idV);

			int num_zonas = empresa.getPrecos().size();

			cout << "Qual a zona que pretende remover?  ";

			zona = respostaNumeros(1, num_zonas);

			try
			{
				empresa.removerZonaEscolar(idV, zona);
			}
			catch (VeiculoNaoExistente &e)
			{
				cout << e.getMsg() << endl;
				return;
			}
			catch (ZonaJaExistente &e) {
				cout << e.getMsg() << endl;
			}

			break;
		}
		case 3:
		{
			return;
			break;
		}
		}
	}
}

void remover_veiculo(Empresa &empresa)
{
	unsigned int id;

	cout << endl << "Insira o id do veiculo que pretende remover" << endl;
	checkCinFail(id);

	try
	{
		empresa.removerVeiculo(id);
	}
	catch (VeiculoNaoExistente &e)
	{
		cout << e.getMsg() << endl;
		return;
	}
}

void alterar_precoZonas(Empresa &empresa)
{
	cout << "Qual a variacao do preco?   ";
	float fator;
	checkCinFail(fator);

	empresa.atualizarPrecos(fator);
}

void calcula_um_passe(Empresa &empresa)
{
	unsigned int id;
	double valor;

	cout << "Qual o numero do utente? ";
	cin >> id;

	try
	{
		valor = empresa.calculoPasseMensal(id);
	}
	catch(UtenteNaoExistente &e)
	{
		cout << e.getMsg() << endl;
		return;
	}

	cout << "O valor do passe mensal do utente n " << id
			<< " e " << valor << " euros" << endl;
}

void calcula_todos_passes(Empresa &empresa)
{
	empresa.atualizarPasses();

	cout << empresa.showTabPasses();
}

void alocar_um_utente(Empresa &empresa)
{
	unsigned int id, veic;

	cout << "Qual o numero do utente? ";
	cin >> id;

	try
	{
		veic = empresa.alocaUt(id);
	}
	catch(UtenteNaoExistente &e)
	{
		cout << e.getMsg() << endl;
		return;
	}
	catch(VeiculosInsuficientes &e)
	{
		cout << e.getMsg() << endl;
		return;
	}

	cout << "O utente n " << id << " foi atribuido ao transporte escolar n " << veic << endl;
}

void alocar_todos_utentes(Empresa &empresa)
{
	try{
	empresa.alocaUtentes();
	}
	catch(VeiculosInsuficientes &e){
		e.getMsg();
	}

	cout << empresa.showTabPassag();
}

void processar_dia(Empresa &empresa)
{
	float kms;

	cout << "//////Processar final do dia//////" << endl
			<< "Qual e a media de kms percorridos por zona? ";
	cin >> kms;

	if(empresa.finalDia(kms))
	{
		cout << empresa.showDiario();
	}
	else
	{
		cout << "Ja se encontra no fim do mes. Processe o final deste mes(opcao 14) para poder fazer mais registos." << endl;
	}
}

void processar_mes(Empresa &empresa)
{
	cout << "//////Processar final do mes//////" << endl;

	if(!empresa.calculoMensal())
		cout << empresa.showMensal();
}

void alugar_recreativo(Empresa &empresa)
{
	unsigned int cap_id;
	string info;

	cout << "Quer alugar o veiculo para quantas pessoas? ";
	cin >> cap_id;

	try
	{
	info = empresa.verificaDispRecreativo(cap_id);
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
	catch(PrecoNaoDefinido &e)
	{
		cout << e.getMsg() << endl;
		return;
	}
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

void inserir_motorista( Empresa &empresa)
{
	string matricula,nome;
	unsigned id;

	cout <<"insira o nome e os veiculos,insira parar para parar"<<endl;
	cin>>nome;

	pair<string,unsigned > m;
	list<pair<string,unsigned>> veiculos;

	cout<<"matricula: ";
	cin>>matricula;

	while(matricula!="parar")
		{
			cout<<"id: ";
			cin>>id;

			m=make_pair(matricula, id);

			veiculos.push_back(m);

			cout<<"matricula: ";
			cin>>matricula;
		}

	if(empresa.contratarNovoMotorista(nome,veiculos))
		cout<< "O veiculo foi inserido com sucesso"<<endl;
	else cout<<"O veiculo que inseriu nao possui motoristas livres, tera que contratar um novo motorista"<<endl;

	empresa.mostrar_nome_motoristas();
}

void inserir_veiculo(Empresa &empresa)
{
	char answer;

	cout<< "Quer atribuir o veiculo a um motorista em especifico?"<<endl;
	cin>>answer;

	if(answer=='y'||answer=='Y')
		{
			//mostrar os motoristas existentes e o seu estado de contratacao
			if(!empresa.mostrar_nome_motoristas())
				{
					cout<< "Para executar esta operacao necessita que haja motoristas no sistema"<<endl;
					return;
				}

		string nome;

		cout<<"insira o nome do motorista"<<endl;
		cin>>nome;

		//introduzir informacoes sobre os veiculos a inserir no motorista

		string matricula;
		unsigned id;
		pair<string,unsigned > m;
		list<pair<string,unsigned>> veiculos;

		//NOTA: ainda falta verificar se o veiculo existe
		cout<<"Insira a matricula e o id correspondente ao veiculo e quando quiser parar escreva parar"<<endl;
		cout<<"Matricula: "<<endl;
		cin>>matricula;

		while(matricula!="parar")
		 {
			  cout<<"id: ";
			  cin>>id;

			  m=make_pair(matricula, id);

			  veiculos.push_back(m);

			  cout<<"Matricula: ";
			  cin>>matricula;
		 }

		if(empresa.inserirVeiculos(nome,veiculos))
			cout<<"Os veiculos foram inseridos com sucesso"<<endl;
		else cout<<"Alguns dos veiculos nao puderam ser inseridos pois ultrapasaram o limite de 5 veiculos por motorista"<<endl;

		empresa.mostrar_nome_motoristas();
	}
	else
	{
		string matricula;
		unsigned id;
		pair<string,unsigned > m;
		list<pair<string,unsigned>> veiculos;

		//NOTA: ainda falta verificar se o veiculo existe
		cout<<"Insira a matricula e o id correspondente ao veiculo e quando quiser parar escreva parar"<<endl;
		cout<<"matricula: ";
		cin>>matricula;

		while(matricula!="parar")
			 {
				cout<<"id: "<<endl;
				cin>>id;

				if(empresa.averiguar_motoristas(matricula,id))
					cout<< "O veiculo foi inserido com sucesso"<<endl;
				else cout<<"O veiculo que inseriu nao possui motoristas livres, tera que contratar um novo motorista"<<endl;

				cout<<"matricula: "<<endl;
				cin>>matricula;
			 }
		empresa.mostrar_nome_motoristas();
	}
}

void removerVeiculo(Empresa & empresa)
{
	empresa.mostrar_nome_motoristas();

	string nome;

	cout<<"insira o nome do motorista"<<endl;
	cin>>nome;

	string matricula;
	unsigned id;
	pair<string,unsigned > m;
	list<pair<string,unsigned>> veiculos;

	cout<<"matricula: "<<endl;
	cin>>matricula;

	cout<<"id: "<<endl;
	cin>>id;

	if(empresa.removerVeiculo(nome,matricula,id))
		cout<<"O veiculo foi removido com sucesso"<<endl;
	else cout<<"O veiculo nao foi removido com sucesso"<<endl;

	empresa.mostrar_nome_motoristas();
}

void remover_motorista(Empresa &empresa)
{
	empresa.mostrar_nome_motoristas();

	string nome;

	cout<<"insira o nome do motorista que pretende remover"<<endl;
	cin>>nome;

	if(empresa.removerMotorista(nome))
		cout<< "Motorista removido com sucesso"<<endl;
	else cout<<"Motorista nao existente"<<endl;

}

void inserir_antigo_motorista(Empresa &empresa)
{
	empresa.mostrar_nome_motoristas();

	string nome;

	cout<<"insira o nome do motorista que pretende colocar no sistema"<<endl;
	cin>>nome;

	if(empresa.inserirAntigoMotorista(nome))
		cout<<"Motorista foi inserido com sucesso"<<endl;
	else cout <<"Motorista nao foi inserido com sucesso"<<endl;
}

void inserir_escola(Empresa &empresa)
{
	string nome, nome_d, morada_d;
	unsigned codigo, zona;

	cout << "Insira o nome da escola." <<  '\t';
	cin >> nome;

	cout << "Insira o nome do Diretor." << '\t';
	cin >> nome_d;

	cout << "Insira a morada do Diretor." << '\t';
	cin >> morada_d;

	cout << "Insira o codigo da escola (5 digitos)." << '\t';
	cin >> codigo;

	while(true)
	{
		if(cin.eof())
		{
			return;
		}
		else if(cin.fail())
		{
			cin.ignore(100000, '\n');
			cin.clear();
		}
		else if(codigo > 99999 || !empresa.verificaEscola(codigo).first)
		{}
		else break;

		cerr << "Input errado. Insira um código de 5 digitos" << '\t';
		cin >> codigo;
	}

	cout << "Insira a Zona." << '\t';
	cin >> zona;

	while(true)
	{
		if(cin.eof())
		{
			return;
		}
		else if(cin.fail())
		{
			cin.ignore(100000, '\n');
			cin.clear();
		}
		else if(zona < 1 || zona > empresa.getPrecos().size())
		{}
		else break;

		cerr << "Input errado. Insira uma zona que exista." << '\t';
		cin >> zona;
	}

	Escola esc(nome, codigo, nome_d, morada_d, zona);

	empresa.adicionaEscola(esc);
}

void remover_escola(Empresa &empresa)
{
	unsigned codigo;

	cout << "Qual o codigo da escola que pretende remover? (Ctrl+Z para sair)" << '\t';
	cin >> codigo;

	if(cin.eof())
	{
		return;
	}

	pair<bool, Escola> res = empresa.verificaEscola(codigo);

	while(cin.fail() && codigo > 99999 && !res.first)
	{
		cin.ignore();

		cerr << "Input errado. Insira um código existente" << '\t';
		cin.clear();
		cin >> codigo;

		if(cin.eof())
		{
			return;
		}
	}

	vector<Utente*> aux = empresa.removeEscola(res.second);

	if(aux.size() > 0)
	{
		inserir_utente_escola(empresa, aux[0]);
	}

	cout << "Os utentes serao recolocados na mesma escola." << endl;

	for(size_t i = 1; i < aux.size(); i++)
	{
		aux[i]->setCodEscola(aux[0]->getCodEscola());
		empresa.InsereUtenteEscola(aux[0]->getCodEscola(), aux[i]);
	}
}

void trabalhar_empresa(Empresa &empresa)
{
	while(true)
	{
		cout << "-------------" << empresa.getNome() << "------------" << endl
			 << "Qual o proximo passo?   " << endl
			 << "1. Adicicionar utente" << endl
			 << "2. Alterar informacoes de um utente" << endl
			 << "3. Remover utente" << endl
			 << "4. Adicionar veiculo" << endl
			 << "5. Alterar zona atravessada por um veiculo" << endl
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
			 << "22. Inserir motorista" << endl
			 << "23. Inserir veiculo(s)" << endl
			 << "24. Remover veiculo de um motorista" << endl
			 << "25. Remover Motorista" << endl
			 << "26. Inserir um antigo motorista" << endl
			 << "27. Adicionar Escola" << endl
			 << "28. Remover Escola" << endl
			 << "29. Voltar" << endl;

		switch(respostaNumeros(1, 30))
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
			inserir_motorista(empresa);
			break;
		case 23:
			inserir_veiculo(empresa);
			break;
		case 24:
			removerVeiculo(empresa);
			break;
		case 25:
			remover_motorista(empresa);
			break;
		case 26:
			inserir_antigo_motorista(empresa);
			break;
		case 27:
			inserir_escola(empresa);
			break;
		case 28:
			remover_escola(empresa);
			break;
		case 29:
			return;
		}
	}
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

	checkCinFail(zonas);

	for(int i = 0; i < zonas; i++)
	{
		precos_zona.push_back(vector<double>(zonas));
		for(int j = 0; j <= i; j++)
		{
			cout<<"Qual o preco entre a zona "<< i + 1<<" e "<< j + 1 <<"?  ";

			checkCinFail(preco);

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
	cout << "Deseja salvar o progresso?(S ou N)  ";

	if(respostaS_N() == 'S')
	{
		ofstream ficheiro;
		string nome_ficheiro;

		nome_ficheiro = empresa.getNome() + ".txt";

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
