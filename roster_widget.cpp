#include <QVBoxLayout>
#include <QListWidget>

#include "roster_widget.h"

RosterWidget::RosterWidget(QWidget *parent) :
  QWidget(parent)
{
  setupUi();
}

RosterWidget::~RosterWidget()
{
}

void RosterWidget::setupUi()
{
  QVBoxLayout *layout= new QVBoxLayout(this);
  setLayout(layout);

  m_contact_list= new QListWidget(this);
  layout->addWidget(m_contact_list);
}
