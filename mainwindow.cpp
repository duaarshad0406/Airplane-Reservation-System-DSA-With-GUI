#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QGroupBox>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("âœˆï¸ Aeroplane Reservation System");
    this->resize(500, 550);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QLabel *titleLabel = new QLabel("Aeroplane Reservation System");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size:18px;font-weight:bold;");

    nameInput = new QLineEdit();
    nameInput->setPlaceholderText("Enter passenger name");

    seatCombo = new QComboBox();
    seatCombo->addItems({"1A","1B","1C","2A","2B","2C","3A","3B"});

    bookBtn    = new QPushButton("Book Ticket");
    cancelBtn  = new QPushButton("Cancel Ticket");
    searchBtn  = new QPushButton("Search Ticket");
    displayBtn = new QPushButton("Display Passengers");
    resetBtn   = new QPushButton("Reset");

    reservationList = new QListWidget();

    QGroupBox *inputGroup = new QGroupBox("Passenger Details");
    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("Name:", nameInput);
    formLayout->addRow("Seat:", seatCombo);
    inputGroup->setLayout(formLayout);

    QHBoxLayout *btnLayout1 = new QHBoxLayout();
    btnLayout1->addWidget(bookBtn);
    btnLayout1->addWidget(cancelBtn);

    QHBoxLayout *btnLayout2 = new QHBoxLayout();
    btnLayout2->addWidget(searchBtn);
    btnLayout2->addWidget(displayBtn);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(inputGroup);
    mainLayout->addLayout(btnLayout1);
    mainLayout->addLayout(btnLayout2);
    mainLayout->addWidget(resetBtn);
    mainLayout->addWidget(new QLabel("Reservations:"));
    mainLayout->addWidget(reservationList);

    connect(bookBtn, &QPushButton::clicked, this, &MainWindow::bookTicket);
    connect(cancelBtn, &QPushButton::clicked, this, &MainWindow::cancelTicket);
    connect(searchBtn, &QPushButton::clicked, this, &MainWindow::searchTicket);
    connect(displayBtn,&QPushButton::clicked,this,&MainWindow::displayPassengers);
    connect(resetBtn, &QPushButton::clicked, this, &MainWindow::resetForm);
}

MainWindow::~MainWindow() {}

void MainWindow::bookTicket()
{
    QString name = nameInput->text().trimmed();
    QString seat = seatCombo->currentText();

    if(name.isEmpty()){
        QMessageBox::warning(this,"Error","Enter passenger name!");
        return;
    }

    if(bookedSeats.contains(seat)){
        QMessageBox::critical(this,"Error","Seat already booked!");
        return;
    }

    int ticketId = QRandomGenerator::global()->bounded(1000,9999);
    QString record = QString("ID:%1 | Name:%2 | Seat:%3")
                         .arg(ticketId).arg(name).arg(seat);

    reservationList->addItem(record);
    bookedSeats.append(seat);

    QMessageBox::information(this,"Success","Ticket Booked!");
    nameInput->clear();
}

void MainWindow::cancelTicket()
{
    QListWidgetItem *item = reservationList->currentItem();
    if(!item){
        QMessageBox::warning(this,"Error","Select ticket to cancel!");
        return;
    }

    QString text = item->text();
    QString seat = text.section("Seat:",1,1);
    bookedSeats.removeAll(seat);

    delete item;
    QMessageBox::information(this,"Cancelled","Ticket Cancelled!");
}

void MainWindow::searchTicket()
{
    QString name = nameInput->text().trimmed();
    if(name.isEmpty()){
        QMessageBox::warning(this,"Error","Enter name to search!");
        return;
    }

    for(int i=0;i<reservationList->count();i++){
        if(reservationList->item(i)->text().contains(name,Qt::CaseInsensitive)){
            reservationList->setCurrentRow(i);
            QMessageBox::information(this,"Found","Ticket Found!");
            return;
        }
    }
    QMessageBox::critical(this,"Not Found","No ticket found!");
}

void MainWindow::displayPassengers()
{
    if(reservationList->count()==0){
        QMessageBox::information(this,"Empty","No passengers yet!");
        return;
    }
    QMessageBox::information(this,"Passengers","All passengers displayed in list.");
}

void MainWindow::resetForm()
{
    nameInput->clear();
    seatCombo->setCurrentIndex(0);
    reservationList->clear();
    bookedSeats.clear();
}
