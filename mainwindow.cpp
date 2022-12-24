#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "classes.h"

#include <QMessageBox>

//user initialization
Passenger* user = new Passenger();

//plane initialization
Plane plane_1("AP1", "China", 120);
Plane plane_2("AP2", "France", 160);
Plane plane_3("AP3", "India", 90);
Plane plane_4("AP4", "Italy", 200);
Plane plane_5("AP5", "Morocco", 120);
Plane plane_6("AP6", "Canada", 110);

//query model for "cart"
QSqlQueryModel * modal = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //connecting to "fm_db.db" (database)
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("database//fm_db.db");
}

MainWindow::~MainWindow()
{
    //update credit (database)
    QSqlQuery query;
    query.prepare("UPDATE passenger_info SET credit = :credit WHERE username = '"+QString::fromStdString(user->username)+"'");
    if(user->username != "admin")
    {
        query.bindValue(":credit", user->credit);
    }else{
        query.bindValue(":credit", 1337);
    }
    query.exec();

    //delete user
    delete user;

    //close connection
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);

    delete ui;
}

//signup
//(index)
void MainWindow::on_push_register_clicked() //to signup
{
    ui->stackedWidget->setCurrentIndex(9);
}
void MainWindow::on_signup_back_clicked() //to signin
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_push_signup_clicked()
{
    //database check
    if(!mydb.open())
    {
        QMessageBox::warning(this, tr("Database"), tr("Failed to connect to the database."));
    }else{
        //signup check
        std::string u = ui->r_uname->text().toStdString(), p = ui->r_pass->text().toStdString();
        if((u.size() > 2 && p.size() > 2) && (u.size() < 13 && p.size() < 13))
        {
            if((u.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890") == std::string::npos) && (p.find_first_of(" ") == std::string::npos))
            {
                QSqlQuery query;

                //check if username already exists
                if(query.exec("select * from passenger_info where username = '"+ui->r_uname->text()+"'") && query.next())
                {
                    QMessageBox::warning(this, tr("Sign Up"), tr("username already used."));
                }else{
                    //user initialization (database)
                    query.prepare("INSERT INTO passenger_info (username, password, credit) VALUES (:username, :password, :credit)");
                    query.bindValue(":username", ui->r_uname->text());
                    query.bindValue(":password", ui->r_pass->text());
                    query.bindValue(":credit", (int)500);
                    query.exec();
                    //index
                    ui->stackedWidget->setCurrentIndex(0);
                }
            }else{
                QMessageBox::warning(this, tr("Sign Up"), tr("Invalid username or password (avoid special characters in username)."));
            }
        }else{
            QMessageBox::warning(this, tr("Sign Up"), tr("Invalid username or password (no more than 12 and no less than 3 characters)."));
        }
    }
}

//login
void MainWindow::on_push_login_clicked()
{
    //database check
    if(!mydb.open())
    {
        QMessageBox::warning(this, tr("Database"), tr("Failed to connect to the database."));
    }else{
        //login check
        QSqlQuery query;
        QString u = ui->l_uname->text(), p = ui->l_pass->text();
        if(query.exec("select * from passenger_info where username = '"+u+"' and password = '"+p+"'") && query.next())
        {
            //user initialization
            user->username = ui->l_uname->text().toStdString();
            user->password = ui->l_pass->text().toStdString();
            if(query.value("credit").toInt() > 90)
            {
                user->credit = query.value("credit").toInt();
            }else{
                user->credit = 500;
                QMessageBox::information(this, tr("Notification"), tr("Credit reset to 500 coins!"));
            }

            //menu setup
            ui->w_uname->setText(user->username.c_str());//username display
            ui->w_credit->setText((std::to_string(user->credit) + " coins").c_str());//coins display
            //index
            ui->stackedWidget->setCurrentIndex(1);
        }else{
            QMessageBox::warning(this, tr("Sign In"), tr("Invalid username or password."));
        }
    }
}

//view
void MainWindow::on_plane1_view_clicked()
{
    if(!mydb.open())
    {
        QMessageBox::warning(this, tr("Database"), tr("Failed to connect to the database."));
    }else{
        //text ui
        ui->id_1->setText(plane_1.id);
        ui->dest_1->setText(plane_1.direction);
        if(user->checkAvail(plane_1))
        {
            ui->avail_1->setText("Available");
        }else
        {
            ui->avail_1->setText("Unavailable");
        }
        ui->tick_1->setText((std::to_string(plane_1.price)+" coins").c_str());

        ui->stackedWidget->setCurrentIndex(2);
    }
}

void MainWindow::on_plane2_view_clicked()
{
    //text ui
    ui->id_2->setText(plane_2.id);
    ui->dest_2->setText(plane_2.direction);
    if(user->checkAvail(plane_2))
    {
        ui->avail_2->setText("Available");
    }else
    {
        ui->avail_2->setText("Unavailable");
    }
    ui->tick_2->setText((std::to_string(plane_2.price)+" coins").c_str());

    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_plane3_view_clicked()
{
    //text ui
    ui->id_3->setText(plane_3.id);
    ui->dest_3->setText(plane_3.direction);
    if(user->checkAvail(plane_3))
    {
        ui->avail_3->setText("Available");
    }else
    {
        ui->avail_3->setText("Unavailable");
    }
    ui->tick_3->setText((std::to_string(plane_3.price)+" coins").c_str());

    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_plane4_view_clicked()
{
    //text ui
    ui->id_4->setText(plane_4.id);
    ui->dest_4->setText(plane_4.direction);
    if(user->checkAvail(plane_4))
    {
        ui->avail_4->setText("Available");
    }else
    {
        ui->avail_4->setText("Unavailable");
    }
    ui->tick_4->setText((std::to_string(plane_4.price)+" coins").c_str());

    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_plane5_view_clicked()
{
    //text ui
    ui->id_5->setText(plane_5.id);
    ui->dest_5->setText(plane_5.direction);
    if(user->checkAvail(plane_5))
    {
        ui->avail_5->setText("Available");
    }else
    {
        ui->avail_5->setText("Unavailable");
    }
    ui->tick_5->setText((std::to_string(plane_5.price)+" coins").c_str());

    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_plane6_view_clicked()
{
    //text ui
    ui->id_6->setText(plane_6.id);
    ui->dest_6->setText(plane_6.direction);
    if(user->checkAvail(plane_6))
    {
        ui->avail_6->setText("Available");
    }else
    {
        ui->avail_6->setText("Unavailable");
    }
    ui->tick_6->setText((std::to_string(plane_6.price)+" coins").c_str());

    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_cart_view_clicked()
{
    //loading table (cart)
    modal = new QSqlQueryModel();
    modal->setQuery("select plane_ID, order_type from passenger_order where username = '"+QString::fromStdString(user->username)+"'");
    ui->cart_table->setModel(modal);

    //username
    ui->c_uname->setText(user->username.c_str());
    //coins
    ui->c_credit->setText((std::to_string(user->credit)+" coins").c_str());
    //index
    ui->stackedWidget->setCurrentIndex(8);
}


//back
void MainWindow::on_cart_back_clicked()
{
    //delete modal
    delete modal;
    //index
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_back_1_clicked()
{
    ui->w_credit->setText((std::to_string(user->credit)+" coins").c_str());
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_back_2_clicked()
{
    ui->w_credit->setText((std::to_string(user->credit)+" coins").c_str());
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_back_3_clicked()
{
    ui->w_credit->setText((std::to_string(user->credit)+" coins").c_str());
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_back_4_clicked()
{
    ui->w_credit->setText((std::to_string(user->credit)+" coins").c_str());
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_back_5_clicked()
{
    ui->w_credit->setText((std::to_string(user->credit)+" coins").c_str());
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_back_6_clicked()
{
    ui->w_credit->setText((std::to_string(user->credit)+" coins").c_str());
    ui->stackedWidget->setCurrentIndex(1);
}


//book
void MainWindow::on_book_1_clicked()
{
    if(user->checkAvail(plane_1) && user->credit > plane_1.price)
    {
        plane_1.availability = false;
        user->bookPlane(plane_1);
        ui->avail_1->setText("Unavailable");

        //order modification (database)
        QSqlQuery query;
        query.prepare("INSERT INTO passenger_order (username, plane_ID, order_type) VALUES (:username, :plane, :type)");
        query.bindValue(":username", user->username.c_str());
        query.bindValue(":plane", plane_1.id);
        query.bindValue(":type", "Booked");
        query.exec();

        QMessageBox::information(this, tr("Notification"), tr("Ticket booked successfully!"));
    }else{
        QMessageBox::warning(this, tr("Notification"), tr("Not available or not enough credit."));
    }
}

void MainWindow::on_book_2_clicked()
{
    if(user->checkAvail(plane_2) && user->credit > plane_2.price)
    {
        plane_2.availability = false;
        user->bookPlane(plane_2);
        ui->avail_2->setText("Unavailable");

        //order modification (database)
        QSqlQuery query;
        query.prepare("INSERT INTO passenger_order (username, plane_ID, order_type) VALUES (:username, :plane, :type)");
        query.bindValue(":username", user->username.c_str());
        query.bindValue(":plane", plane_2.id);
        query.bindValue(":type", "Booked");
        query.exec();

        QMessageBox::information(this, tr("Notification"), tr("Ticket booked successfully!"));
    }else{
        QMessageBox::warning(this, tr("Notification"), tr("Not available or not enough credit."));
    }
}

void MainWindow::on_book_3_clicked()
{
    if(user->checkAvail(plane_3) && user->credit > plane_3.price)
    {
        plane_3.availability = false;
        user->bookPlane(plane_3);
        ui->avail_3->setText("Unavailable");

        //order modification (database)
        QSqlQuery query;
        query.prepare("INSERT INTO passenger_order (username, plane_ID, order_type) VALUES (:username, :plane, :type)");
        query.bindValue(":username", user->username.c_str());
        query.bindValue(":plane", plane_3.id);
        query.bindValue(":type", "Booked");
        query.exec();

        QMessageBox::information(this, tr("Notification"), tr("Ticket booked successfully!"));
    }else{
        QMessageBox::warning(this, tr("Notification"), tr("Not available or not enough credit."));
    }
}

void MainWindow::on_book_4_clicked()
{
    if(user->checkAvail(plane_4) && user->credit > plane_4.price)
    {
        plane_4.availability = false;
        user->bookPlane(plane_4);
        ui->avail_4->setText("Unavailable");

        //order modification (database)
        QSqlQuery query;
        query.prepare("INSERT INTO passenger_order (username, plane_ID, order_type) VALUES (:username, :plane, :type)");
        query.bindValue(":username", user->username.c_str());
        query.bindValue(":plane", plane_4.id);
        query.bindValue(":type", "Booked");
        query.exec();

        QMessageBox::information(this, tr("Notification"), tr("Ticket booked successfully!"));
    }else{
        QMessageBox::warning(this, tr("Notification"), tr("Not available or not enough credit."));
    }
}

void MainWindow::on_book_5_clicked()
{
    if(user->checkAvail(plane_5) && user->credit > plane_5.price)
    {
        plane_5.availability = false;
        user->bookPlane(plane_5);
        ui->avail_5->setText("Unavailable");

        //order modification (database)
        QSqlQuery query;
        query.prepare("INSERT INTO passenger_order (username, plane_ID, order_type) VALUES (:username, :plane, :type)");
        query.bindValue(":username", user->username.c_str());
        query.bindValue(":plane", plane_5.id);
        query.bindValue(":type", "Booked");
        query.exec();

        QMessageBox::information(this, tr("Notification"), tr("Ticket booked successfully!"));
    }else{
        QMessageBox::warning(this, tr("Notification"), tr("Not available or not enough credit."));
    }
}

void MainWindow::on_book_6_clicked()
{
    if(user->checkAvail(plane_6) && user->credit > plane_6.price)
    {
        plane_6.availability = false;
        user->bookPlane(plane_6);
        ui->avail_6->setText("Unavailable");

        //order modification (database)
        QSqlQuery query;
        query.prepare("INSERT INTO passenger_order (username, plane_ID, order_type) VALUES (:username, :plane, :type)");
        query.bindValue(":username", user->username.c_str());
        query.bindValue(":plane", plane_6.id);
        query.bindValue(":type", "Booked");
        query.exec();

        QMessageBox::information(this, tr("Notification"), tr("Ticket booked successfully!"));
    }else{
        QMessageBox::warning(this, tr("Notification"), tr("Not available or not enough credit."));
    }
}



//cancel
void MainWindow::on_cancel_1_clicked()
{
    if(!(user->checkAvail(plane_1)))
    {
        plane_1.availability = true;
        user->cancelPlane(plane_1);
        ui->avail_1->setText("Available");

        //order modification (database)
        QSqlQuery query;
        query.prepare("INSERT INTO passenger_order (username, plane_ID, order_type) VALUES (:username, :plane, :type)");
        query.bindValue(":username", user->username.c_str());
        query.bindValue(":plane", plane_1.id);
        query.bindValue(":type", "Cancelled");
        query.exec();

        QMessageBox::information(this, tr("Notification"), tr("Ticket cancelled successfully!"));
    }else{
        QMessageBox::warning(this, tr("Notification"), tr("Can not be cancelled."));
    }
}

void MainWindow::on_cancel_2_clicked()
{
    if(!(user->checkAvail(plane_2)))
    {
        plane_2.availability = true;
        user->cancelPlane(plane_2);
        ui->avail_2->setText("Available");

        //order modification (database)
        QSqlQuery query;
        query.prepare("INSERT INTO passenger_order (username, plane_ID, order_type) VALUES (:username, :plane, :type)");
        query.bindValue(":username", user->username.c_str());
        query.bindValue(":plane", plane_2.id);
        query.bindValue(":type", "Cancelled");
        query.exec();

        QMessageBox::information(this, tr("Notification"), tr("Ticket cancelled successfully!"));
    }else{
        QMessageBox::warning(this, tr("Notification"), tr("Can not be cancelled."));
    }
}

void MainWindow::on_cancel_3_clicked()
{
    if(!(user->checkAvail(plane_3)))
    {
        plane_3.availability = true;
        user->cancelPlane(plane_3);
        ui->avail_3->setText("Available");

        //order modification (database)
        QSqlQuery query;
        query.prepare("INSERT INTO passenger_order (username, plane_ID, order_type) VALUES (:username, :plane, :type)");
        query.bindValue(":username", user->username.c_str());
        query.bindValue(":plane", plane_3.id);
        query.bindValue(":type", "Cancelled");
        query.exec();

        QMessageBox::information(this, tr("Notification"), tr("Ticket cancelled successfully!"));
    }else{
        QMessageBox::warning(this, tr("Notification"), tr("Can not be cancelled."));
    }
}

void MainWindow::on_cancel_4_clicked()
{
    if(!(user->checkAvail(plane_4)))
    {
        plane_4.availability = true;
        user->cancelPlane(plane_4);
        ui->avail_4->setText("Available");

        //order modification (database)
        QSqlQuery query;
        query.prepare("INSERT INTO passenger_order (username, plane_ID, order_type) VALUES (:username, :plane, :type)");
        query.bindValue(":username", user->username.c_str());
        query.bindValue(":plane", plane_4.id);
        query.bindValue(":type", "Cancelled");
        query.exec();

        QMessageBox::information(this, tr("Notification"), tr("Ticket cancelled successfully!"));
    }else{
        QMessageBox::warning(this, tr("Notification"), tr("Can not be cancelled."));
    }
}

void MainWindow::on_cancel_5_clicked()
{
    if(!(user->checkAvail(plane_5)))
    {
        plane_5.availability = true;
        user->cancelPlane(plane_5);
        ui->avail_5->setText("Available");

        //order modification (database)
        QSqlQuery query;
        query.prepare("INSERT INTO passenger_order (username, plane_ID, order_type) VALUES (:username, :plane, :type)");
        query.bindValue(":username", user->username.c_str());
        query.bindValue(":plane", plane_5.id);
        query.bindValue(":type", "Cancelled");
        query.exec();

        QMessageBox::information(this, tr("Notification"), tr("Ticket cancelled successfully!"));
    }else{
        QMessageBox::warning(this, tr("Notification"), tr("Can not be cancelled."));
    }
}

void MainWindow::on_cancel_6_clicked()
{
    if(!(user->checkAvail(plane_6)))
    {
        plane_6.availability = true;
        user->cancelPlane(plane_6);
        ui->avail_6->setText("Available");

        //order modification (database)
        QSqlQuery query;
        query.prepare("INSERT INTO passenger_order (username, plane_ID, order_type) VALUES (:username, :plane, :type)");
        query.bindValue(":username", user->username.c_str());
        query.bindValue(":plane", plane_6.id);
        query.bindValue(":type", "Cancelled");
        query.exec();

        QMessageBox::information(this, tr("Notification"), tr("Ticket cancelled successfully!"));
    }else{
        QMessageBox::warning(this, tr("Notification"), tr("Can not be cancelled."));
    }
}
