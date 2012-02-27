#include <TelepathyQt4/Debug>
#include <TelepathyQt4/Types>

#include <QApplication>
#include <QtGui>

#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>

#include "main.h"
#include "roster.h"
#include "account_manager.h"

Main::Main() :
  Window(tr("Roster"))
{
  setupUi();
}

Main::~Main()
{
}

void Main::addWindow(Window *window, QPushButton *button)
{
  if (button)
  {
    connect(button, SIGNAL(toggled(bool)), window, SLOT(setVisible(bool)));
    connect(window, SIGNAL(quit()), button, SLOT(click()));
  }
  connect(this, SIGNAL(quit()), window, SLOT(close()));
}

void Main::setupUi()
{
  Roster *roster= new Roster(this);
  
  QPushButton *account_button= new QPushButton(tr("Account manager"));  
  account_button->setCheckable(true);

  AccountManager *account_window= new AccountManager;
  addWindow(account_window, account_button);

  QVBoxLayout *layout=  new QVBoxLayout(this);
  layout->addWidget(roster);
  layout->addWidget(account_button);
}

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  Tp::registerTypes();
  Tp::enableDebug(true);
  Tp::enableWarnings(true);

  Main m;
  m.show();

  return app.exec();
}
