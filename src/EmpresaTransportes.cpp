#include "EmpresaTransportes.h"

Empresa::Empresa(string nome) {
	nome_empresa = nome;
}

Empresa::Empresa(ifstream &f)
{
 carregarInfo(f);
}

Empresa::Empresa(string nome, vector<Utente *> vUt, vector<Veiculo *> vVeic, ifstream &fprecos) {
	nome_empresa = nome;
	utentes = vUt;
	veiculos = vVeic;
	setPrecos(fprecos);
	lucrosMensais = vector<double>(12,-1);
}

vector<Veiculo*> Empresa::getVeiculos() const {
	return veiculos;
}

vector<Utente*> Empresa::getUtentes() const {
	return utentes;
}

vector<vector<double>> Empresa::getPrecos() const {
	return precos;
}

void Empresa::setUtentes(vector<Utente *> vUt) {
	utentes = vUt;
}

void Empresa::setVeiculos(vector<Veiculo *> vVeic) {
	veiculos = vVeic;
}

void Empresa::setPrecos(istream &fprecos) {
	vector<double> lineVals;
	string line, number;
	double value;
	size_t i;
	int lineCount = -1;

	precos.clear();

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
				} else //line[i] == '\n'
				{
					break;
				}
			}

			precos.push_back(lineVals);
			lineVals.clear();
		}

		lineCount++;
	}
}

void Empresa::setPrecos(const vector<vector<double>> &vet){
	precos.clear();

	precos = vet;
}

void Empresa::adicionarVeiculo(Veiculo *vc) {
	veiculos.push_back(vc);
}

void Empresa::adicionaruUtente(Utente *ut) {
	utentes.push_back(ut);
}

void Empresa::atualizarPrecos(double delta) {

	for (size_t i = 0; i < precos.size(); i++) {
		for (size_t j = 0; j < precos[i].size(); j++) {
			precos[i][j] += delta;
		}
	}

}

void Empresa::guardarInfo(ostream &f) const
{
	size_t i;

	f << "//empresa" << endl
			<< nome_empresa << endl
			<< "//utentes" << endl;

	for(i = 0; i < utentes.size(); i++)
	{
		f << *utentes[i] << endl;
	}

	f << "//veiculos" << endl;

	for(i = 0; i < veiculos.size(); i++)
	{
		f << *veiculos[i] << endl;
	}

	f << "//precos" << endl;

	for(i = 0; i < precos.size(); i++)
	{
		for(size_t j = 0; j < precos[i].size(); j++)
		{

		}
	}

	f << "//lucros" << endl
			<< '{';

	for(i = 0; i < lucrosMensais.size(); i++)
	{
		if(i == lucrosMensais.size() - 1)
			f << lucrosMensais[i] << '}' << endl;
		else
			f << lucrosMensais[i] << ',';
	}
}

void Empresa::carregarInfo(ifstream &f)
{
	char seletor;
	string line, aux;
	vector<string> atributos;
	stringstream str;

	while(getline(f,line))
	{
		if(line == "//empresa\n")
		{
			getline(f,line);
			nome_empresa = line.substr(line.length() - 1);
		}
		else if(line == "//utentes\n")
			seletor = 'u';
		else if(line == "//veiculos\n")
			seletor = 'v';
		else if(line == "//precos\n")
			seletor = 'p';
		else if(line == "//lucros\n")
			seletor = 'l';
		else
		{
			switch(seletor)
			{
			case 'u':
				for(size_t i = 0; i < line.length(); i++)
				{
					if(line[i] == '\t')
					{
						atributos.push_back(aux);
						aux.clear();
					}
					else
					{
						aux += line[i];
					}
				}
				if(atributos[6] == "funcionario(a)")
					utentes.push_back(new Funcionario(atributos[0],atributos[1],atributos[2],stoul(atributos[4]),stoul(atributos[5]),false,stoul(atributos[7])));
				else if(atributos[6] == "docente")
					utentes.push_back(new Funcionario(atributos[0],atributos[1],atributos[2],stoul(atributos[4]),stoul(atributos[5]),true,stoul(atributos[7])));
				else
					utentes.push_back(new Crianca(atributos[0],atributos[1],atributos[2],stoul(atributos[4]),stoul(atributos[5]),atributos[6],stoul(atributos[7])));
				break;

			case 'v':
				for(size_t i = 0; i < line.length(); i++)
				{
					if(line[i] == '\t')
					{
						atributos.push_back(aux);
						aux.clear();
					}
					else
					{
						aux += line[i];
					}
				}
				if(atributos[6] == "livre")
					break;
				else if(atributos[6] == "alugado")
					break;
				else
					break;
				break;

			case 'p':
				str << line;
				break;

			case 'l':
				setPrecos(str);
				for(size_t i = 1; i < line.length() - 2; i++)
				{
					if(isdigit(line[i]))
					{
						aux += line[i];
					}
					else
					{
						lucrosMensais.push_back(stod(aux));
						aux.clear();
					}
				}
				break;
			}
		}
	}
}

ostream& operator <<(ostream& out,const Empresa &emp)
{
	emp.guardarInfo(out);

	return out;
}
