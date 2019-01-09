#include "Veiculo.h"

unsigned int Veiculo::numVeiculos = 0;

Veiculo::Veiculo(const string &matricula, float consumo100km, float precoComb, bool emRep) :
				idV(++numVeiculos), matricula(matricula), emReparacao(emRep) {
	this->consumo100km = consumo100km;
	this->precoComb = precoComb;
}

unsigned int Veiculo::getId() const {
	return idV;
}

string Veiculo::getMatricula() const {
	return matricula;
}

float Veiculo::getConsumo() const
{
	return consumo100km;
}

float Veiculo::getPreco() const
{
	return precoComb;
}

string Veiculo::getInfo() const {
	ostringstream out;

	out << idV << '\t' << matricula << '\t' << consumo100km << '\t'
			<< precoComb << '\t';

	if(emReparacao)
		out << "em reparacao";
	else
		out << "na garagem";

	return out.str();
}

ostream& operator <<(ostream& out, const Veiculo& veic) {
	out << veic.getInfo();

	return out;
}

//========================================
bool Veiculo::getReparacao() const
{
	return emReparacao;
}

void Veiculo::setReparacao(bool rep)
{
	this->emReparacao = rep;
}

////////////////////////////////////////////////////////////////
//////////////////Transporte  Escolar///////////////////////////
////////////////////////////////////////////////////////////////
Escolar::Escolar(const string &matricula, float consumo100km, float precoComb, unsigned int capacidade, const vector<unsigned int>& zonasAtravessadas = vector<unsigned int>(), bool emRep) :
		Veiculo(matricula, consumo100km, precoComb, emRep) , lugTotais(capacidade){
	lugaresLivres = capacidade;
	this->zonasAtravessadas = zonasAtravessadas;
}

unsigned int Escolar::getLugsLivres() const
{
	return lugaresLivres;
}

vector<unsigned int> Escolar::getZonas() const
{
	return zonasAtravessadas;
}

void Escolar::adicionarZona(unsigned int zona) {
	for (size_t i = 0; i < zonasAtravessadas.size(); i++) {
		if (zonasAtravessadas[i] == zona)
			throw ZonaJaExistente(zona);
	}

	zonasAtravessadas.push_back(zona);

	sort(zonasAtravessadas.begin(), zonasAtravessadas.end()); //o vector zonasAtravessadas esta sempre ordenado
}

void Escolar::removerZona(unsigned int zona) {
	vector<unsigned int>::iterator it = find(zonasAtravessadas.begin(), zonasAtravessadas.end(), zona);

	if (it == zonasAtravessadas.end())
	{
		throw ZonaNaoExistente(zona);
	}

	zonasAtravessadas.erase(it);
}

bool Escolar::existeZona(unsigned int zona)
{
	return binary_search(zonasAtravessadas.begin(),zonasAtravessadas.end(),zona);
}

float Escolar::calcGasto(float kms) const {
		return 2 * zonasAtravessadas.size() * kms * consumo100km / 100.0;
}

bool Escolar::cheio() const
{
	return lugaresLivres == 0;
}

void Escolar::aumentaLug()
{
	lugaresLivres++;
}

void Escolar::reduzLug()
{
	lugaresLivres--;
}

string Escolar::getInfo() const {
	ostringstream out;

	out << Veiculo::getInfo() << '\t' << lugTotais << '\t' << '{';

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
Recreativo::Recreativo(const string &matricula, float consumo100km, float precoComb, unsigned int cap, bool alugado = false, bool emRep) :
		Veiculo(matricula, consumo100km, precoComb, emRep), capacidade(cap) {
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
