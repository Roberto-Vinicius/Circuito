#include "porta.h"

using namespace std;
///
/// AS PORTAS
///

/// Porta NOT

//
// IMPLEMENTEI
//
ptr_Porta PortaNOT::clone() const {
    return new PortaNOT(*this);
}

std::string PortaNOT::getName() const {
    return "NT";
}

bool PortaNOT::simular(const std::vector<bool3S>& in_port) {
    if (in_port.size() != 1) {
        setOutput(bool3S::UNDEF);
        return false;
    }
    setOutput(!in_port[0]); // Negação
    return true;
}


/// Porta AND

//
// IMPLEMENTEI
//
ptr_Porta PortaAND::clone() const {
    return new PortaAND(*this);
}

std::string PortaAND::getName() const {
    return "AN";
}

bool PortaAND::simular(const std::vector<bool3S>& in_port) {
    if (in_port.size() != getNumInputs()) {
        setOutput(bool3S::UNDEF);
        return false;
    }

    bool3S result = in_port[0];
    for (size_t i = 1; i < in_port.size(); ++i) {
        result = result && in_port[i];
    }

    setOutput(result);
    return true;
}

/// Porta NAND

//
// IMPLEMENTEI
//
ptr_Porta PortaNAND::clone() const {
    return new PortaNAND(*this);
}

std::string PortaNAND::getName() const {
    return "NA";
}

bool PortaNAND::simular(const std::vector<bool3S>& in_port) {
    if (in_port.size() != getNumInputs()) {
        setOutput(bool3S::UNDEF);
        return false;
    }

    bool3S result = in_port[0];
    for (size_t i = 1; i < in_port.size(); ++i) {
        result = result && in_port[i];
    }

    setOutput(!result); // Negação do resultado
    return true;
}

/// Porta OR

//
// IMPLEMENTEI
//
ptr_Porta PortaOR::clone() const {
    return new PortaOR(*this);
}

std::string PortaOR::getName() const {
    return "OR";
}

bool PortaOR::simular(const std::vector<bool3S>& in_port) {
    if (in_port.size() != getNumInputs()) {
        setOutput(bool3S::UNDEF);
        return false;
    }

    bool3S result = in_port[0];
    for (size_t i = 1; i < in_port.size(); ++i) {
        result = result || in_port[i];
    }

    setOutput(result);
    return true;
}

/// Porta NOR

//
// IMPLEMENTEI
//
ptr_Porta PortaNOR::clone() const {
    return new PortaNOR(*this);
}

std::string PortaNOR::getName() const {
    return "NO";
}

bool PortaNOR::simular(const std::vector<bool3S>& in_port) {
    if (in_port.size() != getNumInputs()) {
        setOutput(bool3S::UNDEF);
        return false;
    }

    bool3S result = in_port[0];
    for (size_t i = 1; i < in_port.size(); ++i) {
        result = result || in_port[i];
    }

    setOutput(!result); // Negação do resultado
    return true;
}

/// Porta XOR

//
// IMPLEMENTEI
//
ptr_Porta PortaXOR::clone() const {
    return new PortaXOR(*this);
}

std::string PortaXOR::getName() const {
    return "XO";
}

bool PortaXOR::simular(const std::vector<bool3S>& in_port) {
    if (in_port.size() != getNumInputs()) {
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

/// Porta NXOR

//
// IMPLEMENTEI
//
ptr_Porta PortaNXOR::clone() const {
    return new PortaNXOR(*this);
}

std::string PortaNXOR::getName() const {
    return "NX";
}

bool PortaNXOR::simular(const std::vector<bool3S>& in_port) {
    if (in_port.size() != getNumInputs()) {
        setOutput(bool3S::UNDEF);
        return false;
    }

    bool3S result = in_port[0];
    for (size_t i = 1; i < in_port.size(); ++i) {
        result = result ^ in_port[i];
    }

    setOutput(!result); // Negação do XOR
    return true;
}
