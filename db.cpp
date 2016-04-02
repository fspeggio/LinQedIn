#include "db.h"
#include <iostream>
#include <QXmlStreamWriter>
#include <QString>
#include <QFile>
#include <QDomDocument>

void DB::load(){
	QDomDocument doc("db");
	
	QFile file("db.xml");
	if (!file.open(QIODevice::ReadOnly))
    	return;
	if (!doc.setContent(&file)) {
    	file.close();
    	return;
	}
	file.close();

	QDomElement root = doc.documentElement(); //ottengo la radice
	if(root.tagName()!="utenti")
		return;

	QDomNode n = root.firstChild(); //recupero il primo utente
	
	//ciclo sugli utenti del file xml
	while(!n.isNull()) { //scorro gli utenti del file			
    	QDomElement e = n.toElement(); 
    	if(!e.isNull()) {
        	    		
    		QDomElement elem;
    		QString qs;

    		//tipo utente
    		QDomNode tipoUtente=e.firstChild(); 	
    		elem=tipoUtente.toElement();
    		qs=elem.text();
    		string t = qs.toUtf8().constData();
    		
    		//profilo	
    		QDomNode profilo=tipoUtente.nextSibling();
    		elem=profilo.toElement();
    		
    			//nome
    			QDomNode nome= elem.firstChild();
    			elem=nome.toElement();
    			qs=elem.text();
	    		string n = qs.toUtf8().constData();
	    			 			
	 			//cognome
	    		QDomNode cognome= nome.nextSibling();
	    		elem=cognome.toElement();
	    		qs=elem.text();
	    		string c = qs.toUtf8().constData();
	    		
	    		//email
	    		QDomNode email= cognome.nextSibling();
	    		elem=email.toElement();
	    		qs=elem.text();
	    		string e = qs.toUtf8().constData();
	    		
		    		//titoli si studio
		    		QDomNode titoli= email.nextSibling();
		    		elem=titoli.toElement();
		    		qs=elem.text();
		    		string tit = qs.toUtf8().constData();
		    		
		    		//lingue
		    		QDomNode lingue= titoli.nextSibling();
		    		elem=lingue.toElement();
		    		qs=elem.text();
		    		string ling = qs.toUtf8().constData();
		    		
		    		//competenze
		    		QDomNode competenze= lingue.nextSibling();
		    		elem=competenze.toElement();
		    		qs=elem.text();
		    		string comp = qs.toUtf8().constData();
		    		
		    		//esperienze
		    		QDomNode esperienze= competenze.nextSibling();
		    		elem=esperienze.toElement();
		    		qs=elem.text();
		    		string esp = qs.toUtf8().constData();
		    		
    		//rete 
     		QDomNode rete=profilo.nextSibling();
    		elem=rete.toElement();
    		qs=elem.text();
			string r = qs.toUtf8().constData();
    		
    		//login 
    		QDomNode login=rete.nextSibling();
    		elem=login.toElement();
    		qs=elem.text();
    		string l = qs.toUtf8().constData();	
    		
    		list<string> x=Profilo::stringToList(tit);
    		list<string> y=Profilo::stringToList(ling);
    		list<string> z=Profilo::stringToList(comp);
    		list<string> w=Profilo::stringToList(esp);

			//creo un utente
			SmartUtente* su=0;
			if(t=="UtenteBasic"){
				UtenteBasic* u=new UtenteBasic(Username(l));
				su=new SmartUtente(u);
				(*su)->setProfilo(n, c, e, x, y, z, w);
    			(*su)->setR(Rete::stringToRete(r));
    			(*this).add(*su);
			}
			else{
				if(t=="UtenteBusiness"){
					UtenteBusiness* u=new UtenteBusiness(Username(l));
					su=new SmartUtente(u);
					(*su)->setProfilo(n, c, e, x, y, z, w);
					(*su)->setR(Rete::stringToRete(r));
    				(*this).add(*su); 
				}
				else{ //t==UtenteExecutive
					UtenteExecutive* u=new UtenteExecutive(Username(l));
					su=new SmartUtente(u);
					(*su)->setProfilo(n, c, e, x, y, z, w);
					(*su)->setR(Rete::stringToRete(r));
    				(*this).add(*su);
				}
			}
    		
    	}
    	n = n.nextSibling(); //passo al prossimo utente
    }
}

void DB::save() const {
	QFile file("db.xml");
	
	if(!file.open(QFile::WriteOnly | QFile::Text)) {
        std::cerr << "Error: Cannot write file "
                  << qPrintable("db_xml.xml") << ": "
                  << qPrintable(file.errorString()) << std::endl;
        return;
    }

	QXmlStreamWriter stream(&file);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("utenti");
    string s;
    QString qs;
    list<string> l;
	for(vector<SmartUtente>::const_iterator it=db.begin(); it<db.end(); ++it){
		stream.writeStartElement("utente");
		
		//viene salvato il tipo di utente con il dynamic cast
		stream.writeStartElement("tipoUtente");
		UtenteBasic* a=dynamic_cast<UtenteBasic*>((*it).getUtente());
		if(a){ //utente basic
			s="UtenteBasic";
			qs = QString::fromStdString(s);
			stream.writeCharacters(qs);
		}
		UtenteBusiness* b=dynamic_cast<UtenteBusiness*>((*it).getUtente());
		if(b){ //utente basic
			s="UtenteBusiness";
			qs = QString::fromStdString(s);
			stream.writeCharacters(qs);
		}
		UtenteExecutive* c=dynamic_cast<UtenteExecutive*>((*it).getUtente());
		if(c){ //utente basic
			s="UtenteExecutive";
			qs = QString::fromStdString(s);
			stream.writeCharacters(qs);
		}
		stream.writeEndElement();

		stream.writeStartElement("profilo");

		stream.writeStartElement("nome");
		s=(((**it).getPf()).getNome());
		qs = QString::fromStdString(s);
		stream.writeCharacters(qs);
		stream.writeEndElement(); //nome
		
		stream.writeStartElement("cognome");
		s=(((**it).getPf()).getCognome());
		qs = QString::fromStdString(s);
		stream.writeCharacters(qs);
		stream.writeEndElement(); //cognome
		
		stream.writeStartElement("email");
		s=(((**it).getPf()).getEmail());
		qs = QString::fromStdString(s);
		stream.writeCharacters(qs);
		stream.writeEndElement(); //email

		stream.writeStartElement("titoliDiStudio");
		l=(**it).getPf().getTitoliDiStudio();
		s=Profilo::listToString(l);
		qs = QString::fromStdString(s);
		stream.writeCharacters(qs);
		stream.writeEndElement();

		stream.writeStartElement("lingue");
		l=(**it).getPf().getLingue();
		s=Profilo::listToString(l);
		qs = QString::fromStdString(s);
		stream.writeCharacters(qs);
		stream.writeEndElement();
		
		stream.writeStartElement("competenze");
		l=(**it).getPf().getCompetenze();
		s=Profilo::listToString(l);
		qs = QString::fromStdString(s);
		stream.writeCharacters(qs);
		stream.writeEndElement();

		stream.writeStartElement("esperienze");
		l=(**it).getPf().getEsperienze();
		s=Profilo::listToString(l);
		qs = QString::fromStdString(s);
		stream.writeCharacters(qs);
		stream.writeEndElement();
		stream.writeEndElement();//profilo

		stream.writeStartElement("rete");
		if(((**it).getR())){
			s=(*(**it).getR()).reteToString();
			qs = QString::fromStdString(s);
			stream.writeCharacters(qs);
		}
		stream.writeEndElement();//rete

		stream.writeStartElement("login");
		s=(((**it).getUsr()).getLogin());
		qs = QString::fromStdString(s);
		stream.writeCharacters(qs);
		stream.writeEndElement(); //login
		stream.writeEndElement(); //utente
	}
	stream.writeEndElement(); //utenti
    stream.writeEndDocument();
}

vector<SmartUtente> DB::getDb() const{return db;}

void DB::add(SmartUtente u) throw (Gia_Presente){
	bool trovato=(*this).presente(u->getUsr());
	if(!trovato)
		db.push_back(u);
	else
		throw Gia_Presente();
}


void DB::remove(Username u) throw (Non_Presente){
	bool trovato=false;
	for(vector<SmartUtente>::iterator it=db.begin(); it!=db.end(); ++it){
		if((*it)->getUsr()==u){
			trovato=true;
			it=db.erase(it);
			return;
		}
	}
	if(!trovato)
		throw Non_Presente();
}

//ricerca mediante nome e/o cognome
list<SmartUtente> DB::find(string n, string c) const throw (Non_Presente){
	list<SmartUtente> l;
	bool trovato=false;
	if(n!="" && c!=""){ //ricerca mediante nome E cognome
		for(vector<SmartUtente>::const_iterator it=db.begin(); it!=db.end(); ++it){
			if((*it)->getPf().getNome()==n && (*it)->getPf().getCognome()==c){
				trovato=true;
				l.push_back(*it);
			}
		}
	}
	else{ //ricerca mediante nome O cognome
		for(vector<SmartUtente>::const_iterator it=db.begin(); it!=db.end(); ++it){
			if((*it)->getPf().getNome()==n || (*it)->getPf().getCognome()==c){
				trovato=true;
				l.push_back(*it);
			}
		}
	}
	if(!trovato)
		throw Non_Presente();
	else
		return l;
}

//ricerca tramite username
SmartUtente* DB::find(Username s) const throw (Non_Presente){
	bool trovato=false;
	for(vector<SmartUtente>::const_iterator it=db.begin(); it!=db.end(); ++it){
		if((*it)->getUsr()==s){
			trovato=true;
			return new SmartUtente(*it);
		}
	}
	if(!trovato)
		throw Non_Presente();
}

bool DB::presente(Username u) const{
	bool b=false;
	for(vector<SmartUtente>::const_iterator it=db.begin(); it!=db.end(); ++it){
		if((*it)->getUsr()==u){
			b=true;
		}
	}
	return b;
}

void DB::cambiaTipoAccount(Username u, string t) throw(Tipo_Utente_Errato, Non_Presente, Stesso_Tipo) {

	if(t!="UtenteBasic" && t!="UtenteBusiness" && t!="UtenteExecutive")
		throw Tipo_Utente_Errato();

	//tipo utente corretto
	bool trovato=false;
	for(vector<SmartUtente>::iterator it=db.begin(); it!=db.end(); ++it){
		if((*it)->getUsr()==u){
			trovato=true;
			if(t=="UtenteBasic"){
				UtenteBasic* ub=dynamic_cast<UtenteBasic*>((*it).getUtente());
				if(!ub){ 
					ub=new UtenteBasic(**it); 
					*it=ub;
				}
				else
					throw Stesso_Tipo();
			}
			if(t=="UtenteBusiness"){
				UtenteBusiness* ub=dynamic_cast<UtenteBusiness*>((*it).getUtente());
				if(!ub){ 
					ub=new UtenteBusiness(**it); 
					*it=ub;
				}
				else
					throw Stesso_Tipo();
			}
			if(t=="UtenteExecutive"){
				UtenteExecutive* ue=dynamic_cast<UtenteExecutive*>((*it).getUtente());
				if(!ue){ 
					ue=new UtenteExecutive(**it); 
					*it=ue;
				}
				else
					throw Stesso_Tipo();
			}
		}
	}
	if(!trovato)
		throw Non_Presente();
}

Utente* DB::cerca(Username u) const throw(Non_Presente){
	bool trovato=false;
	for(vector<SmartUtente>::const_iterator it=db.begin(); it!=db.end(); ++it){
		if((**it).getUsr()==u){
			trovato=true;
			return (*it).getUtente();
		}
	}
	if(!trovato)
		throw Non_Presente();
}

string DB::dbToString() const {
	string s="";
	for(vector<SmartUtente>::const_iterator it=db.begin(); it!=db.end(); ++it){
			s=s + (**it).utenteToString();
	}
	return s;
}

//rimuove l'usr passato da tutte le reti del db
void DB::removeUsrReti(Username u){
	for(vector<SmartUtente>::iterator it=db.begin(); it!=db.end(); ++it){
		if((**it).getR()->presente(u)){
			(**it).getR()->remove(u);
		}
	}
}