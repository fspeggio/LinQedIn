#ifndef MAINWIDOW_H
#define MAINWIDOW_H

#include <QWidget>
class AdminWindow;
class UserWindow;
class QLineEdit;
class QTextEdit;

class MainWindow : public QWidget {
	Q_OBJECT

private:
	QLineEdit* login;
    QTextEdit* mess;

    //finestre figlie
    AdminWindow* aw;
    UserWindow* uw;

public:
    MainWindow(QWidget* =0); //costruttore    

public slots:
	void openAreaUser();
	void openAreaAdmin();
};

#endif