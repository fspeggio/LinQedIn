#ifndef SMARTUTENTE_H
#define SMARTUTENTE_H
#include "utente.h"

//dichiarazione incompleta di classe
class Utente;

class SmartUtente{
private:
	Utente* u;
public:
	SmartUtente(Utente* =0); //costruttore
	SmartUtente(const SmartUtente&); //costruttore di copia
	SmartUtente& operator=(const SmartUtente&);
	~SmartUtente(); //distruttore
	Utente& operator*() const;
	Utente* operator->() const;
	bool operator==(const SmartUtente&) const;
	bool operator!=(const SmartUtente&) const;
	Utente* getUtente() const;
	
};

#endif