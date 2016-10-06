#include "Banco.h"

Banco::Banco(QString nome)
{
    dbName = nome;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);

    if(!db.open())
    {
        qDebug() << "Couldn't open database!";
    }
    else
    {
        qDebug() << "Database open!";

        /*adicionarAluno("Filipe Nascimento", "AAAAAAAA");
        adicionarAluno("Henrique Jung", "BBBBBBB");
        adicionarAluno("Alessandra Jandrey", "CCCCCC");

        adicionarDisciplina("ProgEstruturada");
        adicionarDisciplina("AnaliseAlgoritmos");
        adicionarDisciplina("SistemasOperacionais");

        adicionarTurma(2016,2,"ProgEstruturada");
        adicionarTurma(2016,2,"AnaliseAlgoritmos");
        adicionarTurma(2016,2,"SistemasOperacionais");
        adicionarTurma(2017,1,"ProgEstruturada");
        adicionarTurma(2017,1,"AnaliseAlgoritmos");

        adicionarAula("2016-01-01",1);
        adicionarAula("2016-01-02",1);
        adicionarAula("2016-02-01",2);
        adicionarAula("2016-02-02",2);
        adicionarAula("2016-03-01",3);
        adicionarAula("2016-03-02",3);
        adicionarAula("2016-04-01",4);
        adicionarAula("2016-04-02",4);

        inserirAlunoEmTurma("Filipe Nascimento", 1);
        inserirAlunoEmTurma("Filipe Nascimento", 3);
        inserirAlunoEmTurma("Henrique Jung", 1);
        inserirAlunoEmTurma("Henrique Jung", 2);
        inserirAlunoEmTurma("Alessandra Jandrey", 2);
        inserirAlunoEmTurma("Alessandra Jandrey", 3);

        qDebug() << "";

        inserirTodosAlunosNasAulas();

        mostrarAlunosTurmasAulas();
        */

    }
}
bool Banco::adicionarDisciplina(QString nome)
{
    if(!existeDisciplina(nome))
    {
        QSqlQuery query;
        QString insert = "INSERT INTO Disciplina(nome) VALUES(\"";
        insert.append(nome);
        insert.append("\");");
        return query.exec(insert);
        qDebug() << "INSERINDO DISCIPLINA" << nome;
    }
    return false;
}

bool Banco::adicionarAluno(QString nome, QString rfid)
{
    if(!existeAluno(nome))
    {
        QSqlQuery query;
        QString insert = "INSERT INTO Aluno(nome, rfid) VALUES(\"";
        insert.append(nome).append("\",\"").append(rfid);
        insert.append("\");");
        qDebug() << "INSERINDO ALUNO" << nome;
        return query.exec(insert);
    }
    return false;
}

bool Banco::adicionarTurma(int ano, int semestre, QString nomeDisciplina)
{
    int disciplina = getIdDisciplina(nomeDisciplina);
    if(disciplina > 0)
    {
        QSqlQuery query;
        QString insert = "INSERT INTO Turma(ano,semestre,idDisciplina) VALUES(";
        insert.append(QString::number(ano)).append(",").append(QString::number(semestre)).append(",").append(QString::number(disciplina));
        insert.append(");");
        qDebug() << "INSERINDO TURMA" << ano << semestre << nomeDisciplina;
        return query.exec(insert);
    }
    else qDebug() << "idDisciplina = 0";
    return false;
}

bool Banco::adicionarAula(QString data, int idTurma)
{
    QSqlQuery query;
    QString insert = "INSERT INTO Aula(data, idTurma) Values(\"";
    insert.append(data).append("\",").append(QString::number(idTurma));
    insert.append(");");
    qDebug() << "INSERINDO AULA" << data << idTurma;
    return query.exec(insert);
}

bool Banco::existeTurma(int idTurma)
{
    bool existe = false;
    QSqlQuery query;
    QString select = "SELECT * FROM Turma WHERE Turma.idTurma = ";
    select.append(QString::number(idTurma));
    query.exec(select);
    while(query.next())
    {
        existe = true;
    }
    if(!existe) qDebug() << "Turma " << idTurma << " Nao existe!";
    return existe;
}

bool Banco::existeAluno(QString nomeAluno)
{
    bool existe = false;
    QSqlQuery query;
    QString select = "SELECT * FROM Aluno WHERE Aluno.nome = \"";
    select.append(nomeAluno);
    select.append("\"");
    query.exec(select);
    while(query.next())
    {
        existe = true;
    }
    return existe;
}

bool Banco::existeDisciplina(QString disciplina)
{
    bool existe = false;
    QSqlQuery query;
    QString select = "SELECT nome FROM Disciplina WHERE Disciplina.nome = \"";
    select.append(disciplina);
    select.append("\"");
    query.exec(select);
    while(query.next())
    {
        existe = true;
    }
    if(existe) qDebug() << "Disciplina" << disciplina << "JA EXISTE!";
    return existe;
}

int Banco::getMatriculaAluno(QString nomeAluno)
{
    int matricula = 0;
    QSqlQuery query;
    QString select = "SELECT matricula FROM Aluno WHERE Aluno.nome = \"";
    select.append(nomeAluno);
    select.append("\"");
    query.exec(select);
    while(query.next())
    {
        matricula = query.value(0).toInt();
    }
    return matricula;
}

int Banco::getIdDisciplina(QString disciplina)
{
    int id = 0;
    QSqlQuery query;
    QString select = "SELECT idDisciplina FROM Disciplina WHERE Disciplina.nome = \"";
    select.append(disciplina);
    select.append("\"");
    query.exec(select);
    while(query.next())
    {
        id = query.value(0).toInt();
    }
    return id;
}

bool Banco::inserirAlunoEmTurma(QString nomeAluno, int idTurma)
{
    // VERIFICAR SE ALUNO e TURMA EXISTEM
    if(!existeAluno(nomeAluno) || !existeTurma(idTurma)) return false;

    // VERIFICAR SE ALUNO JA ESTA NA TURMA
    bool jaExiste = false;
    int matricula = 0;
    QSqlQuery queryExiste;
    QString selectExiste = "SELECT Aluno_has_Turma.matricula, Aluno.nome FROM Aluno_has_Turma JOIN Aluno ON Aluno.matricula = Aluno_has_Turma.matricula WHERE Aluno.nome = \"";
    selectExiste.append(nomeAluno);
    selectExiste.append("\" AND Aluno_has_turma.idTurma = ");
    selectExiste.append(QString::number(idTurma));
    queryExiste.exec(selectExiste);
    while(queryExiste.next())
    {
        jaExiste = true;
    }

    // SE NAO ESTIVER...
    matricula = getMatriculaAluno(nomeAluno);
    if(!jaExiste)
    {
        QSqlQuery queryInsert;
        QString insert = "INSERT INTO Aluno_has_Turma(matricula, idTurma) VALUES(";
        insert.append(QString::number(matricula));
        insert.append(", ");
        insert.append(QString::number(idTurma));
        insert.append(");");
        queryInsert.exec(insert);
        qDebug() << "Inserido";
        //inserirAlunoNasAulas(nomeAluno);
        return true;
    }
    else qDebug() << "ALUNO JA ESTA NA TURMA!";
    return false;
}

bool Banco::inserirAlunoNasAulas(QString nomeAluno)
{
    if(!existeAluno(nomeAluno)) return false;
    QSqlQuery queryAlunoTurma;
    QString selectAlunoTurma = "SELECT Aluno.matricula, Aluno.nome, Turma.idTurma FROM Aluno JOIN Aluno_has_Turma ON Aluno.matricula = Aluno_has_Turma.matricula JOIN Turma ON Aluno_has_Turma.idTurma = Turma.idTurma WHERE Aluno.nome = \"";
    selectAlunoTurma.append(nomeAluno);
    selectAlunoTurma.append("\"");
    queryAlunoTurma.exec(selectAlunoTurma);
    while(queryAlunoTurma.next())
    {
        QString mat = queryAlunoTurma.value(0).toString();
        QString name = queryAlunoTurma.value(1).toString();
        QString turma = queryAlunoTurma.value(2).toString();
        qDebug() << mat << name << turma;

        QSqlQuery queryTurmaAula;
        QString selectTurmaAula = "SELECT idAula, data FROM Aula WHERE idTurma = ";
        selectTurmaAula.append(turma);
        queryTurmaAula.exec(selectTurmaAula);
        while(queryTurmaAula.next())
        {
            QString aula = queryTurmaAula.value(0).toString();
            QString data = queryTurmaAula.value(1).toString();
            qDebug() << "  " << aula << data;

            bool existeAlunoHasAula = false;
            QSqlQuery queryAula;
            QString selectAula = "SELECT matricula, idAula, presenca FROM Aluno_has_Aula WHERE idAula = ";
            selectAula.append(aula);
            queryAula.exec(selectAula);
            while(queryAula.next())
            {
                existeAlunoHasAula = true;
                qDebug() << "     " << "OK!" << queryTurmaAula.value(2).toString();
            }
            if(!existeAlunoHasAula)
            {
                // CRIAR ALUNO HAS AULA
                qDebug() << "     " << "NAO EXISTE ALUNO_HAS_AULA, CRIANDO";
                QSqlQuery queryInsert;
                QString insert = "INSERT INTO Aluno_has_Aula(matricula, idAula, presenca) VALUES(";
                insert.append(mat);
                insert.append(",");
                insert.append(aula);
                insert.append(",");
                insert.append("0");
                insert.append(");");
                queryInsert.exec(insert);
            }
        }
    }
    return false;
}

void Banco::inserirTodosAlunosNasAulas()
{
    QSqlQuery query;
    query.exec("SELECT * FROM Aluno");
    while(query.next())
    {
        QString name = query.value(1).toString();
        inserirAlunoNasAulas(name);
    }
}

void Banco::mostrarAlunosTurmasAulas()
{
    QSqlQuery queryAlunoTurma;
    QString selectAlunoTurma = "SELECT Aluno.matricula, Aluno.nome, Turma.idTurma FROM Aluno JOIN Aluno_has_Turma ON Aluno.matricula = Aluno_has_Turma.matricula JOIN Turma ON Aluno_has_Turma.idTurma = Turma.idTurma ORDER BY Aluno.matricula, Turma.idTurma";
    queryAlunoTurma.exec(selectAlunoTurma);
    while(queryAlunoTurma.next())
    {
        QString mat = queryAlunoTurma.value(0).toString();
        QString name = queryAlunoTurma.value(1).toString();
        QString turma = queryAlunoTurma.value(2).toString();
        qDebug() << mat << name << turma;

        QSqlQuery queryTurmaAula;
        QString selectTurmaAula = "SELECT idAula, data FROM Aula WHERE idTurma = ";
        selectTurmaAula.append(turma);
        queryTurmaAula.exec(selectTurmaAula);
        while(queryTurmaAula.next())
        {
            QString aula = queryTurmaAula.value(0).toString();
            QString data = queryTurmaAula.value(1).toString();
            qDebug() << "  " << aula << data;

            bool existeAlunoHasAula = false;
            QSqlQuery queryAula;
            QString selectAula = "SELECT matricula, idAula, presenca FROM Aluno_has_Aula WHERE idAula = ";
            selectAula.append(aula);
            queryAula.exec(selectAula);
            while(queryAula.next())
            {
                existeAlunoHasAula = true;
                qDebug() << "     " << "OK!" << queryAula.value(2).toString();
            }
            if(!existeAlunoHasAula)
            {
                qDebug() << "     " << "FALTA ALUNO_HAS_AULA!";
            }
        }
    }
}

void Banco::mostrarAlunos()
{
    qDebug() << "Alunos:";
    QSqlQuery query;
    query.exec("SELECT * FROM Aluno");
    while(query.next())
    {
        QString id = query.value(0).toString();
        QString name = query.value(1).toString();
        qDebug() << id << name;
    }
}

void Banco::mostrarTurmas()
{
    qDebug() << "Turmas:";
    QSqlQuery query;
    query.exec("SELECT Turma.idTurma, Turma.ano, Turma.semestre, Disciplina.nome FROM Turma JOIN Disciplina ON Turma.idDisciplina = Disciplina.idDisciplina");
    while(query.next())
    {
        QString turma = query.value(0).toString();
        QString ano = query.value(1).toString();
        ano.append("/");
        ano.append(query.value(2).toString());
        QString disciplina = query.value(3).toString();
        qDebug() << turma << ano << disciplina;
    }
}

void Banco::mostrarDisciplinas()
{
    qDebug() << "Disciplinas:";
    QSqlQuery query;
    query.exec("SELECT * FROM Disciplina");
    while(query.next())
    {
        QString id = query.value(0).toString();
        QString name = query.value(1).toString();
        qDebug() << id << name;
    }
}
bool Banco::marcarPresenca(QString rfid)
{
    qDebug() << "INDO MARCAR RFID" << rfid;
    int idAula = 0;
    QSqlQuery queryEncontrarIDAula;
    QString select = "SELECT Aluno_has_Aula.idAula, Aluno_has_aula.presenca, Aula.data FROM Aluno JOIN Aluno_has_Aula ON Aluno.matricula = Aluno_has_Aula.matricula JOIN Aula ON Aluno_has_Aula.idAula = Aula.idAula WHERE Aluno.rfid = \"";

    select.append(rfid);
    select.append("\" ");
    select.append("ORDER BY Aluno_has_aula.presenca, Aula.data ASC");
    queryEncontrarIDAula.exec(select);
    while(queryEncontrarIDAula.next())
    {
        idAula = queryEncontrarIDAula.value(0).toInt();
        if(idAula > 0) break;
    }
    qDebug() << "ID:" << idAula;
    if(idAula == 0) return false; // ERRO
    QSqlQuery queryUpdate;
    QString update = "UPDATE Aluno_has_Aula SET presenca = 1 WHERE idAula = ";
    update.append(QString::number(idAula));

    queryUpdate.exec(update);
    return true;
}
