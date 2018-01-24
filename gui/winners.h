#ifndef WINNERS_H
#define WINNERS_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
class winners : public QWidget
{
    Q_OBJECT
public:
    explicit winners(QWidget *parent = 0);

signals:

public slots:
    void getWinner(const std::string& win);
    void exitVietname();
private:
    QLabel* winner;
    QPushButton* rematch;
    QPushButton* newGame;
    QPushButton* exit_;
    QHBoxLayout* lay;
};

#endif // WINNERS_H
