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
	string codigo;

	cout << "A que escola pretende associar o utente? ('v' para ver lista de escolas; 'i' para inserir nova escola)   ";

	while(true)
	{
		cin >> codigo;

		if(codigo == "v")
		{
			cout << empresa.getEscolasZona(ut->getZonaEscola()) << endl;
			cout << endl << "Introduza o codigo da escola onde pretende adicionar o utente.    ";
		}
		else if(codigo == "i")
		{
			inserir_escola(empresa);

			cout << endl << "Introduza o codigo da escola onde pretende adicionar o utente.    ";
		}
		else
		{
			bool valid = true;

			for(size_t i = 0; i < codigo.size(); i++)
			{
				if(!isdigit(codigo[i]))
				{
					cerr << "Introduza um código válido ('v' para ver lista de escolas; 'i' para inserir nova escola)    ";
					valid = false;
					break;
				}
			}

			if(!valid)
				continue;

			try
			{
				empresa.InsereUtenteEscola(stoul(codigo), ut);
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

			ut->setCodEscola(stoul(codigo));
			break;
		}
	}
}

void remover_utente_escola(Empresa &empresa, Utente *ut)
{
	empresa.RemoveUtenteEscola(ut);

	cout << "Devera agora associar o utente a uma nova escola." << endl;

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
			return;
		}
	}

	throw UtenteNaoExistente();
}

void inserir_escola(Empresa &empresa)
{
	string nome, nome_d, morada_d;
	unsigned codigo, zona;

	cout << "Insira o nome da escola.   ";
	cin.ignore(1000,'\n');
	getline(cin,nome);

	if(cin.eof())
		return;

	cout << "Insira o nome do Diretor.   ";
	getline(cin,nome_d);

	if(cin.eof())
		return;

	cout << "Insira a morada do Diretor.   ";
	getline(cin,morada_d);

	if(cin.eof())
		return;

	cout << "Insira o codigo da escola (5 digitos).   ";
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
		else if(codigo > 99999)
		{}
		else if(empresa.verificaEscola(codigo).first)
		{
			cerr << "Escola ja existe. ";
		}
		else break;

		cerr << "Input errado. Insira um código de 5 digitos.   ";
		cin >> codigo;
	}

	cout << "Insira a Zona.   ";
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

		cerr << "Input errado. Insira uma zona que exista.   ";
		cin >> zona;
	}

	Escola esc(nome, codigo, nome_d, morada_d, zona);

	empresa.adicionaEscola(esc);
}

void remover_escola(Empresa &empresa)
{
	unsigned codigo;

	cout << "Qual o codigo da escola que pretende remover? (Ctrl+Z para sair)   ";
	cin >> codigo;

	while(true)
	{
		if(cin.eof())
		{
			return;
		}
		else if(cin.fail())
		{
			cin.ignore(10000, '\n');
			cin.clear();
		}
		else if(codigo > 99999)
		{}
		else
		{
			if(!empresa.verificaEscola(codigo).first)
			{}
			else
			{
				break;
			}
		}

		cerr << "Input errado. Insira um código existente.   ";
		cin >> codigo;
	}

	pair<bool, Escola> res = empresa.verificaEscola(codigo);

	vector<Utente*> aux = empresa.removeEscola(res.second);

	if(aux.size() > 0)
	{
		inserir_utente_escola(empresa, aux[0]);
		cout << "Os utentes serao recolocados na mesma escola." << endl;

		for(size_t i = 1; i < aux.size(); i++)
		{
			empresa.InsereUtenteEscola(aux[0]->getCodEscola(), aux[i]);
		}
	}
}

void mostrar_escolas(Empresa &empresa)
{
	cout << empresa.getEscolas();
}

void alterar_escola(Empresa &emp)
{
	unsigned codigo;

	Escola esc("", 0, "", "", 0);

	cin.ignore(10000, '\n');

	cout << "Qual o código da escola que pretende alterar? (Ctrl+Z para sair)     ";
	cin >> codigo;

	do
	{
		if(cin.eof())
		{
			return;
		}
		else if(cin.fail())
		{
			cin.clear();
			cin.ignore(10000, '\n');
			cerr << "Codigo invalido. Insira o codigo da escola que pretende alterar.     ";
		}
		else
		{
			pair<bool, Escola> par = emp.verificaEscola(codigo);

			if(par.first)
			{
				esc = par.second;
				break;
			}
			else cout << "Nao existe uma escola com o codigo inserido. Insira um codigo valido.     ";
		}

		cin >> codigo;

	}while(true);


	string nome, morada;

	cin.ignore(10000, '\n');

	cout << "Insira o nome do Diretor.   ";
	getline(cin,nome);

	if(cin.eof())
		return;

	cout << "Insira a morada do Diretor.   ";
	getline(cin,morada);

	if(cin.eof())
		return;

	emp.removeEscola(esc);

	esc.set_diretor(nome, morada);

	emp.adicionaEscola(esc);
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
		Utente* ut = new Crianca(nome, data_nasc, BI, zonaHabit, zonaEsc, nomeEE, contactoEE);

		try
		{
			empresa.adicionarUtente(ut);
		}
		catch (UtenteJaExiste &e)
		{
			cout << e.getMsg() << endl;
			return;
		}

		inserir_utente_escola(empresa, ut);
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

		Utente* ut = new Funcionario(nome, data_nasc, BI, zonaHabit, zonaEsc, docente, contacto);

		try
		{
			empresa.adicionarUtente(ut);
		}
		catch (UtenteJaExiste &e)
		{
			cout << e.getMsg() << endl;
			return;
		}

		inserir_utente_escola(empresa, ut);
	}
	else return;
}

void alterar_utente(Empresa &empresa)
{
	while(true)
	{
		cout << "-------------" << empresa.getNome() << "------------" << endl
			 << "O que pretende alterar no utente?  " << endl
			 << "1. Contacto" << endl
			 << "2. Zona de habitacao" << endl
			 << "3. Zona escolar" << endl
			 << "4. Escola" << endl
			 << "5. Voltar" << endl;

		switch(respostaNumeros(1, 5))
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
		{
			unsigned int numUtente;

			cout << "Qual o numero de utente?  ";
			checkCinFail(numUtente);

			try
			{
				mudar_escola_utente(empresa, numUtente);
			}
			catch (UtenteNaoExistente&e)
			{
				cout << e.getMsg() << endl;
				return;
			}

			break;
		}
		case 5:
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
		cout << "-------------" << empresa.getNome() << "------------" << endl
			 << "O que pretende alterar no veiculo?  " << endl
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
		cout << "Ja se encontra no fim do mes. Processe o final deste mes(opcao 9) para poder fazer mais registos." << endl;
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
		catch(VeiculoEmReparacao &e)
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

void mostrar_oficinas(Empresa &empresa)
{
	cout << empresa.showOficinas();
}

void inserir_oficina(Empresa &empresa)
{
	string nome;
	unsigned int dist;

	cout << "Qual o nome da Oficina que pretende inserir? ";
	cin.ignore(1000,'\n');
	getline(cin,nome);
	cout << "Qual a distancia, em kms, da Oficina a garagem da Empresa? "; checkCinFail(dist);

	if(empresa.insertOficina(Oficina(nome, dist)))
		cout << "Oficina inserida com sucesso!" << endl;
	else
		cout << "Uma Oficina com o mesmo nome ja existe! A insercao falhou." << endl;
}

void remover_oficina(Empresa &empresa)
{
	string nome;

	cout << "Qual o nome da Oficina que pretende remover? ";
	cin.ignore(1000,'\n');
	getline(cin,nome);

	if(empresa.removeOficina(Oficina(nome)))
		cout << "A Oficina foi removida com sucesso!" << endl;
	else
		cout << "A Oficina nao existe! A remocao falhou." << endl;
}

void alterar_oficina(Empresa &empresa)
{
	string nome, resp;
	int nVal;
	bool flag;

	cout << "Qual o nome da Oficina que pretende remover? ";
	cin.ignore(1000,'\n');
	getline(cin,nome);

	if(!empresa.checkOficina(Oficina(nome)))
	{
		cout << "A Oficina nao existe! Verifique o nome e tente outra vez." << endl;
		return;
	}

	cout << "Quer alterar a distancia da garagem a Oficina ou a disponibilidade da Oficina? ";
	checkCinFail(resp);

	if(resp == "distancia")
	{
		flag = true;
		cout << "Qual a nova distancia (em kms)? "; checkCinFail(nVal);
	}
	else
	{
		flag = false;
		cout << "Quantos dias faltam para a Oficina estar disponivel? "; checkCinFail(nVal);
	}

	empresa.editOficina(nome, nVal, flag);

	cout << "A edicao foi feita com sucesso! Deseja visualizar as Oficinas? ";

	if(respostaS_N() == 'S')
		mostrar_oficinas(empresa);
}

void reparar_veiculo(Empresa &empresa)
{
	double dist_max;
	unsigned int id;

	cout << "Qual o id do veiculo a reparar? "; checkCinFail(id);
	cout << "Qual a distancia maxima, em kms, da Oficina a garagem? "; checkCinFail(dist_max);

	Oficina temp;

	try
	{
		temp = empresa.repararVeiculo(id,dist_max);
	}
	catch(VeiculoNaoExistente &e)
	{
		cout << e.getMsg();
	}

	if(temp == Oficina())
	{
		cout << "Nao existe nenhuma Oficina a essa distancia. Nao foi possivel enviar o veiculo para reparacao." << endl;
	}
	else
		cout << "O veiculo foi enviado para reparacao com sucesso!" << endl;
}

void mostrar_motoristas(Empresa &empresa)
{
	empresa.mostrar_nome_motoristas();
}

void inserir_motorista( Empresa &empresa)
{
	string nome;
	unsigned id;
	int counter=0;

	cout <<"Insira o nome do novo motorista e os veiculos associado. Insira 0 para parar"<<endl;
	cin>>nome;

	list<unsigned> veiculos;

	cout<<"id: ";
	cin>>id;

	counter++;

	veiculos.push_back(id);

	while(id!=0 && counter<=5)
		{

		veiculos.push_back(id);

		cout<<"id: ";
		cin>>id;

			counter++;
		}

	if(counter==5)
		cout<<"Ja nao pode inserir mais veiculos neste motorista. O limite sao 5 por motorista"<<endl;

	if(empresa.contratarNovoMotorista(nome,veiculos))
		cout<< "O(s) veiculo(s) foi inserido com sucesso"<<endl;
	else cout<<"O(s) veiculo(s) que inseriu nao possui(em) motoristas livres, tera que contratar um novo motorista"<<endl;

	empresa.mostrar_nome_motoristas();
}

void inserir_veiculo(Empresa &empresa)
{
	char answer;

	cout<< "Quer atribuir o veiculo a um motorista em especifico?"<<endl;
	cin>>answer;

	if(answer=='s'||answer=='S')
		{
			//mostrar os motoristas existentes e o seu estado de contratacao
			if(!empresa.mostrar_nome_motoristas())
				{
					cout<< "Para executar esta operacao necessita que haja motoristas no sistema"<<endl;
					return;
				}

		string nome;

		cout<<"Insira o nome do motorista"<<endl;
		cin>>nome;

		//introduzir informacoes sobre os veiculos a inserir no motorista

		unsigned id;
		list<unsigned> veiculos;

		//NOTA: ainda falta verificar se o veiculo existe
		cout<<"Insira o id correspondente ao veiculo e quando quiser parar insira 0"<<endl;
		cout<<"id: "<<endl;
		cin>>id;

		for(int i=1;id!=0;i++)
		 {
			veiculos.push_back(id);

			if((empresa.nr_restante_veiculos(nome)-i)>=0 && empresa.nr_restante_veiculos(nome)!=6 )
			  {
				cout<<"id: ";
				cin>>id;

				if(id==0)
					break;
			  }
			else
			{
				cout<< "Ja nao pode adicionar mais veiculos, o limite por motorista sao 5"<<endl;
				break;
			}

		 }

		if(empresa.inserirVeiculos(nome,veiculos))
			cout<<"Os veiculos foram inseridos com sucesso"<<endl;
		else cout<<"Alguns dos veiculos nao puderam ser inseridos pois ultrapasaram o limite de 5 veiculos por motorista"<<endl;

		empresa.mostrar_nome_motoristas();
	}
	else
	{
		unsigned id;
		list<unsigned> veiculos;

		//NOTA: ainda falta verificar se o veiculo existe
		cout<<"Insira o id correspondente ao veiculo e quando quiser parar insira 0"<<endl;
		cout<<"Id: ";
		cin>>id;

		while(id!=0)
			 {
				if(empresa.averiguar_motoristas(id))
					cout<< "O veiculo foi inserido com sucesso"<<endl;
				else cout<<"O veiculo que inseriu nao possui motoristas livres, tera que contratar um novo motorista"<<endl;

				cout<<"id: "<<endl;
				cin>>id;
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

	unsigned id;
	list<unsigned> veiculos;

	cout<<"id: "<<endl;
	cin>>id;

	if(empresa.removerVeiculo(nome,id))
		cout<<"O veiculo foi removido com sucesso"<<endl;
	else cout<<"O veiculo nao foi removido com sucesso"<<endl;

	empresa.mostrar_nome_motoristas();
}

void remover_motorista(Empresa &empresa)
{
	empresa.mostrar_nome_motoristas();

	string nome;

	cout<<"Insira o nome do motorista que pretende remover: "<<endl;
	cin>>nome;

	if(empresa.removerMotorista(nome))
		cout<< "Motorista removido com sucesso"<<endl;
	else cout<<"Motorista nao existente"<<endl;

}

void inserir_antigo_motorista(Empresa &empresa)
{
	empresa.mostrar_nome_motoristas();

	string nome;

	cout<<"Insira o nome do motorista que pretende colocar no sistema: "<<endl;
	cin>>nome;

	if(empresa.inserirAntigoMotorista(nome))
		cout<<"Motorista foi inserido com sucesso"<<endl;
	else cout <<"Motorista nao foi inserido com sucesso"<<endl;
}

void despedir_motorista(Empresa &empresa)
{
	empresa.mostrar_nome_motoristas();

	string nome;

	cout<<"Insira o nome do motorista cujo estado do contrato pretende alterar: "<<endl;
	cin>>nome;

	if(empresa.despedir_motorista(nome))
		cout<<"Contrato terminado com sucesso"<<endl;
	else cout<<"O contrato nao foi terminado com sucesso"<<endl;

}

void alterar_motorista(Empresa &empresa)
{
	while (true)
	{
		cout << "-------------" << empresa.getNome() << "------------" << endl
			<< "O que pretende editar no motorista?" << endl
			<< "1. Inserir veiculo" << endl
			<< "2. Remover veiculo" << endl
			<< "3. Voltar" << endl;
		switch(respostaNumeros(1,3)){
		case(1):
			inserir_veiculo(empresa);
			break;
		case(2):
			removerVeiculo(empresa);
			break;
		case(3):
			return;
		}
	}
}

void menu_insercao(Empresa &empresa)
{
	while (true)
	{
		cout << "-------------" << empresa.getNome() << "------------" << endl
			<< "O que pretende inserir na base de dados?" << endl
			<< "1. Novo Utente" << endl
			<< "2. Nova Escola" << endl
			<< "3. Novo Motorista" << endl
			<< "4. Antigo Motorista" << endl
			<< "5. Novo Veiculo" << endl
			<< "6. Nova Oficina" << endl
			<< "7. Voltar ao Menu Principal" << endl;

		switch(respostaNumeros(1,7)){
		case 1:
			adicicionar_utente(empresa);
			break;
		case 2:
			inserir_escola(empresa);
			break;
		case 3:
			inserir_motorista(empresa);
			break;
		case 4:
			inserir_antigo_motorista(empresa);
			break;
		case 5:
			adicicionar_veiculo(empresa);
			break;
		case 6:
			inserir_oficina(empresa);
			break;
		case 7:
			return;
		}
	}
}

void menu_remocao(Empresa &empresa)
{
	while (true)
	{
		cout << "-------------" << empresa.getNome() << "------------" << endl
			<< "O que pretende remover da base de dados?" << endl
			<< "1. Remover Utente" << endl
			<< "2. Remover Escola" << endl
			<< "3. Remover Motorista" << endl
			<< "4. Remover Veiculo" << endl
			<< "5. Remover Oficina" << endl
			<< "6. Voltar ao Menu Principal" << endl;
		switch(respostaNumeros(1,6)){
		case 1:
			remover_utente(empresa);
			break;
		case 2:
			remover_escola(empresa);
			break;
		case 3:
			remover_motorista(empresa);
			break;
		case 4:
			remover_veiculo(empresa);
			break;
		case 5:
			remover_oficina(empresa);
			break;
		case 6:
			return;
		}
	}
}

void menu_edicao(Empresa &empresa)
{
	while (true)
	{
		cout << "-------------" << empresa.getNome() << "------------" << endl
			<< "Qual dos seguintes elementos pretende editar?" << endl
			<< "1. Utentes" << endl
			<< "2. Escolas" << endl
			<< "3. Motoristas" << endl
			<< "4. Veiculos" << endl
			<< "5. Oficinas" << endl
			<< "6. Voltar ao Menu Principal" << endl;
		switch(respostaNumeros(1,6)){
		case 1:
			alterar_utente(empresa);
			break;
		case(2):
			alterar_escola(empresa);
			break;
		case 3:
			alterar_motorista(empresa);
			break;
		case 4:
			alterar_veiculo(empresa);
			break;
		case 5:
			alterar_oficina(empresa);
			break;
		case 6:
			return;
		}
	}
}

void menu_visualizacao(Empresa &empresa)
{
	while (true)
	{
		cout << "-------------" << empresa.getNome() << "------------" << endl
			<< "Qual dos elementos da base de dados pretende visualizar?" << endl
			<< "1. Mostrar Utentes" << endl
			<< "2. Mostrar Escolas" << endl
			<< "3. Mostrar Motoristas" << endl
			<< "4. Mostrar Veiculos" << endl
			<< "5. Mostrar Oficinas" << endl
			<< "6. Voltar ao Menu Principal" << endl;
		switch(respostaNumeros(1,6)){
		case 1:
			mostrar_utentes(empresa);
			break;
		case 2:
			mostrar_escolas(empresa);
			break;
		case 3:
			mostrar_motoristas(empresa);
			break;
		case 4:
			mostrar_veiculos(empresa);
			break;
		case 5:
			mostrar_oficinas(empresa);
			break;
		case 6:
			return;
		}
	}
}

void menu_trabalho(Empresa &empresa)
{
	while (true)
	{
		cout << "-------------" << empresa.getNome() << "------------" << endl
			 << "Escolha o que pretende fazer na Empresa:" << endl
			 << "1. Alterar preco das zonas" << endl
			 << "2. Calcular o valor do passe mensal de um utente" << endl
			 << "3. Atualizar o valor dos passes mensais no registo" << endl
			 << "4. Alocar um utente para o transporte escolar" << endl
			 << "5. Alocar todos os utentes para os transportes escolares" << endl
			 << "6. Alugar trasnporte recreativo por um dia" << endl
			 << "7. Despedir um motorista" << endl
			 << "8. Reparar um veiculo" << endl
			 << "9. Processar o final do dia de hoje" << endl
			 << "10. Processar o final deste mes" << endl
			 << "11. Mostrar a tabela do valor dos passes" << endl
			 << "12. Mostrar a tabela de alocacao de utentes por veiculo" << endl
			 << "13. Mostrar os lucros mensais deste ano" << endl
			 << "14. Mostrar os balancos diarios deste mes" << endl
			 << "15. Mostrar a matriz de precos por zona" << endl
			 << "16. Voltar ao Menu Princiapl" << endl;
		switch (respostaNumeros(1,16)){
		case 1:
			alterar_precoZonas(empresa);
			break;
		case 2:
			calcula_um_passe(empresa);
			break;
		case 3:
			calcula_todos_passes(empresa);
			break;
		case 4:
			alocar_um_utente(empresa);
			break;
		case 5:
			alocar_todos_utentes(empresa);
			break;
		case 6:
			alugar_recreativo(empresa);
			break;
		case 7:
			despedir_motorista(empresa);
			break;
		case 8:
			reparar_veiculo(empresa);
			break;
		case 9:
			processar_dia(empresa);
			break;
		case 10:
			processar_mes(empresa);
			break;
		case 11:
			mostrar_tab_passes(empresa);
			break;
		case 12:
			mostrar_tab_alocacao(empresa);
			break;
		case 13:
			mostrar_lucros_mensais(empresa);
			break;
		case 14:
			mostrar_registo_diario(empresa);
			break;
		case 15:
			mostrar_precos(empresa);
			break;
		case 16:
			return;
		}
	}
}

void menu_principal(Empresa &empresa)
{
	while (true)
	{
		cout << "-------------" << empresa.getNome() << "------------" << endl
			<< "Qual dos seguintes menus da empresa pretende aceder?" << endl
			<< "1. Menu de insercao na base de dados" << endl
			<< "2. Menu de remocao da base de dados" << endl
			<< "3. Menu de edicao da base de dados" << endl
			<< "4. Menu de visualizacao da base de dados" << endl
			<< "5. Menu de trabalho e gesta da empresa" << endl
			<< "6. Sair" << endl;
		switch (respostaNumeros(1,6)){
		case 1:
			menu_insercao(empresa);
			break;
		case 2:
			menu_remocao(empresa);
			break;
		case 3:
			menu_edicao(empresa);
			break;
		case 4:
			menu_visualizacao(empresa);
			break;
		case 5:
			menu_trabalho(empresa);
			break;
		case 6:
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

	menu_principal(empresa);

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

		menu_principal(empresa);

		return empresa;
	}
	else
	{
		Empresa empresa("Nao criada");

		return empresa;
	}
}

void resetIDs()
{
	Veiculo::numVeiculos = 0;
	Utente::ult_numUtente = 0;
}

void sair(Empresa &empresa)
{
	resetIDs();

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

			cout << emp;

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

			cout << emp;

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
