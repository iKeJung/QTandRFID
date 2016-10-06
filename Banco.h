#ifndef BANCO_H
#define BANCO_H

#include <QString>
#include <QtSql>
#include <QDebug>

class Banco
{
public:
    Banco(QString nome);
    bool adicionarDisciplina(QString nome);  //OK
    bool adicionarAluno(QString nome, QString rfid); //OK
    bool adicionarTurma(int ano, int semestre, QString nomeDisciplina); //OK
    bool adicionarAula(QString data, int idTurma); //OK

    bool existeTurma(int idTurma); //OK
    bool existeAluno(QString nomeAluno); //OK
    bool existeDisciplina(QString disciplina); //OK

    int getMatriculaAluno(QString nomeAluno); //OK
    int getIdDisciplina(QString disciplina); //OK

    bool inserirAlunoEmTurma(QString nomeAluno, int idTurma); //OK
    bool inserirAlunoNasAulas(QString nomeAluno); //OK

    void inserirTodosAlunosNasAulas(); //OK

    void mostrarAlunosTurmasAulas(); //OK

    void mostrarAlunos(); //OK
    void mostrarTurmas(); //OK
    void mostrarDisciplinas(); //OK

    bool marcarPresenca(QString rfid);
private:
    QString dbName;
    QSqlDatabase db;
};

#endif // BANCO_H
