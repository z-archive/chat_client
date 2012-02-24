#include <QVBoxLayout>
#include <QListWidget>

#include "roster.h"

Roster::Roster(QWidget *parent) :
  QWidget(parent)
{
  setupUi();
}

Roster::~Roster()
{
}

void Roster::setupUi()
{
  QVBoxLayout *layout= new QVBoxLayout(this);
  setLayout(layout);

  m_contact_list= new QListWidget(this);
  layout->addWidget(m_contact_list);
}
