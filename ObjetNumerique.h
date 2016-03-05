/*
Fichier: ObjetNumerique.h
Auteur(s): Charles-Olivier Favreau et Stéphanie Leclerc
Date de creation: 1er mars 2016
Date de modification: 4 mars 2016
Description: Définition de la classe ObjetNumerique
*/
#ifndef	OBJETNUMERIQUE_H
#define OBJETNUMERIQUE_H




class ObjetNumerique : public ObjetEmpruntable
{
public:

	virtual unsigned int obtenirTailleDoc() const = 0;
	virtual string obtenirLien() const = 0;

	virtual void modifierTailleDoc() = 0;
	virtual void modifierLien() = 0;
	
};



#endif

