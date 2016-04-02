#ifndef USERWINDOWAGGIORNA_H
#define USERWINDOWAGGIORNA_H

#include "userwindow.h"
#include "linqedinclient.h"
#include <QWidget>

class QLineEdit;
class QTextEdit;

class UserWindowAggiorna : public QWidget {
		Q_OBJECT
private:
	LinQedInClient* x;

	//componenti grafiche
	QTextEdit* profilo;
	QLineEdit* email;
	QLineEdit* titoloAdd;
	QLineEdit* titoloRemove;
	QLineEdit* linguaAdd;
	QLineEdit* linguaRemove;
	QLineEdit* competenzaAdd;
	QLineEdit* competenzaRemove;
	QLineEdit* esperienzaAdd;
	QLineEdit* esperienzaRemove;
public:
	UserWindowAggiorna(QWidget* =0, LinQedInClient* =0); //costruttore

public slots:	
	void showProfilo();
	void modificaProfilo();
};

#endif