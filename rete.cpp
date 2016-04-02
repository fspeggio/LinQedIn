#include "rete.h"

list<Username> Rete::getNet() const {return net;}

void Rete::setNet(const list<Username>& l){net=l;}

void Rete::add(Username u) throw (Gia_Presente) {
	bool trovato=(*this).presente(u);
	if(!trovato){	
		Username usr(u);
		net.push_back(usr);
	}
	else
		throw Gia_Presente();
}

void Rete::remove(Username u) throw (Non_Presente){
    bool trovato=false;
	for(list<Username>::iterator it=net.begin(); it!=net.end(); ++it){
 		if(*it==u){
        	trovato=true;
			it=net.erase(it);
			return;
    	}
	} 
	if(!trovato){
        throw Non_Presente();
    }
}

string Rete::reteToString() const {
	string s="";
	for(list<Username>::const_iterator it=net.begin(); it!=net.end(); ++it){
		s=s+((*it).getLogin())+"; ";
	}
	return s;
}

Rete* Rete::stringToRete(string s){
	Rete* r=new Rete();
	if(s=="")
		return r;
	unsigned int i=0;
	while(i<s.length()){
		string x="";
		while(s[i]!=';'){
			x=x+s[i];
			++i; 
		}
		i=i+2;
		Username u(x);
		r->add(u);
	}
	return r;
}

bool Rete::presente(Username u) const{
	bool trovato=false;
	for(list<Username>::const_iterator it=net.begin(); it!=net.end(); ++it){
		if((*it)==u)
			trovato=true;
	}
	return trovato;
}