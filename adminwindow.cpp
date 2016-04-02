#include "adminwindow.h"
#include "adminwindowinserisci.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>


AdminWindow::AdminWindow(QWidget* parent) : QWidget(parent) {
    
    x=new LinQedInAdmin(); //costruisce e riempie il db leggendolo dal file
   
    setWindowTitle(tr("AdminWindow"));
    QGridLayout* mainLayout=new QGridLayout();
    
    //inserimento nuovo utente
    QGroupBox* inserimentoBox=new QGroupBox(tr("Inserimento"));
    QVBoxLayout* inserimentoLayout=new QVBoxLayout();
    QPushButton* inserisci=new QPushButton(tr("Inserisci nuovo utente"));
    connect(inserisci, SIGNAL(clicked()), this, SLOT(openAdminWindowInserisci()));
    inserimentoLayout->addWidget(inserisci,0,0);
    inserimentoBox->setLayout(inserimentoLayout);
    mainLayout->addWidget(inserimentoBox,0,0);
    
    //rimozione di un utente
    QGroupBox* rimozioneBox=new QGroupBox(tr("Rimozione"));
    QGridLayout* rimozioneLayout=new QGridLayout();
    QLabel* l=new QLabel(tr("Username dell'utente da rimuovere:"));
    usrRimuovi=new QLineEdit();
    QPushButton* del=new QPushButton(tr("Rimuovi"));
    rimozioneLayout->addWidget(l,1,0);
    rimozioneLayout->addWidget(usrRimuovi,1,1);
    rimozioneLayout->addWidget(del,1,2);
    connect(del, SIGNAL(clicked()), this, SLOT(remove()));   
    rimozioneBox->setLayout(rimozioneLayout);
    mainLayout->addWidget(rimozioneBox,1,0);
    
    //ricerca
    QGroupBox* ricercaBox=new QGroupBox(tr("Area di ricerca"));
    QGridLayout* ricercaLayout=new QGridLayout();
    QLabel* nomeCognomeLabel=new QLabel(tr("Ricerca tramite nome e cognome"));
    QLabel* usernameLabel=new QLabel(tr("Ricerca tramite username"));
    QLabel* nomeLabel=new QLabel(tr("Nome:"));
    QLabel* cognomeLabel=new QLabel(tr("Cognome:"));
    QLabel* usrLabel=new QLabel(tr("Username:"));
    nome=new QLineEdit();
    cognome=new QLineEdit();
    login=new QLineEdit();
    QPushButton* cercaNomeCognome= new QPushButton(tr("Cerca"));
    connect(cercaNomeCognome, SIGNAL(clicked()), this, SLOT(cercaNomeCognome()));
    QPushButton* cercaUsername=new QPushButton(tr("Cerca"));
    connect(cercaUsername, SIGNAL(clicked()), this, SLOT(cercaUsername()));
    ricercaLayout->addWidget(nomeCognomeLabel,0,0);
    ricercaLayout->addWidget(nomeLabel,1,0);
    ricercaLayout->addWidget(nome,1,1);
    ricercaLayout->addWidget(cognomeLabel,2,0);
    ricercaLayout->addWidget(cognome,2,1);
    ricercaLayout->addWidget(cercaNomeCognome,3,1);
    ricercaLayout->addWidget(usernameLabel,4,0);
    ricercaLayout->addWidget(usrLabel,5,0);
    ricercaLayout->addWidget(login,5,1);
    ricercaLayout->addWidget(cercaUsername,6,1);
    ricercaBox->setLayout(ricercaLayout);
    mainLayout->addWidget(ricercaBox,2,0);

    //modifica tipo utente
    QGroupBox* modificaBox=new QGroupBox(tr("Modifica tipo utente"));
    QGridLayout* modificaLayout=new QGridLayout();
    QLabel* labelUsrModifica=new QLabel(tr("Username utente:"));
    usrModifica=new QLineEdit();
    QLabel* labelTipoModifica=new QLabel(tr("Nuovo tipo:"));
    basic=new QRadioButton("Basic");
    business=new QRadioButton("Business");
    executive=new QRadioButton("Executive");
    QPushButton* modifica=new QPushButton(tr("Modifica"));
    connect(modifica, SIGNAL(clicked()), this, SLOT(modifica()));
    modificaLayout->addWidget(labelUsrModifica,0,0); 
    modificaLayout->addWidget(usrModifica,0,1);
    modificaLayout->addWidget(labelTipoModifica,1,0);
    modificaLayout->addWidget(basic,1,1);
    modificaLayout->addWidget(business,2,1);
    modificaLayout->addWidget(executive,3,1);
    modificaLayout->addWidget(modifica,4,0);
    modificaBox->setLayout(modificaLayout);
    mainLayout->addWidget(modificaBox,3,0);

    //dati db
    QGroupBox* dbBox=new QGroupBox(tr("Database"));
    QVBoxLayout* dbLayout=new QVBoxLayout();
    QPushButton* mostra=new QPushButton(tr("Mostra database"));
    connect(mostra, SIGNAL(clicked()), this, SLOT(showDb()));   
    dbLayout->addWidget(mostra,0,0);
    dbBox->setLayout(dbLayout);
    mainLayout->addWidget(dbBox,0,1);

    //area messaggi
    mess=new QTextEdit();
    mess->setReadOnly(true);
    mess->setMinimumWidth(500);
    mainLayout->addWidget(mess,1,1,5,1);
    
    //salva database
    QGroupBox* salvaBox=new QGroupBox(tr("Salva modifiche"));
    QGridLayout* salvaLayout= new QGridLayout();
    QLabel* labelSalva=new QLabel (tr("Applica tutte le modifiche al database"));
    QPushButton* salva=new QPushButton(tr("Salva modifiche"));
    connect(salva, SIGNAL(clicked()), this, SLOT(salva()));
    salvaLayout->addWidget(labelSalva,0,0);
    salvaLayout->addWidget(salva,0,1);
    salvaBox->setLayout(salvaLayout);
    mainLayout->addWidget(salvaBox,5,0);

    //uscita area amministratore
    QGroupBox* esciBox=new QGroupBox(tr("Esci dall'area dedicata all'amministratore"));
    QVBoxLayout* esciLayout=new QVBoxLayout();
    QPushButton* close=new QPushButton(tr("Esci"));
    connect(close, SIGNAL(clicked()), this, SLOT(close()));   
    esciLayout->addWidget(close,6,0);
    esciBox->setLayout(esciLayout);
    mainLayout->addWidget(esciBox,7,0);

    //applica il layout
    setLayout(mainLayout);
}

void AdminWindow::openAdminWindowInserisci(){
    awi=new AdminWindowInserisci(0, x);
    awi->show();
}    

void AdminWindow::remove(){
    if(usrRimuovi->text()=="")
        mess->setText(tr("Specificare lo username dell'utente da rimuovere."));
    else{
        try{
            x->remove(Username(usrRimuovi->text().toUtf8().constData()));
            mess->setText(tr("Rimozione dell'utente dal database avvenuta correttamente."));
        }
        catch(Non_Presente){
            mess->setText(tr("L'utente scelto non esiste nel database."));
        }
    }
}

void AdminWindow::showDb(){
    string str=x->showDb();
    QString qs=QString::fromStdString(str);
    mess->setText(qs);
}

void AdminWindow::modifica(){
    string t="";
    if(basic->isChecked())
        t="UtenteBasic";
    if(business->isChecked())
        t="UtenteBusiness";
    if(executive->isChecked())
        t="UtenteExecutive";
    if(usrModifica->text()=="")
        mess->setText(tr("Nessun utente specificato."));
    else{
        if(t=="")
            mess->setText(tr("Nessun tipo specificato."));
        else{
            try{
                x->changeSubscriptionType(Username(usrModifica->text().toUtf8().constData()),t);
                mess->setText(tr("Modifica tipo utente avvenuta correttamente."));
            }
            catch(Non_Presente){
                mess->setText(tr("L'utente scelto non esiste nel database."));
            }
            catch(Tipo_Utente_Errato){
                mess->setText(tr("Tipo utente errato."));
            }
            catch(Stesso_Tipo){
                mess->setText(tr("L'utente era già del tipo selezionato."));
            }
        }
    }
}

void AdminWindow::salva(){
    x->save();
    mess->setText(tr("Modifiche al database salvate correttamente."));
}

void AdminWindow::cercaNomeCognome(){
    if(nome->text()=="" && cognome->text()=="")
        mess->setText(tr("Specificare nome e/o cognome dell'utente da cercare."));
    else{
        try{
            string str=x->find(nome->text().toUtf8().constData(),cognome->text().toUtf8().constData());
            QString qs=QString::fromStdString(str);
            mess->setText(qs);
        }
        catch(Non_Presente){
            mess->setText(tr("Utente non presente nel database."));
        }
    }
}

void AdminWindow::cercaUsername(){
    if(login->text()=="")
        mess->setText(tr("Specificare lo username dell'utente da cercare."));
    else{
        try{
            string str=x->find(Username(login->text().toUtf8().constData()));
            QString qs=QString::fromStdString(str);
            mess->setText(qs);
        }
        catch(Non_Presente){
            mess->setText(tr("Utente non presente nel database."));
        }
    }
}