#ifndef UTENTE_H
#define UTENTE_H	

#include "profilo.h"
#include "username.h"
#include "rete.h"
#include "db.h"
#include "smartutente.h"
#include <list>
using namespace std;

//definizione incompleta di classi
class DB;
class SmartUtente;

//classe base polimorfa astratta
class Utente{
private:
	Profilo pf; 
	Rete* r; 
	Username usr; 

protected:
	
	class SearchFunctor{
	public:
		int searchType;
		SearchFunctor(int =0); //costruttore
		string operator() (const list<SmartUtente>& l, string) const;
	};

public:
	Utente(Username =Username(" ")); //costruttore
	virtual ~Utente(); //distruttore virtuale
	Utente(const Utente&); //costruttore di copia
	Utente& operator=(const Utente&); 
	bool operator==(const Utente&) const;

	//metodi virtuali puri
	virtual Utente* clone() const =0; 
	virtual string userSearch(const DB& d, string, string) const =0;

	//selettori
	Profilo getPf() const;
	Rete* getR() const;
	Username getUsr() const;

	void setPf(const Profilo&);
	void setUsr(const Username&);
	void setR(Rete*);
	
	void setProfilo(string, string, string, const list<string>&, const list<string>&, const list<string>&, const list<string>&);
	void aggiornaProfilo(string ="", string ="", string ="", string ="", string ="", string ="", string ="", string ="", string ="");

	string utenteToString() const;
};

class UtenteBasic : public Utente{
public:
	UtenteBasic(Username);//costruttore
	virtual Utente* clone() const;
	UtenteBasic(const Utente&); //costruttore 

	//funtore di tipo 1
	virtual string userSearch(const DB&, string, string) const;
	
};

class UtenteBusiness : public Utente{
public:
	UtenteBusiness(Username);//costruttore
	virtual Utente* clone() const;
	UtenteBusiness(const Utente&);//costruttore 

	//funtore di tipo 2
	virtual string userSearch(const DB&, string, string) const;
};

class UtenteExecutive : public Utente{
public:
	UtenteExecutive(Username);//costruttore
	virtual Utente* clone() const;
	UtenteExecutive(const Utente&);//costruttore 

	//funtore di tipo 3
	virtual string userSearch(const DB&, string, string) const;
};

#endif