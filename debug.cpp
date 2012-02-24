#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "debug.h"

Debug::Debug() :
  Window(tr("Debug"))
{
  setupUi();
}

Debug::~Debug()
{
}

void Debug::setupUi()
{
  QVBoxLayout *layout= new QVBoxLayout(this);

  m_event_list= new QListWidget(this);
  layout->addWidget(m_event_list);

  QPushButton *clear= new QPushButton(tr("Clear"), this);
  layout->addWidget(clear);

  connect(clear, SIGNAL(clicked()), m_event_list, SLOT(clear()));
}

void Debug::trace(const QString& event)
{
  m_event_list->addItem(event);
}
