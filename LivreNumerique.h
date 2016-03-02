#ifndef LIVRENUMERIQUE_H
#define LIVRENUMERIQUE_H


#include "ObjetNumerique.h"
#include "Livre.h"
#include <string>
#include <iostream>


/* Enumeration pour les types de documents possibles
- FORMAT_PDF:		Le format du livre est en "pdf"
- FORMAT_EPUB:		Le format du livre est en "epub"
- FORMAT_DOCX:		Le format du livre est en "docx"
- FORMAT_TXT:		Le format du livre est en "txt"
- FORMAT_INCONNU :	Le format du livre est inconnu
*/
enum FORMAT_DOCUMENT
{
	FORMAT_PDF		= 0,
	FORMAT_EPUB		= 1,
	FORMAT_DOCX		= 2,
	FORMAT_TXT		= 3,
	FORMAT_INCONNU	= 4,
};



class LivreNumerique :	public ObjetNumerique, public Livre
{
public:
	
	
	

private:
	FORMAT_DOCUMENT format_;
	unsigned int tailleOctet_;
	std::string lien_;

};


#endif // LIVRENUMERIQUE_H
