#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "EmpresaTransportes.h"
#include <iomanip>

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
/*VerificacaoDeResposta(string &resposta)
{
	if(resposta.size()!=10||resposta.size())
}*/
void adiciona_utente(Empresa &empresa) {
/*cout<<endl<<"O utente que quer inserir uma crianca?"<<endl;
string resposta;
cin>>resposta;
VerificacaoDeResposta(resposta);*/
}

void remove_utente(Empresa &empresa) {

}

void modifica_utente(Empresa &empresa) {

}

void adiciona_veiculo(Empresa &empresa) {

}

void remove_veiculo(Empresa &empresa) {

}

void modifica_veiculo(Empresa &empresa) {

}

void sair() {
	cout <<endl<< "deseja sair sem guardar ou guardar e sair?" << endl;

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
	//////////////////////////////////////
	///PODEMOS TER ISTO OU ALGO MAIS SIMPLES COM 1 2 3 EM TUDO MAS NO ENTANTO O TRATAMENTO DE OPÇOES PODE SER OVERCOMPLICATED?
	/////////////////////////////////////
	////////////DUNNO
	bool invalidOp = true;
	while (invalidOp) {
		if (op.size() > 3) {
			invalidOp = true;
			break;
		} else if (op.size() == 1 && (op[0] >= '1' || op[0] <= '4') && first)//menu geral
				{
			invalidOp = false;
			break;
		} else if (((op.size() == 3
				&& (op[0] == '1' || op[1] != '.' || op[2] >= '1' || op[2] <= '3'))
				|| (op.size() == 1 && (op[0] == '3' || op[0] == '4'))) && inside
				&& !first)	//menu veiculos
				{
			invalidOp = false;
			break;
		} else if (((op.size() == 3
				&& (op[0] == '2' || op[1] != '.' || op[2] >= '1' || op[2] <= '3'))
				|| (op.size() == 1 && (op[0] == '3' || op[0] == '4')))
				&& !inside && !first)	//menu utentes
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
		} else if (opcao == "2") {
			display_Opcoes_Utente();
			//Agora saber o que e que quer fazer
			cin >> opcao;
			valid_Option(opcao, false, false);
			break;
		} else if (opcao == "3") {
			sair();
			again = false;
			break;
		} else if (opcao == "2.1") {
			adiciona_utente(empresa);
			again = false;
			break;
		} else if (opcao == "2.2") {
			remove_utente(empresa);
			again = false;
			break;
		} else if (opcao == "2.3") {
			modifica_utente(empresa);
			again = false;
			break;
		} else if (opcao == "1.1") {
			adiciona_veiculo(empresa);
			again = false;
			break;
		} else if (opcao == "1.2") {
			remove_veiculo(empresa);
			again = false;
			break;
		} else if (opcao == "1.3") {
			modifica_veiculo(empresa);
			again = false;
			break;
		} else if (opcao == "4") {
			display_Opcoes_Geral();
			//Agora saber o que e que quer fazer
			cin >> opcao;
			valid_Option(opcao, true, false);

		}
	}
}

/*bool interface()
 {
 string nome_empresa;

 cout << "////////////////////////////" << endl
 << "///Empresa de Transportes///" << endl
 << "////////////////////////////" << endl;

 cout << endl << "Crie a sua empresa!" << endl;

 cout << "Nome da Empresa: " << endl;

 cin >> nome_empresa;

 Empresa empresa = Empresa(nome_empresa);

 char opcao;

 while(true)
 {
 cout << endl << "O que gostaria de fazer na " << nome_empresa << "?" << endl;

 display_opcoes();

 cin >> opcao;

 if(cin.eof())
 {
 break;
 }

 while(cin.fail() || opcao < '1' || opcao > '7')
 {
 cin.clear();
 cin.ignore(1000, '\n');

 cout << endl << "A opçao que colocou nao e valida. Coloque um numero valido (ou  para rever as opçoes) ";

 cin >> opcao;

 if (opcao == 'H')
 {
 display_opcoes();
 }
 }

 tratamento_opcoes(opcao);
 }

 return 0;
 }*/

int main(/*int argc, char const *argv[]*/) {
	/*return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;*/

	//interface();
	//ifstream f;
	//f.open("emp.txt");
	//Empresa emp(f);
	bool again = true;
	string nome_empresa;

	cout << "////////////////////////////" << endl
			<< "///Empresa de Transportes///" << endl
			<< "////////////////////////////" << endl;

	string answer;
	while (again) {
		cout << endl << "Crie a sua empresa!" << endl;

		cout << "Nome da Empresa: " << endl;

		cin >> nome_empresa;

		cout << "Tem a certeza que esse e o nome pretendido?" << endl;

		cin >> answer;

		while ( (answer != "Y" && answer != "y") && (answer != "N"
				&& answer != "n")) {
			cin.clear();
			cin.ignore(1000, '\n');

			cout << endl
					<< "A opçao que colocou nao e valida. Insira Y(sim) ou N(nao) para confirmar,ou nao o nome que inseriu ";

			cin >> answer;

		}

		if (answer == "Y" || answer == "y")
			break;

	}

	Empresa empresa(nome_empresa);

	string opcao;
	bool first = true, inside = false;//primeira vez e os outros 2 menus ainda nao foram apresntados

///////////////////////////
//1 vez a fazer alteracoes/
///////////////////////////

	while (first) {

		cout << endl << "O que gostaria de fazer na " << nome_empresa << "?"
				<< endl;

		display_Opcoes_Geral();

		cin >> opcao;

		valid_Option(opcao, first, inside);

		tratamento_opcoes(opcao, empresa);

		first = false;
	}

/////////////////////////////////
//Voltar a fazer mais alteraçoes/
/////////////////////////////////

	again = true;
	while (again) {
		//perguntar se quer que isto aconteça
		cout << endl << "Would you like to do more operations?(Y/N)" << endl;
		cin >> answer;

		while (cin.fail() || answer != "Y" || answer != "y" || answer == "N"
				|| answer == "n") {
			cin.clear();
			cin.ignore(1000, '\n');

			cout << endl
					<< "A opçao que colocou nao e valida. Insira Y(sim) ou N(nao) para confirmar,ou nao se quer fazer mais alteracoes";

			cin >> answer;

		}
		//se nao quiser continuar
		if (answer == "N" || answer == "n")
			break;

		//Peguntar o que quer fazer
		cout << endl << "O que gostaria de fazer na " << nome_empresa << "?"
				<< endl;

		display_Opcoes_Geral();

		cin >> opcao;

		valid_Option(opcao, first, inside);

		tratamento_opcoes(opcao, empresa);

	}
	//f.close();
//fim do programa
	cout << endl << "Obrigada" << endl;
	return 0;

}
