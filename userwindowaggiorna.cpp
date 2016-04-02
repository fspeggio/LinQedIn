#include "userwindowaggiorna.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

UserWindowAggiorna::UserWindowAggiorna(QWidget* parent, LinQedInClient* y) : QWidget(parent), x(y) {

    setWindowTitle(tr("UserWindowAggiorna"));

    QVBoxLayout* mainLayout=new QVBoxLayout();

    //mostra profilo
    QGroupBox* mostraBox=new QGroupBox(tr("Mostra profilo"));
    QVBoxLayout* mostraLayout=new QVBoxLayout();
    QPushButton* mostraProfilo=new QPushButton(tr("Mostra profilo"));
    connect(mostraProfilo, SIGNAL(clicked()), this, SLOT(showProfilo()));
    profilo=new QTextEdit();
    profilo->setReadOnly(true);
    mostraLayout->addWidget(mostraProfilo);
    mostraLayout->addWidget(profilo);
    mostraBox->setLayout(mostraLayout);
    mainLayout->addWidget(mostraBox);


    //modifica
    QGroupBox* modificaBox=new QGroupBox(tr("Modifica profilo"));
    QGridLayout* modificaGrid=new QGridLayout();
    QLabel* e=new QLabel(tr("Email:"));
    QLabel* tA=new QLabel(tr("Aggiungi titolo:"));
    QLabel* tR=new QLabel(tr("Rimuovi titolo:"));
    QLabel* lA=new QLabel(tr("Aggiungi lingua:"));
    QLabel* lR=new QLabel(tr("Rimuovi lingua:"));
    QLabel* compA=new QLabel(tr("Aggiungi competenza:"));
    QLabel* compR=new QLabel(tr("Rimuovi competenza:"));
    QLabel* espA=new QLabel(tr("Aggiungi esperienza:"));
    QLabel* espR=new QLabel(tr("Rimuovi esperienza:"));
    email=new QLineEdit();
    email->setMinimumWidth(500);
    titoloAdd=new QLineEdit();
    titoloRemove=new QLineEdit();
    linguaAdd=new QLineEdit();
    linguaRemove=new QLineEdit();
    competenzaAdd=new QLineEdit();
    competenzaRemove=new QLineEdit();
    esperienzaAdd=new QLineEdit();
    esperienzaRemove=new QLineEdit();
    QPushButton* modifica=new QPushButton(tr("Modifica profilo"));
    modificaGrid->addWidget(e,0,0);
    modificaGrid->addWidget(email,0,1);
    modificaGrid->addWidget(tA,1,0);
    modificaGrid->addWidget(titoloAdd,1,1);
    modificaGrid->addWidget(tR,2,0);
    modificaGrid->addWidget(titoloRemove,2,1);
    modificaGrid->addWidget(lA,3,0);
    modificaGrid->addWidget(linguaAdd,3,1);
    modificaGrid->addWidget(lR,4,0);
    modificaGrid->addWidget(linguaRemove,4,1);
    modificaGrid->addWidget(compA,5,0);
    modificaGrid->addWidget(competenzaAdd,5,1);
    modificaGrid->addWidget(compR,6,0);
    modificaGrid->addWidget(competenzaRemove,6,1);
    modificaGrid->addWidget(espA,7,0);
    modificaGrid->addWidget(esperienzaAdd,7,1);
    modificaGrid->addWidget(espR,8,0);
    modificaGrid->addWidget(esperienzaRemove,8,1);
    modificaGrid->addWidget(modifica,9,1);
    modificaBox->setLayout(modificaGrid);
    mostraLayout->addWidget(modificaBox);
    connect(modifica, SIGNAL(clicked()), this, SLOT(modificaProfilo()));

    //uscita
    QPushButton* close=new QPushButton(tr("Esci"));
    connect(close, SIGNAL(clicked()), this, SLOT(close()));
    mainLayout->addWidget(close);

    setLayout(mainLayout);
}

void UserWindowAggiorna::showProfilo(){
    string str=x->showProfilo();
    QString qs=QString::fromStdString(str);
    profilo->setText(qs);
}

void UserWindowAggiorna::modificaProfilo(){
    x->aggiornaProfilo(email->text().toUtf8().constData(), 
                        titoloAdd->text().toUtf8().constData(), 
                        titoloRemove->text().toUtf8().constData(), 
                        linguaAdd->text().toUtf8().constData(), 
                        linguaRemove->text().toUtf8().constData(), 
                        competenzaAdd->text().toUtf8().constData(), 
                        competenzaRemove->text().toUtf8().constData(), 
                        esperienzaAdd->text().toUtf8().constData(), 
                        esperienzaRemove->text().toUtf8().constData());
    profilo->setText(tr("Profilo aggiornato con successo."));
}