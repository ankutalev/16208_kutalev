#ifndef VISIONAREA_H
#define VISIONAREA_H

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include "/home/ulyssess/qtProjects/core_war/renderarea.h"
class infoWindow : public QWidget
{
    Q_OBJECT
public:
    explicit infoWindow(QWidget *parent = 0);
    ~infoWindow();
signals:

public slots:
  void setName(const std::string& name);
  void setCommand(const std::string& command);
  void setDanger(bool x);
  void setPosition(int x);
private:
   /// RenderArea* fullModel;
    QLabel* name = nullptr;
    QLabel* command = nullptr;
    QLabel* danger = nullptr;
    QLabel* position = nullptr;
    QVBoxLayout* lay = nullptr;
};

#endif // VISIONAREA_H
