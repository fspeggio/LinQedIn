#include "profilo.h"

//selettori
string Profilo::getNome() const {return nome;}

string Profilo::getCognome() const {return cognome;}

string Profilo::getEmail() const {return email;}

list<string> Profilo::getTitoliDiStudio() const {return titoliDiStudio;}

list<string> Profilo::getLingue() const {return lingue;}

list<string> Profilo::getCompetenze() const {return competenze;}

list<string> Profilo::getEsperienze() const {return esperienze;}

//aggiornamento campi dati
void Profilo::setNome(string n) {nome=n;}

void Profilo::setCognome(string c) {cognome=c;}

void Profilo::setEmail(string e) {email=e;}

void Profilo::setTitoli(const list<string>& l) {titoliDiStudio=l;}

void Profilo::setLingue(const list<string>& l) {lingue=l;}

void Profilo::setCompetenze(const list<string>& l) {competenze=l;}

void Profilo::setEsperienze(const list<string>& l) {esperienze=l;}

//add
void Profilo::addTitolo(string s){
	if(!presente(titoliDiStudio,s))
		titoliDiStudio.push_back(s);
}

void Profilo::addLingua(string s){
	if(!presente(lingue,s))
		lingue.push_back(s);
}

void Profilo::addCompetenza(string s){
	if(!presente(competenze,s))
		competenze.push_back(s);
}

void Profilo::addEsperienza(string s){
	if(!presente(esperienze,s))
		esperienze.push_back(s);
}

//remove
void Profilo::removeTitolo(string s) {
	for(list<string>::iterator it=titoliDiStudio.begin(); it!=titoliDiStudio.end(); ++it){
		if((*it)==s){
			titoliDiStudio.erase(it);
			return;
		}
	}
}

void Profilo::removeLingua(string s) {
	for(list<string>::iterator it=lingue.begin(); it!=lingue.end(); ++it){
		if((*it)==s){
			lingue.erase(it);
			return;
		}
	}
}

void Profilo::removeCompetenza(string s) {
	for(list<string>::iterator it=competenze.begin(); it!=competenze.end(); ++it){
		if((*it)==s){
			competenze.erase(it);
			return;
		}
	}
}

void Profilo::removeEsperienza(string s) {
	for(list<string>::iterator it=esperienze.begin(); it!=esperienze.end(); ++it){
		if((*it)==s){
			esperienze.erase(it);
			return;
		}
	}
}

//restituisce una stringa contente tutti i nodi della lista
string Profilo::listToString(const list<string>& l){
	string s="";
	for(list<string>::const_iterator it=l.begin(); it!=l.end(); ++it){
		s=s+(*it)+"; ";
	}
	return s;
}

//restituisce una lista in cui ogni nodo contiene un pezzo singolo di stringa
list<string> Profilo::stringToList(string s){
	list<string> l;
	unsigned int i=0;
	while(i<s.length()){
		string x="";
		while(s[i]!=';'){
			x=x+s[i];
			++i; 
		}
		i=i+2;
		l.push_back(x);
	}
	return l;
} 

string Profilo::profiloToString() const{
	string s="Nome: " + nome + 
			"\nCognome: " + cognome +
			"\nE-mail: " + email + 
			"\nTitoli di studio: " + listToString(titoliDiStudio) +
			"\nLingue: " + listToString(lingue) +
			"\nCompetenze: " + listToString(competenze) +
			"\nEsperienze: " + listToString(esperienze) + "\n";
	return s;
}

bool Profilo::presente(const list<string>& l, string s){
	bool trovato=false;
	for(list<string>::const_iterator it=l.begin(); it!=l.end(); ++it){
		if(*it==s)
			trovato=true;
	}
	return trovato;
}
