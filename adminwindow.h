#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include "linqedinadmin.h"
#include <QWidget>
#include "adminwindowinserisci.h"

class QLineEdit;
class QTextEdit;
class QRadioButton;

class AdminWindow : public QWidget {
	Q_OBJECT
public:
    AdminWindow(QWidget* =0); //costruttore 

private:
	LinQedInAdmin* x;

	//componenti grafiche
	QLineEdit* usrRimuovi;
	QLineEdit* nome;
	QLineEdit* cognome;
	QLineEdit* login;
	QLineEdit* usrModifica;
	QRadioButton* basic;
	QRadioButton* business;
	QRadioButton* executive;
	QTextEdit* mess;

	//finestra figlia
	AdminWindowInserisci* awi;

public slots:
	void openAdminWindowInserisci();
	void remove();	
	void showDb();
	void modifica();
	void salva();
	void cercaNomeCognome();
	void cercaUsername();
};

#endif	