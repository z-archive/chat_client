#include <QCheckBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QDataWidgetMapper>
#include <QItemSelectionModel>

#include <TelepathyQt4/Types>
#include <TelepathyQt4/Account>

#include "account.h"
#include "account_model.h"

Account::Account(AccountModel *model, QWidget *parent) :
  QWidget(parent), m_state(eNothing), m_model(model)
{
  setupUi();
  setupMapping();
  updateUi();
}

Account::~Account()
{
}

bool Account::isValid()
{
  return true;
}

void Account::toView()
{
  m_state= eView;
  updateUi();
}
void Account::toEdit()
{
  if (m_state == eView)
  {
    m_state= eEdit;
    updateUi();
  }
}

void Account::revert()
{
  m_state= eLoad;
  m_mapper->revert();
  QTimer::singleShot(0, this, SLOT(toView()));
}

void Account::submit()
{
  m_state= eLoad;
  m_mapper->submit();
  QTimer::singleShot(0, this, SLOT(toView()));
}

void Account::updateUi()
{
  m_protocolName->setReadOnly(m_state != eCreate);
  m_buttonGroup->setVisible(m_state == eEdit || m_state == eCreate);
}

void Account::setupMapping()
{
  m_mapper= new QDataWidgetMapper(this);
  m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
  m_mapper->setModel(m_model);
  for(int column= 0, column_count= m_widget_vector.count();
      column < column_count; ++column)
  {
    m_mapper->addMapping(m_widget_vector[column], column);
  }
  connect(m_enabled, SIGNAL(clicked(bool)), this, SLOT(toEdit()));
  connect(m_displayName, SIGNAL(textEdited(const QString&)), this, SLOT(toEdit()));
  connect(m_nickName, SIGNAL(textEdited(const QString&)), this, SLOT(toEdit()));
  connect(m_connectsAutomatically, SIGNAL(clicked(bool)), this, SLOT(toEdit()));
}
void Account::setupUi()
{
  m_valid= new QCheckBox(); 
  m_enabled= new QCheckBox();
  m_connectionManager= new QLineEdit();
  m_protocolName= new QLineEdit();
  m_displayName= new QLineEdit();
  m_nickName= new QLineEdit();
  m_connectsAutomatically= new QCheckBox();
  m_widget_vector.append(m_valid);
  m_widget_vector.append(m_enabled);
  m_widget_vector.append(m_connectionManager);
  m_widget_vector.append(m_protocolName);
  m_widget_vector.append(m_displayName);
  m_widget_vector.append(m_nickName);
  m_widget_vector.append(m_connectsAutomatically);

  m_valid->setCheckable(false);
  m_connectionManager->setReadOnly(true);

  QPushButton *revert= new QPushButton(tr("Revert"));
  QPushButton *submit= new QPushButton(tr("Submit"));
  connect(revert, SIGNAL(clicked()), this, SLOT(revert()));
  connect(submit, SIGNAL(clicked()), this, SLOT(submit()));

  m_buttonGroup= new QWidget();
  QHBoxLayout *buttonLayout= new QHBoxLayout();
  buttonLayout->addStretch();
  buttonLayout->addWidget(revert);
  buttonLayout->addWidget(submit);
  m_buttonGroup->setLayout(buttonLayout);
  m_buttonGroup->setVisible(false);
  
  QGridLayout *fieldLayout= new QGridLayout();
  for(int column= 0, column_count= m_widget_vector.count();
      column < column_count; ++column)
  {
    fieldLayout->addWidget(new QLabel(m_model->headerData(column).toString()), column, 0);
    fieldLayout->addWidget(m_widget_vector[column], column, 1);
  }

  QVBoxLayout *mainLayout= new QVBoxLayout();
  mainLayout->addLayout(fieldLayout);
  mainLayout->addWidget(m_buttonGroup);
  setLayout(mainLayout);
}

void Account::currentChanged(const QModelIndex& selected,
			       const QModelIndex& deselected)
{
  if (selected == m_current)
  {
    return;
  }
  if (m_state == eEdit || m_state == eCreate)
  {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,
				  tr("Discard your changes?"),
				  tr("Discard your changes?"),
				  QMessageBox::Ok | QMessageBox::Cancel);
    if (reply == QMessageBox::Ok)
    {
      revert();
    }
    else
    {
      emit currentSelection(m_current);
      return;
    }
  }
  setCurrentIndex(selected);
}

void Account::setCurrentIndex(const QModelIndex& index)
{
  m_current= index;
  m_state= eLoad;
  qDebug() << "Account::setCurrentIndex(" << index.row() << ")";
  m_mapper->setCurrentIndex(index.row());
  QTimer::singleShot(0, this, SLOT(toView()));
}
