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

void adiciona_utente()
{

}

void remove_utente()
{

}

void modifica_utente()
{

}

void adiciona_veiculo()
{

}

void remove_veiculo()
{

}

void modifica_veiculo()
{

}

void sair()
{
	cout << "deseja sair sem guardar ou guardar e sair?" << endl;
}

void display_opcoes()
{
	cout << endl <<"1. Adicionar utente" << setw(5) << "2. Remover utente" << setw(5) << "3. Modificar utente" << endl
		 << "4. Adicionar veÃ­culo" << setw(5) << "5. Remover veÃ­culo" << setw(5) << "6. Modificar VeÃ­culo" << endl
		 << "7. Sair" << endl;
}

void tratamento_opcoes(char opcao)
{
	switch(opcao)
	{
	case 1:
		adiciona_utente();
		break;
	case 2:
		remove_utente();
		break;
	case 3:
		modifica_utente();
		break;
	case 4:
		adiciona_veiculo();
		break;
	case 5:
		remove_veiculo();
		break;
	case 6:
		modifica_veiculo();
		break;
	case 7:
		sair();
	}
}

bool interface()
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
}

int main(/*int argc, char const *argv[]*/)
{
    /*return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;*/

	//interface();
	ifstream f;

	f.open("emp.txt");

	Empresa emp(f);

	f.close();

	return 0;


}
