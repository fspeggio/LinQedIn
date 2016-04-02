#include "linqedinclient.h"
#include <iostream>
using namespace std;

LinQedInClient::LinQedInClient(Username s) throw(Non_Presente){
	db=new DB();
	db->load();
	u=db->cerca(s); //ritorna l'utente del db riferito allo username passato
}

LinQedInClient::~LinQedInClient(){
	if(db) delete db;	
}

void LinQedInClient::aggiornaProfilo(string e, string tA, string tR, string lA, string lR, string compA, string compR, string espA, string espR){
	u->aggiornaProfilo(e,tA,tR,lA,lR,compA,compR,espA,espR);
	db->save();
}

void LinQedInClient::insertRete(Username usr) throw (Non_Presente, Gia_Presente, Stesso_Utente){
	if(u->getUsr()!=usr){
		bool b=db->presente(usr);
		if(!b)
			throw Non_Presente();
		else{
			u->getR()->add(usr);
			db->save();	
		}
	}
	else
		throw Stesso_Utente();
}

void LinQedInClient::removeRete(Username usr) throw (Non_Presente){
	u->getR()->remove(usr);
	db->save();
}

string LinQedInClient::ricerca(string n, string c){
	string s=u->userSearch(*db,n,c);
	return s;
}

string LinQedInClient::showProfilo() const {
	string s;
	s=u->utenteToString();
	return s;
}
