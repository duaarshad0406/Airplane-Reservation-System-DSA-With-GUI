#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <QStringList>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void bookTicket();
    void resetForm();
    void cancelTicket();
    void searchTicket();
    void displayPassengers();

private:
    QLineEdit *nameInput;
    QComboBox *seatCombo;

    QPushButton *bookBtn;
    QPushButton *resetBtn;
    QPushButton *cancelBtn;
    QPushButton *searchBtn;
    QPushButton *displayBtn;

    QListWidget *reservationList;

    QStringList bookedSeats;
};

#endif // MAINWINDOW_H
