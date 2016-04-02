#ifndef ADMINWINDOWINSERISCI_H
#define ADMINWINDOWINSERISCI_H

#include "linqedinadmin.h"
#include <QWidget>

class QTextEdit;
class QPushButton;
class QLineEdit;
class QRadioButton;

class AdminWindowInserisci : public QWidget {
	Q_OBJECT
private:
	LinQedInAdmin* x;

	//componenti grafiche
	QLineEdit* login;
	QLineEdit* nome;
	QLineEdit* cognome;
	QLineEdit* email;
	QRadioButton* basic;
	QRadioButton* business;
	QRadioButton* executive;
	QTextEdit* mess;
public:
    AdminWindowInserisci(QWidget* =0,LinQedInAdmin* =0); //costruttore 
    
public slots:
	void inserisci();
	void inserisciNuovo();
};
#endif