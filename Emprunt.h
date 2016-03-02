#ifndef EMPRUNT_H
#define EMPRUNT_H

#include <string>
#include "Livre.h"
#include "Dvd.h"

class Emprunt
{
public:

	~Emprunt();

	std::string obtenirMatricule() const;
	unsigned int obtenirDateRetour() const;

	void modifierMatricule(const std::string& matricule);
	void modifierDateRetour(unsigned int date);


	/// _____ TP4 _____






private:
	std::string matricule_;
	unsigned int dateRetour_;

	/// _____ TP4 _____
	ObjetEmpruntable* objEmprunt_;

};

#endif