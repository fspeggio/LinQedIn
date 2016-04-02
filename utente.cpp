#include "utente.h"

//costruttore
Utente::Utente(Username u) : usr(u) {
	r=new Rete();
}

//distruttore
Utente::~Utente(){
	if(r)
		delete r;
}

//costruttore di copia 
Utente::Utente(const Utente& u) : pf(u.pf), usr(u.usr) {
	r=new Rete(*(u.r));// invoca il costruttore di copia standard di rete
}

Utente& Utente::operator=(const Utente& u){
	if(this!=&u){
		pf=u.pf;
		usr=u.usr;
		if(r)
			delete r;
		r=new Rete((*u.r));
	}
	return *this;
}

bool Utente::operator==(const Utente& u) const{
	if(usr==u.usr)
		return true;
	else
		return false;
}

//selettori dei campi dati
Profilo Utente::getPf() const{return pf;}

Rete* Utente::getR() const{return r;}

Username Utente::getUsr() const{return usr;}

void Utente::setPf(const Profilo& p){pf=p;}

void Utente::setUsr(const Username& u){usr=u;}

void Utente::setR(Rete* x){r=x;}

void Utente::setProfilo(string n, string c, string e, const list<string>& t, 
						const list<string>& l, const list<string>& comp, 
						const list<string>& esp){
 	pf.setNome(n);
 	pf.setCognome(c);
 	pf.setEmail(e);
 	pf.setTitoli(t);
 	pf.setLingue(l);
 	pf.setCompetenze(comp);
 	pf.setEsperienze(esp);
}

void Utente::aggiornaProfilo(string e, string tA, string tR, string lA, string lR, string compA, string compR, string espA, string espR){
	if(e!="")	
		pf.setEmail(e);
	if(tA!="")
		pf.addTitolo(tA);
	if(tR!="")
		pf.removeTitolo(tR);
	if(lA!="")
		pf.addLingua(lA);
	if(lR!="")
		pf.removeLingua(lR);
	if(compA!="")
		pf.addCompetenza(compA);
	if(compR!="")
		pf.removeCompetenza(compR);
	if(espA!="")
		pf.addEsperienza(espA);
	if(espR!="")
		pf.removeEsperienza(espR);
}

string Utente::utenteToString() const{
	string s="";
	string t;
	//controllo il tipo per stamparlo
	Utente* u=const_cast<Utente*>(this);
	UtenteBasic* x=dynamic_cast<UtenteBasic*>(u);
	if(x) t="Basic";
	UtenteBusiness* y=dynamic_cast<UtenteBusiness*>(u);
	if(y) t="Business";
	UtenteExecutive* z=dynamic_cast<UtenteExecutive*>(u);
	if(z) t="Executive";
	s=s + "Tipo utente: " + t + "\n";
	s=s + "Login: " + (*this).getUsr().getLogin() + "\n";
	s=s + (*this).getPf().profiloToString();
	s=s+"Rete: " + (*this).getR()->reteToString() + "\n\n";
	return s;
}

//costruttori classi derivate
UtenteBasic::UtenteBasic(Username u) : Utente(u) {}

UtenteBusiness::UtenteBusiness(Username u) : Utente(u) {}

UtenteExecutive::UtenteExecutive(Username u) : Utente(u) {}

Utente* UtenteBasic::clone() const{
	return new UtenteBasic(*this); 
}

Utente* UtenteBusiness::clone() const{
	return new UtenteBusiness(*this);
}

Utente* UtenteExecutive::clone() const{
	return new UtenteExecutive(*this);
}

UtenteBasic::UtenteBasic(const Utente& u){
	(*this).setPf(u.getPf());
	(*this).setR(new Rete(*u.getR()));
	(*this).setUsr(u.getUsr());
}

UtenteBusiness::UtenteBusiness(const Utente& u){
	(*this).setPf(u.getPf());
	(*this).setR(new Rete(*u.getR()));
	(*this).setUsr(u.getUsr());
}

UtenteExecutive::UtenteExecutive(const Utente& u){
	(*this).setPf(u.getPf());
	(*this).setR(new Rete(*u.getR()));
	(*this).setUsr(u.getUsr());
}

//funtori
string UtenteBasic::userSearch(const DB& d, string n, string c) const{
	//per escludere dalla stampa l'utente stesso
	string login=(*this).getUsr().getLogin();
	list<SmartUtente> l=d.find(n,c);
	SearchFunctor f(1);
	string s=f(l,login);
	return s;
}

string UtenteBusiness::userSearch(const DB& d, string n, string c) const{
	//per escludere dalla stampa l'utente stesso
	string login=(*this).getUsr().getLogin();
	list<SmartUtente> l=d.find(n,c);
	SearchFunctor f(2);
	string s=f(l,login);
	return s;
}

string UtenteExecutive::userSearch(const DB& d, string n, string c) const{
	//per escludere dalla stampa l'utente stesso
	string login=(*this).getUsr().getLogin();
	list<SmartUtente> l=d.find(n,c);
	SearchFunctor f(3);
	string s=f(l,login);
	return s;
}


//metodi della classe SearchFunctor
//costruttore
Utente::SearchFunctor::SearchFunctor(int x) : searchType(x) {}

//operator()
string Utente::SearchFunctor::operator() (const list<SmartUtente>& l, string login) const{
	string s="";
	switch(searchType){
		case 1:
			for(list<SmartUtente>::const_iterator it=l.begin(); it!=l.end(); ++it){
				if(login!=(*it)->getUsr().getLogin())
					s=s+"Login: "+(*it)->getUsr().getLogin()+"\nNome: "+(*it)->getPf().getNome()+"\nCognome: "+(*it)->getPf().getCognome()+"\n\n";
			}
			return s;
			break;
		case 2:
			for(list<SmartUtente>::const_iterator it=l.begin(); it!=l.end(); ++it){
				if(login!=(*it)->getUsr().getLogin()){
					s=s+"Login: "+(*it)->getUsr().getLogin()+"\n";
					s=s+(*it)->getPf().profiloToString()+"\n\n";
				}
			}
			return s;
			break;
		case 3:
			for(list<SmartUtente>::const_iterator it=l.begin(); it!=l.end(); ++it){
				if(login!=(*it)->getUsr().getLogin())
					s=s+(**it).utenteToString()+"\n\n";
			}
			return s;
			break;
		default:
			for(list<SmartUtente>::const_iterator it=l.begin(); it!=l.end(); ++it){
				s=s+"Login: "+(*it)->getUsr().getLogin()+"\n\n";
			}
			return s;
	}
}
