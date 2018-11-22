#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "EmpresaTransportes.h"
#include <iomanip>

using namespace std;
/*void thisIsATest() {
 ASSERTM("start writing tests", false);
 }

 bool runAllTests(int argc, char const *argv[]) {
 cute::suite s { };
 //TODO add your test here
 s.push_back(CUTE(thisIsATest));
 cute::xml_file_opener xmlfile(argc, argv);
 cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
 auto runner = cute::makeRunner(lis, argc, argv);
 bool success = runner(s, "AllTests");
 return success;
 }*/
void checkingOnlyCinFail(unsigned int &answer)
{
	while(cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl<< " Inseriu uma resposta invalida."<< endl;
		cin>>answer;
	}
}
void checkingOnlyCinFailDouble(double &answer)
{
	while(cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl<< " Inseriu uma resposta invalida."<< endl;
		cin>>answer;
	}
}
void checkingOnlyCinFailFLoat(float &answer)
{
	while(cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl<< " Inseriu uma resposta invalida."<< endl;
		cin>>answer;
	}
}
void checkingOnlyCinFailint(int &answer)
{
	while(cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl<< " Inseriu uma resposta invalida."<< endl;
		cin>>answer;
	}
}
void allNumbers(string &answer)//checks if in a string there are only numbers
{
	bool invalidAnswer=true;
	while(invalidAnswer)
	{
		invalidAnswer=false;
		for (int i=0;i<answer.size();i++)
	{
		if(isalpha(answer[i]))
		{
			invalidAnswer=true;
			break;
		}
	}
	if(invalidAnswer)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl<< " Inseriu uma resposta invalida."<< endl;
		cin>>answer;
	}
	else break;}
}
void data_De_Nascimento(string &data_nasc)
{
	bool invalidOp=true;
	while(cin.fail()||invalidOp)
	{
		invalidOp=false;
		if(data_nasc.size()==8)
			{
				for(int i=0;i<data_nasc.size();i++)
				{
					if((i+1)%3 && i<6)//verificar se e '-'
						{
							if(data_nasc[i]!='-')
								{
									invalidOp=true;
									break;//sai do ciclo for
								}

						}
					else if(!isdigit(data_nasc[i]))
						{
							invalidOp=true;
							break;//sai do ciclo for
						}
				}
			}
		if(invalidOp)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << endl<< " Inseriu uma data com o formato errado. Por favor insira uma data com este formato: DD-MM-AAAA"<< endl;
			cin>>data_nasc;
		}
	}

}
void respostaYorN(char &resposta)
{
	while(cin.fail()||(resposta!='y' && resposta!='Y' && resposta!='n' && resposta!='N'))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl<< " Opcao invalida, por favor, volte a inserir uma opcao valida(Y/N)"<< endl;
		cin>>resposta;
	}
}
void display_First_Menu()
{
	cout<<endl<<"Que deseja fazer?"<<endl;
	cout<<"1. Criar uma nova empresa"<<endl;
	cout<<"2. Aceder a uma empresa ja existente"<<endl;
}
void adiciona_utente(Empresa &empresa) {

	//TIRAR INFO COMUM A CRIANCA E AO FUNCIONARIO
	string nome,data_nasc,BI,zonaHabit;
	unsigned int zonaHabit_,zonaEsc;

	//NOME
	cout<<"Qual o nome do novo utente?"<<endl;
	getline(cin,nome);

	//DATA DE NASCIMENTO
	cout<<endl<<"Qual a data de nascimento do utente?"<<endl;
	cin>>data_nasc;
	data_De_Nascimento(data_nasc);

	//BI
	cout<<endl<<"Qual o BI?"<<endl;
	cin>>BI;
	allNumbers(BI);

	//ZONA DE HABITACAO
	cout<<endl<<"Qual a zona onde a habitacao se encontra?"<<endl;
	cin>>zonaHabit;

	//ZONA DA ESCOLA
	cout<<endl<<"Qual a zona onde a escola se encontra?"<<endl;
	cin>>zonaEsc;

	/////////////////////
	//DADOS ESPECIFICOS//
	/////////////////////
	cout<<endl<<"Quer inserir uma crianca?"<<endl;

	char resposta;
	cin>>resposta;
	respostaYorN(resposta);

	if(resposta=='y'||resposta=='Y')
	{
		string nomeEE;
		unsigned int contactoEE;
		/////////////////////////////////
		///Pedir informacao da crianca///
		/////////////////////////////////

		//NOME DO ENCARREGADO DE EDUCACAO
		cout<<endl<<"Qual o nome do encarregado de educacao da crianca?"<<endl;
		getline(cin,nomeEE);

		//CONTACTO DO ENCARREGADO DE EDUCACAO
		cout<<endl<<"Qual o contacto do encarregado de educacao da crianca?"<<endl;
		cin>>contactoEE;
		checkingOnlyCinFail(contactoEE);

		//ADICIONAR A CRIANCA AOS UTENTES
		Crianca c1(nome,data_nasc,BI,zonaHabit_,zonaEsc,nomeEE,contactoEE);
		empresa.adicionarUtente(&c1);
	}
	else
	{
		char resposta;
		bool docente;
		unsigned int contacto;
		///////////////////////////////////
		//Pedir informacao do funcionario//
		///////////////////////////////////

		//DOCENTE
		cout<<"O funcionario que pretende adicionar e docente(Y/N)?"<<endl;
		cin>>resposta;
		respostaYorN(resposta);

		//CONTACTO DO FUNCIONARIO
		cout<<"Qual o contacto do funcionario?"<<endl;
		cin>>contacto;
		checkingOnlyCinFail(contacto);

		//ADICIONAR O FUNCIONARIO AOS UTENTES
		Funcionario f1(nome,data_nasc,BI,zonaHabit_,zonaEsc,docente,contacto);
		empresa.adicionarUtente(&f1);
	}
	//adicionado!! FALTA VER AS EXECOES E ERROS DE INPUT PARA A MAIOR PARTE DAS CENAS
}

void remove_utente(Empresa &empresa) {

	string BI;
	unsigned int num_Utente;
	//Perguntar qual o numero de utente que pretende remover
	cout<<endl<<"Insira o bi do utente( se apenas possuir o numero de utente, insira -1)"<<endl;
	cin>>BI;
	if(BI=="-1")
	{
		cout<<endl<<"Insira o numero do utente"<<endl;
		cin>>num_Utente;

		empresa.removerUtente(num_Utente);
	}
	else
	{
	allNumbers(BI);//checking if BI is corect
	empresa.removerUtente(BI);
	}
			///FALTA A EXECAO SE O UTENTE NAO EXISTIR
			///FALTA TRATAR DAS FALHAS

}

void modifica_utente(Empresa &empresa) {



}

void adiciona_veiculo(Empresa &empresa) {
//const string &matricula, float consumo100km, float precoComb
	string matricula;
	float consumo100km;
	float precoComb;

	//RETIRAR DADOS COMUNS AOS VEICULOS

	//MATRICULA
	cout<<endl<<"Qual a matricula do veiculo que pretende adicionar?"<<endl;
	cin>>matricula; //tem um formato especia??

	//CONSUMO 100 KM
	cout<<endl<<"Qual o consumo por 100km?"<<endl;
	cin>>consumo100km;
	checkingOnlyCinFailFLoat(consumo100km);

	//PRECO COMBUSTIVEL
	cout<<endl<<"Qual o consumo por 100km?"<<endl;
	cin>>precoComb;
	checkingOnlyCinFailFLoat(precoComb);

	///////////////////////////
	//ESPECIFICACAO DO VEICULO/
	///////////////////////////
	char resposta;

	cout<<"O veiculo que pretende adicionar e escolar?"<<endl;
	cin>>resposta;
	respostaYorN(resposta);

	if(resposta=='Y'||resposta=='y')
	{
		unsigned int lugaresLivres;
		vector<unsigned int> zonasAtravessadas;

		//LUGARES LIVRES
		cout<<endl<<"Quantos lugares livres?"<<endl;
		cin>>lugaresLivres;

		//ZONAS ATRAVESSADAS
		cout<<endl<< "Quais sao as zonas que atravessa?"<<endl;
		//	CENAS DE PEEEEEEEEEK E TAL NAO ME LEMBRO OOLOLOLOLOL
	}
	else{
	    int capacidade;
	    bool alugado;
	    char resp;
	    //CAPACIDADE
	    cout<<endl<<"Qual a capacidade do veiculo Recreativo?"<<endl;
	    cin>>capacidade;
	    checkingOnlyCinFailint(capacidade);
	    //ALUGADOS
	    cout<<endl<<"Esta alugado?"<<endl;
	    cin>>resp;
	    respostaYorN(resp);

	    if(resp=='y'||resp=='Y')
	    	alugado=true;
	    else alugado=false;

	    Recreativo r1(matricula,consumo100km,precoComb, capacidade,alugado);
	    empresa.adicionarVeiculo(&r1);

	}
}

void remove_veiculo(Empresa &empresa) {
	string matricula;
	//Perguntar qual a matricula do carro que quer remover
	cout<<endl<<"Insira a matricula do veiculo a remover ( se apenas possuir o id do veiculo, insira -1)"<<endl;
	cin>>matricula;
	if(matricula=="-1")
		{
		empresa.removerVeiculo(matricula);//matricula
		}
	else {
		unsigned int id;
		cout<<endl<<"Insira o id do veiculo que pretende remover"<<endl;
		cin>>id;
		checkingOnlyCinFail(id);

		empresa.removerVeiculo(id);
	}
}

void modifica_veiculo(Empresa &empresa) {

}

void sair(Empresa &empresa) {
	char resposta;
	cout <<endl<< "deseja sair sem guardar ou guardar e sair?" << endl;

	if(resposta=='y'||resposta=='Y')//guardar as alteracoes
	{
	string nome=empresa.getNome()+".txt";//adicionar a extensao .txt
	ofstream nf;
	nf.open(nome);//criar um ficheiro com o nome da empresa
	empresa.guardarInfo(nf);//guardar a informacao
	nf.close();
	exit(0);//sair do programa
	}
	else exit(0);//sair do programa
}

void display_Opcoes_Geral() {
	cout << endl << "1. Alterar Veiculo" << setw(5) << "2. Alterar utente"
			<< setw(5) << endl << "3. Sair" << endl;
}
void display_Opcoes_Veiculo() {
	cout << endl << "1.1. Adicionar veiculo" << setw(5)
			<< "1.2. Remover veiculo" << setw(5) << "1.3. Modificar Veiculo"
			<< endl << "4. Voltar atras" << setw(5) << "3.Sair" << endl;
}
void display_Opcoes_Utente() {
	cout << endl << "2.1. Adicionar utente" << setw(5) << "2.2. Remover utente"
			<< setw(5) << "2.3. Modificar utente" << endl << "4. Voltar atras"
			<< setw(5) << "3. Sair" << endl;
}
void valid_Option(string &op, bool first, bool inside) {

	bool invalidOp = true;
	while (invalidOp) {
		if (op.size() > 3) {
			invalidOp = true;
			break;
		} else if (op.size() == 1 && (op[0] <= '1' || op[0] >= '4') && first)//menu geral
				{
			invalidOp = false;
			break;
		} else if (((op.size() == 3 && (op[0] != '1' || op[1] != '.' || op[2] <= '1' || op[2] >= '3'))|| (op.size() == 1 && (op[0] != '3'&& op[0] != '4'))) && inside && !first)	//menu veiculos
				{
			invalidOp = false;
			break;
		} else if (((op.size() == 3 && (op[0] != '2' || op[1] != '.' || op[2] <= '1' || op[2] >= '3')) || (op.size() == 1 && (op[0] != '3' && op[0] != '4'))) && !inside && !first)	//menu utentes
				{
			invalidOp = false;
			break;
		} else
			invalidOp = true;

		if (invalidOp) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << endl
					<< " Opcao invalida, por favor, volte a inserir uma opcao valida"
					<< endl;
			if (first)
				display_Opcoes_Geral();
			else if (inside)	//se estiver a tratar dos veiculos
				display_Opcoes_Veiculo();
			else
				display_Opcoes_Utente();
			cin >> op;
		}

	}
}
void tratamento_opcoes(string opcao, Empresa &empresa) {
	bool again = true;
	while (again) {
		if (opcao == "1") {
			display_Opcoes_Veiculo();
			//Agora saber o que e que quer fazer
			cin >> opcao;
			valid_Option(opcao, false, true);
			again=true;
		} else if (opcao == "2") {
			display_Opcoes_Utente();
			//Agora saber o que e que quer fazer
			cin >> opcao;
			valid_Option(opcao, false, false);
			again=true;
		} else if (opcao == "3") {
			sair(empresa);
			again = false;
		} else if (opcao == "2.1") {
			adiciona_utente(empresa);
			again = false;
		} else if (opcao == "2.2") {
			remove_utente(empresa);
			again = false;
		} else if (opcao == "2.3") {
			modifica_utente(empresa);
			again = false;
		} else if (opcao == "1.1") {
			adiciona_veiculo(empresa);
			again = false;
		} else if (opcao == "1.2") {
			remove_veiculo(empresa);
			again = false;
		} else if (opcao == "1.3") {
			modifica_veiculo(empresa);
			again = false;
		} else if (opcao == "4") {
			display_Opcoes_Geral();
			//Agora saber o que e que quer fazer
			cin >> opcao;
			valid_Option(opcao, true, false);

		}
	}
}
void default_Handler(Empresa &empresa)
{
	bool first = true, inside = false;
	string opcao;

	display_Opcoes_Geral();

	cin >> opcao;

	valid_Option(opcao, first, inside);

	tratamento_opcoes(opcao, empresa);
}

void main_Handler(Empresa &empresa,string nome_empresa )
{
	char answer;
	while (true) {
			//perguntar se quer que isto aconteça
			cout << endl << "Would you like to do more operations?(Y/N)" << endl;
			cin >> answer;

			respostaYorN(answer);
			//se nao quiser continuar
			if (answer == 'N' || answer == 'n')
				break;

			//Peguntar o que quer fazer
			cout << endl << "O que gostaria de fazer na " << nome_empresa << "?" << endl;

			default_Handler(empresa);

		}
}
Empresa getEmpresa(bool &abertura_por_ficheiro,ifstream &f,string &nome_empresa )
{
	Empresa empresa("teste");//inicializar a empresa
	bool again=true;
	char resposta1;

	while (again)
	{
		    bool back=false; //variavel para voltar atras

			display_First_Menu();
			cin>>resposta1;

			while(cin.fail()||(resposta1 !='1' && resposta1 != '2'))//se a reposta for diferente de 1 ou 2 e se der cin fail, vai voltar a pedir uma resposta
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << endl<< " Opcao invalida, por favor, volte a inserir uma opcao valida(1/2)"<< endl;
				cin >> resposta1;
			}

			switch(resposta1)
			{

			case '1': //caso seja pretendido criar uma empresa nova

			cout << endl << "Crie a sua empresa!" << endl;

			while (true)
			{

			cout<<endl<<"(Se quiser voltar atras insira -1)"<<endl;
			cout<< "Nome da Empresa: " << endl;//pergunta o nome da empresa

			cin >> nome_empresa;
			if(nome_empresa=="-1")//verificar se nao quer voltar para tras
				{
				back=true;
				break;
				}

			cout << "Tem a certeza que " <<nome_empresa<<" e o nome pretendido?(Y/N)" << endl;//verificar se o nome pretendido
			cin >> resposta1;
			respostaYorN(resposta1);

			if(resposta1=='Y'||resposta1=='y')// se sim, entao podemos sair do ciclo e prosseguir com a criacao da empresa
				break;
			}
			if(!back)//se nao quisermos voltar ao menu inicial
		    {
			empresa=Empresa(nome_empresa);//criar a nossa empresa
			again=false;//para sair do ciclo mais tarde, pois ja temos a nossa empresa criada

			//Tratamento da tabela de precos
			char resp;
			cout<<endl<<"Tem um ficheiro com os precos?"<<endl;
			cin>>resp;
			respostaYorN(resp);

			if(resp=='y'||resp=='Y') //se os precos estiverem num ficheiro
			{
				ifstream f;
				string nome_do_ficheiro;
			while(true)
				{
				  cout<<"Qual o nome do ficheiro com precos?(sem .txt no fim) "<<endl;
				  cin>>nome_do_ficheiro;

			      nome_do_ficheiro+=".txt";//adicionar a extensao .txt
			      f.open(nome_do_ficheiro);

		    	if(f.is_open())//se existe ou nao
			      {
					abertura_por_ficheiro=true;
					empresa.setPrecos(f);
					break;
				  }
			    else cout<<"O nome do ficheiro nao existe"<<endl;//se nao existir volta a perguntar o nome do ficheiro
				}
			}
			else{//Como nao estao no ficheiro, o utilizador vai ter de criara sua tabela

				vector<vector<double>> precos; //multi vetores que vai armazenar os precos dados pelo utilizador
				vector<double> temp;
				double preco;
				int zonas;

				//Perguntar quantas zonas
				cout<<"Quantas zonas?"<<endl;
				cin>>zonas;
				checkingOnlyCinFailint(zonas);

				//Criar o nosso multivetor com precos
				for(int i=0;i<zonas;i++)
				{
					for(int j=0;j<zonas;j++)
					{
						cout<<"Qual o preco entre a zona "<<i<<" e "<<j<<" ?"<<endl;
						cin>>preco;
						checkingOnlyCinFailDouble(preco);

						temp.push_back(preco);
					}
					precos.push_back(temp);
					temp.clear();
				}
				empresa.setPrecos(precos);//Agora a empresa tem os precos

		      }
		    }
				break;

			case '2'://caso a empresa ja exista num ficheiro
				string nome_do_ficheiro;
				while(true)
				{
				cout<< endl<<"Qual o nome to ficheiro onde se situa a empresa(sem o .txt no fim)?"<<endl;
				cout<<"Se quiser voltar para tras, insira 1"<<endl;
				cin>>nome_do_ficheiro;

				if(nome_do_ficheiro!="1")//verificar se e preciso voltar para tras ou nao
				{
				    nome_do_ficheiro+=".txt";
				    f.open(nome_do_ficheiro);
					if(f.is_open())//verificar se o ficheiro existe
					{
						abertura_por_ficheiro=true;
						empresa=Empresa(f); //creating our object
						again=false;
						break;
					}
					else cout<<"O nome do ficheiro nao existe"<<endl;
				}
				else back=true;
				if(back)
					break;

				}
				break;
			}

		  }
	return empresa;
}
int main(/*int argc, char const *argv[]*/) {
	/*return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;*/
	ifstream f;
	bool abertura_por_ficheiro=false;// se foi aberto por ficheiro ou nao
	string nome_empresa;

	cout<< "////////////////////////////" << endl
		<< "///Empresa de Transportes///" << endl
		<< "////////////////////////////" << endl;

	Empresa empresa=getEmpresa(abertura_por_ficheiro,f,nome_empresa);
////////////////////////////
//1 vez a fazer alteracoes//
////////////////////////////
	cout << endl << "O que gostaria de fazer na " << nome_empresa << " ?"<< endl;
	default_Handler(empresa);//Handler de primeira utilizacao
/////////////////////////////////
//Voltar a fazer mais alteraçoes/
/////////////////////////////////
	main_Handler(empresa,nome_empresa);

	if(abertura_por_ficheiro)//se a empresa foi criada por um ficheirob
		f.close();
//fim do programa
	cout << endl << "FIM" << endl;
	return 0;

}
