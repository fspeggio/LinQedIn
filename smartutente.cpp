#include "smartutente.h"

//costruttore
SmartUtente::SmartUtente(Utente* x) : u(x) {}

//costruttore di copia
SmartUtente::SmartUtente(const SmartUtente& s) {
	u=s.u->clone();
}

SmartUtente& SmartUtente::operator=(const SmartUtente& su){
	if(this!=&su){
		if(u)
			delete u;
		u=su.u->clone();
	}
	return *this;
}

//distruttore
SmartUtente::~SmartUtente(){
	if(u){
		delete u;
	}

}

Utente& SmartUtente::operator*() const{
	return *u;
}

Utente* SmartUtente::operator->() const{
	return u;
}

bool SmartUtente::operator==(const SmartUtente& su) const{
	return *u==*(su.u);
}

bool SmartUtente::operator!=(const SmartUtente& su) const{
	return !(*u==*(su.u));
}

Utente* SmartUtente::getUtente() const{
	return u;
}