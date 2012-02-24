#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include "main_window.h"
#include "roster.h"
#include "debug.h"

MainWindow::MainWindow(QWidget *parent) :
  QWidget(parent, Qt::Window)
{
  setupUi();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUi()
{
  setWindowTitle(tr("Main"));

  QVBoxLayout *layout=  new QVBoxLayout(this);

  Roster *main= new Roster(this);
  layout->addWidget(main);
  
  QPushButton *account_button= new QPushButton(tr("Account manager"));  
  layout->addWidget(account_button);
  connect(account_button, SIGNAL(clicked()), this, SLOT(accountManager()));

  QPushButton *debug_button= new QPushButton(tr("Debug window"));
  debug_button->setCheckable(true);
  layout->addWidget(debug_button);

  Debug *debug_window= new Debug;
  connect(this, SIGNAL(trace(const QString&)), debug_window, SLOT(trace(const QString&)));
  connect(debug_button, SIGNAL(toggled(bool)), debug_window, SLOT(setVisible(bool)));
  connect(debug_window, SIGNAL(quit()), debug_button, SLOT(click()));
  connect(this, SIGNAL(quit()), debug_window, SLOT(close()));
}

void MainWindow::closeEvent(QCloseEvent* event)
{
  emit quit();
  QWidget::closeEvent(event);
}

void MainWindow::accountManager()
{
  emit trace(tr("Account manager click"));
}

