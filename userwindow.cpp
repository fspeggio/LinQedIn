#include "userwindow.h"
#include "userwindowaggiorna.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QGroupBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>

UserWindow::UserWindow(Username usr, QWidget* parent) : QWidget(parent) {
    
    x=new LinQedInClient(usr); //contiene un utente e un database

    setWindowTitle(tr("UserWindow"));
    QVBoxLayout* mainLayout=new QVBoxLayout();

    //mostra profilo
    QGroupBox* mostraBox=new QGroupBox(tr("Mostra profilo"));
    QVBoxLayout* mostraLayout=new QVBoxLayout();
    QPushButton* mostraProfilo=new QPushButton(tr("Mostra profilo"));
    connect(mostraProfilo, SIGNAL(clicked()), this, SLOT(showProfilo()));
    mostraLayout->addWidget(mostraProfilo);
    mostraBox->setLayout(mostraLayout);
    mainLayout->addWidget(mostraBox);

    //Aggiornamento profilo
    QGroupBox* aggiornaBox=new QGroupBox(tr("Aggiornamento del profilo"));
    QVBoxLayout* aggiornaLayout=new QVBoxLayout();
    QPushButton* aggiorna=new QPushButton(tr("Aggiorna"));
    connect(aggiorna, SIGNAL(clicked()), this, SLOT(openUserWindowAggiorna()));
    aggiornaLayout->addWidget(aggiorna);
    aggiornaBox->setLayout(aggiornaLayout);
    mainLayout->addWidget(aggiornaBox);

    //inserimento e rimozione contatto dalla rete
    QGroupBox* reteBox=new QGroupBox(tr("Inserimento e rimozione contatti dalla rete"));
    QGridLayout* reteLayout=new QGridLayout();
    QLabel* aggiungiLabel=new QLabel(tr("Username da aggiungere:"));
    QLabel* rimuoviLabel=new QLabel(tr("Username da rimuovere:"));
    reteAggiungi=new QLineEdit();
    reteRimuovi=new QLineEdit();
    QPushButton* aggiungi=new QPushButton(tr("Aggiungi"));
    QPushButton* rimuovi=new QPushButton(tr("Rimuovi"));
    connect(aggiungi, SIGNAL(clicked()), this, SLOT(addRete()));
    connect(rimuovi, SIGNAL(clicked()), this, SLOT(removeRete()));
    reteLayout->addWidget(aggiungiLabel,0,0);
    reteLayout->addWidget(reteAggiungi,0,1);
    reteLayout->addWidget(aggiungi,0,2);
    reteLayout->addWidget(rimuoviLabel,1,0);
    reteLayout->addWidget(reteRimuovi,1,1);
    reteLayout->addWidget(rimuovi,1,2);
    reteBox->setLayout(reteLayout);
    mainLayout->addWidget(reteBox);

    //ricerca utenti
    QGroupBox* ricercaBox=new QGroupBox(tr("Ricerca utenti"));
    QGridLayout* ricercaLayout=new QGridLayout();
    QLabel* nomeLabel=new QLabel(tr("Nome:"));
    QLabel* cognomeLabel=new QLabel(tr("Cognome:"));
    nome=new QLineEdit();
    cognome=new QLineEdit();
    QPushButton* cerca=new QPushButton(tr("Cerca utente"));
    connect(cerca, SIGNAL(clicked()), this, SLOT(cerca()));
    ricercaLayout->addWidget(nomeLabel,0,0);
    ricercaLayout->addWidget(nome,0,1);
    ricercaLayout->addWidget(cognomeLabel,1,0);
    ricercaLayout->addWidget(cognome,1,1);
    ricercaLayout->addWidget(cerca,2,1);
    ricercaBox->setLayout(ricercaLayout);
    mainLayout->addWidget(ricercaBox);

    //messaggi
    mess=new QTextEdit();
    mess->setReadOnly(true);
    mainLayout->addWidget(mess);

    //uscita area utente
    QGroupBox* esciBox=new QGroupBox(tr("Esci dall'area dedicata all'utente"));
    QVBoxLayout* esciLayout=new QVBoxLayout();
    QPushButton* close=new QPushButton(tr("Esci"));
    connect(close, SIGNAL(clicked()), this, SLOT(close())); 
    esciLayout->addWidget(close);  
    esciBox->setLayout(esciLayout);
    mainLayout->addWidget(esciBox);

    setLayout(mainLayout);
}

void UserWindow::showProfilo(){
	string str=x->showProfilo();
    QString qs=QString::fromStdString(str);
    mess->setText(qs);
}

void UserWindow::addRete(){
	if(reteAggiungi->text()=="")
		mess->setText(tr("Specificare lo username da aggiungere."));
	else{
		try{
			x->insertRete(Username(reteAggiungi->text().toUtf8().constData()));
			mess->setText(tr("Utente inserito correttamente nella rete di contatti."));
		}
		catch(Non_Presente){
			mess->setText(tr("Utente non presente nel database."));
		}
		catch(Gia_Presente){
			mess->setText(tr("Utente già presente nella rete di contatti"));
		}
        catch(Stesso_Utente){
            mess->setText(tr("Operazione non consentita.\nStai tentando di aggiungere te stesso alla tua rete."));
        }
	}
}

void UserWindow::removeRete(){
	if(reteRimuovi->text()=="")
		mess->setText(tr("Specificare lo username da rimuovere."));
	else{
		try{
			x->removeRete(Username(reteRimuovi->text().toUtf8().constData()));
			mess->setText(tr("Utente rimosso correttamente dalla rete di contatti."));
		}
		catch(Non_Presente){
			mess->setText(tr("Utente non presente nella rete."));
		}
	}
}

void UserWindow::openUserWindowAggiorna(){
	uw=new UserWindowAggiorna(0,x);
	uw->show();
}

void UserWindow::cerca(){
    try{
        string n=nome->text().toUtf8().constData();
        string c=cognome->text().toUtf8().constData();
        string str=x->ricerca(n,c);
        QString qs=QString::fromStdString(str);
        mess->setText(qs);
    }
    catch(Non_Presente){
        mess->setText(tr("Nessun utente nel database soddisfa i criteri di ricerca"));
    }
}