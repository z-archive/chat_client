#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "debug_window.h"

DebugWindow::DebugWindow(QWidget *parent) :
  QDialog(parent)
{
  setupUi();
}

DebugWindow::~DebugWindow()
{
}

void DebugWindow::setupUi()
{
  setWindowTitle(tr("Debug window"));

  QVBoxLayout *layout= new QVBoxLayout;
  this->setLayout(layout);

  m_event_list= new QListWidget(this);
  layout->addWidget(m_event_list);

  QPushButton *clear= new QPushButton(tr("Clear"), this);
  layout->addWidget(clear);

  connect(clear, SIGNAL(clicked()), m_event_list, SLOT(clear()));
}

void DebugWindow::addEvent(const QString& event)
{
  m_event_list->addItem(event);
}
