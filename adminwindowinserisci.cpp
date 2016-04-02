#include "adminwindowinserisci.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <string>
using namespace std;

AdminWindowInserisci::AdminWindowInserisci(QWidget* parent, LinQedInAdmin* y) : QWidget(parent), x(y) {
    
    setWindowTitle(tr("AdminWindowInserisci"));
    QVBoxLayout* mainLayout=new QVBoxLayout();
   
    QGroupBox* form=new QGroupBox();
    QGridLayout* formLayout=new QGridLayout();
   
    //form dati nuovo utente
    QLabel* loginLabel=new QLabel(tr("Login:"));
    QLabel* nomeLabel=new QLabel(tr("Nome:"));
    QLabel* cognomeLabel=new QLabel(tr("Cognome:"));
    QLabel* emailLabel=new QLabel(tr("E-mail:"));
    QLabel* tipoLabel=new QLabel(tr("Tipo Account:"));

    formLayout->addWidget(loginLabel,0,0);
    formLayout->addWidget(nomeLabel,1,0);
    formLayout->addWidget(cognomeLabel,2,0);
    formLayout->addWidget(emailLabel,3,0);
    formLayout->addWidget(tipoLabel,4,0);

    login=new QLineEdit();
    nome=new QLineEdit();
    cognome=new QLineEdit();
    email=new QLineEdit();
    basic=new QRadioButton("Basic");
    business=new QRadioButton("Business");
    executive=new QRadioButton("Executive");
    mess=new QTextEdit();
    mess->setReadOnly(true);
    mess->setMaximumHeight(50);
    mess->setMaximumWidth(500);

    formLayout->addWidget(login,0,1);
    formLayout->addWidget(nome,1,1);
    formLayout->addWidget(cognome,2,1);
    formLayout->addWidget(email,3,1);
    formLayout->addWidget(basic,4,1);
    formLayout->addWidget(business,5,1);
    formLayout->addWidget(executive,6,1);
    form->setLayout(formLayout);
    mainLayout->addWidget(form);
    
    //pulsante inserisci
    QPushButton* ins=new QPushButton(tr("Inserisci"));
    mainLayout->addWidget(ins);
    connect(ins, SIGNAL(clicked()), this, SLOT(inserisci()));

    //pulsante inserisci
    QPushButton* insNuovo=new QPushButton(tr("Inserisci nuovo utente"));
    mainLayout->addWidget(insNuovo);
    connect(insNuovo, SIGNAL(clicked()), this, SLOT(inserisciNuovo()));

    mainLayout->addWidget(mess);

    //uscita
    QPushButton* close=new QPushButton(tr("Esci"));
    connect(close, SIGNAL(clicked()), this, SLOT(close()));
    mainLayout->addWidget(close);
   
    //applica il layout
    setLayout(mainLayout);
}

void AdminWindowInserisci::inserisci(){
        try{
            string l=login->text().toUtf8().constData();
            string n=nome->text().toUtf8().constData();
            string c=cognome->text().toUtf8().constData();
            string t="UtenteBasic";
            if(basic->isChecked())
                t="UtenteBasic";
            if(business->isChecked())
                t="UtenteBusiness";
            if(executive->isChecked())
                t="UtenteExecutive";
            if(l!="" && n!="" && c!=""){
                x->insert(l,n,c,email->text().toUtf8().constData(),t);
                mess->setText(tr("Inserimento del nuovo utente effettuato correttamente"));
            }
            else
                mess->setText("Login, nome e cognome sono obbligatori.");
        }
        catch(Gia_Presente){
            mess->setText(tr("E' già presente un utente con lo stesso username nel database. \nImpossibile effettuare l'inserimento."));
        }      
}

void AdminWindowInserisci::inserisciNuovo(){
    login->setText("");
    nome->setText("");
    cognome->setText("");
    email->setText("");
    basic->setChecked(true);
    business->setChecked(false);
    executive->setChecked(false);
    mess->setText("");
}