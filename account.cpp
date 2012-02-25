#include <QCheckBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QDataWidgetMapper>

#include <TelepathyQt4/Types>
#include <TelepathyQt4/Account>

#include "account.h"
#include "account_model.h"

/*QTextStream& operator<<(QTextStream& stream, const Tp::Account& account)
{
  QString connection;
  if (!account.connection().isNull())
  {
    connection= account.connection()->objectPath();
  }
  stream << "Valid: '"                 << account.isValidAccount()             << "'\t";
  stream << "Enabled: '"               << account.isEnabled()                  << "'\t";
  stream << "Connection_manager: '"    << account.cmName()                     << "'\t";
  stream << "Protocol_name: '"         << account.protocolName()               << "'\t";
  stream << "Display_name: '"          << account.displayName()                << "'\t";
  stream << "Nickname: '"              << account.nickname()                   << "'\t";
  stream << "Connect_automatically: '" << account.connectsAutomatically()      << "'\t";
  stream << "Automatic_presence: '"    << account.automaticPresence().status() << "'\t";
  stream << "Current_presence: '"      << account.currentPresence().status()   << "'\t";
  stream << "Requested_presence: '"    << account.requestedPresence().status() << "'\t";
  stream << "Changing_presence: '"     << account.isChangingPresence()         << "'\t";
  stream << "Connection_status: '"     << account.connectionStatus()           << "'\t";
  stream << "Connection: '"            << connection;
  return stream;
  }*/


Account::Account(AccountModel *model, QWidget *parent) : QWidget(parent)
{
  setupUi(model);
}

Account::~Account()
{
}

namespace
{
QWidget* create(int column)
{
  switch(column)
  {
  case AccountModel::eValid: return new QCheckBox();
  case AccountModel::eEnabled: return new QCheckBox();
  case AccountModel::eDisplayName: return new QLineEdit();
  default: return 0;
  }
}
}

void Account::setupUi(AccountModel *model)
{
  m_mapper= new QDataWidgetMapper(this);
  m_mapper->setOrientation(Qt::Vertical);
  m_mapper->setModel(model);
  for(int column= 0, column_count= model->columnCount(); column < column_count; ++column)
  {
    QWidget* current= ::create(column);
    m_mapper->addMapping(current, column);
  }
  QGridLayout *layout= new QGridLayout(this);
  for(int column= 0, column_count= model->columnCount(); column < column_count; ++column)
  {
    layout->addWidget(new QLabel(model->headerData(column).toString()), column, 0);
    layout->addWidget(m_mapper->mappedWidgetAt(column), column, 1);
  }
  setLayout(layout);
  m_mapper->toFirst();
}

void Account::setCurrentModelIndex(const QModelIndex &index)
{
  qDebug() << "Account::setCurrentIndex(" << index.row() << ")";
  m_mapper->setCurrentModelIndex(index);
}
