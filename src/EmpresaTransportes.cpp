#include "EmpresaTransportes.h"

Empresa::Empresa(string nome) :
		escolas(Escola("", 0, "", "", 0)) {
	nome_empresa = nome;
	precoPessoa = -1;
	lucrosMensais = vector<double>(12, -1);
}

Empresa::Empresa(ifstream &f) :
		escolas(Escola("", 0, "", "", 0)) {
	carregarInfo(f);
}

Empresa::Empresa(string nome, vector<Utente *> vUt, vector<Veiculo *> vVeic,
		unsigned int precoPessoa, ifstream &fprecos) :
		escolas(Escola("", 0, "", "", 0)) {
	nome_empresa = nome;
	utentes = vUt;
	veiculos = vVeic;
	this->precoPessoa = precoPessoa;
	setPrecos(fprecos);
	lucrosMensais = vector<double>(12, -1);
}

vector<Veiculo*> Empresa::getVeiculos() const {
	return veiculos;
}

vector<Utente*> Empresa::getUtentes() const {
	return utentes;
}

unsigned int Empresa::getPrecoPessoa() const {
	return precoPessoa;
}

vector<vector<double>> Empresa::getPrecos() const {
	return precos_zona;
}

void Empresa::setUtentes(vector<Utente *> vUt) {
	utentes = vUt;
}

void Empresa::setVeiculos(vector<Veiculo *> vVeic) {
	veiculos = vVeic;
}

void Empresa::setPrecoPessoa(unsigned int precoP) {
	precoPessoa = precoP;
}

void Empresa::setPrecos(istream &fprecos) {
	vector<double> lineVals;
	string line, number;
	double value;
	size_t i;
	int lineCount = -1;

	precos_zona.clear();

	while (getline(fprecos, line)) {
		if (lineCount != -1) {
			i = line.find_first_of('\t');
			i++;
			while (true) {
				while (isdigit(line[i]) || line[i] == '.' || line[i] == ',') {
					number += line[i];
					i++;
				}

				value = stod(number);
				number.clear();
				lineVals.push_back(value);

				if (line[i] == '\t') {
					i++;
				} else {
					break;
				}
			}

			precos_zona.push_back(lineVals);
			lineVals.clear();
		}

		lineCount++;
	}
}

void Empresa::setPrecos(const vector<vector<double>> &vet) {
	precos_zona.clear();

	precos_zona = vet;
}

void Empresa::adicionarVeiculo(Veiculo *vc) {
	for (size_t i = 0; i < veiculos.size(); i++) {
		if (veiculos[i]->getMatricula() == vc->getMatricula()) {
			Veiculo::numVeiculos--;
			throw VeiculoJaExiste(veiculos[i]->getMatricula());
		}
	}

	veiculos.push_back(vc);
	sort(veiculos.begin(), veiculos.end(), CmpId());
}

void Empresa::adicionarUtente(Utente *ut) {
	for (size_t i = 0; i < utentes.size(); i++) {
		if (utentes[i]->getBI() == ut->getBI()) {
			Utente::ult_numUtente--;
			throw UtenteJaExiste(utentes[i]->getNumUtente());
		}
	}

	utentes.push_back(ut);
	sort(utentes.begin(), utentes.end(), CmpId());
}

void Empresa::removerVeiculo(unsigned int id) {
	for (size_t i = 0; i < veiculos.size(); i++) {
		if (veiculos[i]->getId() == id) {
			veiculos.erase(veiculos.begin() + i);
			alocaUtentes();
			if (removeVeiculoMotoristas(id))
				cout << "Veiculo removido com sucesso dos motoristas";
			return;
		}
	}

	throw VeiculoNaoExistente();

}

void Empresa::removerVeiculo(string matricula) {
	for (size_t i = 0; i < veiculos.size(); i++) {
		if (veiculos[i]->getMatricula() == matricula) {
			veiculos.erase(veiculos.begin() + i);
			alocaUtentes();
			removeVeiculoMotoristas(veiculos[i]->getId());
			return;
		}
	}

	throw VeiculoNaoExistente();
}

void Empresa::removerUtente(unsigned int numUt) {
	for (size_t i = 0; i < utentes.size(); i++) {
		if (utentes[i]->getNumUtente() == numUt) {
			if (tabelaPasses.find(utentes[i]->getNumUtente())
					!= tabelaPasses.end())
				tabelaPasses.erase(utentes[i]->getNumUtente());
			if (tabelaPassageiros.find(utentes[i]->getNumUtente())
					!= tabelaPassageiros.end())
				tabelaPassageiros.erase(utentes[i]->getNumUtente());

			utentes.erase(utentes.begin() + i);
			return;
		}
	}
	throw UtenteNaoExistente();
}

void Empresa::removerUtente(string BI) {
	for (size_t i = 0; i < utentes.size(); i++) {
		if (utentes[i]->getBI() == BI) {
			if (tabelaPasses.find(utentes[i]->getNumUtente())
					!= tabelaPasses.end())
				tabelaPasses.erase(utentes[i]->getNumUtente());
			if (tabelaPassageiros.find(utentes[i]->getNumUtente())
					!= tabelaPassageiros.end())
				tabelaPassageiros.erase(utentes[i]->getNumUtente());

			utentes.erase(utentes.begin() + i);
			return;
		}
	}

	throw UtenteNaoExistente();
}

void Empresa::adicionarZonaEscolar(unsigned int idV, unsigned int zona) {
	for (size_t i = 0; i < veiculos.size(); i++) {
		if (veiculos[i]->getId() == idV) {
			if (veiculos[i]->getCapacidade() != 0) {
				throw VeiculoNaoEscolar();
			} else {
				veiculos[i]->adicionarZona(zona);
				alocaUtentes();
				return;
			}
		}
	}

	throw VeiculoNaoExistente();
}

void Empresa::removerZonaEscolar(unsigned int idV, unsigned int zona) {
	for (size_t i = 0; i < veiculos.size(); i++) {
		if (veiculos[i]->getId() == idV) {
			if (veiculos[i]->getCapacidade() != 0) {
				throw VeiculoNaoEscolar();
			} else {
				veiculos[i]->removerZona(zona);
				alocaUtentes();
				return;
			}
		}
	}

	throw VeiculoNaoExistente();
}

void Empresa::alterarZonaHab(unsigned int numUtente, unsigned int zona) {
	for (size_t i = 0; i < utentes.size(); i++) {
		if (utentes[i]->getNumUtente() == numUtente) {
			utentes[i]->setZonaHabitacao(zona);
			if (tabelaPasses.find(utentes[i]->getNumUtente())
					!= tabelaPasses.end())
				atualizarPasses();
			if (tabelaPassageiros.find(utentes[i]->getNumUtente())
					!= tabelaPassageiros.end())
				alocaUtentes();
			return;
		}
	}

	throw UtenteNaoExistente();
}

void Empresa::alterarZonaEsc(unsigned int numUtente, unsigned int zona) {
	for (size_t i = 0; i < utentes.size(); i++) {
		if (utentes[i]->getNumUtente() == numUtente) {
			utentes[i]->setZonaEscola(zona);
			if (tabelaPasses.find(utentes[i]->getNumUtente())
					!= tabelaPasses.end())
				atualizarPasses();
			if (tabelaPassageiros.find(utentes[i]->getNumUtente())
					!= tabelaPassageiros.end())
				alocaUtentes();
			return;
		}
	}
	throw UtenteNaoExistente();
}

void Empresa::alterarContacto(unsigned int numUtente, unsigned int cont) {
	for (size_t i = 0; i < utentes.size(); i++) {
		if (utentes[i]->getNumUtente() == numUtente) {
			utentes[i]->setContacto(cont);
			return;
		}
	}
	throw UtenteNaoExistente();
}

unsigned int Empresa::getContacto(unsigned int numUtente) {
	for (size_t i = 0; i < utentes.size(); i++) {
		if (utentes[i]->getNumUtente() == numUtente) {
			return utentes[i]->getContacto();
		}
	}

	throw UtenteNaoExistente();
}

unsigned int Empresa::getContacto(string BI) {
	for (size_t i = 0; i < utentes.size(); i++) {
		if (utentes[i]->getBI() == BI) {
			return utentes[i]->getContacto();
		}
	}

	throw UtenteNaoExistente();
}

double Empresa::calculoPasseMensal(unsigned int numUtente) {
	unsigned int zona1;
	unsigned int zona2;

	size_t i;

	for (i = 0; i < utentes.size(); i++) {
		if (utentes[i]->getNumUtente() == numUtente) {
			zona1 = utentes[i]->getZonaHabitacao();
			zona2 = utentes[i]->getZonaEscola();
			break;
		}
	}

	if (i == utentes.size()) {
		throw UtenteNaoExistente();
	}

	return precos_zona[zona1 - 1][zona2 - 1];
}

void Empresa::atualizarPasses() {
	tabelaPassageiros.clear();

	for (unsigned int i = 0; i < utentes.size(); i++) {
		unsigned int num = utentes[i]->getNumUtente();
		tabelaPasses.insert(
				pair<unsigned int, double>(num, calculoPasseMensal(num)));
	}
}

void Empresa::atualizarPrecos(double delta) {
	for (size_t i = 0; i < precos_zona.size(); i++) {
		for (size_t j = 0; j < precos_zona[i].size(); j++) {
			precos_zona[i][j] += delta;
		}
	}

	atualizarPasses();
}

double Empresa::calcularAluguer(unsigned int idV) {
	size_t i;
	for (i = 0; i < veiculos.size(); i++) {
		if (veiculos[i]->getId() == idV) {
			if (veiculos[i]->getCapacidade() == 0) {
				throw VeiculoNaoRecreativo();
			} else {
				break;
			}
		}
	}

	if (i == veiculos.size()) {
		throw VeiculoNaoExistente();
	} else if (precoPessoa == -1) {
		throw PrecoNaoDefinido();
	}
	return precoPessoa * veiculos[i]->getCapacidade();
}

string Empresa::verificaDispRecreativo(unsigned int capacidade) {
	stringstream strst;
	vector<unsigned int> aux;

	for (size_t i = 0; i < veiculos.size(); i++) {
		if (veiculos[i]->getCapacidade() != 0) //E Recreativo
		{
			if (!veiculos[i]->getEstado() && !veiculos[i]->getReparacao()
					&& veiculos[i]->getCapacidade() >= capacidade)
			{
				aux.push_back(veiculos[i]->getId());
				aux.push_back(veiculos[i]->getCapacidade());
			}
		}
	}

	if (aux.size() == 0)
		strst << "Nao existe nenhum veiculo disponivel com essa capacidade."
				<< endl;
	else {
		strst << "Veiculos que pode alugar:" << endl;
		for (size_t i = 0; i <= aux.size() / 2; i += 2) {
			strst << "ID: " << aux[i] << "\tCapacidade: " << aux[i + 1]
					<< "\tPreco: " << calcularAluguer(aux[i]) << endl;
		}
	}

	return strst.str();
}

void Empresa::alugaRecreativo(unsigned int idV) {
	size_t i;

	for (i = 0; i < veiculos.size(); i++) {
		if (veiculos[i]->getId() == idV) {
			if (veiculos[i]->getCapacidade() == 0) {
				throw VeiculoNaoRecreativo();
			} else if (veiculos[i]->getReparacao()) {
				throw VeiculoEmReparacao();
			} else
				break;
		}
	}

	if (i == veiculos.size()) {
		throw VeiculoNaoExistente();
	} else {
		veiculos[i]->setEstado(true);
	}
}

void Empresa::alocaUtentes() {
	tabelaPassageiros.clear();

	for (size_t i = 0; i < utentes.size(); i++) {
		for (size_t j = 0; j < veiculos.size(); j++) {
			if (veiculos[j]->existeZona(utentes[i]->getZonaEscola())
					&& veiculos[j]->existeZona(utentes[i]->getZonaHabitacao())
					&& !veiculos[j]->cheio() && !veiculos[j]->getReparacao()) {
				tabelaPassageiros.insert(
						pair<unsigned int, unsigned int>(
								utentes[i]->getNumUtente(),
								veiculos[j]->getId()));
				veiculos[j]->reduzLug();
				break;
			} else if (j == veiculos.size() - 1)
				throw VeiculosInsuficientes();
		}
	}
}

unsigned int Empresa::alocaUt(unsigned int numUt) {
	for (size_t i = 0; i < utentes.size(); i++) {
		if (utentes[i]->getNumUtente() == numUt) {
			for (size_t j = 0; j < veiculos.size(); j++) {
				if (veiculos[j]->existeZona(utentes[i]->getZonaEscola())
						&& veiculos[j]->existeZona(utentes[i]->getZonaHabitacao())
						&& !veiculos[j]->cheio() && !veiculos[j]->getReparacao()) {
					tabelaPassageiros.insert(
							pair<unsigned int, unsigned int>(numUt,
									veiculos[j]->getId()));
					veiculos[j]->reduzLug();
					return veiculos[j]->getId();
				} else if (j == veiculos.size() - 1)
					throw VeiculosInsuficientes();
			}
		}
	}

	throw UtenteNaoExistente();
}

bool Empresa::finalDia(float kmsZona) {
	double sum = 0;
	string str = "";

	for (size_t i = 0; i < veiculos.size(); i++) {
		if (veiculos[i]->getCapacidade() == 0) //Nao e recreativo
		{
			if(!veiculos[i]->getReparacao())
				sum -= veiculos[i]->calcGasto(kmsZona);
		}
		else //E recreativo
		{
			if (veiculos[i]->getEstado()) {
				float kms;
				veiculos[i]->setEstado(false);

				cout << "Quantos kms percorreu o veiculo (recreativo) n "
						<< veiculos[i]->getId() << "? ";
				cin >> kms;

				sum -= veiculos[i]->calcGasto(kms);
				sum += calcularAluguer(veiculos[i]->getId());
			}
		}
	}

	finalDiaOficinas();

	if (registoDiario.size() <= 31) {
		registoDiario.push_back(sum);
		return true;
	} else
		return false;
}

bool Empresa::calculoMensal() {
	double sumPasses = 0;
	double sumDiarios = 0;

	for (map<unsigned int, double>::iterator it = tabelaPasses.begin();
			it != tabelaPasses.end(); it++) {
		sumPasses += it->second;
	}

	for (size_t i = 0; i < registoDiario.size(); i++) {
		sumDiarios = registoDiario[i];
	}

	registoDiario.clear();

	size_t j;

	for (j = 0; j < lucrosMensais.size(); j++) {
		if (lucrosMensais[j] == -1) {
			lucrosMensais[j] = sumPasses + sumDiarios;
			return false;
		}
	}

	if (j == lucrosMensais.size()) {
		cout << "Chegou ao fim do ano! Eis os lucros deste ano que passou:"
				<< endl << showMensal();
		lucrosMensais.clear();
		return true;
	}

	return false;
}

void Empresa::guardarInfo(ostream &ficheiro) const {
	size_t i;

	ficheiro << "//empresa" << endl << nome_empresa << endl;

	ficheiro << "//escolas" << endl;

	BSTItrIn<Escola> itr(escolas);

	while (!itr.isAtEnd())
	{
		ficheiro << itr.retrieve() << endl;

		itr.advance();
	}

	ficheiro << "//utentes" << endl;

	for (i = 0; i < utentes.size(); i++) {
		ficheiro << *utentes[i] << endl;
	}

	ficheiro << "//motoristas" << endl;

	if (!(motoristas.empty())) {
		tabHMotorista::const_iterator it = motoristas.begin();

		Motorista motorista = *it;

		while (it != motoristas.end()) {
			motorista = *it;

			ficheiro << motorista.getNome() << "\t" << "Estado do contracto:\t";
			cout << "motorsta: " << motorista.getNome() << endl;

			if (motorista.getAtual())
				ficheiro << "+ativo";
			else
				ficheiro << "-nao ativo";

			list<unsigned> veic = motorista.getVeiculos();

			list<unsigned>::iterator v = veic.begin();

			while (v != veic.end()) {
				ficheiro << "\t" << *v;
				v++;
			}
			ficheiro << endl;

			it++;
		}
	}

	ficheiro << "//veiculos" << endl;

	for (i = 0; i < veiculos.size(); i++) {
		ficheiro << *veiculos[i] << endl;
	}

	ficheiro << "//precos" << endl << precoPessoa << endl << '\t';

	for (i = 0; i < precos_zona.size(); i++) {
		ficheiro << 'Z' << i + 1;

		if (i != precos_zona.size() - 1)
			ficheiro << '\t';
		else
			ficheiro << endl;
	}

	for (i = 0; i < precos_zona.size(); i++) {
		ficheiro << 'Z' << i + 1;

		for (size_t j = 0; j < precos_zona[i].size(); j++) {
			ficheiro << '\t' << precos_zona[i][j];
		}
		ficheiro << endl;
	}

	ficheiro << "//lucros" << endl << '{';

	for (i = 0; i < lucrosMensais.size(); i++) {
		if (i == lucrosMensais.size() - 1)
			ficheiro << lucrosMensais[i] << '}' << endl;
		else
			ficheiro << lucrosMensais[i] << ',';
	}

	ficheiro << "//diarios" << endl << '{';

	for (i = 0; i < registoDiario.size(); i++) {
		if (i == registoDiario.size() - 1)
			ficheiro << registoDiario[i];
		else
			ficheiro << registoDiario[i] << ',';
	}

	ficheiro << '}';
}

void Empresa::carregarInfo(ifstream &f) {
	char seletor;
	bool precoP = true;
	string line, aux;
	vector<string> atributos;
	stringstream str;
	string nome = " lool";
	bool atual = false;
	list<unsigned> veic;

	while (getline(f, line)) {
		if (line == "//empresa")
			seletor = 'e';
		else if (line == "//escolas")
			seletor = 's';
		else if (line == "//utentes")
			seletor = 'u';
		else if (line == "//veiculos")
			seletor = 'v';
		else if (line == "//precos")
			seletor = 'p';
		else if (line == "//lucros")
			seletor = 'l';
		else if (line == "//diarios")
			seletor = 'd';
		else if (line == "//motoristas")
			seletor = 'm';
		else {
			cout << "seletor: " << seletor << endl;
			switch (seletor) {
			case 'e':
				nome_empresa = line.substr(0, line.length());
				break;
			case 's':
			{
				unsigned zona, codigo;

				for (size_t i = 0; i <= line.length(); i++)
				{
					if (line[i] == '\t' || i == line.length()) {
						atributos.push_back(aux);
						aux.clear();
					} else {
						aux += line[i];
					}
				}

				codigo = stoul(atributos[1]);
				zona = stoul(atributos[4]);

				escolas.insert(Escola(atributos[0], codigo, atributos[2], atributos[3], zona));

				break;
			}
			case 'u':
			{
				for (size_t i = 0; i <= line.length(); i++) {

					if (line[i] == '\t' || i == line.length()) {
						atributos.push_back(aux);
						aux.clear();
					} else {
						aux += line[i];
					}
				}
				if (atributos[7] == "funcionario(a)")
				{
					Utente* ut = new Funcionario(atributos[0], atributos[1],
							atributos[2], stoul(atributos[4]),
							stoul(atributos[5]), false,
							stoul(atributos[8]));

					InsereUtenteEscola(stoul(atributos[6]), ut);
					ut->setCodEscola(stoul(atributos[6]));

					utentes.push_back(ut);
				}
				else if (atributos[7] == "docente")
				{
					Utente* ut = new Funcionario(atributos[0], atributos[1],
							atributos[2], stoul(atributos[4]),
							stoul(atributos[5]), true,
							stoul(atributos[8]));

					InsereUtenteEscola(stoul(atributos[6]), ut);
					ut->setCodEscola(stoul(atributos[6]));

					utentes.push_back(ut);
				}
				else
				{
					Utente* ut = new Crianca(atributos[0], atributos[1],
							atributos[2], stoul(atributos[4]),
							stoul(atributos[5]), atributos[7],
							stoul(atributos[8]));

					InsereUtenteEscola(stoul(atributos[6]), ut);
					ut->setCodEscola(stoul(atributos[6]));

					utentes.push_back(ut);
				}
				atributos.resize(0);
				break;
			}
			case 'v':
			{
				for (size_t i = 0; i <= line.length(); i++) {
					if (line[i] == '\t' || i == line.length()) {
						atributos.push_back(aux);
						aux.clear();
					} else {
						aux += line[i];
					}
				}
				if (atributos[5] == "livre")
					veiculos.push_back(
							new Recreativo(atributos[1], stof(atributos[2]),
									stof(atributos[3]), stoul(atributos[4]),
									false));
				else if (atributos[5] == "alugado")
					veiculos.push_back(
							new Recreativo(atributos[1], stof(atributos[2]),
									stof(atributos[3]), stoul(atributos[4]),
									true));
				else {
					vector<unsigned int> vecZonas;
					string str = atributos[5];
					for (size_t i = 1; i < str.length(); i++) {
						if (isdigit(str[i])) {
							aux += str[i];
						} else {
							vecZonas.push_back(stoul(aux));
							aux.clear();
						}
					}

					veiculos.push_back(
							new Escolar(atributos[1], stof(atributos[2]),
									stof(atributos[3]), stoul(atributos[4]),
									vecZonas));
				}
				atributos.resize(0);
				break;
			}
			case 'p':
			{
				if (precoP) {
					precoPessoa = stof(line);
					precoP = false;
				} else
					str << line << endl;
				break;
			}
			case 'l':
			{
				this->setPrecos(str);
				for (size_t i = 1; i <= line.length() - 1; i++) {
					if (isdigit(line[i]) || line[i] == '-' || line[i] == '.') {
						aux += line[i];
					} else {
						lucrosMensais.push_back(stod(aux));
						aux.clear();
					}
				}
				break;
			}
			case 'd':
			{
				for (size_t i = 1; i <= line.length() - 1; i++) {
					if (isdigit(line[i]) || line[i] == '-' || line[i] == '.') {
						aux += line[i];
					} else {
						registoDiario.push_back(stod(aux));
						aux.clear();
					}
				}
				break;
			}
			case 'm':
			{
				unsigned int counter=0;
				int number=0;
				nome.clear();

				for (;line[counter]!='\t';counter++)//le o nome ate encontrar um tab
				{
					nome +=line[counter];
				}


				for (;counter<line.length()-1;counter++)//le ate encontrar um mais(esta contratado) ou um menos
				{
					if(line[counter]=='+')
					{
						atual=true;
						break;
					}
					else if(line[counter]=='-')
					{
						atual=false;
						break;
					}
				}

				veic.clear();//da clear aos veiculos

				cout<<line<<endl;
				for(;counter<=line.length();counter++)
					{
						if(line[counter]=='\t')
						{
							veic.push_back(number);//se for um digito coloca o id na lista de veiculos
							cout<<"line "<<number<<endl;
							number=0;
						}
						if(isdigit(line[counter]))
							{
								number*=10;
								number+=((int)line[counter]-48);
							}
					}

				veic.push_back(number);//se for um digito coloca o id na lista de veiculos				cout<<"donne"<<endl;

				Motorista motorista(nome, atual, veic);//cria o motorista

				motoristas.insert(motorista);

				nome.clear();
				veic.clear();
				counter=0;
				break;
			}
			default:
				return;
			}
		}
	}

	atualizarPasses();
}

string Empresa::showUtentes() const {
	ostringstream out;

	out << endl << "///////////Utentes//////////" << endl;

	for (size_t i = 0; i < utentes.size(); i++) {
		out << endl << "Utente n" << utentes[i]->getNumUtente() << " :" << endl
				<< "Nome: " << utentes[i]->getNome() << "; Data de Nascimento: "
				<< utentes[i]->getData_Nasc() << "; BI: " << utentes[i]->getBI()
				<< endl << "Zona de habitacao: Z"
				<< utentes[i]->getZonaHabitacao() << "; Zona de escola: Z"
				<< utentes[i]->getZonaEscola() << endl;
		if (utentes[i]->getNomeEE() == "") //E funcionario
				{
			if (utentes[i]->getDocente())
				out << "Ocupacao: Docente; Contacto: "
						<< utentes[i]->getContacto() << endl;
			else
				out << "Ocupacao: Funcionario; Contacto: "
						<< utentes[i]->getContacto() << endl;
		} else //E crianca
		{
			out << "Nome E.Educacao: " << utentes[i]->getNomeEE()
					<< "; Contacto do E.Educacao: " << utentes[i]->getContacto()
					<< endl;
		}
	}

	return out.str();
}

string Empresa::showVeiculos() const {
	ostringstream out;

	out << endl << "///////////Veiculos//////////" << endl;

	for (size_t i = 0; i < veiculos.size(); i++) {
		out << endl << "Veiculo n" << veiculos[i]->getId() << " :" << endl
				<< "Matricula: " << veiculos[i]->getMatricula()
				<< "; Consumo p/ 100Km: " << veiculos[i]->getConsumo()
				<< "; Preco p/L de combustivel: " << veiculos[i]->getPreco()
				<< "; Em Reparacao: ";

		if(veiculos[i]->getReparacao())
			out << "Sim" << endl;
		else
			out << "Nao" << endl;

		if (veiculos[i]->getCapacidade() == 0) {
			out << "Lugares livres: " << veiculos[i]->getLugsLivres()
					<< "; Zonas atravessadas:";
			vector<unsigned int> zonas = veiculos[i]->getZonas();
			for (size_t j = 0; j < zonas.size(); j++) {
				out << " Z" << zonas[j];
			}
			out << endl;
		} else {
			out << "Capacidade: " << veiculos[i]->getCapacidade()
					<< "; Estado: ";
			if (veiculos[i]->getEstado())
				out << "Alugado" << endl;
			else
				out << "Livre" << endl;
		}
	}

	return out.str();
}

string Empresa::showTabPasses() const {
	stringstream out;

	out << endl << "////////Tabela de Passes/////////" << endl
			<< "Utente\t->\tValor" << endl;

	for (map<unsigned int, double>::const_iterator it = tabelaPasses.begin();
			it != tabelaPasses.end(); it++) {
		out << " " << it->first << "\t->\t " << it->second << endl;
	}

	return out.str();
}

string Empresa::showTabPassag() const {
	stringstream out;

	out << endl << "////////Tabela de Passageiros/////////" << endl
			<< "Utente\t->\tVeiculo" << endl;

	for (map<unsigned int, unsigned int>::const_iterator it =
			tabelaPassageiros.begin(); it != tabelaPassageiros.end(); it++) {
		out << " " << it->first << "\t->\t " << it->second << endl;
	}

	return out.str();
}

string Empresa::showMensal() const {
	ostringstream out;

	string aux[] = { "Janeiro", "Fevereiro", "Marco", "Abril", "Maio", "Junho",
			"Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro" };

	out << endl << "///////Lucros Mensais///////" << endl;
	for (size_t i = 0; i < lucrosMensais.size(); i++) {
		out << aux[i] << ": ";
		if (lucrosMensais[i] == -1)
			out << "Nao Registado" << endl;
		else
			out << lucrosMensais[i] << " euros" << endl;
	}

	return out.str();
}

string Empresa::showDiario() const {
	ostringstream out;

	out << endl << "///////Registos Diarios///////" << endl;

	for (size_t i = 0; i < registoDiario.size(); i++) {
		out << "Dia " << i + 1 << ": " << registoDiario[i] << " euros" << endl;
	}

	return out.str();
}

string Empresa::showPrecos() const {
	ostringstream out;
	size_t i;

	out << endl << "///////Matrix de Precos///////" << endl << '\t';

	for (i = 0; i < precos_zona.size(); i++) {
		out << 'Z' << i + 1;

		if (i != precos_zona.size() - 1)
			out << '\t';
		else
			out << endl;
	}

	for (i = 0; i < precos_zona.size(); i++) {
		out << 'Z' << i + 1;

		for (size_t j = 0; j < precos_zona[i].size(); j++) {
			out << '\t' << precos_zona[i][j];
		}
		out << endl;
	}

	return out.str();
}

ostream& operator <<(ostream& out, const Empresa &emp) {
	emp.guardarInfo(out);

	return out;
}

//=======================================================
bool Empresa::checkOficina(const Oficina& ofc) {
	bool flag = false;
	vector<Oficina> aux;

	while (!oficinas.empty()) {
		if (oficinas.top() == ofc) {
			flag = true;
			break;
		} else {
			aux.push_back(oficinas.top());
			oficinas.pop();
		}
	}

	for (size_t i = 0; i < aux.size(); i++) {
		oficinas.push(aux[i]);
	}

	return flag;
}

void Empresa::editOficina(string nm, double newVal, bool dist) {
	vector<Oficina> aux;
	Oficina ofc(nm);
	Oficina temp;
	bool flag = false;

	while (!oficinas.empty()) {
		if (oficinas.top() == ofc) {
			temp = oficinas.top();
			oficinas.pop();
			flag = true;
			break;
		}
		aux.push_back(oficinas.top());
		oficinas.pop();
	}

	if (dist && flag) { //o valor a ser alterado e a distancia
		temp.setDist(newVal);
		oficinas.push(temp);
	} else if (!dist && flag) { //o valor a ser alterado e a disponibilidade
		temp.setDisp(newVal);
		oficinas.push(temp);
	}

	for (size_t i = 0; i < aux.size(); i++) {
		oficinas.push(aux[i]);
	}
}

bool Empresa::insertOficina(const Oficina& ofc) {
	if (!checkOficina(ofc)) {
		oficinas.push(ofc);
		return true;
	} else
		return false;
}

bool Empresa::removeOficina(const Oficina& ofc) {
	vector<Oficina> aux;
	bool retVal = false;

	while (!oficinas.empty()) {
		if (oficinas.top() == ofc) {
			oficinas.pop();
			retVal = true;
			break;
		} else {
			aux.push_back(oficinas.top());
			oficinas.pop();
		}
	}

	for (size_t i = 0; i < aux.size(); i++) {
		oficinas.push(aux[i]);
	}

	return retVal;
}

Oficina Empresa::repararVeiculo(unsigned int id, double dist_max) {
	vector<Oficina> aux;
	Oficina temp;
	size_t i;

	while (!oficinas.empty()) {
		if (oficinas.top().getDist() <= dist_max) {
			temp = oficinas.top();
			oficinas.pop();

			for (i = 0; i < veiculos.size(); i++) {
				if (veiculos[i]->getId() == id)
					break;
			}
			break;
		}

		aux.push_back(oficinas.top());
		oficinas.pop();
	}

	for (size_t j = 0; j < aux.size(); j++) {
		oficinas.push(aux[j]);
	}

	if(i == veiculos.size()){
		oficinas.push(temp);
		throw VeiculoNaoExistente();
	}
	else if (!oficinas.empty() && !veiculos[i]->getReparacao()) {
		temp.reparacao(id);
		oficinas.push(temp);
		veiculos[i]->setReparacao(true);
		alocaUtentes();
	}
	else{
		oficinas.push(temp);
		temp = Oficina();
	}

	return temp;
}

void Empresa::finalDiaOficinas() {
	vector<Oficina> aux;

	while (!oficinas.empty()) {
		Oficina temp = oficinas.top();
		unsigned int id = temp.fimReparacao();
		if(id != 0){
			for (unsigned int i = 0; i < veiculos.size(); i++) {
				if (veiculos[i]->getId() == id)
					veiculos[i]->setReparacao(false);
			}
		}
		aux.push_back(temp);
		oficinas.pop();
	}

	for (size_t i = 0; i < aux.size(); i++) {
		oficinas.push(aux[i]);
	}
}

string Empresa::showOficinas()
{
	stringstream out;
	vector<Oficina> aux;
	unsigned int counter = 0;

	out << endl << "////////Fila de Oficinas/////////" << endl;

	while(!oficinas.empty())
	{
		counter++;
		out << "Posicao n " << counter << ":" << endl
			<< "Nome: " << oficinas.top().getNome() << "; Disponivel daqui a " << oficinas.top().getDisp() << " dias" << endl
			<< "Distancia da garagem: " << oficinas.top().getDist() << " kms" << endl
			<< "Veiculos em reparacao:";

		queue<unsigned int> fila = oficinas.top().getFila();

		while (!fila.empty())
		{
			out << ' ' << fila.front();
			fila.pop();
		}

		out << endl << endl;

		aux.push_back(oficinas.top());
		oficinas.pop();
	}

	for(size_t i = 0; i < aux.size(); i++)
		oficinas.push(aux[i]);

	return out.str();
}

//===============================================================
bool Empresa::contratarNovoMotorista(string nome, list<unsigned> veiculos) {
	Motorista motorista(nome, true);

	motorista.inserirVeiculos(veiculos);

	motoristas.insert(motorista);

	return true;
}

bool Empresa::inserirAntigoMotorista(string nome) {
	Motorista m(nome);

	pair<tabHMotorista::iterator, bool> res = motoristas.insert(m);

	return res.second;
}

bool Empresa::inserirVeiculo(string nome, unsigned id) {
	if (motoristas.empty())
		return false;

	tabHMotorista::iterator it = motoristas.begin();

	while (it != motoristas.end()) {
		if ((*it).getNome() == nome) {
			break;
		}
	}

	if (it == motoristas.end())
		return false;

	Motorista motorista = *it;

	if (motorista.getVeiculos().size() >= 5) {
		cout
				<< "Nao e possivel inserir o veiculo pois exede o limite maximo de veiculos por motorista"
				<< endl;
		return false;
	}

	motoristas.erase(it);

	motorista.inserirVeiculo(id);

	motoristas.insert(motorista);

	return true;
}

bool Empresa::inserirVeiculos(string nome, list<unsigned> veiculos) {
	if (motoristas.empty())
		return false;

	tabHMotorista::iterator it = motoristas.begin();

	while (it != motoristas.end()) {
		if ((*it).getNome() == nome) {
			break;
		}

		it++;
	}

	if (it == motoristas.end())
		return false;

	Motorista motorista = *it;

	if (motorista.getVeiculos().size() >= 5)
		return false;

	motoristas.erase(it);

	motorista.inserirVeiculos(veiculos);

	motoristas.insert(motorista);

	return true;
}
bool Empresa::removerVeiculo(string nome, unsigned id) {
	if (motoristas.empty())
		return false;

	tabHMotorista::iterator it = motoristas.begin();

	while (it != motoristas.end()) {
		if ((*it).getNome() == nome) {
			break;
		}

		it++;
	}

	if (it == motoristas.end()) {
		cout << "O motorista que inserio nao existe" << endl;

		return false;
	}

	Motorista motorista = *it;

	motoristas.erase(it);

	motorista.removerVeiculo(id);

	motoristas.insert(motorista);

	return true;
}

bool Empresa::removerMotorista(string nome) {
	if (motoristas.empty())
		return false;

	tabHMotorista::iterator it = motoristas.begin();

	while (it != motoristas.end()) {
		if ((*it).getNome() == nome) {
			break;
		}

		it++;
	}

	if (it == motoristas.end()) {
		cout << "O motorista que inserio nao existe" << endl;
		return false;
	}

	motoristas.erase(it);

	return true;
}

bool Empresa::mostrar_nome_motoristas() {
	if (motoristas.empty()) {
		cout << "Nao ha motoristas no sistema" << endl;

		return false;
	}

	tabHMotorista::iterator it = motoristas.begin();

	Motorista motorista = *it;

	while (it != motoristas.end()) {
		cout << "Motorista: " << it->getNome() << "  Estado do contrato: ";

		motorista = *it;

		if (motorista.getAtual())
			cout << "Ativo" << endl;
		else
			cout << "Nao Ativo" << endl;

		motorista.mostrar_veiculos();

		it++;
	}

	return true;
}

bool Empresa::averiguar_motoristas(unsigned id) {
	if (motoristas.empty()) {
		cout << "Nao ha motoristas no sistema";
		return false;
	}

	tabHMotorista::iterator it = motoristas.begin();
	tabHMotorista::iterator it1 = motoristas.end();

	Motorista motorista = *it;

	while (it != motoristas.end()) {
		motorista = *it;

		if (!motorista.getAtual()) //se nao estiver contratado
		{
			it1 = it;

			it++;

			continue;
		}

		else {
			it++;

			list<unsigned> veiculos = motorista.getVeiculos();

			if (find(veiculos.begin(), veiculos.end(), id) == veiculos.end()
					&& (veiculos.size() < 5)) //garantir que o veiculo ja nao existe no motorista
					{
				motoristas.erase(motorista);

				motorista.inserirVeiculo(id);

				motoristas.insert(motorista);

				return true;
			}

		}

	}
	//se nao houver motoristas contratados disponiveis
	if (it1 == motoristas.end()) {
		return false;
	} else {
		motorista = *(it1);

		motoristas.erase(it1);

		motorista.contratar(id);

		motoristas.insert(motorista);

		return true;
	}
	return false;
}

bool Empresa::despedir_motorista(string nome) {
	if (motoristas.empty()) {
		cout << "Nao ha motoristas no sistema";
		return false;
	}

	tabHMotorista::iterator it = motoristas.begin();

	while (it != motoristas.end()) {

		if (it->getNome() == nome)
			break;

		it++;
	}

	if (it == motoristas.end()) {
		cout << "O motorista nao existe" << endl;

		return false;
	}

	Motorista motorista = *it;

	motoristas.erase(it);

	motorista.despedir();

	motoristas.insert(motorista);

	return true;
}

int Empresa::nr_restante_veiculos(string nome) {
	if (motoristas.empty()) {
		cout << "Nao ha motoristas no sistema";
		return 6;
	}

	tabHMotorista::iterator it = motoristas.begin();

	while (it != motoristas.end()) {

		if (it->getNome() == nome)
			break;

		it++;
	}

	if (it == motoristas.end()) {
		cout << "O motorista nao existe" << endl;

		return 6;
	}

	Motorista motorista = *it;

	return motorista.nr_veiculos_por_inserir();
}

bool Empresa::remover_Veiculo(unsigned id) {
	if (motoristas.empty())
		return true;

	tabHMotorista::iterator it = motoristas.begin();

	list<unsigned> veiculos;

	while (it != motoristas.end()) {
		Motorista motorista = *it;

		if (motorista.getAtual()) //se possuir veiculos
		{
			motoristas.erase(*it);

			motorista.removerVeiculo(id);

			motoristas.insert(motorista);
		}

		it++;
	}

	return true;
}

bool Empresa::removeVeiculoMotoristas(unsigned id) {
	if (motoristas.empty())
		return false;

	tabHMotorista::iterator it = motoristas.begin();

	list<unsigned> veiculos;

	while (it != motoristas.end()) {
		Motorista motorista = *it;

		motoristas.erase(motorista);

		motorista.removerVeiculo(id);

		motoristas.insert(motorista);

		it++;
	}

	return true;
}
//===============================================================

pair<bool, Escola> Empresa::verificaEscola(unsigned codigo) {
	BSTItrIn<Escola> itr(escolas);

	Escola null("", 0, "", "", 0);

	pair<bool, Escola> par(false, null);

	while (!itr.isAtEnd()) {
		if (itr.retrieve().getCodigo() == codigo) {
			par.first = true;
			par.second = itr.retrieve();
			return par;
		}

		itr.advance();
	}

	return par;
}

void Empresa::adicionaEscola(Escola &esc) {
	escolas.insert(esc);
}

vector<Utente*> Empresa::removeEscola(Escola &esc) {
	vector<Utente*> temp = esc.getUtentes();

	escolas.remove(esc);

	return temp;
}

pair<bool, Escola> Empresa::encontraEscolaUtente(Utente &ut) {

	unsigned codigo = ut.getCodEscola();

	return verificaEscola(codigo);
}

void Empresa::InsereUtenteEscola(unsigned codigo, Utente *ut) {
	pair<bool, Escola> res = verificaEscola(codigo);

	if (res.first) {
		if (ut->getZonaEscola() == res.second.getZona()) {
			ut->setCodEscola(codigo);

			Escola aux = res.second;

			aux.addUtente(ut);

			escolas.remove(res.second);

			escolas.insert(aux);
		} else
			throw ZonasIncompativeis();
	} else
		throw EscolaNaoExistente();
}

void Empresa::RemoveUtenteEscola(Utente *ut) {
	pair<bool, Escola> res = encontraEscolaUtente(*ut);

	if (res.first) {
		ut->setCodEscola(0);

		Escola aux = res.second;

		aux.removeUtente(ut);

		escolas.remove(res.second);

		escolas.insert(aux);
	} else
		throw EscolaNaoExistente();
}

string Empresa::getEscolas() {
	ostringstream s;

	for (unsigned zona = 1; zona <= this->getUtentes().size(); zona++) {
		s << "======= z" << zona << " =======" << endl;

		BSTItrIn<Escola> itr(escolas);

		while (!itr.isAtEnd()) {
			if (itr.retrieve().getZona() == zona) {
				s << itr.retrieve().getCodigo() << '\t'
						<< itr.retrieve().getNome() << '\t'
						<< itr.retrieve().getDiretorInfo().first << '\n';
			}

			itr.advance();
		}

		s << endl;
	}

	return s.str();
}

string Empresa::getEscolasZona(unsigned zona) {
	BSTItrIn<Escola> itr(escolas);

	ostringstream s;

	while (!itr.isAtEnd()) {
		if (itr.retrieve().getZona() == zona) {
			s << itr.retrieve().getCodigo() << '\t' << itr.retrieve().getNome()
					<< '\n';
		}

		itr.advance();
	}

	return s.str();
}

