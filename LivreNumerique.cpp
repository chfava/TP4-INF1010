#include "LivreNumerique.h"


using namespace std;


LivreNumerique::LivreNumerique(){

};

LivreNumerique::LivreNumerique(FORMAT_DOCUMENT format, unsigned int tailleOctet, std::string lien,
	const std::string& cote, const std::string& titre, unsigned int annee,
	unsigned int ageMin, unsigned int nbExemplaires, const std::string& auteur, const std::string& genre):Livre(cote,titre,annee, ageMin,nbExemplaires, auteur, genre), ObjetNumerique(){
	format_ = format;
	tailleOctet_ = tailleOctet;
	lien_ = lien;
};

LivreNumerique::~LivreNumerique(){

};

FORMAT_DOCUMENT LivreNumerique::obtenirFormat()const{
	return format_;
};

void LivreNumerique::modifierFormat(FORMAT_DOCUMENT format){
	format_ = format;
};

unsigned int LivreNumerique::obtenirTailleOctet()const{
	return tailleOctet_;
};

void LivreNumerique::modifierTailleOctet(unsigned int tailleOctet){
	tailleOctet_ = tailleOctet;
};

std::string LivreNumerique::obtenirLien()const{
	return lien_;
};

void LivreNumerique::modifierLien(std::string lien){
	lien_ = lien;
};

std::string LivreNumerique::obtenirFormatStr()const{
	switch (format_){
	case '0' :
		return "pdf";
		break;
	case '1' :
		return "epub";
		break;
	case '2':
		return "docx";
		break;
	case '3':
		return "txt";
		break;
	case '4':
		return "inconnu";
		break;
	}
};
bool LivreNumerique::recherche(const std::string& motsCle) const{
	bool trouvé;
	std::size_t format = obtenirFormatStr().find(convertirMinuscule(motsCle));
	trouvé = Livre::recherche(motsCle) || (format != string::npos)  ;
};

ostream& operator<<(ostream& o, LivreNumerique livreNumerique){
	o << "Objet Numérique: Taille: " << livreNumerique.tailleOctet_ << "Lien Internet: " << livreNumerique.lien_;
	o << Livre(livreNumerique);
	o << endl;
	return o;
};





