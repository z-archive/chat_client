#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include "roster_window.h"
#include "roster_widget.h"

RosterWindow::RosterWindow(QWidget *parent) :
  QMainWindow(parent)
{
  setupUi();
}

RosterWindow::~RosterWindow()
{
}

void RosterWindow::setupUi()
{
  setWindowTitle(tr("Roster"));

  QWidget     *central= new QWidget(this);
  setCentralWidget(central);

  QVBoxLayout *layout=  new QVBoxLayout(this);
  central->setLayout(layout);

  RosterWidget *roster= new RosterWidget(this);
  QPushButton *account= new QPushButton(tr("Account manager"));
  QPushButton *debug=   new QPushButton(tr("Debug window"));

  layout->addWidget(roster);
  layout->addWidget(account);
  layout->addWidget(debug);

  connect(account, SIGNAL(clicked()), this, SLOT(accountManager()));
  connect(debug,   SIGNAL(clicked()), this, SLOT(debugWindow()));
}

void RosterWindow::accountManager()
{
  QMessageBox message;
  message.setText(tr("Account manager click"));
  message.exec();
}

void RosterWindow::debugWindow()
{
  QMessageBox message;
  message.setText(tr("Debug window click"));
  message.exec();
}
