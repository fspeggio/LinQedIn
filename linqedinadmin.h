#ifndef LINQEDINADMIN_H
#define LINQEDINADMIN_H

#include "db.h"

class LinQedInAdmin{
private:
	DB* db; 
public:	
	
	//costruttore
	LinQedInAdmin();

	//distruttore
	~LinQedInAdmin();
	
	//salvataggio
	void save() const;

	//inserimento
	void insert(string, string, string, string, string) throw(Gia_Presente);

	//rimozione
	void remove(Username) throw(Non_Presente);

	//ricerca nome e/o cognome
	string find(string, string) const throw (Non_Presente);
	
	//ricerca username
	string find(Username)const throw (Non_Presente);
	
	//cambio tipologia di account di un utente
	void changeSubscriptionType(Username, string) throw(Tipo_Utente_Errato, Non_Presente, Stesso_Tipo);

	string showDb() const;
};

#endif