/**
Matrice.h
Marc-Antoine Gauthier
Fichier d'en-tête pour la classe Matrice
*/
#pragma once
#include <vector>
#include <string>

class Matrice
{
	private:
		// Attributs
		unsigned int m_m = 0;
		unsigned int m_n = 0;
		std::vector<std::vector<float>>* m_row;


	public:
		//Constructeur
		Matrice();
		Matrice(unsigned int m, unsigned int n);
		~Matrice();

		// Méthodes
		void setM(unsigned int p_m);

		void setN(unsigned int p_n);

		Matrice* additionner(Matrice* p_B);

		Matrice* multiplier(Matrice* p_B);

		float determinant();

		std::vector<std::vector<float>>* getData();

		void setData(std::vector<std::vector<float>>* p_data);

		Matrice* transposer();

		unsigned int getM();
		unsigned int getN();

		void afficher();
};

