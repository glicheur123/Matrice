// Matrice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "Matrice.h"

#define MENULENGHT 20
#define MENUSEPARATOR '-'

using namespace std;


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


const unsigned int menuPrincipal() {
    system("cls");
    for (unsigned int i = 0; i < MENULENGHT; i++) {
        cout << MENUSEPARATOR;
    }
    cout << endl;
    cout << "0. Supprimer les matrices enregistrées" << endl;
    cout << "1. Afficher les matrices enregistrées" << endl;
    cout << "2. Créer une matrice" << endl;
    cout << "3. Additionner deux matrices" << endl;
	cout << "4. Afficher matrice transposée" << endl;
    cout << "5. Multiplier deux matrices" << endl;
    cout << "6. Calculer déterminant" << endl;
	cout << "7. Sortie" << endl << endl << endl;

	return (verificationChoix("Votre choix : ", "ERREUR : Veuillez entrez un nombre!", "ERREUR : Veuillez entrez un nombre entre 0 et 7!", 0, 7));

}

Matrice* creeMatrice() {
	int m = verificationChoix("Nb de colonnes (1-10) : ", "Veuillez entrer un nombre!", "Veuillez entrer entre 1 et 10!", 1, 10);
	int n = verificationChoix("Nb de lignes (1-10) : ", "Veuillez entrer un nombre!", "Veuillez entrer entre 1 et 10!", 1, 10);
	
	Matrice* matrice = new Matrice(m, n);

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

	matrice->setData(data);
	return matrice;

}

Matrice* add(vector<Matrice*> matrices) {
	if (matrices.size() == 0) {
		cout << "ATTENTION : Rien à afficher - Addition impossible!" << endl;
		return nullptr;
	}

	for (unsigned int i = 0; i < matrices.size(); i++) {
		cout << i << ". Matrice " << matrices[i]->getM() << "X" << matrices[i]->getN() << endl;
	}

	int a = verificationChoix("Matrice A : ", "Erreur", "Erreur", 0, matrices.size() - 1);

	int b = verificationChoix("Matrice B : ", "Erreur", "Erreur", 0, matrices.size() - 1);

	Matrice* t = matrices[a]->additionner(matrices[b]);
	if (t != nullptr) {
		cout << "Matrice correctement enregistrée à dernière position!" << endl;
		cout << "----------------------------------------------------" << endl;
		t->afficher();
	}

	return t;

}

Matrice* trans(vector<Matrice*> matrices) {
	if (matrices.size() == 0) {
		cout << "ATTENTION : Rien à afficher - Transposition impossible!" << endl;
		return nullptr;
	}

	for (unsigned int i = 0; i < matrices.size(); i++) {
		cout << i << ". Matrice " << matrices[i]->getM() << "X" << matrices[i]->getN() << endl;
	}

	int a = verificationChoix("Matrice : ", "Erreur", "Erreur", 0, matrices.size() - 1);
	Matrice* t = matrices[a]->transposer();
	
	cout << "Matrice correctement enregistrée à dernière position!" << endl;
	cout << "----------------------------------------------------" << endl;
	t->afficher();

	return t;

	
}

Matrice* mult(vector<Matrice*> matrices) {
	if (matrices.size() == 0) {
		cout << "ATTENTION : Rien à afficher - Multiplication impossible!" << endl;
		return nullptr;
	}

	for (unsigned int i = 0; i < matrices.size(); i++) {
		cout << i << ". Matrice " << matrices[i]->getM() << "X" << matrices[i]->getN() << endl;
	}

	int a = verificationChoix("Matrice A : ", "Erreur", "Erreur", 0, matrices.size() - 1);

	int b = verificationChoix("Matrice B : ", "Erreur", "Erreur", 0, matrices.size() - 1);

	Matrice* t = matrices[a]->multiplier(matrices[b]);

	if (t != nullptr) {
		cout << "Matrice correctement enregistrée à dernière position!" << endl;
		cout << "----------------------------------------------------" << endl;
		t->afficher();
	}

	return t;

}

int det(vector<Matrice*> matrices) {
	if (matrices.size() == 0) {
		cout << "ATTENTION : Rien à afficher - Déterminant impossible!" << endl;
		return -1;
	}

	for (unsigned int i = 0; i < matrices.size(); i++) {
		cout << i << ". Matrice " << matrices[i]->getM() << "X" << matrices[i]->getN() << endl;
	}

	int a = verificationChoix("Matrice A : ", "Erreur", "Erreur", 0, matrices.size() - 1);

	cout << "Déterminant de la matrice : " << matrices[a]->determinant() << endl;
}



int main()
{

    locale::global(locale(""));
	
	vector<Matrice*> matrices(0);

	while (true)
	{
		int choix = menuPrincipal();
		system("cls");
		if (choix == 0) {
			matrices.clear();
		} else if (choix == 1) {
			if (matrices.size() == 0) {
				cout << "ATTENTION : Rien à afficher!" << endl;
				system("pause");
				continue;
			}

			for (unsigned int i = 0; i < matrices.size(); i++) {
				cout << i << ". Matrice " << matrices[i]->getM() << "X" << matrices[i]->getN() << endl;
			}

			int a = verificationChoix("Matrice à afficher : ", "Erreur", "Erreur", 0, matrices.size() - 1);
			matrices[a]->afficher();

			system("pause");
		}
		else if (choix == 2) {
			matrices.push_back(creeMatrice());
		}
		else if (choix == 3) {
			Matrice* t = add(matrices);
			if (t != nullptr) {
				matrices.push_back(t);
			}
			system("pause");
		}
		else if (choix == 4) {
			Matrice* t = trans(matrices);
			if (t != nullptr) {
				matrices.push_back(t);
			}
			system("pause");
		}
		else if (choix == 5) {
			Matrice* t = mult(matrices);
			if (t != nullptr) {
				matrices.push_back(t);
			}
			system("pause");
		}
		else if (choix == 6) {
			det(matrices);
			system("pause");
		} else if( choix == 7){
			return 0;
		}
		else {
			return 0;
		}
	}

	return 0;
    
}
