#include "username.h"

//costruttore
Username::Username(string s) : login(s) {}

//selettore campo dati
string Username::getLogin() const {return login;}

//operatori
bool Username::operator==(const Username& u) const{
	return login==u.login;
}

bool Username::operator!=(const Username& u) const{
	return login!=u.login;
}