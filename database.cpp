#include "entidades.h"
#include "dominios.h"
#include "sqlite3.h"
#include "database.h"
#include <string>
#include <sstream>

//Atributo estatico container List.

list<ElementoResultado> ComandoSQL::listaResultado;



//---------------------------------------------------------------------------
//Classe ErroPersistencia.

EErroPersistencia::EErroPersistencia(string mensagem)
{
        this->mensagem = mensagem;


}

string EErroPersistencia::what()
{
        return mensagem;
}

//---------------------------------------------------------------------------
//Classe ElementoResultado.

void ElementoResultado::setNomeColuna(const string &nomeColuna)
{
        this->nomeColuna = nomeColuna;
}

void ElementoResultado::setValorColuna(const string &valorColuna)
{
        this->valorColuna = valorColuna;
}

//---------------------------------------------------------------------------
//Classe ComandoSQL.

void ComandoSQL::conectar()
{
        std::cout << "Hello World!";
}

void ComandoSQL::desconectar()
{
         std::cout << "Hello World!";
}

void ComandoSQL::executar()
{
         std::cout << "Hello World!";
}

int ComandoSQL::callback(void *NotUsed, int argc, char **valorColuna, char **nomeColuna)
{
        std::cout << "Hello World!";
}

ComandoSenha::ComandoSenha(Email email)
{
         std::cout << "Hello World!";
}

string ComandoSenha::getResultado()
{
         std::cout << "Hello World!";
}

// ---------------------------------------------
// Implementação do comando Cadastrar Usuario
// ---------------------------------------------

ComandoCadastrarUsuario::ComandoCadastrarUsuario(Usuario usuario)
{
         std::cout << "Hello World!";
}

// ---------------------------------------------
// Implementação do comando Descadastrar Usuario
// ---------------------------------------------

ComandoDescadastrarUsuario::ComandoDescadastrarUsuario(Email email)
{
        comandoSQL = "DELETE FROM usuario WHERE email = '";
        comandoSQL += email.getValor();
        comandoSQL += "'";
}

// ---------------------------------------------
// Implementação do comando Editar Usuário
// ---------------------------------------------

ComandoEditarUsuario::ComandoEditarUsuario(Usuario usuario)
{
        comandoSQL = "UPDATE usuario ";
        comandoSQL += "SET nome = '" + usuario.getNome().getValor();
        comandoSQL += "', senha = '" + usuario.getSenha().getValor();
        comandoSQL += "' WHERE email = '" + usuario.getEmail().getValor();
        comandoSQL += "'";
}


//--------------------------------------------------------------------------------------
//|                                 Hospedagem                                           |
//--------------------------------------------------------------------------------------

// ------------------------------------------------
// Implementação do comando Cadastrar Hospedagem
// ------------------------------------------------
ComandoCadastrarHospedagem::ComandoCadastrarHospedagem(Hospedagem hospedagem, Email email, Codigo codigo)
{
        comandoSQL = "INSERT INTO Hospedagem VALUES (";
        comandoSQL += "NULL, ";
        comandoSQL += "NULL, ";
        comandoSQL += "'" + hospedagem.getCity().getValor() + "', ";
        comandoSQL += "'" + hospedagem.getPais().getValor() + "', ";
        comandoSQL += "'" + hospedagem.getDescricao_hosp().getValor() + "', ";
        comandoSQL += "'" + to_string(std::stoi(codigo.getValor())) + "', ";
        comandoSQL += "'" + email.getValor() + "')";
}

NextIdHospedagem::NextIdHospedagem()
{
        comandoSQL = "SELECT seq + 1 FROM SQLITE_SEQUENCE WHERE name='Hospedagem'";
}
int NextIdHospedagem::getResultado()
{
        ElementoResultado resultado;
        int result;

        if (listaResultado.empty())
        {
                throw EErroPersistencia("Lista Vazia.");
        }
        resultado = listaResultado.back();
        listaResultado.pop_back();

        result = stoi(resultado.getValorColuna());
        return result;
}

// ------------------------------------------------
// Implementação do comando Descadastrar Hospedagem
// ------------------------------------------------
ComandoDescadastrarHospedagem::ComandoDescadastrarHospedagem(Codigo codigo, Email email)
{
        string icodigo = codigo.getValor();
        icodigo.pop_back();
        comandoSQL = "DELETE FROM Hospedagem WHERE (Codigo = '";
        comandoSQL += icodigo;
        comandoSQL += "') AND (Guia = '";
        comandoSQL += email.getValor();
        comandoSQL += "')";
}

ListarHospedagem::ListarHospedagem()
{
        comandoSQL = "SELECT Codigo FROM Hospedagem";
}

// ------------------------------------------------
// Implementação do comando Editar Hospedagem
// ------------------------------------------------

ComandoEditarHospedagem::ComandoEditarHospedagem(Hospedagem hospedagem, Email email)
{
        comandoSQL = "UPDATE Hospedagem ";
        comandoSQL += ", Cidade = '" + hospedagem.getCity().getValor();
        comandoSQL += ", Descricao = '" + hospedagem.getDescricao_hosp().getValor();
        comandoSQL += "', Pais = '" + hospedagem.getPais().getValor();
        comandoSQL += "' WHERE (Codigo = '" + hospedagem.getCodigo().getValor();
        comandoSQL += "') AND (Guia = '" + email.getValor() + "')";
}

// ------------------------------------------------
// Implementação do comando Listar Hospedagens
// ------------------------------------------------

ComandoListarHospedagem::ComandoListarHospedagem()
{
        comandoSQL = "SELECT * FROM Hospedagem";
}

//--------------------------------------------------------------------------------------
//|                                  Avaliação                                         |
//--------------------------------------------------------------------------------------

// ------------------------------------------------
// Implementação do comando Cadastrar Avaliação
// ------------------------------------------------

ComandoCadastrarAvaliacao::ComandoCadastrarAvaliacao(Avaliacao avaliacao, Email email, Codigo codigo)
{
        comandoSQL = "INSERT INTO Avaliacao VALUES (";
        comandoSQL += "NULL, ";
        comandoSQL += "'" + to_string(std::stoi(avaliacao.getNota_ava().getValor())) + "', ";
        comandoSQL += "'" + avaliacao.getDescricao_ava().getValor() + "', ";
        comandoSQL += "'" + codigo.getValor() + "')";
}

GetNotasAvaliacao::GetNotasAvaliacao()
{
        comandoSQL = "SELECT Nota FROM Avaliacao";
}
list<string> GetNotasAvaliacao::getResultado()
{
        ElementoResultado resultado;

        if (listaResultado.empty())
        {
                throw EErroPersistencia("Lista Vazia.");
        }
        resultado = listaResultado.back();
        listaResultado.pop_back();

        return resultado.getValoresColuna();
}

ComandoDescadastrarAvaliacao::ComandoDescadastrarAvaliacao(Codigo codigo, Email email)
{
        comandoSQL = "DELETE FROM Avaliacao WHERE (Codigo = '";
        comandoSQL += codigo.getValor();
        comandoSQL += "') AND (Avaliador = '";
        comandoSQL += email.getValor();
        comandoSQL += "')";
}

// ------------------------------------------------
// Implementação do comando Editar Avaliação
// ------------------------------------------------

ComandoEditarAvaliacao::ComandoEditarAvaliacao(Avaliacao avaliacao, Email email)
{
        comandoSQL = "UPDATE Avaliacao ";
        comandoSQL += "SET Nota = '" + avaliacao.getNota_ava().getValor();
        comandoSQL += "', Descricao = " + avaliacao.getDescricao_ava().getValor();
        comandoSQL += "' WHERE (Codigo = '" + avaliacao.getCodigo_ava().getValor();
        comandoSQL += "') AND (Avaliador = '" + email.getValor() + "')";
}

// ------------------------------------------------
// Implementação do comando Listar Avaliações
// ------------------------------------------------

ComandoListarAvaliacoes::ComandoListarAvaliacoes(Email)
{
        comandoSQL = "SELECT * FROM Excursao";
}
