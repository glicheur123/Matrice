/**
	Marc-Antoine Gauthier
	main.cpp
	Fichier de d'entr�.
*/
#include <iostream>
#include <vector>
#include "Matrice.h"

// Constantes
#define MENULENGHT 40
#define MENUSEPARATOR '-'

using namespace std;



/// <summary>
/// Cette fonction v�rifie les valeurs num�riques entr�es par l'utilisateur.
/// </summary>
/// <param name="p_texte">Le texte � afficher.</param>
/// <param name="p_entreeErreur">Le texte � afficher si le choix n'est pas un nombre.</param>
/// <param name="p_choixErreur">Le texte � afficher si le choix n'est pas dans la plage acceptable.</param>
/// <param name="p_min">La valeur minimale incluse.</param>
/// <param name="p_max">La valeur maximale incluse.</param>
/// <returns>Retourne le choix de l'utilisateur en constante.</returns>
const int verificationChoix(const string p_texte, const string p_entreeErreur, const string p_choixErreur, const int p_min, const int p_max)
{
	cout << p_texte;

	while (true) {
		int choix = 0;

		cin >> choix;

		if (cin.fail()) { // Si l'utilisateur n'entre pas un nombre.
			cin.clear();
			cout << p_entreeErreur;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (choix < p_min) { // Si le nombre est plus petit que le min
			cout << p_choixErreur;
			continue;
		}

		if (choix > p_max) { // Si le nombre est plus grand que le max
			cout << p_choixErreur;
			continue;
		}


		return choix;
	}
}

Matrice* cramer(vector<Matrice*> matrices) {
	// V�rifie qu'il y a des matrices enregistr�s. Sinon, on retourne un pointeur null.
	if (matrices.size() == 0) {
		cout << "ATTENTION : Rien � afficher - Cramer impossible!" << endl;
		return nullptr;
	}

	// Affiche les matrices enregistr�s.
	for (unsigned int i = 0; i < matrices.size(); i++) {
		cout << i << ". Matrice " << matrices[i]->getM() << "X" << matrices[i]->getN() << endl;
	}

	// Demande � l'utilisateur l'index des matrices.
	int a = verificationChoix("Matrice coefficient : ", "Erreur", "Erreur", 0, matrices.size() - 1);

	int b = verificationChoix("Matrice resultat : ", "Erreur", "Erreur", 0, matrices.size() - 1);

	// Verification des nb de lignes.
	if (matrices[a]->getM() != matrices[b]->getM()) {
		cout << "ERREUR : Les deux matrices doivent avoir le m�me nombre de lignes." << endl;
		return nullptr;
	}

	if (matrices[a]->getM() != 3 || matrices[a]->getN() != 3) {
		cout << "ERREUR : La matrice des coefficient doit �tre d'ordre 3 sur ses lignes et colonnes." << endl;
		return nullptr;
	}

	if (matrices[b]->getM() != 3 || matrices[b]->getN() != 1) {
		cout << "ERREUR : La matrice des r�sultats doit �tre une matrice 3x1!" << endl;
		return nullptr;
	}

	cout << "determinant :";
	float detA = matrices[a]->determinant();
	cout << detA << endl;

	// Si le d�terminant est de 0, on cherche si la matrice b est homog�ne.
	if (detA == 0) {
		float totalB = 0;
		for (unsigned int i = 0; i < matrices[b]->getData()->size(); i++) {
			totalB += (*matrices[b]->getData())[i][0];
		}

		if (totalB == 3 * (*matrices[b]->getData())[0][0]) {
			cout << "La matrice des r�sultats est homog�ne! Il y a donc une infinit� de solution possible !" << endl;
			return nullptr;
		}
		else {
			cout << "La matrice des r�sultats n'est pas homog�ne! Il y a donc soit une infinit� ou aucune solution possible!" << endl;
			return nullptr;
		}

	}

	cout << "Ce SEL comporte une solution possible!" << endl;

	Matrice* x = new Matrice(3, 1);

	vector<vector<float>>* temp = new vector<vector<float>>(3, vector<float>(3, 0));
	vector<vector<float>>* data = new vector<vector<float>>(3, vector<float>(1, 0));

	for (unsigned int k = 0; k < 3; k++) {
		for (unsigned int i = 0; i < 3; i++) {
			for (unsigned int j = 0; j < 3; j++) {
				(*temp)[i][j] = (*matrices[a]->getData())[i][j];
			}
		}

		for (unsigned int j = 0; j < 3; j++) {
			(*temp)[k][j] = (*matrices[b]->getData())[0][j];
		}


		Matrice matriceTemp(1, 3);
		matriceTemp.setData(temp);
		float tempDet = matriceTemp.determinant();

		(*data)[k][0] = tempDet / detA;



	}

	x->setData(data);
	cout << "Matrice des inconnus correctement enregistr�e � la derni�re position!" << endl;
	x->afficher();

	return x;




}

/// <summary>
/// Cette fonction permet l'affichage du menu principal.
/// </summary>
/// <returns>Retourne la valeur correspondant au choix de l'utilisateur.</returns>
const unsigned int menuPrincipal() {
	// Affichage du menu.
    system("cls");
    for (unsigned int i = 0; i < MENULENGHT; i++) {
        cout << MENUSEPARATOR;
    }
    cout << endl;
    cout << "0. Supprimer les matrices enregistr�es" << endl;
    cout << "1. Afficher les matrices enregistr�es" << endl;
    cout << "2. Cr�er une matrice" << endl;
    cout << "3. Additionner deux matrices" << endl;
	cout << "4. Afficher matrice transpos�e" << endl;
    cout << "5. Multiplier deux matrices" << endl;
    cout << "6. Calculer d�terminant" << endl;
	cout << "7. SEL Cramer (matrice 3x3)" << endl;
	cout << "8. Sortie" << endl << endl << endl;

	// retourne la v�rification du choix.
	return (verificationChoix("Votre choix : ", "ERREUR : Veuillez entrez un nombre!", "ERREUR : Veuillez entrez un nombre entre 0 et 7!", 0, 8));

}

/// <summary>
/// Cette fonction permet la cr�ation d'une matrice.
/// </summary>
/// <returns>Retourne le pointeur d'une instance de la classe Matrice.</returns>
Matrice* creeMatrice() {
	// Demande la grandeur de la matrice.
	int m = verificationChoix("Nb de lignes (1-10) : ", "Veuillez entrer un nombre!", "Veuillez entrer entre 1 et 10!", 1, 10);
	int n = verificationChoix("Nb de colonnes (1-10) : ", "Veuillez entrer un nombre!", "Veuillez entrer entre 1 et 10!", 1, 10);
	
	Matrice* matrice = new Matrice(m, n);

	// Demande les valeurs � int�grer dans la matrice.
	vector<vector<float>>* data = new vector<vector<float>>(0);
	for (int i = 0; i < m; i++) {
		vector<float> row(0);
		for (int j = 0; j < n; j++) {
			int c;
			cout << "Position " << i << "," << j << " : ";
			cin >> c;
			row.push_back(c);
		}
		(*data).push_back(row);
	}

	// Met les valeurs dans l'instance et retourne le pointeur.
	matrice->setData(data);
	return matrice;

}

/// <summary>
/// Cette fonction additionne 2 matrices ensemble.
/// </summary>
/// <param name="matrices">Le tableau contenant les pointeurs des matrices enregistr�s.</param>
/// <returns>Retourne le pointeur de l'instance d'une matrice additionn�e.</returns>
Matrice* add(vector<Matrice*> matrices) {
	// V�rifie qu'il y a des matrices enregistr�s. Sinon, on retourne un pointeur null.
	if (matrices.size() == 0) {
		cout << "ATTENTION : Rien � afficher - Addition impossible!" << endl;
		return nullptr;
	}

	// Affiche les matrices enregistr�s.
	for (unsigned int i = 0; i < matrices.size(); i++) {
		cout << i << ". Matrice " << matrices[i]->getM() << "X" << matrices[i]->getN() << endl;
	}

	// Demande � l'utilisateur l'index des matrices � additionner.
	int a = verificationChoix("Matrice A : ", "Erreur", "Erreur", 0, matrices.size() - 1);

	int b = verificationChoix("Matrice B : ", "Erreur", "Erreur", 0, matrices.size() - 1);

	// Va chercher l'instances des matrices pour effectuer l'addition et affiche la nouvelle matrice.
	Matrice* t = matrices[a]->additionner(matrices[b]);
	if (t != nullptr) {
		cout << "Matrice correctement enregistr�e � derni�re position!" << endl;
		cout << "----------------------------------------------------" << endl;
		t->afficher();
	}

	return t;

}

/// <summary>
/// Cette fonction transpose une matrice.
/// </summary>
/// <param name="matrices">La liste des pointeurs des instances de matrices.</param>
/// <returns></returns>
Matrice* trans(vector<Matrice*> matrices) {
	// V�rifie qu'il y a au moins une matrice d'enregistr�e.
	if (matrices.size() == 0) {
		cout << "ATTENTION : Rien � afficher - Transposition impossible!" << endl;
		return nullptr;
	}

	// Affiche la liste des matrices enregistr�es.
	for (unsigned int i = 0; i < matrices.size(); i++) {
		cout << i << ". Matrice " << matrices[i]->getM() << "X" << matrices[i]->getN() << endl;
	}

	// Demande la matrice � transposer et l'affiche.
	int a = verificationChoix("Matrice : ", "Erreur", "Erreur", 0, matrices.size() - 1);
	Matrice* t = matrices[a]->transposer();
	
	cout << "Matrice correctement enregistr�e � derni�re position!" << endl;
	cout << "----------------------------------------------------" << endl;
	t->afficher();

	return t;

	
}

/// <summary>
/// Cette fonction multiplie deux matrices.
/// </summary>
/// <param name="matrices">Liste de pointeurs d'instances de la classe matrice enregistr�s.</param>
/// <returns>Retourne un pointeur d'une instance de la classe matrice �tant le r�sultat de la multiplication.</returns>
Matrice* mult(vector<Matrice*> matrices) {
	// V�rifie qu'il y a des matrices enregistr�es. Sinon, on retourne un pointeur null. 
	if (matrices.size() == 0) {
		cout << "ATTENTION : Rien � afficher - Multiplication impossible!" << endl;
		return nullptr;
	}

	// Affiche les matrices enregistr�es.
	for (unsigned int i = 0; i < matrices.size(); i++) {
		cout << i << ". Matrice " << matrices[i]->getM() << "X" << matrices[i]->getN() << endl;
	}

	// Demande les deux matrices � multiplier.
	int a = verificationChoix("Matrice A : ", "Erreur", "Erreur", 0, matrices.size() - 1);

	int b = verificationChoix("Matrice B : ", "Erreur", "Erreur", 0, matrices.size() - 1);

	Matrice* t = matrices[a]->multiplier(matrices[b]);
	// V�rifie que la multiplication s'est belle et bien effectu� pour afficher la matrice.
	if (t != nullptr) {
		cout << "Matrice correctement enregistr�e � derni�re position!" << endl;
		cout << "----------------------------------------------------" << endl;
		t->afficher();
	}

	return t;

}

/// <summary>
/// Cette fonction calcule le d�terminant d'une matrice.
/// </summary>
/// <param name="matrices">La liste de pointeurs d'instance de matrice enregistr�s.</param>
/// <returns>Retourne la valeur du d�terminant calcul�e.</returns>
int det(vector<Matrice*> matrices) {
	// V�rifie qu'il y a des matrices enregistr�es. 
	if (matrices.size() == 0) {
		cout << "ATTENTION : Rien � afficher - D�terminant impossible!" << endl;
		return 0;
	}

	// Affiche les matrices enregistr�es.
	for (unsigned int i = 0; i < matrices.size(); i++) {
		cout << i << ". Matrice " << matrices[i]->getM() << "X" << matrices[i]->getN() << endl;
	}

	// Demande la matrice � calculer le d�terminant et affiche le r�sultat. 
	int a = verificationChoix("Matrice A : ", "Erreur", "Erreur", 0, matrices.size() - 1);
	cout << "D�terminant de la matrice : " << matrices[a]->determinant() << endl;
}



int main()
{

    locale::global(locale("")); // Accent.
	
	vector<Matrice*> matrices(0); // Tableau de pointeurs.

	while (true) // Boucle principale.
	{
		int choix = menuPrincipal();
		system("cls");
		// Options d�pendant du choix de l'utilisateur.
		if (choix == 0) {
			matrices.clear();
		} else if (choix == 1) {
			if (matrices.size() == 0) {
				cout << "ATTENTION : Rien � afficher!" << endl;
				system("pause");
				continue;
			}

			for (unsigned int i = 0; i < matrices.size(); i++) {
				cout << i << ". Matrice " << matrices[i]->getM() << "X" << matrices[i]->getN() << endl;
			}

			int a = verificationChoix("Matrice � afficher : ", "Erreur", "Erreur", 0, matrices.size() - 1);
			matrices[a]->afficher();

			system("pause");
		}
		else if (choix == 2) {
			matrices.push_back(creeMatrice()); // Enregistre la matrice dans la liste.
		}
		else if (choix == 3) {
			Matrice* t = add(matrices);
			if (t != nullptr) { // V�rifie si la matrice a belle et bien �t� cr�e.
				matrices.push_back(t);
			}
			system("pause");
		}
		else if (choix == 4) {
			Matrice* t = trans(matrices);
			if (t != nullptr) { // V�rifie si la matrice a belle et bien �t� cr�e.
				matrices.push_back(t);
			}
			system("pause");
		}
		else if (choix == 5) {
			Matrice* t = mult(matrices);
			if (t != nullptr) { // V�rifie si la matrice a belle et bien �t� cr�e.
				matrices.push_back(t);
			}
			system("pause");
		}
		else if (choix == 6) {
			det(matrices);
			system("pause");
		} else if( choix == 7){ // Cramer
			Matrice* t = cramer(matrices);
			if (t != nullptr) {
				matrices.push_back(t);
			}
			system("pause");
		}
		else {
			return 0; // no 8
		}
	}

	return 0; // Par convention.
    
}
