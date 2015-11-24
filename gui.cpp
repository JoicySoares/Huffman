#include "gui.h"
#include "ui_gui.h"

Gui::Gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui)
{
    ui->setupUi(this);
}

Gui::~Gui()
{
    delete ui;
}

void Gui::on_pushButton_clicked()
{
    QString text = ui->lineEdit->text();
    compress(text,"");
    QMessageBox info;
    info.setText("arquivo comprimido!");
    info.exec();
}

void Gui::on_toolButton_clicked()
{
    ui->lineEdit->setText(QFileDialog::getOpenFileName(this,tr("Open File"), "/home"));
}

void Gui::on_pushButton_2_clicked()
{
    QString ArquiveName = ui->lineEdit->text();
    if(ArquiveName.right(5) != QString(".huff")){
        QMessageBox info;
        info.setText("Ensira um arquivo .huff Mané !");
        info.exec();
    }
   else{
        decompress(ArquiveName, ui->lineEdit_2->text());
        QMessageBox info;
        info.setText("arquivo Descomprimido!");
        info.exec();
    }
}

void Gui::on_toolButton_2_clicked()
{
    ui->lineEdit_2->setText(QFileDialog::getExistingDirectory(this, tr("Save File"),"/home"));
}
