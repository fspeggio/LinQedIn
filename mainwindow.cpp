#include "mainwindow.h"
#include "userwindow.h"
#include "adminwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

MainWindow::MainWindow(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QGroupBox* adminGroupBox=new QGroupBox(tr("Area Amministratore"));
    QGroupBox* userGroupBox=new QGroupBox(tr("Area Utente"));
    
    //accesso area amministratore
    QVBoxLayout* adminLayout=new QVBoxLayout();
    QPushButton* pushAdmin=new QPushButton(tr("Login Amministratore"));
    adminLayout->addWidget(pushAdmin);
    adminGroupBox->setLayout(adminLayout);

    //accesso area utente
    QGridLayout* gridUser = new QGridLayout();
    QLabel* label=new QLabel(tr("Inserisci lo username:"));
    login=new QLineEdit();
    QPushButton* pushUser=new QPushButton(tr("Login Utente"));
    gridUser->addWidget(label,0,0);
    gridUser->addWidget(login,0,1);
    gridUser->addWidget(pushUser,1,1);
    userGroupBox->setLayout(gridUser);

    //area messaggi
    mess=new QTextEdit();
    mess->setReadOnly(true);
    mess->setMaximumHeight(50);
    mess->setMaximumWidth(500);

    mainLayout->addWidget(adminGroupBox);
    mainLayout->addWidget(userGroupBox);
    mainLayout->addWidget(mess);
    setLayout(mainLayout);

    //connect alle due aree
    connect(pushAdmin, SIGNAL(clicked()), this, SLOT(openAreaAdmin()));
    connect(pushUser, SIGNAL(clicked()), this, SLOT(openAreaUser()));

    //uscita 
    QPushButton* close=new QPushButton(tr("Esci da LinQedIn"));
    connect(close, SIGNAL(clicked()), this, SLOT(close()));   
    mainLayout->addWidget(close);
}

//SLOT
void MainWindow::openAreaAdmin(){
    aw=new AdminWindow();
    aw->show();
}

void MainWindow::openAreaUser(){
    if(login->text()==""){ 
        mess->setText(tr("Inserire uno username per effettuare il login all'area utente."));
    }
    else{ //controllo se esiste l'utente
        try{
            LinQedInClient x(Username(login));
            mess->setText("");
            uw=new UserWindow(Username(login->text().toUtf8().constData()),0);
            uw->show();
        }
        catch (Non_Presente){
            mess->setText(tr("Utente non presente nel database."));
        }
    }
}

