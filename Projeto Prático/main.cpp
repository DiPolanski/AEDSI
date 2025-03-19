#include <iostream>
#include <string>
using namespace std;

bool ERRO;
const int TAM = 100;

class LimiteRecursosException : public std::exception
{
public:
  const char* what() const throw()
  {
    return "Limite de recursos alcançado.";
  }
};

class Pessoa
{
protected:
  string nome;
  int dia;
  int mes;
  int ano;

public:
  Pessoa(string nome, int dia, int mes, int ano)
      : nome(nome), dia(dia), mes(mes), ano(ano)
  {
    if (totalPessoas >= TAM)
    {
      throw LimiteRecursosException();
    }
    totalPessoas++;
  }

  virtual void escrevePessoa()
  {
    cout << "Nome: " << nome << endl;
    cout << "Data de nascimento: " << dia << "/" << mes << "/" << ano << endl;
  }

  virtual bool verificaAniversario(int mesAtual)
  {
    return mes == mesAtual;
  }

  static int getTotalPessoas()
  {
    return totalPessoas;
  }

private:
  static int totalPessoas;
};

int Pessoa::totalPessoas = 0;

class Aluno : public Pessoa
{
private:
  int matricula;

public:
  Aluno(string nome, int dia, int mes, int ano, int matricula)
      : Pessoa(nome, dia, mes, ano), matricula(matricula) {}

  void escrevePessoa() override
  {
    Pessoa::escrevePessoa();
    cout << "Matrícula: " << matricula << endl;
  }
};

class Professor : public Pessoa
{
private:
  string titulo;
  static int totalProfessores;

public:
  Professor(string nome, int dia, int mes, int ano, string titulo)
      : Pessoa(nome, dia, mes, ano), titulo(titulo)
  {
    totalProfessores++;
  }

  void escrevePessoa() override
  {
    Pessoa::escrevePessoa();
    cout << "Título: " << titulo << endl;
  }

  static int getTotalProfessores()
  {
    return totalProfessores;
  }
};

int Professor::totalProfessores = 0;

void cadastraAluno(Aluno* alunos[], int& qntAlunos)
{
  string nome;
  int dia, mes, ano, matricula;

  cout << "\nNome: ";
  cin.ignore();
  getline(cin, nome);
  do
  {
    cout << "Dia: ";
    cin >> dia;
    ERRO = dia < 0 || dia > 31;
    if (ERRO)
    {
      cout << "Dia inválido!\a" << endl;
    }
  } while (ERRO);

  do
  {
    cout << "Mês: ";
    cin >> mes;
    ERRO = mes < 0 || mes > 12;
    if(ERRO)
    {
      cout << "Mes inválido!\a" << endl;
    }
  } while (ERRO);

  do
  {
    cout << "Ano: ";
    cin >> ano;
    ERRO = ano < 0;
    if (ERRO)
    {
      cout << "Ano inválido\a" << endl;
    }
  } while (ERRO);
  cout << "Matrícula: ";
  cin >> matricula;

  try
  {
    Aluno* aluno = new Aluno(nome, dia, mes, ano, matricula);
    alunos[qntAlunos] = aluno;
    qntAlunos++;
  }
  catch (const LimiteRecursosException& e)
  {
    cerr << "Erro: " << e.what() << endl;
  }
}

void cadastraProfessor(Professor* professores[], int& qntProfessores)
{
  string nome, titulo;
  int dia, mes, ano;

  cout << "\nNome: ";
  cin.ignore();
  getline(cin, nome);

  do
  {
    cout << "Dia: ";
    cin >> dia;
    ERRO = dia < 0 || dia > 31;
    if (ERRO)
    {
      cout << "Dia inválido!\a" << endl;
    }
  } while (ERRO);

  do
  {
    cout << "Mês: ";
    cin >> mes;
    ERRO = mes < 0 || mes > 12;
    if(ERRO)
    {
      cout << "Mes inválido!\a" << endl;
    }
  } while (ERRO);

  do
  {
    cout << "Ano: ";
    cin >> ano;
    ERRO = ano < 0;
    if (ERRO)
    {
      cout << "Ano inválido\a" << endl;
    }
  } while (ERRO);

  cout << "Título: ";
  cin.ignore();
  getline(cin, titulo);

  try
  {
    Professor* professor = new Professor(nome, dia, mes, ano, titulo);
    professores[qntProfessores] = professor;
    qntProfessores++;
  }
  catch (const LimiteRecursosException& e)
  {
    cerr << "Erro: " << e.what() << endl;
  }
}

void listarAlunos(Aluno* alunos[], int qntAlunos)
{
  if (qntAlunos == 0)
  {
    cout << "Não há alunos cadastrados." << endl;
    return;
  }

  cout << "\nLista de Alunos:" << endl;
  for (int i = 0; i < qntAlunos; i++)
  {
    cout << "Aluno " << i + 1 << ":" << endl;
    alunos[i]->escrevePessoa();
    cout << endl;
  }
}

void listarProfessores(Professor* professores[], int qntProfessores)
{
  if (qntProfessores == 0)
  {
    cout << "Não há professores cadastrados." << endl;
    return;
  }

  cout << "\nLista de Professores:" << endl;
  for (int i = 0; i < qntProfessores; i++)
  {
    cout << "Professor " << i + 1 << ":" << endl;
    professores[i]->escrevePessoa();
    cout << endl;
  }
}

void listarAniversariantes(Aluno* alunos[], int qntAlunos, Professor* professores[], int qntProfessores, int mes)
{
  bool encontrou = false;

  cout << "\nAniversariantes do mês " << mes << ":" << endl;

  for (int i = 0; i < qntAlunos; i++)
  {
    if (alunos[i]->verificaAniversario(mes))
    {
      alunos[i]->escrevePessoa();
      cout << endl;
      encontrou = true;
    }
  }

  for (int i = 0; i < qntProfessores; i++)
  {
    if (professores[i]->verificaAniversario(mes))
    {
      professores[i]->escrevePessoa();
      cout << endl;
      encontrou = true;
    }
  }

  if (!encontrou)
  {
    cout << "Não há aniversariantes neste mês." << endl;
  }
}

int main()
{
  Aluno* alunos[TAM];
  Professor* professores[TAM];
  int qntAlunos = 0;
  int qntProfessores = 0;

  int opcao;
  do
  {
    cout << "\nMenu:" << endl;
    cout << "0 - Sair" << endl;
    cout << "1 - Cadastrar Aluno" << endl;
    cout << "2 - Cadastrar Professor" << endl;
    cout << "3 - Listar Alunos" << endl;
    cout << "4 - Listar Professores" << endl;
    cout << "5 - Listar Aniversariantes do Mês" << endl;
    cout << "Escolha uma opção: ";
    cin >> opcao;

    switch (opcao)
    {
      case 1:
        cadastraAluno(alunos, qntAlunos);
        break;

      case 2:
        cadastraProfessor(professores, qntProfessores);
        break;

      case 3:
        listarAlunos(alunos, qntAlunos);
        break;

      case 4:
        listarProfessores(professores, qntProfessores);
        break;

      case 5:
        int mes;
        do
        {
          cout << "Mês: ";
          cin >> mes;
          ERRO = mes < 0 || mes > 12;
          if(ERRO)
          {
            cout << "Mes inválido!" << endl;
          }
        } while (ERRO);
        listarAniversariantes(alunos, qntAlunos, professores, qntProfessores, mes);
        break;

      case 0:
        cout << "\nObrigado por usar o programa." << endl;
        break;

      default:
        cout << "\nOpção inválida. Tente novamente." << endl;
        break;
    }
  } while (opcao != 0);

  return 0;
}
