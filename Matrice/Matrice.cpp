#include "Matrice.h"
#include <vector>
#include <iostream>

#define MAXORDRE 10
#define MINORDRE 1

using namespace std;

Matrice::Matrice(unsigned int m, unsigned int n)
{
	if (m > MAXORDRE) {
		cout << "ERREUR : Maximum autorisé à " << MAXORDRE << ".mise en place à " << MAXORDRE << "." << endl;
		m = MAXORDRE;
	}

	if (n > MAXORDRE) {
		cout << "ERREUR : Maximum autorisé à " << MAXORDRE << ".mise en place à " << MAXORDRE << "." << endl;
		n = MAXORDRE;
	}

	if (m < MINORDRE) {
		cout << "ERREUR : Minimum autorisé à " << MINORDRE << ".mise en place à " << MINORDRE << "." << endl;
		m = MINORDRE;
	}

	if (n < MINORDRE) {
		cout << "ERREUR : Minimum autorisé à " << MINORDRE << ".mise en place à " << MINORDRE << "." << endl;
		n = MINORDRE;
	}

	m_m = m;
	m_n = n;
	m_row = new vector<vector<float>>(0);
}

void Matrice::setM(unsigned int p_m)
{
	if (p_m < MINORDRE) {
		cout << "ERREUR : Vous devez entrez un ordre supérieur ou égale à 1!" << endl;
		return;
	}
	else if (p_m > MAXORDRE) {
		cout << "ERREUR : Vous devez entrez un ordre inférieur ou égale à 10!" << endl;
		return;
	}
	
	m_m = p_m;
}

void Matrice::setN(unsigned int p_n)
{
	if (p_n < MINORDRE) {
		cout << "ERREUR : Vous devez entrez un ordre supérieur ou égale à 1!" << endl;
		return;
	}
	else if (p_n > MAXORDRE) {
		cout << "ERREUR : Vous devez entrez un ordre inférieur ou égale à 10!" << endl;
		return;
	}

	m_n = p_n;
}


Matrice::Matrice() {
	m_m = 0;
	m_n = 0;

}


Matrice* Matrice::additionner(Matrice* p_B) {
	if (p_B->getM() != this->m_m) {
		cout << "ERREUR : Les deux matrices doivent avoir le même ordre." << endl;
		return nullptr;

	}

	if (p_B->getN() != this->m_n) {
		cout << "ERREUR : Les deux matrices doivent avoir le même ordre." << endl;
		return nullptr;

	}

	Matrice* temp = new Matrice(this->m_m, this->m_n);

	vector<vector<float>>* data = new vector<vector<float>>(0);

	
	for (unsigned int i = 0; i < (*m_row).size(); i++) {
		vector<float> tempRow(0);
		for (unsigned int j = 0; j < (*m_row)[i].size(); j++) {
			tempRow.push_back((*m_row)[i][j] + (*p_B->getData())[i][j]);
		}
		data->push_back(tempRow);
	}

	temp->setData(data);

}

Matrice* Matrice::multiplier(Matrice* p_B)
{
	if (m_n != p_B->getM()) {
		cout << "ERREUR : Le deuxième ordre doit être similaire que le premier ordre de la deuxième matrice." << endl;
		return nullptr;
	}

	Matrice* temp = new Matrice(m_m, p_B->getN());
	vector<vector<float>>* data = new vector<vector<float>>(m_m, vector<float>(p_B->getN(), 0));

	for (unsigned int i = 0; i < m_m; i++) {
		for (unsigned int j = 0; j < p_B->getN(); j++) {
			for (unsigned int k = 0; k < m_n; k++) {
				(*data)[i][j] += (*m_row)[i][k] * (*(*p_B).getData())[k][j];
			}
		}
	}

	temp->setData(data);
	return temp;
}

float Matrice::determinant()
{
	if (m_m != m_n) {
		cout << "ERREUR : La matrice doit être carrée pour calculer le déterminant." << endl;
		return 0;
	}

	int n = m_m;
	vector<vector<float>> data = *getData();

	if (n == 1) {
		return data[0][0];
	}
	else if (n == 2) {
		return data[0][0] * data[1][1] - data[0][1] * data[1][0];
	}

	float det = 0;
	for (int p = 0; p < n; p++) {
		
		Matrice submatrix(n - 1, n - 1);
		vector<vector<float>> subdata(n - 1, vector<float>(n - 1));
		for (int i = 1; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (j == p) continue;
				int col = (j < p) ? j : j - 1;
				subdata[i - 1][col] = data[i][j];
			}
		}
		submatrix.setData(&subdata);

		// Recursive call
		det += (p % 2 == 0 ? 1 : -1) * data[0][p] * submatrix.determinant();
	}

	return det;
}


std::vector<std::vector<float>>* Matrice::getData()
{
	return m_row;
}

void Matrice::setData(std::vector<std::vector<float>>* p_data)
{
	if (this->m_m != (*p_data).size()) {
		cout << "ERREUR : Les données ne sont pas du même ordre!" << endl;
		return;
	}
	if (this->m_n != (*p_data)[0].size()) {
		cout << "ERREUR : Les données ne sont pas du même ordre!" << endl;
		return;
	}

	m_row = p_data;
}

Matrice* Matrice::transposer()
{
	Matrice* temp = new Matrice(this->m_n, this->m_m);

	vector<vector<float>>* data = new vector<vector<float>>(0);

	float tempFloat[MAXORDRE][MAXORDRE];

	for (int i = 0; i < (*m_row).size(); i++) {
		for (int j = 0; j < (*m_row)[i].size(); j++) {
			tempFloat[j][i] = (*m_row)[i][j];
		}
	}

	for (unsigned int j = 0; j < (*m_row)[0].size(); j++) {
			vector<float> row;
			for (unsigned int i = 0; i < (*m_row).size(); i++) {
				row.push_back(tempFloat[j][i]);
			}

			(*data).push_back(row);

	}

		temp->setData(data);

		return temp;
}

unsigned int Matrice::getM()
{
	return m_m;
}

unsigned int Matrice::getN()
{
	return m_n;
}

void Matrice::afficher()
{
	for (unsigned int i = 0; i < m_m; i++) {
		cout << "[ ";
		for (unsigned int j = 0; j < m_n; j++) {
			cout << (*m_row)[i][j] << " ";
		}
		cout << "]" << endl;
	}
	cout << "Matrice d'ordre : " <<  m_m << " X " << m_n << endl;
}




