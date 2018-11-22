#include "Veiculo.h"

unsigned int Veiculo::numVeiculos = 0;

Veiculo::Veiculo(const string &matricula, float consumo100km, float precoComb) :
				idV(++numVeiculos), matricula(matricula) {
	this->consumo100km = consumo100km;
	this->precoComb = precoComb;
}

unsigned int Veiculo::getId() const {
	return idV;
}

string Veiculo::getMatricula() const {
	return matricula;
}

string Veiculo::getInfo() const {
	ostringstream out;

	out << idV << '\t' << matricula << '\t' << consumo100km << '\t'
			<< precoComb;

	return out.str();
}

ostream& operator <<(ostream& out, const Veiculo& veic) {
	out << veic.getInfo();

	return out;
}

////////////////////////////////////////////////////////////////
//////////////////Transporte  Escolar///////////////////////////
////////////////////////////////////////////////////////////////
Escolar::Escolar(const string &matricula, float consumo100km, float precoComb, unsigned int capacidade, const vector<unsigned int>& zonasAtravessadas = vector<unsigned int>()) :
		Veiculo(matricula, consumo100km, precoComb) {
	lugaresLivres = capacidade;
	this->zonasAtravessadas = zonasAtravessadas;
}

void Escolar::adicionarZona(unsigned int zona) {
	for (size_t i = 0; i < zonasAtravessadas.size(); i++) {
		if (zonasAtravessadas[i] == zona)
			return;
			//throw ZonaJaExistente(zona); TODO ZonaJaExistente
	}

	zonasAtravessadas.push_back(zona);

	sort(zonasAtravessadas.begin(), zonasAtravessadas.end()); //o vector zonasAtravessadas está sempre ordenado
}

void Escolar::removerZona(unsigned int zona) {
	vector<unsigned int>::iterator it = find(zonasAtravessadas.begin(), zonasAtravessadas.end(), zona);

	if (it == zonasAtravessadas.end())
		return;
		//throw ZonaNaoExistente(zona); //TODO ZonaNaoExistente*/

	zonasAtravessadas.erase(it);
}

float Escolar::calcGasto(float kms) const {
	return 2 * zonasAtravessadas.size() * kms * consumo100km / 100.0;
}

string Escolar::getInfo() const {
	ostringstream out;

	out << Veiculo::getInfo() << '\t' << lugaresLivres << '\t' << '{';

	for (size_t i = 0; i < zonasAtravessadas.size(); i++) {
		if (i == zonasAtravessadas.size() - 1)
			out << zonasAtravessadas[i];
		else
			out << zonasAtravessadas[i] << ',';
	}

	out << '}';

	return out.str();
}

ostream& operator <<(ostream& out, const Escolar& veic) {
	out << veic.getInfo();

	return out;
}

////////////////////////////////////////////////////////////////
//////////////////Transporte  Recreativo////////////////////////
////////////////////////////////////////////////////////////////
Recreativo::Recreativo(const string &matricula, float consumo100km, float precoComb, unsigned int cap, bool alugado) :
		Veiculo(matricula, consumo100km, precoComb), capacidade(cap) {
	this->alugado = alugado;
}

unsigned int Recreativo::getCapacidade() const {
	return capacidade;
}

bool Recreativo::getEstado() const {
	return alugado;
}

void Recreativo::setEstado(bool alugado) {
	this->alugado = alugado;
}

float Recreativo::calcGasto(float kms) const {
	return kms * consumo100km / 100.0;
}

string Recreativo::getInfo() const {
	ostringstream out;

	out << Veiculo::getInfo() << '\t' << capacidade << '\t';

	if (alugado)
		out << "alugado";
	else
		out << "livre";

	return out.str();
}

ostream& operator <<(ostream& out, const Recreativo& veic) {
	out << veic.getInfo();

	return out;
}
