#ifndef readerCsv
#define readerCsv

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

class Person {
private:
    std::string cpf; // CPF da pessoa
    std::string firstName; // Primeiro nome da pessoa
    std::string lastName; // Sobrenome da pessoa
    std::string birthDate; // Data de nascimento da pessoa
    std::string address; // Endereço da pessoa

public:
    Person() {} // Construtor padrão

    Person(const std::string& cpf, const std::string& firstName, const std::string& lastName,
           const std::string& birthDate, const std::string& address)
        : cpf(cpf), firstName(firstName), lastName(lastName), birthDate(birthDate), address(address) {}

    const std::string& getCPF() const { // Retorna o CPF da pessoa
        return cpf;
    }

    const std::string& getFirstName() const { // Retorna o primeiro nome da pessoa
        return firstName;
    }

    const std::string& getLastName() const { // Retorna o sobrenome da pessoa
        return lastName;
    }

    const std::string& getBirthDate() const { // Retorna a data de nascimento da pessoa
        return birthDate;
    }

    const std::string& getAddress() const { // Retorna o endereço da pessoa
        return address;
    }
};

class CSVReader {
private:
    std::string filename; // Nome do arquivo CSV

public:
    CSVReader(const std::string& filename)
        : filename(filename) {}

    std::map<std::string, Person> readData() { // Lê os dados do arquivo CSV e retorna um mapa de CPF para objetos Person
        std::map<std::string, Person> people; // Mapa para armazenar as pessoas
        std::ifstream file(filename); // Abre o arquivo para leitura
        std::string line; // String para armazenar cada linha do arquivo

        while (std::getline(file, line)) { // Lê cada linha do arquivo
            std::istringstream iss(line); // Cria um fluxo de string a partir da linha
            std::vector<std::string> tokens; // Vetor para armazenar os valores separados por vírgula
            std::string token; // String temporária para armazenar cada valor

            while (std::getline(iss, token, ',')) { // Separa os valores por vírgula
                tokens.push_back(token); // Armazena cada valor no vetor
            }

            if (tokens.size() == 5) { // Verifica se foram lidos os cinco valores esperados
                const std::string& cpf = tokens[0]; // Lê o CPF
                const std::string& firstName = tokens[1]; // Lê o primeiro nome
                const std::string& lastName = tokens[2]; // Lê o sobrenome
                const std::string& birthDate = tokens[3]; // Lê a data de nascimento
                const std::string& address = tokens[4]; // Lê o endereço

                people[cpf] = Person(cpf, firstName, lastName, birthDate, address); // Adiciona a pessoa ao mapa usando o CPF como chave
            }
        }
        return people; // Retorna o mapa de pessoas lido do arquivo CSV
    }
};

#endif
