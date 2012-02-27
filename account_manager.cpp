#include <QListView>
#include <QTableView>
#include <QHBoxLayout>

#include "account_manager.h"
#include "account_model.h"
#include "account.h"

AccountManager::AccountManager() :
  Window(tr("AccountManager"))
{
  setupUi();
}

AccountManager::~AccountManager()
{
}

void AccountManager::setupUi()
{
  AccountModel *model= new AccountModel(this);
  
  QListView *list= new QListView(this);
  list->setSelectionMode(QAbstractItemView::NoSelection);
  list->setModel(model);
  list->setModelColumn(AccountModel::eDisplayName);
  
  Account *account= new Account(model, list);
  connect(list->selectionModel(),
	  SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)),
	  account,
	  SLOT(currentChanged(const QModelIndex&, const QModelIndex&)));
  connect(account,
	  SIGNAL(currentSelection(const QModelIndex&)),
	  list,
	  SLOT(setCurrentIndex(const QModelIndex&)));
  
  QHBoxLayout *layout=  new QHBoxLayout(this);
  layout->addWidget(list);
  layout->addWidget(account);  
}
