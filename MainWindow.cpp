#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    banco = new Banco("C:/Users/iKe/Downloads/RfidSQL/database.db");
    server = new RfidTcpServer();
    connect(server,SIGNAL(emitirID(QString)),this,SLOT(receberID(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete banco;
    delete server;
}

void MainWindow::receberID(QString id)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Aviso!");
    msgBox.setText("Marcar Presença?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    if(msgBox.exec() == QMessageBox::Yes){
        banco->marcarPresenca(id);
    }else{
        ui->lineEditRFID->setText(id);

    }
}

void MainWindow::on_pushButton_clicked()
{
    banco->adicionarAluno(ui->lineEditNomeAluno->text(),ui->lineEditRFID->text());
    ui->lineEditNomeAluno->setText("");
    ui->lineEditRFID->setText("");
}

void MainWindow::on_pushButton_5_clicked()
{
    banco->mostrarAlunos();
}

void MainWindow::on_pushButton_3_clicked()
{
    int ano = ui->lineEditAno->text().toInt();
    int semestre = ui->lineEditSemestre->text().toInt();

    banco->adicionarTurma(ano,semestre,ui->lineEditDisciplina->text());
}

void MainWindow::on_pushButton_6_clicked()
{
    banco->mostrarTurmas();
}

void MainWindow::on_pushButton_2_clicked()
{
    banco->adicionarDisciplina(ui->lineEditAddDisc->text());
}

void MainWindow::on_pushButton_7_clicked()
{
    banco->mostrarDisciplinas();
}

void MainWindow::on_pushButton_4_clicked()
{
    QDate data = ui->dateEdit->date();
    QString sData = QString::number(data.year());
    sData.append("-").append(QString::number(data.month()));
    sData.append("-").append(QString::number(data.day()));
    banco->adicionarAula(sData,ui->lineEditIDTurma->text().toInt());
}

void MainWindow::on_pushButton_8_clicked()
{
    banco->inserirAlunoEmTurma(ui->lineEditAT->text(),ui->lineEditID_TA->text().toInt());
    banco->inserirTodosAlunosNasAulas();
}

void MainWindow::on_pushButton_9_clicked()
{
    banco->mostrarAlunosTurmasAulas();
}
