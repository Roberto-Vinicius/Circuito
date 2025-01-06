#ifndef _PORTA_H_
#define _PORTA_H_

#include <string>
#include <vector>
#include "bool3S.h"

///
/// A CLASSE ABSTRATA PORTA
///

class Porta;
using ptr_Porta = Porta*;

class Porta
{
protected:
  // O numero de entradas da porta
  int Nin_port;
  // O valor logico da saida da porta (?, F ou T)
  bool3S out_port;

public:
  /// ***********************
  /// Inicializacao e finalizacao
  /// ***********************

  // A classe abstrata Porta nao tem construtor default.
  Porta() = delete;
  // Construtor especifico (recebe como parametro o numero de entradas da porta)
  Porta(int NI): Nin_port(NI),out_port(bool3S::UNDEF) {}
  // Destrutor virtual
  virtual ~Porta() {}

  // Essa funcao virtual pura deve criar e retornar um ponteiro que aponta para
  // uma copia de si mesma, do tipo correto.
  virtual ptr_Porta clone() const = 0;

  /// ***********************
  /// Funcoes de testagem
  /// ***********************

  // Retorna true se um indice (qual entrada da porta) eh valido
  bool validIndex(int I) const
  {
    return (I>=0 && I<getNumInputs());
  }

  /// ***********************
  /// Funcoes de consulta
  /// ***********************

  // Funcao virtual pura que retorna a sigla correta da Port (AN, NT, OR, NX, etc.)
  virtual std::string getName() const = 0;

  // Retorna o numero de entradas da porta
  int getNumInputs() const
  {
    return Nin_port;
  }

  // Retorna a saida logica (?, F ou T) da porta
  bool3S getOutput() const
  {
    return out_port;
  }

  /// ***********************
  /// Funcoes de modificacao
  /// ***********************

  // Fixa o valor logico da saida da porta (?, F, T)
  void setOutput(bool3S S)
  {
    out_port=S;
  }

  /// ***********************
  /// SIMULACAO (funcao principal da porta)
  /// ***********************

  // Simula uma porta logica.
  // Recebe um vector de bool3S com os valores logicos das entradas da porta
  // com os quais deve ser simulada a funcao logica da porta.
  // Se a dimensao do vetor in_port for adequada (>0 e igual ao numero de entradas
  // da porta), armazena o resultado da simulacao em out_port e retorna true.
  // Se nao for, faz out_port = UNDEF e retorna false.
  virtual bool simular(const std::vector<bool3S>& in_port) = 0;
};

///
/// As outras PORTAS
///

class PortaNOT: public Porta
{
public:
  // Construtor default (fixa o numero de entradas da porta como sendo 1)
  PortaNOT(): Porta(1) {}
  // DEMAIS FUNCOES DA PORTA
  //
  //  DECLAREI
  //
  // Retorna a sigla da porta
  std::string getName() const override {
      return "NT";
  }

  // Clona a porta
  ptr_Porta clone() const override {
      return new PortaNOT(*this);
  }

  // Simula a porta NOT
  bool simular(const std::vector<bool3S>& in_port) override {
      if (in_port.size() != 1) {
          setOutput(bool3S::UNDEF);
          return false;
      }
      setOutput(~in_port[0]); // Use ~ ou ! dependendo da implementação
      return true;
  }
};

class PortaAND: public Porta
{
public:
  // PortaAND nao tem construtor default: sempre deve ser informado o num de entradas
  PortaAND() = delete;
  // Construtor especifico (recebe como parametro o numero de entradas da porta)
  // Se o parametro for invalido, faz Nin_port=0
  PortaAND(int NI): Porta(NI)
  {
    if (NI<2) Nin_port=0;
  }
  // DEMAIS FUNCOES DA PORTA
  //
  //   DECLAREI
  //
  // Retorna a sigla da porta
  std::string getName() const override {
      return "AN";
  }

  ptr_Porta clone() const override {
      return new PortaAND(*this);
  }

  bool simular(const std::vector<bool3S>& in_port) override {
      if (in_port.size() != static_cast<size_t>(getNumInputs())) {
          setOutput(bool3S::UNDEF);
          return false;
      }

      bool3S result = in_port[0];
      for (size_t i = 1; i < in_port.size(); ++i) {
          result = result & in_port[i];
      }

      setOutput(result);
      return true;
  }
};

class PortaNAND: public Porta
{
public:
  // PortaNAND nao tem construtor default: sempre deve ser informado o num de entradas
  PortaNAND() = delete;
  // Construtor especifico (recebe como parametro o numero de entradas da porta)
  // Se o parametro for invalido, faz Nin_port=0
  PortaNAND(int NI): Porta(NI)
  {
    if (NI<2) Nin_port=0;
  }
  // DEMAIS FUNCOES DA PORTA
  //
  // DECLAREI
  //
  // Retorna a sigla da porta
  std::string getName() const override {
      return "NA";
  }

  ptr_Porta clone() const override {
      return new PortaNAND(*this);
  }

  bool simular(const std::vector<bool3S>& in_port) override {
      if (in_port.size() != static_cast<size_t>(getNumInputs())) {
          setOutput(bool3S::UNDEF);
          return false;
      }

      bool3S result = in_port[0];
      for (size_t i = 1; i < in_port.size(); ++i) {
          result = result & in_port[i];
      }

      setOutput(~result);
      return true;
  }
};

class PortaOR: public Porta
{
public:
  // PortaOR nao tem construtor default: sempre deve ser informado o num de entradas
  PortaOR() = delete;
  // Construtor especifico (recebe como parametro o numero de entradas da porta)
  // Se o parametro for invalido, faz Nin_port=0
  PortaOR(int NI): Porta(NI)
  {
    if (NI<2) Nin_port=0;
  }
  // DEMAIS FUNCOES DA PORTA
  //
  // DECLAREI
  //
  // Retorna a sigla da porta
  std::string getName() const override {
      return "OR";
  }

  ptr_Porta clone() const override {
      return new PortaOR(*this);
  }

  bool simular(const std::vector<bool3S>& in_port) override {
      if (in_port.size() != static_cast<size_t>(getNumInputs())) {
          setOutput(bool3S::UNDEF);
          return false;
      }

      bool3S result = in_port[0];
      for (size_t i = 1; i < in_port.size(); ++i) {
          result = result | in_port[i];
      }

      setOutput(result);
      return true;
  }
};

class PortaNOR: public Porta
{
public:
  // PortaNOR nao tem construtor default: sempre deve ser informado o num de entradas
  PortaNOR() = delete;
  // Construtor especifico (recebe como parametro o numero de entradas da porta)
  // Se o parametro for invalido, faz Nin_port=0
  PortaNOR(int NI): Porta(NI)
  {
    if (NI<2) Nin_port=0;
  }
  // DEMAIS FUNCOES DA PORTA
  //
  // DECLAREI
  //
  // Retorna a sigla da porta
  std::string getName() const override {
      return "NO";
  }

  ptr_Porta clone() const override {
      return new PortaNOR(*this);
  }

  bool simular(const std::vector<bool3S>& in_port) override {
      if (in_port.size() != static_cast<size_t>(getNumInputs())) {
          setOutput(bool3S::UNDEF);
          return false;
      }

      bool3S result = in_port[0];
      for (size_t i = 1; i < in_port.size(); ++i) {
          result = result | in_port[i];
      }

      setOutput(~result);
      return true;
  }
};

class PortaXOR: public Porta
{
public:
  // PortaXOR nao tem construtor default: sempre deve ser informado o num de entradas
  PortaXOR() = delete;
  // Construtor especifico (recebe como parametro o numero de entradas da porta)
  // Se o parametro for invalido, faz Nin_port=0
  PortaXOR(int NI): Porta(NI)
  {
    if (NI<2) Nin_port=0;
  }
  // DEMAIS FUNCOES DA PORTA
  //
  // DECLAREI
  //
  // Retorna a sigla da porta
  std::string getName() const override {
      return "XO";
  }

  ptr_Porta clone() const override {
      return new PortaXOR(*this);
  }

  bool simular(const std::vector<bool3S>& in_port) override {
      if (in_port.size() != static_cast<size_t>(getNumInputs())) {
          setOutput(bool3S::UNDEF);
          return false;
      }

      bool3S result = in_port[0];
      for (size_t i = 1; i < in_port.size(); ++i) {
          result = result ^ in_port[i];
      }

      setOutput(result);
      return true;
  }
};

class PortaNXOR: public Porta
{
public:
  // PortaNXOR nao tem construtor default: sempre deve ser informado o num de entradas
  PortaNXOR() = delete;
  // Construtor especifico (recebe como parametro o numero de entradas da porta)
  // Se o parametro for invalido, faz Nin_port=0
  PortaNXOR(int NI): Porta(NI)
  {
    if (NI<2) Nin_port=0;
  }
  // DEMAIS FUNCOES DA PORTA
  //
  // DECLAREI
  //
  // Retorna a sigla da porta
  std::string getName() const override {
      return "NX";
  }

  ptr_Porta clone() const override {
      return new PortaNXOR(*this);
  }

  bool simular(const std::vector<bool3S>& in_port) override {
      if (in_port.size() != static_cast<size_t>(getNumInputs())) {
          setOutput(bool3S::UNDEF);
          return false;
      }

      bool3S result = in_port[0];
      for (size_t i = 1; i < in_port.size(); ++i) {
          result = result ^ in_port[i];
      }

      setOutput(~result);
      return true;
  }
};

#endif // _PORTA_H_
