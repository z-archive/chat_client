#include <QCheckBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QDataWidgetMapper>
#include <QStandardItemModel>

#include <TelepathyQt4/Types>
#include <TelepathyQt4/Account>

#include "account.h"
#include "account_model.h"

Account::Account(AccountModel *model, QWidget *parent) : QWidget(parent)
{
  setupUi(model);
}

Account::~Account()
{
}

namespace
{

template<typename T>
T* create(QWidget *parent, int column);

template<>
QCheckBox* create<QCheckBox>(QWidget *parent, int column)
{
  QCheckBox *result= new QCheckBox(parent);
  result->setEnabled(AccountModel::editable(column));
  return result;  
}

template<>
QLineEdit* create<QLineEdit>(QWidget *parent, int column)
{
  QLineEdit *result= new QLineEdit(parent);
  result->setEnabled(AccountModel::editable(column));
  return result;  
}

template<>
QSpinBox* create<QSpinBox>(QWidget *parent, int column)
{
  QSpinBox *result= new QSpinBox(parent);
  result->setEnabled(AccountModel::editable(column));
  return result;  
}

QWidget* create(QWidget *parent, int column)
{
  switch(column)
  {
  case AccountModel::eValid:                return create<QCheckBox>(parent, column);
  case AccountModel::eEnabled:              return create<QCheckBox>(parent, column);
  case AccountModel::eConnectionManager:    return create<QLineEdit>(parent, column);
  case AccountModel::eProtocolName:         return create<QLineEdit>(parent, column);
  case AccountModel::eDisplayName:          return create<QLineEdit>(parent, column);
  case AccountModel::eNickName:             return create<QLineEdit>(parent, column);
  case AccountModel::eConnectAutomatically: return create<QCheckBox>(parent, column);
  case AccountModel::eAutomaticPresence:    return create<QLineEdit>(parent, column);
  case AccountModel::eCurrentPresence:      return create<QLineEdit>(parent, column);
  case AccountModel::eRequestedPresence:    return create<QLineEdit>(parent, column);
  case AccountModel::eChangingPresence:     return create<QLineEdit>(parent, column);
  case AccountModel::eConnectionStatus:     return create<QSpinBox>(parent, column);
  case AccountModel::eConnection:           return create<QLineEdit>(parent, column);
  default:                                  return 0;
  };
}

}

void Account::setupUi(AccountModel *model)
{
  m_mapper= new QDataWidgetMapper(this);
  m_mapper->setModel(model);
  for(int column= 0, column_count= model->columnCount(); column < column_count; ++column)
  {
    QWidget* current= ::create(this, column);
    m_mapper->addMapping(current, column);
  }
  QGridLayout *layout= new QGridLayout(this);
  for(int column= 0, column_count= model->columnCount(); column < column_count; ++column)
  {
    layout->addWidget(new QLabel(model->headerData(column).toString()), column, 0);
    layout->addWidget(m_mapper->mappedWidgetAt(column), column, 1);
  }
  setLayout(layout);
}

void Account::setCurrentModelIndex(const QModelIndex &index)
{
  qDebug() << "Account::setCurrentIndex(" << index.row() << ")";
  m_mapper->setCurrentIndex(index.row());
}
