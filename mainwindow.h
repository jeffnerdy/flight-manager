#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QFileInfo>
#include <QSqlQueryModel>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_push_login_clicked();

    void on_plane1_view_clicked();

    void on_plane2_view_clicked();

    void on_plane3_view_clicked();

    void on_plane4_view_clicked();

    void on_plane5_view_clicked();

    void on_plane6_view_clicked();

    void on_back_1_clicked();

    void on_back_2_clicked();

    void on_back_3_clicked();

    void on_back_4_clicked();

    void on_back_5_clicked();

    void on_back_6_clicked();

    void on_book_1_clicked();

    void on_book_2_clicked();

    void on_book_3_clicked();

    void on_book_4_clicked();

    void on_book_5_clicked();

    void on_book_6_clicked();

    void on_cancel_6_clicked();

    void on_cancel_5_clicked();

    void on_cancel_4_clicked();

    void on_cancel_3_clicked();

    void on_cancel_2_clicked();

    void on_cancel_1_clicked();

    void on_cart_back_clicked();

    void on_cart_view_clicked();

    void on_push_signup_clicked();

    void on_push_register_clicked();

    void on_signup_back_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase mydb;
};
#endif // MAINWINDOW_H
