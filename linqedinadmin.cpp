#include "linqedinadmin.h"
#include <list>
using namespace std;

LinQedInAdmin::LinQedInAdmin(){
	db=new DB();
	db->load(); //carico il database con i dati del file xml
}

LinQedInAdmin::~LinQedInAdmin(){
	if(db) delete db;
}

void LinQedInAdmin::save() const{
	db->save();
}

void LinQedInAdmin::insert(string usr, string n, string c, string e, string tipo) throw(Gia_Presente){
	list<string> l;
	if(tipo=="UtenteBasic"){
		UtenteBasic* u=new UtenteBasic(Username(usr));
		SmartUtente x(u);
		x->setProfilo(n,c,e,l,l,l,l);
		db->add(x);
	}
	else{
		if(tipo=="UtenteBusiness"){
			UtenteBusiness* u=new UtenteBusiness(Username(usr));
			SmartUtente y(u);
			y->setProfilo(n,c,e,l,l,l,l);
			db->add(y);
		}
		else{ //executive 
			UtenteExecutive* u=new UtenteExecutive(Username(usr));
			SmartUtente z(u);
			z->setProfilo(n,c,e,l,l,l,l);
			db->add(z);
		}
	}
}

void LinQedInAdmin::remove(Username u) throw(Non_Presente){
	db->remove(u);
	//rimozione di u da tutte le reti degli utenti del db
	db->removeUsrReti(u);
}

string LinQedInAdmin::find(string n, string c) const throw (Non_Presente){
	list<SmartUtente> l=db->find(n,c);
	string s;
	for(list<SmartUtente>::const_iterator it=l.begin(); it!=l.end(); ++it){
		s=s+(**it).utenteToString();
	}
	s=s+"\n\n";
	return s;
}

string LinQedInAdmin::find(Username usr) const throw (Non_Presente){
	SmartUtente* u=db->find(usr);
	return (**u).utenteToString();
}

void LinQedInAdmin::changeSubscriptionType(Username usr, string s) throw(Tipo_Utente_Errato, Non_Presente, Stesso_Tipo){
	SmartUtente* su=db->find(usr);
	db->cambiaTipoAccount((*su)->getUsr(),s);
}

string LinQedInAdmin::showDb() const{
	string s=db->dbToString();
	return s;
}