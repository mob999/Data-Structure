#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include"mgraph.h"
#include"sql.h"
#include"dialog.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->searchButton,QPushButton::clicked,this,searchButton_click);
    connect(ui->testshow_button,QPushButton::clicked,this,testshow_Button_click);
   /* QString s;
    MGraph m;
    m.create();
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
            s=s+QString::number(m.arc[i][j].length)+" ";
        s+="\n";
    }
    QMessageBox::information(this,"邻接矩阵",s);*/
   // createConnection();
    MGraph m;
    m.create();
    QString s;
    m.get_shortest(m.vexs[0],m.vexs[2],s);
    QMessageBox::information(this,"test",s);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::searchButton_click()
{
    MGraph m;
    m.create();
    vextype result1;
    vextype result2;
    int _id=-1;
    _id=ui->id_edit->text().toInt();
    QString _name;
    _name=ui->name_edit->text();
    if(m.search(_id,result1)||_id==-1)
    {
        if(m.search(_name,result2)||_name=="")
        {
            if(_id==-1)
            {
                QString finalres
                        ="景点代号："+QString::number(result2.id)+"\n"
                        +"景点名称："+result2.name+"\n"
                        +"景点简介："+result2.information;
                ui->infor_lable->setText(finalres);
            }
            else if(_name=="")
            {
                QString finalres
                        ="景点代号："+QString::number(result1.id)+"\n"
                        +"景点名称："+result1.name+"\n"
                        +"景点简介："+result1.information;
                ui->infor_lable->setText(finalres);
            }
            else if(result1.name==_name&&result2.id==_id)
            {
                QString finalres
                        ="景点代号："+QString::number(result1.id)+"\n"
                        +"景点名称："+result1.name+"\n"
                        +"景点简介："+result1.information;
                ui->infor_lable->setText(finalres);
            }
            else
                QMessageBox::warning(this,"警告",tr("查找失败"));
        }
    }
    else
        QMessageBox::warning(this,"警告",tr("查找失败"));
}

void MainWindow::testshow_Button_click()
{
    Dialog* dialog=new Dialog;
    dialog->show();
}
