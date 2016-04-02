#ifndef RETE_H
#define RETE_H	

#include "username.h"
#include <list>
using namespace std;

//eccezioni
class Non_Presente{};
class Gia_Presente{};

class Rete{
private:
    list<Username> net;

public:

    list<Username> getNet() const; //selettore

    void setNet(const list<Username>&);

	void add(Username) throw (Gia_Presente);
	void remove(Username) throw (Non_Presente);

	string reteToString() const;
	static Rete* stringToRete(string);

	bool presente(Username) const; //controlla se uno usr è presente nella rete
};


#endif


