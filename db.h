#ifndef DB_H
#define DB_H	

#include "smartutente.h"
#include "utente.h"
#include <vector>
#include <list>
using namespace std;

//dichiarazioni incomplete di classi
class Utente;
class SmartUtente;

//eccezioni
class Tipo_Utente_Errato{};
class Stesso_Tipo{};

class DB{
private:
	vector<SmartUtente> db;

public:
	
	void load(); //carica i dati dal file
	void save() const; //salva i dati nel file
    
    vector<SmartUtente> getDb() const;

	void add(SmartUtente) throw (Gia_Presente);
	void remove(Username) throw (Non_Presente);

	//ricerca mediante nome e/o cognome
	list<SmartUtente> find(string, string) const throw (Non_Presente); 
	SmartUtente* find(Username) const throw (Non_Presente); //ricerca mediante username
	
	bool presente(Username) const; //controlla se uno usr è presente nel db
	
	void cambiaTipoAccount(Username, string) throw(Tipo_Utente_Errato, Non_Presente, Stesso_Tipo);

	Utente* cerca(Username) const throw(Non_Presente);

	string dbToString() const;

	//si occupa di rimuovere un utente da tutte le reti
	void removeUsrReti(Username);
};



#endif

