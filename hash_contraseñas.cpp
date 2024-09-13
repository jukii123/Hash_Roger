#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <sstream>

// Función para generar un salt aleatorio
std::string generateSalt(size_t length = 8) {
    static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string salt;
    salt.reserve(length);
    for (size_t i = 0; i < length; ++i) {
        salt += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return salt;
}


// Función hash simple basado en valores ASCII de la contraseña y el salt
std::string hashPassword(const std::string& password, const std::string& salt) {
    unsigned long hash = 0;
    for (char c : password + salt) {
        hash = hash * 31 + static_cast<unsigned long>(c);
    }

    std::stringstream ss;
    ss << std::hex << hash;
    return ss.str();
}

// Función para verificar una contraseña
bool verifyPassword(const std::string& storedHash, const std::string& password, const std::string& salt) {
    return storedHash == hashPassword(password, salt);
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Inicializar la semilla para la generación de números aleatorios para salt

    // Ejemplo de uso
    std::string password = "Hola";
    std::string salt = generateSalt(); // Generar un sal aleatorio
    std::string hashedPassword = hashPassword(password, salt); // Hash de la contraseña con el sal

    // Imprimir información
    std::cout << "Salt: " << salt << std::endl;
    std::cout << "Hashed Password: " << hashedPassword << std::endl;

    // Verificar la contraseña
    std::string inputPassword = "Hola";
    if (verifyPassword(hashedPassword, inputPassword, salt)) {
        std::cout << "Password is correct!" << std::endl;
    } else {
        std::cout << "Password is incorrect!" << std::endl;
    }

    return 0;
}