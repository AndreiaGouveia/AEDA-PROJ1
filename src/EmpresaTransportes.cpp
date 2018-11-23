#include "EmpresaTransportes.h"

Empresa::Empresa(string nome) {
	nome_empresa = nome;
	precoPessoa = -1;
	lucrosMensais = vector<double>(12, -1);
}

Empresa::Empresa(ifstream &f) {
	carregarInfo(f);
}

Empresa::Empresa(string nome, vector<Utente *> vUt, vector<Veiculo *> vVeic,unsigned int precoPessoa, ifstream &fprecos) {
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

unsigned int Empresa::getPrecoPessoa() const{
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

void Empresa::setPrecoPessoa(unsigned int precoP){
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
	for(size_t i = 0; i < veiculos.size(); i++)
	{
		if(veiculos[i]->getMatricula() == vc->getMatricula())
		{
			//throw VeiculoJaExistente(veiculos[i]->getId(), veiculos[i]->getMatricula());
			cout << "Ja Existe" << endl;
			Veiculo::numVeiculos--;
			return;
		}
	}

	veiculos.push_back(vc);
	sort(veiculos.begin(),veiculos.end(),CmpId());
}

void Empresa::adicionarUtente(Utente *ut) {
	for(size_t i = 0; i < utentes.size(); i++)
	{
		if(utentes[i]->getBI() == ut->getBI())
		{
			//throw UtenteJaExistente(utentes[i]->getNumUtente(), utentes[i]->getBI());
			cout << "Ja Existe" << endl;
			Utente::ult_numUtente--;
			return;
		}
	}

	utentes.push_back(ut);
	sort(utentes.begin(),utentes.end(),CmpId());
}

void Empresa::removerVeiculo(unsigned int id)
{
	veiculos.erase(veiculos.begin() + id - 1);

	//throw VeiculoNaoExistente(id);
}

void Empresa::removerVeiculo(string matricula)
{
	for(size_t i = 0; i < veiculos.size(); i++)
	{
		if(veiculos[i]->getMatricula() == matricula)
		{
			veiculos.erase(veiculos.begin() + i);
			return;
		}
	}

	//throw VeiculoNaoExistente(matricula);
}

void Empresa::removerUtente(unsigned int numUt)
{
	utentes.erase(utentes.begin() + numUt - 1);

	//throw UtenteNaoExistente(id);
}

void Empresa::removerUtente(string BI)
{
	for(size_t i = 0; i < utentes.size(); i++)
	{
		if(utentes[i]->getBI() == BI)
		{
			utentes.erase(utentes.begin() + i);
			return;
		}
	}

	//throw UtenteNaoExistente(BI);
}

void Empresa::adicionarZonaEscolar(unsigned int idV, unsigned int zona)
{
	if(idV > veiculos.size())
		//throw VeiculoNaoExistente(); //TODO VeiculoNaoExistente
		return;
	string info = veiculos[idV-1]->getInfo();

	size_t index = info.find_last_of('\t');
	info = info.substr(index);

	if(info == "livre" || info == "alugado")
	{
		//throw VeiculoNaoEscolar(); //TODO VeiculoNaoEscolar
	}
	else
		veiculos[idV-1]->adicionarZona(zona);
}

void Empresa::removerZonaEscolar(unsigned int idV, unsigned int zona)
{
	if(idV > veiculos.size())
		//throw VeiculoNaoExistente(); //TODO VeiculoNaoExistente
		return;

	string info = veiculos[idV-1]->getInfo();

	size_t index = info.find_last_of('\t');
	info = info.substr(index);

	if(info == "livre" || info == "alugado")
	{
		//throw VeiculoNaoEscolar(); //TODO VeiculoNaoEscolar
	}
	else
		veiculos[idV-1]->removerZona(zona);
}

void Empresa::alterarZonaHab(unsigned int numUtente, unsigned int zona)
{
	if(numUtente > utentes.size())
		//throw UtenteNaoExistente();
		return;

	utentes[numUtente-1]->setZonaHabitacao(zona);
}

void Empresa::alterarZonaEsc(unsigned int numUtente, unsigned int zona)
{
	if(numUtente > utentes.size())
		//throw UtenteNaoExistente();
		return;

	utentes[numUtente-1]->setZonaEscola(zona);
}

void Empresa::alterarContacto(unsigned int numUtente, unsigned int cont)
{
	if(numUtente > utentes.size())
		//throw UtenteNaoExistente();
		return;

	utentes[numUtente-1]->setContacto(cont);
}

unsigned int Empresa::getContacto(unsigned int numUtente)
{
	if(numUtente > utentes.size())
		//throw UtenteNaoExistente();
		return 0;

	return utentes[numUtente-1]->getContacto();
}

unsigned int Empresa::getContacto(string BI)
{
	for(size_t i = 0; i < utentes.size(); i++)
	{
		if(utentes[i]->getBI() == BI)
		{
			return utentes[i]->getContacto();
		}
	}

	return 0;
	//throw UtenteNaoExistente();
}

double Empresa::calculoPasseMensal(unsigned int numUtente)
{
	unsigned int zona1 = utentes[numUtente-1]->getZonaEscola();
	unsigned int zona2 = utentes[numUtente-1]->getZonaHabitacao();

	return precos_zona[zona1-1][zona2-1];
}

void Empresa::atualizarPasses()
{
	for(unsigned int i = 0; i < utentes.size(); i++)
	{
		tabelaPasses.insert(pair<unsigned int, double>(i+1,calculoPasseMensal(i+1)));
	}

	/*testes
	for(map<unsigned int,double>::iterator it = tabelaPasses.begin(); it != tabelaPasses.end(); it++)
	{
		cout << "NumUt= " << it->first << " Passe= " << it->second << "�" << endl;
	}*/
}

void Empresa::atualizarPrecos(double delta) {
	for (size_t i = 0; i < precos_zona.size(); i++) {
		for (size_t j = 0; j < precos_zona[i].size(); j++) {
			precos_zona[i][j] += delta;
		}
	}

	atualizarPasses();
}

double Empresa::calcularAluguer(unsigned int idV)
{
	if(precoPessoa == -1)
	{
		//throw PrecoNaoDefinido(); //TODO PrecoNaoDefinido
	}
	return precoPessoa * veiculos[idV - 1]->getCapacidade();
}

string Empresa::verificaDispRecreativo(unsigned int capacidade)
{
	stringstream strst;
	vector<unsigned int> aux;

	for(size_t i = 0; i < veiculos.size(); i++)
	{
		if(veiculos[i]->getCapacidade() != 0) //� Recreativo
		{
			if(!veiculos[i]->getEstado())
			{
				aux.push_back(veiculos[i]->getId());
				aux.push_back(veiculos[i]->getCapacidade());
			}
		}
	}

	if(aux.size() == 0)
		strst << "Nao existe nenhum veiculo disponivel com essa capacidade.";
	else
	{
		strst << "Veiculos que pode alugar:" << endl;
		for(size_t i = 0; i < aux.size()/2; i+=2)
		{
			strst << "ID: " << aux[i] << "\tCapacidade: " << aux[i + 1] << "\tPreco: " << calcularAluguer(aux[i]) <<endl;
		}
	}

	return strst.str();
}

bool Empresa::alugaRecreativo(unsigned int idV)
{
	if(idV > veiculos.size())
		//throw VeiculoNaoExistente();
		return false;
	else if(veiculos[idV-1]->getCapacidade() == 0)
	{
		//throw VeiculoNaoRecreativo();
		return false;
	}
	else
	{
		veiculos[idV-1]->setEstado(true);
		return true;
	}
}

void Empresa::alocaUtentes()
{
	for(size_t i = 0; i < utentes.size(); i++)
	{
		for(size_t j = 0; j < veiculos.size(); j++)
		{
			if(veiculos[j]->existeZona(utentes[i]->getZonaEscola()) &&
				veiculos[j]->existeZona(utentes[i]->getZonaHabitacao()) && !veiculos[j]->cheio())
			{
				tabelaPassageiros.insert(pair<unsigned int, unsigned int>(utentes[i]->getNumUtente(),veiculos[j]->getId()));
				veiculos[j]->reduzLug();
				break;
			}
			else
				//throw VeiculosInsuficientes(); //TODO VeiculosInsuficientes
				return;
		}
	}
}

void Empresa::alocaUt(unsigned int numUt)
{
	for(size_t i = 0; i < utentes.size(); i++)
	{
		if(utentes[i]->getNumUtente() == numUt)
		{
			for(size_t j = 0; j < veiculos.size(); j++)
			{
				if(veiculos[j]->existeZona(utentes[i]->getZonaEscola()) &&
						veiculos[j]->existeZona(utentes[i]->getZonaHabitacao()) && !veiculos[j]->cheio())
				{
					tabelaPassageiros.insert(pair<unsigned int, unsigned int>(numUt,veiculos[j]->getId()));
					veiculos[j]->reduzLug();
					return;
				}
				else
					//throw VeiculosInsuficientes(); //TODO VeiculosInsuficientes
					return;
			}
		}
	}

	//throw UtenteNaoExistente();
}

bool Empresa::finalDia(float kmsZona)
{
	double sum = 0;
	string str = "";

	for(size_t i = 0; i < veiculos.size(); i++)
	{
		if(veiculos[i]->getCapacidade() == 0) //Nao � recreativo
			sum += veiculos[i]->calcGasto(kmsZona);
		else//� recreativo
		{
			if(veiculos[i]->getEstado())
			{
				float kms;
				veiculos[i]->setEstado(false);

				cout << "Quantos kms percorreu o veiculo (recreativo) n�"
						<< veiculos[i]->getId() << " ?"; cin >> kms;

				sum += veiculos[i]->calcGasto(kms);
				sum += calcularAluguer(veiculos[i]->getId());
			}
		}
	}

	if(registoDiario.size() <= 31){
		registoDiario.push_back(sum);
		return true;
	}
	else
		return false;
}

void Empresa::calculoMensal()
{
	double sumPasses = 0;
	double sumDiarios = 0;

	for(map<unsigned int, double>::iterator it = tabelaPasses.begin(); it != tabelaPasses.end(); it++)
	{
		sumPasses += it->second;
	}

	for(size_t i = 0; i < registoDiario.size(); i++)
	{
		sumDiarios = registoDiario[i];
	}

	registoDiario.clear();

	size_t j;

	for(j = 0; j < lucrosMensais.size(); j++)
	{
		if(lucrosMensais[j] == -1)
		{
			lucrosMensais[j] = sumPasses + sumDiarios;
			return;
		}
	}

	if(j == lucrosMensais.size())
	{
		cout << "Chegou ao fim do ano! Eis os lucros do ano passado:" << endl;
		showMensal();
	}
}

void Empresa::guardarInfo(ostream &f) const {
	size_t i;

	f << "//empresa" << endl << nome_empresa << endl << "//utentes" << endl;

	for (i = 0; i < utentes.size(); i++) {
		f << *utentes[i] << endl;
	}

	f << "//veiculos" << endl;

	for (i = 0; i < veiculos.size(); i++) {
		f << *veiculos[i] << endl;
	}

	f << "//precos" << endl << precoPessoa << endl << '\t';

	for (i = 0; i < precos_zona.size(); i++) {
		f << 'Z' << i + 1;

		if (i != precos_zona.size() - 1)
			f << '\t';
		else
			f << endl;
	}

	for (i = 0; i < precos_zona.size(); i++) {
		f << 'Z' << i + 1;
		for (size_t j = 0; j < precos_zona[i].size(); j++) {
			f << '\t' << precos_zona[i][j];
		}
		f << endl;
	}

	f << "//lucros" << endl << '{';

	for (i = 0; i < lucrosMensais.size(); i++) {
		if (i == lucrosMensais.size() - 1)
			f << lucrosMensais[i] << '}' << endl;
		else
			f << lucrosMensais[i] << ',';
	}

	f << "//diarios" << endl << '{';

	for (i = 0; i < registoDiario.size(); i++) {
		if (i == registoDiario.size() - 1)
			f << registoDiario[i] << '}';
		else
			f << registoDiario[i] << ',';
	}
}

void Empresa::carregarInfo(ifstream &f) {
	char seletor;
	bool precoP = true;
	string line, aux;
	vector<string> atributos;
	stringstream str;

	while (getline(f, line)) {
		if (line == "//empresa")
			seletor = 'e';
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
		else {
			switch (seletor) {
			case 'e':
				nome_empresa = line.substr(0, line.length());
				break;
			case 'u':
				for (size_t i = 0; i <= line.length(); i++) {
					if (line[i] == '\t' || i == line.length()) {
						atributos.push_back(aux);
						aux.clear();
					} else {
						aux += line[i];
					}
				}
				if (atributos[6] == "funcionario(a)")
					utentes.push_back(new Funcionario(atributos[0], atributos[1], atributos[2], stoul(atributos[4]), stoul(atributos[5]), false, stoul(atributos[7])));
				else if (atributos[6] == "docente")
					utentes.push_back(new Funcionario(atributos[0], atributos[1], atributos[2], stoul(atributos[4]), stoul(atributos[5]), true, stoul(atributos[7])));
				else
					utentes.push_back(new Crianca(atributos[0], atributos[1], atributos[2], stoul(atributos[4]), stoul(atributos[5]), atributos[6], stoul(atributos[7])));
				atributos.resize(0);
				break;

			case 'v':
				for (size_t i = 0; i <= line.length(); i++) {
					if (line[i] == '\t' || i == line.length()) {
						atributos.push_back(aux);
						aux.clear();
					} else {
						aux += line[i];
					}
				}
				if (atributos[5] == "livre")
					veiculos.push_back(new Recreativo(atributos[1], stof(atributos[2]), stof(atributos[3]), stoul(atributos[4]), false));
				else if (atributos[5] == "alugado")
					veiculos.push_back(new Recreativo(atributos[1], stof(atributos[2]), stof(atributos[3]), stoul(atributos[4]), true));
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

					veiculos.push_back(new Escolar(atributos[1], stof(atributos[2]), stof(atributos[3]), stoul(atributos[4]), vecZonas));
				}
				atributos.resize(0);
				break;

			case 'p':
				if(precoP){
					precoPessoa = stof(line);
					precoP = false;
				}
				else
					str << line << endl;
				break;

			case 'l':
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

			case 'd':
				for (size_t i = 1; i <= line.length() - 1; i++) {
					if (isdigit(line[i]) || line[i] == '-' || line[i] == '.') {
						aux += line[i];
					} else {
						registoDiario.push_back(stod(aux));
						aux.clear();
					}
				}
				break;
			default:
				return;
			}
		}
	}
	alocaUtentes();
	atualizarPasses();
}

void Empresa::showUtentes() const
{
	cout << endl << "///////////Utentes//////////" << endl;

	for (size_t i = 0; i < utentes.size(); i++) {
		cout << endl << "Utente n�" << utentes[i]->getNumUtente() << " :" << endl
				<< "Nome: " << utentes[i]->getNome() << "; Data de Nascimento: " << utentes[i]->getData_Nasc()<< "; BI: " << utentes[i]->getBI() << endl
				<< "Zona de habitacao: Z" << utentes[i]->getZonaHabitacao() << "; Zona de escola: Z" << utentes[i]->getZonaEscola() << endl;
		if(utentes[i]->getNomeEE() == "") //E funcionario
		{
			if(utentes[i]->getDocente())
				cout << "Ocupacao: Docente; Contacto: " << utentes[i]->getContacto() << endl;
			else
				cout << "Ocupacao: Funcionario; Contacto: " << utentes[i]->getContacto() << endl;
		}
		else //E crianca
		{
			cout << "Nome E.Educacao: " << utentes[i]->getNomeEE() << "; Contacto do E.Educacao: " << utentes[i]->getContacto() << endl;
		}
	}
}

void Empresa::showVeiculos() const{
	cout << endl << "///////////Veiculos//////////" << endl;

	for (size_t i = 0; i < veiculos.size(); i++) {
		cout << endl << "Veiculo n�" << veiculos[i]->getId() << " :" << endl
				<< "Matricula: " << veiculos[i]->getMatricula() << "; Consumo p/ 100Km: " << veiculos[i]->getConsumo()
				<< "; Preco p/L de combustivel: " << veiculos[i]->getPreco() << endl;

		if(veiculos[i]->getCapacidade() == 0)
		{
			cout << "Lugares livres: " << veiculos[i]->getLugsLivres() << "; Zonas atravessadas:";
			vector<unsigned int> zonas = veiculos[i]->getZonas();
			for (size_t j = 0; j < zonas.size(); j++) {
				cout << " Z" << zonas[i];
			}
			cout << endl;
		}
		else
		{
			cout << "Capacidade: " << veiculos[i]->getCapacidade() << "; Estado: ";
			if(veiculos[i]->getEstado())
				cout << "Alugado" << endl;
			else
				cout << "Livre" << endl;
		}
	}
}

void Empresa::showMensal() const
{
	string aux[] = {"Janeiro","Fevereiro","Marco","Abril","Maio","Junho","Julho","Agosto","Setembro","Outubro","Novembro","Dezembro"};

	cout << endl << "///////Lucros Mensais///////" << endl;
	for(size_t i = 0; i < lucrosMensais.size(); i++)
	{
		cout << aux[i] << ": ";
		if(lucrosMensais[i] == -1)
			cout << "Nao Registado" << endl;
		else
			cout << lucrosMensais[i] << "�" << endl;
	}
}

void Empresa::showDiario() const
{
	cout << endl << "///////Registos Diarios///////" << endl;

	for(size_t i = 0; i < registoDiario.size(); i++)
	{
		cout << "Dia " << i + 1 << ": " << registoDiario[i] << "�" << endl;
	}
}

ostream& operator <<(ostream& out,const Empresa &emp) {
	emp.guardarInfo(out);

	return out;
}
