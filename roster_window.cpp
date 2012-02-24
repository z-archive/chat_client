#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include "roster_window.h"
#include "roster_widget.h"
#include "debug_window.h"

RosterWindow::RosterWindow(QWidget *parent) :
  QWidget(parent, Qt::Window)
{
  setupUi();
}

RosterWindow::~RosterWindow()
{
}

void RosterWindow::setupUi()
{
  setWindowTitle(tr("Roster"));

  QVBoxLayout *layout=  new QVBoxLayout(this);

  RosterWidget *roster= new RosterWidget(this);
  layout->addWidget(roster);
  
  QPushButton *account_button= new QPushButton(tr("Account manager"));  
  layout->addWidget(account_button);
  connect(account_button, SIGNAL(clicked()), this, SLOT(accountManager()));

  QPushButton *debug_button= new QPushButton(tr("Debug window"));
  debug_button->setCheckable(true);
  layout->addWidget(debug_button);

  DebugWindow *debug_window= new DebugWindow;
  connect(this, SIGNAL(trace(const QString&)), debug_window, SLOT(trace(const QString&)));
  connect(debug_button, SIGNAL(toggled(bool)), debug_window, SLOT(setVisible(bool)));
  connect(debug_window, SIGNAL(quit()), debug_button, SLOT(click()));
  connect(this, SIGNAL(quit()), debug_window, SLOT(close()));
}

void RosterWindow::closeEvent(QCloseEvent* event)
{
  emit quit();
  QWidget::closeEvent(event);
}

void RosterWindow::accountManager()
{
  emit trace(tr("Account manager click"));
}

