#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void controllerCommand(int Warrior, int Address,bool isDanger);
    void filesOpenError(const std::string& file);
    void filesError(const char* message);
    void reOrganize();
    void sizeError(const std::string& message);
    void separationError();
    void rezults(const std::string& winner);
    void off();
private slots:


    void on_checkBox_2_clicked();

    void on_comboBox_activated(int index);

    void on_checkBox_clicked();

    void on_pushButton_clicked();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    QLabel* filesErrors[6];
};

#endif // MAINWINDOW_H
