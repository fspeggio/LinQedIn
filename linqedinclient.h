#ifndef LINQEDINCLIENT_H
#define LINQEDINCLIENT_H
#include "db.h"

//eccezione sollevata nel caso in cui un utente voglia inserire
//se stesso nella propria rete
class Stesso_Utente{};

class LinQedInClient{
private:
	Utente* u;
	DB* db;

public:

	LinQedInClient(Username) throw(Non_Presente); //costruttore
	~LinQedInClient(); //distruttore

	//aggiornamento del profilo
	void aggiornaProfilo(string ="", string ="", string ="", string ="", string ="", string ="", string ="", string ="", string ="");

	//inserimento di un contatto nella rete
	void insertRete(Username) throw (Non_Presente, Gia_Presente, Stesso_Utente);

	//rimozione di un contatto dalla rete
	void removeRete(Username) throw (Non_Presente);

	//ricarca in base alla tipologia di account
	string ricerca(string ="", string ="");

	string showProfilo() const;
};

#endif