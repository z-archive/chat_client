#include <TelepathyQt4/Types>
#include <TelepathyQt4/Account>
#include <TelepathyQt4/AccountFactory>
#include <TelepathyQt4/AccountManager>
#include <TelepathyQt4/PendingOperation>
#include <TelepathyQt4/PendingReady>

#include "account_model.h"

AccountModel::AccountModel(QObject *parent) :  QAbstractListModel(parent)
{
  m_account_manager= Tp::AccountManager::create();
  connect(m_account_manager->becomeReady(), SIGNAL(finished(Tp::PendingOperation*)),
          this, SLOT(reset()));
  connect(m_account_manager.data(), SIGNAL(newAccount(const Tp::AccountPtr&)),
          this, SLOT(added(const Tp::AccountPtr&)));
}

AccountModel::~AccountModel()
{
}

void AccountModel::connect_account(const Tp::AccountPtr& account_pointer)
{
  qDebug() << "AccountModel::connect";
  Tp::Account *account= account_pointer.data();
  connect(account, SIGNAL(validityChanged(bool)),
          this, SLOT(changedValid()));
  connect(account, SIGNAL(stateChanged(bool)),
          this, SLOT(changedEnabled()));
  connect(account, SIGNAL(displayNameChanged(const QString&)),
          this, SLOT(changedDisplayName()));
  connect(account, SIGNAL(nicknameChanged(const QString&)),
          this, SLOT(changedNickName()));
  connect(account, SIGNAL(connectsAutomaticallyPropertyChanged(bool)),
          this, SLOT(changedConnectsAutomatically()));
  connect(account, SIGNAL(removed()), this, SLOT(removed()));
}
void AccountModel::reset()
{
  qDebug() << "AccountModel::reset";
  foreach(const Tp::AccountPtr &account, m_account_list)
  {
    account->disconnect();
  }
  m_account_list= m_account_manager->allAccounts();
  foreach(const Tp::AccountPtr &account, m_account_list)
  {
    connect_account(account);
  }
  QAbstractListModel::reset();
}
void AccountModel::added(const Tp::AccountPtr &account)
{
  int count= m_account_list.count();
  beginInsertRows(QModelIndex(), count, count + 1);
  m_account_list.append(account);
  connect_account(account);
  endInsertRows();
}
void AccountModel::removed()
{
  /* can be optimized by look to sender() and remove from list */
  reset();
}
void AccountModel::changedValid()
{
  changed(sender(), eValid);
}
void AccountModel::changedEnabled()
{
  changed(sender(), eEnabled);
}
void AccountModel::changedDisplayName()
{
  changed(sender(), eDisplayName);
}
void AccountModel::changedNickName()
{
  changed(sender(), eNickName);
}
void AccountModel::changedConnectsAutomatically()
{
  changed(sender(), eConnectsAutomatically);
}

void AccountModel::changed(QObject* target, int column)
{
  int row= 0;
  foreach(const Tp::AccountPtr& account, m_account_list)
  {
    if (account.data() == target)
    {
      QModelIndex result= createIndex(row, column);
      emit dataChanged(result, result);
    }
    else
    {
      ++row;
    }
  }
}

int AccountModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return m_account_list.count();
}

int AccountModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return eColumnCount;
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

  if (role != Qt::DisplayRole && role != Qt::EditRole)
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
  case eValid:
    return account->isValidAccount();
  case eEnabled:
    return account->isEnabled();
  case eConnectionManager:
    return account->cmName();
  case eProtocolName:
    return account->protocolName();
  case eDisplayName:
    return account->displayName();
  case eNickName:
    return account->nickname();
  case eConnectsAutomatically:
    return account->connectsAutomatically();
  default:
    return QVariant();
  };
}

bool AccountModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  if (!index.isValid())
  {
    return false;
  }

  if (index.row() >= rowCount())
  {
    return false;
  }

  if (index.column() >= columnCount())
  {
    return false;
  }

  if (role != Qt::EditRole)
  {
    return false;
  }

  const Tp::AccountPtr &account= m_account_list.at(index.row());
  Q_ASSERT(editable(index.column()));

  switch(index.column())
  {
  case eEnabled:
    account->setEnabled(value.toBool());
    return true;
  case eDisplayName:
    account->setDisplayName(value.toString());
    return true;
  case eNickName:
    account->setNickname(value.toString());
    return true;
  case eConnectsAutomatically:
    account->setConnectsAutomatically(value.toBool());
    return true;
  default:
    return false;
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
  case eValid:
    return tr("Valid");
  case eEnabled:
    return tr("Enabled");
  case eConnectionManager:
    return tr("Connection manager");
  case eProtocolName:
    return tr("Protocol name");
  case eDisplayName:
    return tr("Display name");
  case eNickName:
    return tr("Nick name");
  case eConnectsAutomatically:
    return tr("Connect automaticly");
  default:
    return QVariant();
  };
}
