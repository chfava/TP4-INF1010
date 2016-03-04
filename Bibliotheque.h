/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Fichier: Bibliotheque.h
//	Auteur(s) : Charles - Olivier Favreau et St�phanie Leclerc
//	Date de creation : 01 mars 2016
//	Date de modification : 03 mars 2016
//Description : Description de la classe Bibliotheque
////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef BIBLIOTHEQUE_H
#define BIBLIOTHEQUE_H

#include <string>
#include <vector>
#include "Abonne.h"
#include "Etudiant.h"
#include "Professeur.h"
#include "ObjetEmpruntable.h"
#include "Emprunt.h"
#include <iostream>


class Bibliotheque
{
public:

	Bibliotheque();
	~Bibliotheque();

	Abonne* trouverAbonne(const std::string& matricule) const;

	ObjetEmpruntable* trouverObjetEmpruntable(const std::string& cote) const;

	std::string obtenirClasseObjet(std::string const& cote) const;

	bool ajouterAbonne(Abonne& abonne);
	bool retirerAbonne(const std::string& matricule);	

	bool ajouterObjetEmpruntable(ObjetEmpruntable* objet);
	
	bool retirerObjetEmpruntable(const std::string& cote);
	void rechercherObjetEmpruntable(const std::string& str) const;

	bool estEmpruntable(const std::string& matricule, const ObjetEmpruntable& objetEmpruntable) const;
	bool emprunter(const std::string& matricule, const std::string& cote, unsigned int date);
	bool retourner(const std::string& matricule, const std::string& cote);

	void infoAbonne(const std::string& matricule) const;

	Bibliotheque& operator+=(Abonne* abonne);
	Bibliotheque& operator+=(ObjetEmpruntable* obj);
	Bibliotheque& operator-=(Abonne* abonne);
	Bibliotheque& operator-=(ObjetEmpruntable* obj);

	friend std::istream& operator>>(std::istream& in, const Bibliotheque& biblio);


private:
	std::vector<Abonne*> vecAbonnes_;
	std::vector<Emprunt*> vecEmprunts_;

	/// ____ TP4 ___
	std::vector<ObjetEmpruntable*> vecObj_;
};

#endif