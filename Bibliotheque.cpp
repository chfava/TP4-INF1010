/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Fichier: Bibliotheque.cpp
//	Auteur(s) : Charles - Olivier Favreau et Stéphanie Leclerc
//	Date de creation : 01 mars 2016
//	Date de modification : 03 mars 2016
//Description : Fonctions reliées à classe Bibliotheque
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <string>
#include "Bibliotheque.h"
#include "Abonne.h"
#include "Etudiant.h"
#include "Professeur.h"
#include "EtudiantBaccalaureat.h"

using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//Le constructeur par défaut construit un objet de la classe Bibliothèque 
//Aucun paramètre.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
Bibliotheque::Bibliotheque()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//Le destructeur lière la mémoire occupée par la classe.
//Aucun paramètre.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
Bibliotheque::~Bibliotheque()
{
	// Supprimer uniquement les emprunts
	for (size_t i = 0; i < vecEmprunts_.size(); i++)
	{
		delete vecEmprunts_.back();
		vecEmprunts_.pop_back();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// Retourne l'abonné selon le matricule donné
//@param string matricule (Référence)
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
Abonne * Bibliotheque::trouverAbonne(const std::string & matricule) const
{
	for (size_t i = 0; i < vecAbonnes_.size(); i++)
	{
		if (*(vecAbonnes_[i]) == matricule)
		{
			return vecAbonnes_[i];
		}
	}
	return nullptr;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// Retourne l'objet empruntable selon la cote donnée
//@param string cote (Référence)
//@return ObjetEmpruntable*
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
ObjetEmpruntable* Bibliotheque::trouverObjetEmpruntable(const std::string& cote) const
{
	for (size_t i = 0; i < vecObj_.size(); i++)
	{
		if (vecObj_[i]->obtenirCote() == cote)
			return vecObj_[i];
	}
	return nullptr;
}




////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// Retourne un string correspondant au nom de la classe selon la cote donnée
//@param string cote (Référence)
//@return string
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string Bibliotheque::obtenirClasseObjet(std::string const & cote) const
{
	return trouverObjetEmpruntable(cote)->obtenirNomClasse();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// Ajoute un objet Aonnne à la Bibliothèque
//@param Abonne abonne (Référence)
//@return bool
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Bibliotheque::ajouterAbonne(Abonne& abonne)
{
	// Vérifier s'il est présent dans le vecteur. Si non, l'ajouter
	bool estPresent = false;
	Abonne* ab = trouverAbonne(abonne.obtenirMatricule());
	if (ab != nullptr) {
		for (size_t i = 0; i < vecAbonnes_.size(); i++)
		{
			if ((*vecAbonnes_[i]) == abonne)
				estPresent = true;
		}
	}
	if (!estPresent)
	{
		vecAbonnes_.push_back(&abonne);
	}
	return !estPresent;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// Retire un abonne de la Bibliothèque et retoune vrai si l'abonne a été enlevé avec succès.
//@param string matricule (Référence)
//@return bool
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Bibliotheque::retirerAbonne(const string& matricule)
{
	bool estRetire = false;

	for (size_t i = 0; i < vecAbonnes_.size(); i++)
	{
		// Si l'abonne est trouvé, alors swap sa position avec le dernier élément du vecteur, 
		// puis enlever de le dernier élément du vecteur
		if ((*vecAbonnes_[i]) == matricule)
		{
			// Retirer tous les emprunts
			vector<Emprunt*> abEmprunt = vecAbonnes_[i]->obtenirEmprunts();
			for (size_t j = 0; j < abEmprunt.size(); j++)
			{
				retourner(matricule, abEmprunt[j]->obtenirObjetEmpruntable()->obtenirCote());
			}

			// Retirer l'abonné
			estRetire = true;
			vecAbonnes_[i] = vecAbonnes_.back();
			vecAbonnes_.pop_back();
		}
	}

	return estRetire;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// Ajoute un pointeur ObjetEmpruntable à la Bibliothèque et retourne une valeur booléenne confirmant l'action.
//@param ObjetEmpruntable* objet
//@return bool
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Bibliotheque::ajouterObjetEmpruntable(ObjetEmpruntable* objet)
{
	// Vérifier s'il est présent dans le vecteur. Si non, l'ajouter
	bool estPresent = false;
	for (size_t i = 0; i < vecObj_.size(); i++)
	{
		if (vecObj_[i] == objet)
			estPresent = true;
	}

	if (!estPresent)
	{
		vecObj_.push_back(objet);
	}
	return !estPresent;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// Retire un ObjetEmpruntable à la Bibliothèque et retourne une valeur booléenne confirmant l'action.
//@param string cote (Référence)
//@return bool
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Bibliotheque::retirerObjetEmpruntable(const std::string & cote)
{

	for (size_t i = 0; i < vecObj_.size(); i++)
	{
		if (vecObj_[i]->obtenirCote() == cote){
			vecObj_[i] = vecObj_[vecObj_.size() - 1];
			vecObj_.pop_back();
		}
	}


	return false;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//recherche la chaine de mots parmi les attributs de type string de tous les classes de la famille ObjetEmpruntable.
//@param string str (Référence)
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
void Bibliotheque::rechercherObjetEmpruntable(const string& str) const
{
	bool trouve = false;
	cout << "Recherche pour le mot : " << str << endl;
	//recherche parmi les objets empruntable
	for (size_t i = 0; i < vecObj_.size(); i++)
	{
		if (vecObj_[i]->recherche(str)){
			vecObj_[i]->afficherObjetEmpruntable(cout);
			trouve = true;
		}
	}
		
	if (!trouve)
	{
		cout << "Aucun Resultat Trouve :-(" << endl;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// Vérifie si les conditions de bases sont respectées et va vérifier aussi parmi les éléments dérivés d'Abonne.
//@param string matricule (Référence)
//@param ObjetEmpruntable objetEmpruntable (Référence)
//@return bool
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Bibliotheque::estEmpruntable(const std::string & matricule, const ObjetEmpruntable & objetEmpruntable) const
{	
	bool empruntable = false;
	Abonne* abonne = trouverAbonne(matricule);
	//On doit vérifier que tous les vecteurs sont parcourus
	if (abonne != nullptr)
	{
		empruntable = (objetEmpruntable.obtenirNbDisponibles() >= 1) &&
			(abonne->obtenirAge() >= objetEmpruntable.obtenirAgeMinimal()) &&
			(!(abonne->estEmprunte(objetEmpruntable))) && abonne->obtenirEmprunts().size()<abonne->obtenirLimiteEmprunt();
	}
	
	return empruntable;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// Emprunte l'objet selon d'après sa cote pour la personne correspondant au matricule.
//@param string matricule (Référence)
//@param string cote (Référence)
//@param unsigned int date 
//@return bool
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Bibliotheque::emprunter(const string& matricule, const string& cote, unsigned int date)
{
	//On doit vérifier que tous les vecteurs sont parcourus
	Abonne* ab = trouverAbonne(matricule);

	ObjetEmpruntable* obj = trouverObjetEmpruntable(cote);

	bool peutEmprunte = false;

	if ((ab != nullptr) && (obj != nullptr))
	{
		// Vérifier s'il est possible d'emprunter l'objet, puis l'emprunter

		peutEmprunte = (estEmpruntable(ab->obtenirMatricule(), *obj));

		if (peutEmprunte)
		{
			vecEmprunts_.push_back(new Emprunt(matricule, *obj, date));
			obj->modifierNbDisponibles(obj->obtenirNbDisponibles()-1)
		}
	}

	return peutEmprunte;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// Retourne un objetEmpruntable associé à un Abonné et retourne true ou false si accompli.
//@param string matricule (Référence)
//@param string cote (Référence)
//@return bool
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Bibliotheque::retourner(const string& matricule, const string& cote)
{
	int emPos = -1;
	bool estRetourne = false;

	// Chercher l'emprunt
	for (size_t i = 0; i < vecEmprunts_.size(); i++)
	{
		if ((vecEmprunts_[i]->obtenirMatricule() == matricule) &&
			(*(vecEmprunts_[i]->obtenirObjetEmpruntable()) == cote))
			emPos = i;
	}


	if (emPos != -1)
	{
		Emprunt* em = vecEmprunts_[emPos];
		ObjetEmpruntable* obj = em->obtenirObjetEmpruntable();
		//On doit vérifier que tous les vecteurs sont parcourus
		Abonne* ab = trouverAbonne(matricule);
	
		// Vérifier s'il est possible de retourner l'objetEmpruntable, puis le retourner et détruire l'emprunt
		estRetourne = ab->estEmprunte(*obj);
		if (estRetourne)
		{
			ab->retirerEmprunt(obj);
			vecEmprunts_[emPos] = vecEmprunts_.back();
			vecEmprunts_.pop_back();
			delete em;
			obj->modifierNbDisponibles(obj->obtenirNbDisponibles() + 1);
		}
	}
	return estRetourne;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// Afficher l'information de l'abonné correspondant au matricule
//@param string matricule (Référence)
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
void Bibliotheque::infoAbonne(const string& matricule) const
{
	//On doit vérifier que tous les vecteurs sont parcourus
	Abonne* ab = trouverAbonne(matricule);

	if (ab != nullptr)
	{
		string type = ab->obtenirNomClasse();
		if (type == "Professeur"){
			cout << dynamic_cast<Professeur*>(ab);
		}
		else{
			if (type == "Etudiant"){
				cout << dynamic_cast<Etudiant*>(ab);
			}
			else if(type == "EtudiantBaccalaureat"){
				cout << dynamic_cast<EtudiantBaccalaureat*>(ab);
			}
		}

	}
	else
	{
		cout << "Abonne - " << matricule << " - non trouve" << endl;
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// L'opérateur += apelle la fonction ajouterAbonne() et retourne l'objet de type Bibliothèque après la modification
//@param Abonne* abonne
//@return Bibliothèque
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
Bibliotheque & Bibliotheque::operator+=(Abonne * abonne)
{
	
	ajouterAbonne(*abonne);
	return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// L'opérateur += apelle la fonction ajouterObjetEmpruntable() et retourne l'objet de type Bibliothèque après la modification
//@param ObjetEmpruntable * obj
//@return Bibliothèque
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
Bibliotheque & Bibliotheque::operator+=(ObjetEmpruntable * obj)
{
	ajouterObjetEmpruntable(obj);
	return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// L'opérateur -= apelle la fonction retirerAbonne() et retourne l'objet de type Bibliothèque après la modification
//@param Abonne * abonne
//@return Bibliothèque
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
Bibliotheque & Bibliotheque::operator-=(Abonne * abonne)
{
	retirerAbonne(abonne->obtenirMatricule());
	return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// L'opérateur -= apelle la fonction retirerObjetEmpruntable() et retourne l'objet de type Bibliothèque après la modification
//@param ObjetEmpruntable * obj
//@return Bibliothèque
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
Bibliotheque & Bibliotheque::operator-=(ObjetEmpruntable * obj)
{
	retirerObjetEmpruntable(obj->obtenirCote());
	return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// L'opérateur >> appelle la fonction rechercherObjetEmpruntable() en premant en paramètre un string passé par le istream
//@param istream in (Référence)
//@param Bibliotheque biblio (Référence)
//@return istream in (Référence)
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
std::istream & operator>>(std::istream & in, const Bibliotheque & biblio)
{
	string mot;
	in >> mot;
	biblio.rechercherObjetEmpruntable(mot);
	return in;
}


