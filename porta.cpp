#include "porta.h"

///
/// AS PORTAS
///

/// Porta NOT
ptr_Porta PortaNOT::clone() const {
    return new PortaNOT(*this);
}

// Retorno do nome da porta
std::string PortaNOT::getName() const {
    return "NT";
}

// Simulador da porta NOT
bool PortaNOT::simular(const std::vector<bool3S>& in_port) {
    if (in_port.size() == 1) { // Verifica se há exatamente uma entrada
        if (in_port[0] == bool3S::TRUE) {
            setOutput(bool3S::FALSE);
        } else if (in_port[0] == bool3S::FALSE) {
            setOutput(bool3S::TRUE);
        } else {
            setOutput(bool3S::UNDEF);
        }
        return true;
    } else {
        setOutput(bool3S::UNDEF);
        return false;
    }
}

/// Porta AND
ptr_Porta PortaAND::clone() const {
    return new PortaAND(*this);
}

// Retorno do nome da porta
std::string PortaAND::getName() const {
    return "AN";
}

// Simulador da porta AND
bool PortaAND::simular(const std::vector<bool3S>& in_port) {
    if (in_port.size() == static_cast<size_t>(getNumInputs())) {
        bool3S result = bool3S::TRUE;
        for (const auto& input : in_port) {
            if (input == bool3S::FALSE) {
                setOutput(bool3S::FALSE);
                return true; // Curto-circuito
            } else if (input == bool3S::UNDEF) {
                result = bool3S::UNDEF;
            }
        }
        setOutput(result);
        return true;
    } else {
        setOutput(bool3S::UNDEF);
        return false;
    }
}

/// Porta NAND
ptr_Porta PortaNAND::clone() const {
    return new PortaNAND(*this);
}

// Retorno do nome da porta
std::string PortaNAND::getName() const {
    return "NA";
}

// Simulador da porta NAND
bool PortaNAND::simular(const std::vector<bool3S>& in_port) {
    if (in_port.size() == static_cast<size_t>(getNumInputs())) {
        PortaAND andGate(getNumInputs());
        if (andGate.simular(in_port)) {
            bool3S result = andGate.getOutput();
            setOutput(result == bool3S::TRUE ? bool3S::FALSE : (result == bool3S::FALSE ? bool3S::TRUE : bool3S::UNDEF));
            return true;
        }
    }
    setOutput(bool3S::UNDEF);
    return false;
}

/// Porta OR
ptr_Porta PortaOR::clone() const {
    return new PortaOR(*this);
}

// Retorno do nome da porta
std::string PortaOR::getName() const {
    return "OR";
}

// Simulador da porta OR
bool PortaOR::simular(const std::vector<bool3S>& in_port) {
    if (in_port.size() == static_cast<size_t>(getNumInputs())) {
        bool3S result = bool3S::FALSE;
        for (const auto& input : in_port) {
            if (input == bool3S::TRUE) {
                setOutput(bool3S::TRUE);
                return true; // Curto-circuito
            } else if (input == bool3S::UNDEF) {
                result = bool3S::UNDEF;
            }
        }
        setOutput(result);
        return true;
    } else {
        setOutput(bool3S::UNDEF);
        return false;
    }
}

/// Porta NOR
ptr_Porta PortaNOR::clone() const {
    return new PortaNOR(*this);
}

// Retorno do nome da porta
std::string PortaNOR::getName() const {
    return "NO";
}

// Simulador da porta NOR
bool PortaNOR::simular(const std::vector<bool3S>& in_port) {
    if (in_port.size() == static_cast<size_t>(getNumInputs())) {
        PortaOR orGate(getNumInputs());
        if (orGate.simular(in_port)) {
            bool3S result = orGate.getOutput();
            setOutput(result == bool3S::TRUE ? bool3S::FALSE : (result == bool3S::FALSE ? bool3S::TRUE : bool3S::UNDEF));
            return true;
        }
    }
    setOutput(bool3S::UNDEF);
    return false;
}

/// Porta XOR
ptr_Porta PortaXOR::clone() const {
    return new PortaXOR(*this);
}

// Retorno do nome da porta
std::string PortaXOR::getName() const {
    return "XO";
}

// Simulador da porta XOR
bool PortaXOR::simular(const std::vector<bool3S>& in_port) {
    if (in_port.size() == static_cast<size_t>(getNumInputs())) {
        bool3S result = bool3S::FALSE;
        int trueCount = 0;
        for (const auto& input : in_port) {
            if (input == bool3S::UNDEF) {
                setOutput(bool3S::UNDEF);
                return true;
            } else if (input == bool3S::TRUE) {
                ++trueCount;
            }
        }
        setOutput((trueCount % 2 == 1) ? bool3S::TRUE : bool3S::FALSE);
        return true;
    } else {
        setOutput(bool3S::UNDEF);
        return false;
    }
}

/// Porta NXOR
ptr_Porta PortaNXOR::clone() const {
    return new PortaNXOR(*this);
}

// Retorno do nome da porta
std::string PortaNXOR::getName() const {
    return "NX";
}

// Simulador da porta NXOR
bool PortaNXOR::simular(const std::vector<bool3S>& in_port) {
    if (in_port.size() == static_cast<size_t>(getNumInputs())) {
        PortaXOR xorGate(getNumInputs());
        if (xorGate.simular(in_port)) {
            bool3S result = xorGate.getOutput();
            setOutput(result == bool3S::TRUE ? bool3S::FALSE : (result == bool3S::FALSE ? bool3S::TRUE : bool3S::UNDEF));
            return true;
        }
    }
    setOutput(bool3S::UNDEF);
    return false;
}
