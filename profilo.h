#ifndef PROFILO_H
#define PROFILO_H		

#include <string>
#include <list>
using namespace std;

class Profilo{
private:
	string nome, cognome, email;
	list<string> titoliDiStudio, lingue, competenze, esperienze;

public:
	
	//selettori dei campi dati
	string getNome() const;
	string getCognome() const;
	string getEmail() const;
	list<string> getTitoliDiStudio() const;
	list<string> getLingue() const;
	list<string> getCompetenze() const;
	list<string> getEsperienze() const;

	//aggiornamento campi dati
	void setNome(string);
	void setCognome(string);
	void setEmail(string);
	void setTitoli(const list<string>&);
	void setLingue(const list<string>&);
	void setCompetenze(const list<string>&);
	void setEsperienze(const list<string>&);

	void addTitolo(string);
	void addLingua(string);
	void addCompetenza(string);
	void addEsperienza(string);

	void removeTitolo(string);
	void removeLingua(string);
	void removeCompetenza(string);
	void removeEsperienza(string);

	static string listToString(const list<string>&);
	static list<string> stringToList(string);

	string profiloToString() const;

	//restituisce true se una certa stringa è contenuta nella lista
	static bool presente(const list<string>&, string);
};

#endif
