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
    std::string cpf;
    std::string firstName;
    std::string lastName;
    std::string birthDate;
    std::string address;

public:
    Person() {} // Construtor padrão

    Person(const std::string& cpf, const std::string& firstName, const std::string& lastName,
           const std::string& birthDate, const std::string& address)
        : cpf(cpf), firstName(firstName), lastName(lastName), birthDate(birthDate), address(address) {}

    const std::string& getCPF() const {
        return cpf;
    }

    const std::string& getFirstName() const {
        return firstName;
    }

    const std::string& getLastName() const {
        return lastName;
    }

    const std::string& getBirthDate() const {
        return birthDate;
    }

    const std::string& getAddress() const {
        return address;
    }
};

class CSVReader {
private:
    std::string filename;

public:
    CSVReader(const std::string& filename)
        : filename(filename) {}

    std::map<std::string, Person> readData() {
        std::map<std::string, Person> people;
        std::ifstream file(filename);
        std::string line;

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::vector<std::string> tokens;
            std::string token;

            while (std::getline(iss, token, ',')) {
                tokens.push_back(token);
            }

            if (tokens.size() == 5) {
                const std::string& cpf = tokens[0];
                const std::string& firstName = tokens[1];
                const std::string& lastName = tokens[2];
                const std::string& birthDate = tokens[3];
                const std::string& address = tokens[4];

                people[cpf] = Person(cpf, firstName, lastName, birthDate, address);
            }
        }
        return people;
    }
};

// void printData(const std::map<std::string, Person>& people) {
//     for (const auto& pair : people) {
//         const std::string& cpf = pair.first;
//         const Person& person = pair.second;

//         std::cout << "CPF: " << cpf << std::endl;
//         std::cout << "Nome: " << person.getFirstName() << " " << person.getLastName() << std::endl;
//         std::cout << "Data de Nascimento: " << person.getBirthDate() << std::endl;
//         std::cout << "Endereço: " << person.getAddress() << std::endl;
//         std::cout << std::endl;
//     }
// }

#endif