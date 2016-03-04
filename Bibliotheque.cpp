/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Fichier: Bibliotheque.cpp
//	Auteur(s) : Charles - Olivier Favreau et St�phanie Leclerc
//	Date de creation : 01 mars 2016
//	Date de modification : 03 mars 2016
//Description : Fonctions reli�es � classe Bibliotheque
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
//Le constructeur par d�faut construit un objet de la classe Biblioth�que 
//Aucun param�tre.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
Bibliotheque::Bibliotheque()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//Le destructeur li�re la m�moire occup�e par la classe.
//Aucun param�tre.
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
// Retourne l'abonn� selon le matricule donn�
//@param string matricule (R�f�rence)
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
// Retourne l'objet empruntable selon la cote donn�e
//@param string cote (R�f�rence)
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
// Retourne un string correspondant au nom de la classe selon la cote donn�e
//@param string cote (R�f�rence)
//@return string
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string Bibliotheque::obtenirClasseObjet(std::string const & cote) const
{
	return trouverObjetEmpruntable(cote)->obtenirNomClasse();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// Ajoute un objet Aonnne � la Biblioth�que
//@param Abonne abonne (R�f�rence)
//@return bool
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Bibliotheque::ajouterAbonne(Abonne& abonne)
{
	// V�rifier s'il est pr�sent dans le vecteur. Si non, l'ajouter
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
// Retire un abonne de la Biblioth�que et retoune vrai si l'abonne a �t� enlev� avec succ�s.
//@param string matricule (R�f�rence)
//@return bool
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Bibliotheque::retirerAbonne(const string& matricule)
{
	bool estRetire = false;

	for (size_t i = 0; i < vecAbonnes_.size(); i++)
	{
		// Si l'abonne est trouv�, alors swap sa position avec le dernier �l�ment du vecteur, 
		// puis enlever de le dernier �l�ment du vecteur
		if ((*vecAbonnes_[i]) == matricule)
		{
			// Retirer tous les emprunts
			vector<Emprunt*> abEmprunt = vecAbonnes_[i]->obtenirEmprunts();
			for (size_t j = 0; j < abEmprunt.size(); j++)
			{
				retourner(matricule, abEmprunt[j]->obtenirObjetEmpruntable()->obtenirCote());
			}

			// Retirer l'abonn�
			estRetire = true;
			vecAbonnes_[i] = vecAbonnes_.back();
			vecAbonnes_.pop_back();
		}
	}

	return estRetire;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// Ajoute un pointeur ObjetEmpruntable � la Biblioth�que et retourne une valeur bool�enne confirmant l'action.
//@param ObjetEmpruntable* objet
//@return bool
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Bibliotheque::ajouterObjetEmpruntable(ObjetEmpruntable* objet)
{
	// V�rifier s'il est pr�sent dans le vecteur. Si non, l'ajouter
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
// Retire un ObjetEmpruntable � la Biblioth�que et retourne une valeur bool�enne confirmant l'action.
//@param string cote (R�f�rence)
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
//@param string str (R�f�rence)
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
// V�rifie si les conditions de bases sont respect�es et va v�rifier aussi parmi les �l�ments d�riv�s d'Abonne.
//@param string matricule (R�f�rence)
//@param ObjetEmpruntable objetEmpruntable (R�f�rence)
//@return bool
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Bibliotheque::estEmpruntable(const std::string & matricule, const ObjetEmpruntable & objetEmpruntable) const
{	
	bool empruntable = false;
	Abonne* abonne = trouverAbonne(matricule);
	//On doit v�rifier que tous les vecteurs sont parcourus
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
// Emprunte l'objet selon d'apr�s sa cote pour la personne correspondant au matricule.
//@param string matricule (R�f�rence)
//@param string cote (R�f�rence)
//@param unsigned int date 
//@return bool
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Bibliotheque::emprunter(const string& matricule, const string& cote, unsigned int date)
{
	//On doit v�rifier que tous les vecteurs sont parcourus
	Abonne* ab = trouverAbonne(matricule);

	ObjetEmpruntable* obj = trouverObjetEmpruntable(cote);

	bool peutEmprunte = false;

	if ((ab != nullptr) && (obj != nullptr))
	{
		// V�rifier s'il est possible d'emprunter l'objet, puis l'emprunter

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
// Retourne un objetEmpruntable associ� � un Abonn� et retourne true ou false si accompli.
//@param string matricule (R�f�rence)
//@param string cote (R�f�rence)
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
		//On doit v�rifier que tous les vecteurs sont parcourus
		Abonne* ab = trouverAbonne(matricule);
	
		// V�rifier s'il est possible de retourner l'objetEmpruntable, puis le retourner et d�truire l'emprunt
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
// Afficher l'information de l'abonn� correspondant au matricule
//@param string matricule (R�f�rence)
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
void Bibliotheque::infoAbonne(const string& matricule) const
{
	//On doit v�rifier que tous les vecteurs sont parcourus
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
// L'op�rateur += apelle la fonction ajouterAbonne() et retourne l'objet de type Biblioth�que apr�s la modification
//@param Abonne* abonne
//@return Biblioth�que
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
Bibliotheque & Bibliotheque::operator+=(Abonne * abonne)
{
	
	ajouterAbonne(*abonne);
	return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// L'op�rateur += apelle la fonction ajouterObjetEmpruntable() et retourne l'objet de type Biblioth�que apr�s la modification
//@param ObjetEmpruntable * obj
//@return Biblioth�que
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
Bibliotheque & Bibliotheque::operator+=(ObjetEmpruntable * obj)
{
	ajouterObjetEmpruntable(obj);
	return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// L'op�rateur -= apelle la fonction retirerAbonne() et retourne l'objet de type Biblioth�que apr�s la modification
//@param Abonne * abonne
//@return Biblioth�que
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
Bibliotheque & Bibliotheque::operator-=(Abonne * abonne)
{
	retirerAbonne(abonne->obtenirMatricule());
	return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// L'op�rateur -= apelle la fonction retirerObjetEmpruntable() et retourne l'objet de type Biblioth�que apr�s la modification
//@param ObjetEmpruntable * obj
//@return Biblioth�que
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
Bibliotheque & Bibliotheque::operator-=(ObjetEmpruntable * obj)
{
	retirerObjetEmpruntable(obj->obtenirCote());
	return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// L'op�rateur >> appelle la fonction rechercherObjetEmpruntable() en premant en param�tre un string pass� par le istream
//@param istream in (R�f�rence)
//@param Bibliotheque biblio (R�f�rence)
//@return istream in (R�f�rence)
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
std::istream & operator>>(std::istream & in, const Bibliotheque & biblio)
{
	string mot;
	in >> mot;
	biblio.rechercherObjetEmpruntable(mot);
	return in;
}


