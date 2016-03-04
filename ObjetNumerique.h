#ifndef	OBJETNUMERIQUE_H
#define OBJETNUMERIQUE_H




class ObjetNumerique : virtual public ObjetEmpruntable
{
public:

	virtual unsigned int obtenirTailleDoc() const =0;
	virtual string obtenirLien() const=0;

	virtual void modifierTailleDoc() =0;
	virtual void modifierLien() =0;
	
};



#endif

