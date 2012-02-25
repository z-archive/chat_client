#include <TelepathyQt4/Types>
#include <TelepathyQt4/Account>
#include <TelepathyQt4/AccountFactory>
#include <TelepathyQt4/AccountManager>
#include <TelepathyQt4/PendingOperation>
#include <TelepathyQt4/PendingReady>

#include "account_model.h"

AccountModel::AccountModel(QObject *parent) : QAbstractTableModel(parent)
{
  m_account_manager= Tp::AccountManager::create();
  connect(m_account_manager->becomeReady(), SIGNAL(finished(Tp::PendingOperation*)),
	  this, SLOT(onReady(Tp::PendingOperation*)));
  connect(m_account_manager.data(), SIGNAL(newAccount(const Tp::AccountPtr&)),
	  this, SLOT(onNewAccount(const Tp::AccountPtr&)));
}

void AccountModel::onReady(Tp::PendingOperation *operation)
{
  Q_UNUSED(operation);
  m_account_list= m_account_manager->allAccounts();
  reset();
}

void AccountModel::onNewAccount(const Tp::AccountPtr &account)
{
  Q_UNUSED(account);
  m_account_list= m_account_manager->allAccounts();
  reset();
}

AccountModel::~AccountModel()
{
}

int AccountModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return m_account_list.count();
}

int AccountModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return 3;
}
 
QVariant AccountModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
  {
    return QVariant();
  }

  if (index.row() >= rowCount())
  {
    return QVariant();
  }

  if (index.column() >= columnCount())
  {
    return QVariant();
  }

  if (role != Qt::DisplayRole)
  {
    return QVariant();
  }

  const Tp::AccountPtr &account= m_account_list.at(index.row());

  if (account.isNull())
  {
    return QVariant();
  }

  switch (index.column())
  {
  case eValid:       return account->isValidAccount();
  case eEnabled:     return account->isEnabled();
  case eDisplayName: return account->displayName();
  default:           return QVariant();
  };
}
 
QVariant AccountModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation != Qt::Horizontal)
  {
    return QVariant();
  }
    
  switch(section)
  {
  case eValid:       return tr("Valid");
  case eEnabled:     return tr("Enabled");
  case eDisplayName: return tr("Display name");
  default:           return QVariant();      
  };
}
