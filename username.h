#ifndef USERNAME_H
#define USERNAME_H	

#include <string>
using namespace std;

class Username{
private:
	string login;

public:
    Username(string);//costruttore

	//selettore
	string getLogin() const;

	//operatori
	bool operator==(const Username&) const;
	bool operator!=(const Username&) const;
};

#endif
