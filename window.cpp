#include "debug.h"

Window::Window(const QString& title) :
  QWidget(0, Qt::Window)
{
  setWindowTitle(title);
}

Window::~Window()
{
}

void Window::closeEvent(QCloseEvent* event)
{
  emit quit();
  QWidget::closeEvent(event);
}
