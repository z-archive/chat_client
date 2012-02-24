#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "debug_window.h"

DebugWindow::DebugWindow(QWidget *parent) :
  QWidget(parent, Qt::Window)
{
  setupUi();
}

DebugWindow::~DebugWindow()
{
}

void DebugWindow::setupUi()
{
  
  setWindowTitle(tr("Debug window"));

  QVBoxLayout *layout= new QVBoxLayout(this);

  m_event_list= new QListWidget(this);
  layout->addWidget(m_event_list);

  QPushButton *clear= new QPushButton(tr("Clear"), this);
  layout->addWidget(clear);

  connect(clear, SIGNAL(clicked()), m_event_list, SLOT(clear()));
}

void DebugWindow::closeEvent(QCloseEvent* event)
{
  emit quit();
  QWidget::closeEvent(event);
}

void DebugWindow::trace(const QString& event)
{
  m_event_list->addItem(event);
}
