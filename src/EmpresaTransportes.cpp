#include "EmpresaTransportes.h"

Empresa::Empresa(string nome) {
	nome_empresa = nome;
}

/*Empresa::Empresa(ifstream &f)
 {
 carregarInfo(f);
 }*/

Empresa::Empresa(string nome, vector<Utente *> vUt, vector<Veiculo *> vVeic,
		ifstream &fprecos) {
	nome_empresa = nome;
	utentes = vUt;
	veiculos = vVeic;
	setPrecos(fprecos);
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

void Empresa::setPrecos(ifstream &fprecos) {
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

void Empresa::guardarInfo(ofstream &f)
{

}

void Empresa::carregarInfo(ifstream &f)
{

}
