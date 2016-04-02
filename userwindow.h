#ifndef USERWINDOW_H
#define USERWINDOW_H

#include "linqedinclient.h"
#include <QWidget>

class QLineEdit;
class QTextEdit;
class UserWindowAggiorna;

class UserWindow : public QWidget {
		Q_OBJECT
private:
	LinQedInClient* x;
	
	//componenti grafiche
	QLineEdit* reteAggiungi;
    QLineEdit* reteRimuovi;
    QTextEdit* mess;
    QLineEdit* nome;
	QLineEdit* cognome;
	
    //finestra figlia
    UserWindowAggiorna* uw;
public:
	UserWindow(Username,QWidget* =0); //costruttore

public slots:
	void openUserWindowAggiorna();	
	void showProfilo();
	void addRete();
	void removeRete();
	void cerca();
};

#endif