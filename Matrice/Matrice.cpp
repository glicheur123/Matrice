/**
Matrice.cpp
Marc-Antoine Gauthier
Fichier source pour la classe Matrice.

*/
#include "Matrice.h"
#include <vector>
#include <iostream>

// Constantes
#define MAXORDRE 10
#define MINORDRE 1

using namespace std;

/// <summary>
/// Constructeur de la classe matrice.
/// </summary>
/// <param name="m">Nombre de colonnes</param>
/// <param name="n">Nombre de lignes</param>
Matrice::Matrice(unsigned int m, unsigned int n)
{
	// Vérifie que les valeurs soit dans la plage acceptable.
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

	// Instanciation
	m_m = m;
	m_n = n;
	m_row = new vector<vector<float>>(0);
}

/// <summary>
/// Déconstructeur de la classe Matrice.
/// S'assure qu'il n'y a aucune fuite de mémoire.
/// </summary>
Matrice::~Matrice() {
	delete m_row;
}

/// <summary>
/// Cette méthode permet d'affecter une valeur à l'attribut m.
/// </summary>
/// <param name="p_m">La valeur à affecter.</param>
void Matrice::setM(unsigned int p_m)
{
	// Vérifie que la valeur donnée soit dans la plage de valeurs acceptable.
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

/// <summary>
/// Cette méthode permet d'affecter une valeur à l'attribut n.
/// </summary>
/// <param name="p_n">La valeur à affecter.</param>
void Matrice::setN(unsigned int p_n)
{
	// Vérifie que la valeur donnée soit dans la plage de valeurs acceptable.
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

/// <summary>
/// Constructeur par défaut de la classe Matrice.
/// </summary>
Matrice::Matrice() {
	m_m = 0;
	m_n = 0;
	m_row = new vector<vector<float>>(0);
}


/// <summary>
/// Cette méthode calcule l'addition entre deux matrices.
/// </summary>
/// <param name="p_B">Le pointeur de la deuxième instance à calculer.</param>
/// <returns>Retourne le pointeur d'une instance de la classe résultant de l'addition.</returns>
Matrice* Matrice::additionner(Matrice* p_B) {
	// Vérifie que les deux matrices soit du même ordre.
	if (p_B->getM() != this->m_m) {
		cout << "ERREUR : Les deux matrices doivent avoir le même ordre." << endl;
		return nullptr;

	}

	if (p_B->getN() != this->m_n) {
		cout << "ERREUR : Les deux matrices doivent avoir le même ordre." << endl;
		return nullptr;

	}

	// Matrice temporaire.
	Matrice* temp = new Matrice(this->m_m, this->m_n);

	vector<vector<float>>* data = new vector<vector<float>>(0);

	// Additionne les valeurs des colonnes et des lignes entre les deux matrices.
	for (unsigned int i = 0; i < (*m_row).size(); i++) {
		vector<float> tempRow(0);
		for (unsigned int j = 0; j < (*m_row)[i].size(); j++) {
			tempRow.push_back((*m_row)[i][j] + (*p_B->getData())[i][j]);
		}
		data->push_back(tempRow);
	}

	temp->setData(data);

	return temp;

}

/// <summary>
/// Cette méthode permet de calculer la multiplication entre deux matrices.
/// </summary>
/// <param name="p_B">Le pointeur de la matrice B.</param>
/// <returns>Retourne le pointeur de l'instance avec la multiplication.</returns>
Matrice* Matrice::multiplier(Matrice* p_B)
{
	// Vérifie si les deux matrices peuvent se multiplier.
	if (m_n != p_B->getM()) {
		cout << "ERREUR : Le deuxième ordre doit être similaire que le premier ordre de la deuxième matrice." << endl;
		return nullptr;
	}

	// Matrice temporaire.
	Matrice* temp = new Matrice(m_m, p_B->getN());
	vector<vector<float>>* data = new vector<vector<float>>(m_m, vector<float>(p_B->getN(), 0));

	// Calcule pour effectuer la multiplication.
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

/// <summary>
/// Cette méthode calcule le déterminant de la matrice.
/// </summary>
/// <returns>Retourne la valeur du calcul.</returns>
float Matrice::determinant()
{
	// Si la matrice n'est pas carré.
	if (m_m != m_n) {
		cout << "ERREUR : La matrice doit être carrée pour calculer le déterminant." << endl;
		return 0;
	}

	int n = m_m;
	vector<vector<float>> data = *getData();

	// Si l matrice a un ordre de 1
	if (n == 1) {
		return data[0][0];
	}
	else if (n == 2) { // si la matrice à un ordre de 2
		return data[0][0] * data[1][1] - data[0][1] * data[1][0];
	}

	// Calcule du déterminant
	float det = 0;
	for (int p = 0; p < n; p++) {
		
		// Matrice temporaire.
		Matrice submatrix(n - 1, n - 1);
		vector<vector<float>> subdata(n - 1, vector<float>(n - 1));
		// Lis les valeurs de la matrices pour retirer une ligne des valeurs de la matrice subsécante.
		for (int i = 1; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (j == p) continue;
				int col = (j < p) ? j : j - 1;
				subdata[i - 1][col] = data[i][j];
			}
		}
		submatrix.setData(&subdata);

		// Calcule le déterminant en calculant le déterminant de la matrice subsécante.
		det += (p % 2 == 0 ? 1 : -1) * data[0][p] * submatrix.determinant();
	}

	return det;
}

/// <summary>
/// Cette méthode retourne les données de la matrice.
/// </summary>
/// <returns>Le pointeur du tableau contenant les données.</returns>
std::vector<std::vector<float>>* Matrice::getData()
{
	return m_row;
}

/// <summary>
/// Cette méthode affecte les valeurs à la liste de données.
/// </summary>
/// <param name="p_data">Le pointeur de la table de données.</param>
void Matrice::setData(std::vector<std::vector<float>>* p_data)
{
	// Vérifie que le tableau soit de la meme grandeur que la matrice.
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

/// <summary>
/// Cette méthode transpose la matrice.
/// </summary>
/// <returns>Retourne le pointeur de l'instance d'une matrice transposé.</returns>
Matrice* Matrice::transposer()
{
	// Matrice temporaire.
	Matrice* temp = new Matrice(this->m_n, this->m_m);
	vector<vector<float>>* data = new vector<vector<float>>(0);

	float tempFloat[MAXORDRE][MAXORDRE];

	// Transpose la matrice dans une variable temporaire.
	for (int i = 0; i < (*m_row).size(); i++) {
		for (int j = 0; j < (*m_row)[i].size(); j++) {
			tempFloat[j][i] = (*m_row)[i][j];
		}
	}

	// Affecte la variable temporaire à la matrice.
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

/// <summary>
/// Cette méthode retourne la valeur associée à m.
/// </summary>
/// <returns>Retourne une valeur numérique.</returns>
unsigned int Matrice::getM()
{
	return m_m;
}

/// <summary>
/// Cette méthode retourne la valeur associée à n.
/// </summary>
/// <returns>Retourne une valeur numérique.</returns>
unsigned int Matrice::getN()
{
	return m_n;
}

/// <summary>
/// Cette méthode affiche la matrice de manière visuel.
/// </summary>
void Matrice::afficher()
{
	// Affiche chaque valeurs de la matrice.
	for (unsigned int i = 0; i < m_m; i++) {
		cout << "[ ";
		for (unsigned int j = 0; j < m_n; j++) {
			cout << (*m_row)[i][j] << " ";
		}
		cout << "]" << endl;
	}
	// Affiche l'ordre de la matrice.
	cout << "Matrice d'ordre : " <<  m_m << " X " << m_n << endl;
}




