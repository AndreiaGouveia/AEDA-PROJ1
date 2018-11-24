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
			Veiculo::numVeiculos--;
			throw VeiculoJaExiste(veiculos[i]->getMatricula());
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
			Utente::ult_numUtente--;
			throw UtenteJaExiste(utentes[i]->getNumUtente());
		}
	}

	utentes.push_back(ut);
	sort(utentes.begin(),utentes.end(),CmpId());
}

void Empresa::removerVeiculo(unsigned int id)
{
	for(size_t i = 0; i < veiculos.size(); i++)
	{
		if(veiculos[i]->getId() == id)
		{
			veiculos.erase(veiculos.begin() + i);
			return;
		}
	}

	throw VeiculoNaoExistente();
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

	throw VeiculoNaoExistente();
}

void Empresa::removerUtente(unsigned int numUt)
{
	for(size_t i = 0; i < utentes.size(); i++)
	{
		if(utentes[i]->getNumUtente() == numUt)
		{
			utentes.erase(utentes.begin() + i);
			return;
		}
	}
	throw UtenteNaoExistente();
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

	throw UtenteNaoExistente();
}

void Empresa::adicionarZonaEscolar(unsigned int idV, unsigned int zona)
{
	for(size_t i = 0; i < veiculos.size(); i++)
	{
		if(veiculos[i]->getId() == idV)
		{
			if(veiculos[i]->getCapacidade() != 0)
			{
				throw VeiculoNaoEscolar();
			}
			else
			{
				veiculos[i]->adicionarZona(zona);
				return;
			}
		}
	}

	throw VeiculoNaoExistente();
}

void Empresa::removerZonaEscolar(unsigned int idV, unsigned int zona)
{
	for(size_t i = 0; i < veiculos.size(); i++)
	{
		if(veiculos[i]->getId() == idV)
		{
			if(veiculos[i]->getCapacidade() != 0)
			{
				throw VeiculoNaoEscolar();
			}
			else
			{
				veiculos[i]->removerZona(zona);
				return;
			}
		}
	}

	throw VeiculoNaoExistente();
}

void Empresa::alterarZonaHab(unsigned int numUtente, unsigned int zona)
{
	for(size_t i = 0; i < utentes.size(); i++)
	{
		if(utentes[i]->getNumUtente() == numUtente)
		{
			utentes[i]->setZonaHabitacao(zona);
			return;
		}
	}

	throw UtenteNaoExistente();
}

void Empresa::alterarZonaEsc(unsigned int numUtente, unsigned int zona)
{
	for(size_t i = 0; i < utentes.size(); i++)
	{
		if(utentes[i]->getNumUtente() == numUtente)
		{
			utentes[i]->setZonaEscola(zona);
			return;
		}
	}
	throw UtenteNaoExistente();
}

void Empresa::alterarContacto(unsigned int numUtente, unsigned int cont)
{
	for(size_t i = 0; i < utentes.size(); i++)
	{
		if(utentes[i]->getNumUtente() == numUtente)
		{
			utentes[i]->setContacto(cont);
			return;
		}
	}
	throw UtenteNaoExistente();
}

unsigned int Empresa::getContacto(unsigned int numUtente)
{
	for(size_t i = 0; i < utentes.size(); i++)
	{
		if(utentes[i]->getNumUtente() == numUtente)
		{
			return utentes[i]->getContacto();
		}
	}

	throw UtenteNaoExistente();
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

	throw UtenteNaoExistente();
}

double Empresa::calculoPasseMensal(unsigned int numUtente)
{
	unsigned int zona1;
	unsigned int zona2;

	size_t i;

	for(i = 0; i < utentes.size(); i++)
	{
		if(utentes[i]->getNumUtente() == numUtente)
		{
			zona1 = utentes[i]->getZonaHabitacao();
			zona2 = utentes[i]->getZonaEscola();
			break;
		}
	}

	if(i == utentes.size())
	{
		throw UtenteNaoExistente();
	}

	return precos_zona[zona1-1][zona2-1];
}

void Empresa::atualizarPasses()
{
	for(unsigned int i = 0; i < utentes.size(); i++)
	{
		unsigned int num = utentes[i]->getNumUtente();
		tabelaPasses.insert(pair<unsigned int, double>(num,calculoPasseMensal(num)));
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

double Empresa::calcularAluguer(unsigned int idV)
{
	size_t i;
	for(i = 0; i < veiculos.size(); i++)
	{
		if(veiculos[i]->getId() == idV)
		{
			if(veiculos[i]->getCapacidade() == 0)
			{
				throw VeiculoNaoRecreativo();
			}
			else
			{
				break;
			}
		}
	}

	if(i == veiculos.size())
	{
		throw VeiculoNaoExistente();
	}
	else if(precoPessoa == -1)
	{
		throw PrecoNaoDefinido();
	}
	return precoPessoa * veiculos[i]->getCapacidade();
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

void Empresa::alugaRecreativo(unsigned int idV)
{
	size_t i;

	for(i = 0; i < veiculos.size(); i++)
	{
		if(veiculos[i]->getId() == idV)
		{
			if(veiculos[i]->getCapacidade() == 0)
			{
				throw VeiculoNaoRecreativo();
			}
			else
			{
				break;
			}
		}
	}

	if(i == veiculos.size())
	{
		throw VeiculoNaoExistente();
	}
	else
	{
		veiculos[i]->setEstado(true);
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
				throw VeiculosInsuficientes();
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
					throw VeiculosInsuficientes();
			}
		}
	}

	throw UtenteNaoExistente();
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

bool Empresa::calculoMensal()
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
			return false;
		}
	}

	if(j == lucrosMensais.size())
	{
		cout << "Chegou ao fim do ano! Eis os lucros do ano passado:" << showMensal() << endl;
		return true;
	}

	return false;
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

string Empresa::showUtentes() const
{
	ostringstream out;

	out << endl << "///////////Utentes//////////" << endl;

	for (size_t i = 0; i < utentes.size(); i++) {
		out << endl << "Utente n�" << utentes[i]->getNumUtente() << " :" << endl
				<< "Nome: " << utentes[i]->getNome() << "; Data de Nascimento: " << utentes[i]->getData_Nasc()<< "; BI: " << utentes[i]->getBI() << endl
				<< "Zona de habitacao: Z" << utentes[i]->getZonaHabitacao() << "; Zona de escola: Z" << utentes[i]->getZonaEscola() << endl;
		if(utentes[i]->getNomeEE() == "") //E funcionario
		{
			if(utentes[i]->getDocente())
				out << "Ocupacao: Docente; Contacto: " << utentes[i]->getContacto() << endl;
			else
				out << "Ocupacao: Funcionario; Contacto: " << utentes[i]->getContacto() << endl;
		}
		else //E crianca
		{
			out << "Nome E.Educacao: " << utentes[i]->getNomeEE() << "; Contacto do E.Educacao: " << utentes[i]->getContacto() << endl;
		}
	}

	return out.str();
}

string Empresa::showVeiculos() const
{
	ostringstream out;

	out << endl << "///////////Veiculos//////////" << endl;

	for (size_t i = 0; i < veiculos.size(); i++) {
		out << endl << "Veiculo n�" << veiculos[i]->getId() << " :" << endl
				<< "Matricula: " << veiculos[i]->getMatricula() << "; Consumo p/ 100Km: " << veiculos[i]->getConsumo()
				<< "; Preco p/L de combustivel: " << veiculos[i]->getPreco() << endl;

		if(veiculos[i]->getCapacidade() == 0)
		{
			out << "Lugares livres: " << veiculos[i]->getLugsLivres() << "; Zonas atravessadas:";
			vector<unsigned int> zonas = veiculos[i]->getZonas();
			for (size_t j = 0; j < zonas.size(); j++) {
				out << " Z" << zonas[i];
			}
			out << endl;
		}
		else
		{
			out << "Capacidade: " << veiculos[i]->getCapacidade() << "; Estado: ";
			if(veiculos[i]->getEstado())
				out << "Alugado" << endl;
			else
				out << "Livre" << endl;
		}
	}

	return out.str();
}

string Empresa::showMensal() const
{
	ostringstream out;

	string aux[] = {"Janeiro","Fevereiro","Marco","Abril","Maio","Junho","Julho","Agosto","Setembro","Outubro","Novembro","Dezembro"};

	out << endl << "///////Lucros Mensais///////" << endl;
	for(size_t i = 0; i < lucrosMensais.size(); i++)
	{
		out << aux[i] << ": ";
		if(lucrosMensais[i] == -1)
			out << "Nao Registado" << endl;
		else
			out << lucrosMensais[i] << "�" << endl;
	}

	return out.str();
}

string Empresa::showDiario() const
{
	ostringstream out;

	out << endl << "///////Registos Diarios///////" << endl;

	for(size_t i = 0; i < registoDiario.size(); i++)
	{
		out << "Dia " << i + 1 << ": " << registoDiario[i] << "�" << endl;
	}

	return out.str();
}

ostream& operator <<(ostream& out,const Empresa &emp)
{
	emp.guardarInfo(out);

	return out;
}
