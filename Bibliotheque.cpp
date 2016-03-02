#include <iostream>
#include <vector>
#include <string>
#include "Bibliotheque.h"
#include "Abonne.h"
#include "Etudiant.h"
#include "Professeur.h"
#include "EtudiantBaccalaureat.h"

using namespace std;

Bibliotheque::Bibliotheque()
{

}

Bibliotheque::~Bibliotheque()
{
	// Supprimer uniquement les emprunts
	for (size_t i = 0; i < vecEmprunts_.size(); i++)
	{
		delete vecEmprunts_.back();
		vecEmprunts_.pop_back();
	}
}


// Retourne l'abonn� selon le matricule donn�
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


// Retourne l'objet empruntable selon la cote donn�e
ObjetEmpruntable* Bibliotheque::trouverObjetEmpruntable(const std::string& cote) const
{
	for (size_t i = 0; i < vecObj_.size(); i++)
	{
		// !!!!!!!!!! A COMPLETER !!!!!!!!!!!
	}
	return nullptr;
}



// Retourne un string correspondant au nom de la classe selon la cote donn�e
std::string Bibliotheque::obtenirClasseObjet(std::string const & cote) const
{
	for (int i = 0; i < vecObj_.size(); i++)
	{
		// !!!!!!!!!! A COMPLETER !!!!!!!!!!!
	}

	return "";
}



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

bool Bibliotheque::ajouterObjetEmpruntable(ObjetEmpruntable* objet)
{
	// V�rifier s'il est pr�sent dans le vecteur. Si non, l'ajouter
	bool estPresent = false;
	for (size_t i = 0; i < vecObj_.size(); i++)
	{
		// !!!!!!!!!! A COMPLETER !!!!!!!!!!!
	}

	if (!estPresent)
	{
		vecObj_.push_back(objet);
	}
	return !estPresent;
}



bool Bibliotheque::retirerObjetEmpruntable(const std::string & cote)
{

	for (size_t i = 0; i < vecObj_.size(); i++)
	{
		// Si le livre est trouv�, alors swap sa position avec le dernier �l�ment du vecteur, 
		// puis enlever de le dernier �l�ment du vecteur
		
		// !!!!!!!!!! A COMPLETER !!!!!!!!!!!
	}


	return false;
}

//recherche la chaine de mots parmi les attributs de type string de tous les classes de la famille ObjetEmpruntable
void Bibliotheque::rechercherObjetEmpruntable(const string& str) const
{
	bool trouve = false;
	cout << "Recherche pour le mot : " << str << endl;
	//recherche parmi les objets empruntable
	for (size_t i = 0; i < vecObj_.size(); i++)
	{
		// !!!!!!!!!! A COMPLETER !!!!!!!!!!!
		// Utilisez : vecObj_[i]->afficherObjetEmpruntable(cout);
		
	}

	if (!trouve)
	{
		cout << "Aucun Resultat Trouve :-(" << endl;
	}
}


bool Bibliotheque::estEmpruntable(const std::string & matricule, const ObjetEmpruntable & objetEmpruntable) const
{	// V�rifie si les conditions de bases sont respect�es et va v�rifier aussi parmi les �l�ments d�riv�s d'Abonne
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


// Emprunte l'objet selon d'apr�s sa cote pour la personne correspondant au matricule
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
			// !!!!!!!!!! A COMPLETER !!!!!!!!!!!
		}
	}

	return peutEmprunte;

}

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

// Afficher l'information de l'abonn� correspondant au matricule
void Bibliotheque::infoAbonne(const string& matricule) const
{
	//On doit v�rifier que tous les vecteurs sont parcourus
	Abonne* ab = trouverAbonne(matricule);

	if (ab != nullptr)
	{
		// !!!!!!!!!! A COMPLETER !!!!!!!!!!!
		// Utilisez dynamic_cast<>()  pour convertir les types de pointeurs et appeler le bon op�rateur <<
	}
	else
	{
		cout << "Abonne - " << matricule << " - non trouve" << endl;
	}

}

Bibliotheque & Bibliotheque::operator+=(Abonne * abonne)
{
	
	ajouterAbonne(*abonne);
	return *this;
}


Bibliotheque & Bibliotheque::operator+=(ObjetEmpruntable * obj)
{
	ajouterObjetEmpruntable(obj);
	return *this;
}


Bibliotheque & Bibliotheque::operator-=(Abonne * abonne)
{
	retirerAbonne(abonne->obtenirMatricule());
	return *this;
}

Bibliotheque & Bibliotheque::operator-=(ObjetEmpruntable * obj)
{
	retirerObjetEmpruntable(obj->obtenirCote());
	return *this;
}

std::istream & operator>>(std::istream & in, const Bibliotheque & biblio)
{
	string mot;
	in >> mot;
	biblio.rechercherObjetEmpruntable(mot);
	return in;
}


