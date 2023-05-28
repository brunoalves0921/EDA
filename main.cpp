#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "RedBlackTree.cpp"
#include "readerCsv.cpp"

/**
 * joãn
 * joão victor
 * joão pedro
 * joão paulo
 * joãp
*/

void Menu() {
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "Escolha uma opção:" << std::endl;
    std::cout << "1 - Buscar por CPF" << std::endl;
    std::cout << "2 - Buscar por Nome" << std::endl;
    std::cout << "3 - Buscar por Data" << std::endl;
    std::cout << "4 - Sair" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
}

std::string transformDate(const std::string& date) {
    // 11/10/1972
    // 1972 10 11
    // 1972 09 30

    // Encontra as posições das barras no formato da data
    size_t firstSlashPos = date.find('/');
    size_t lastSlashPos = date.rfind('/');

    // Obtém os substrings para o dia, mês e ano
    std::string month = date.substr(0, firstSlashPos);
    std::string day = date.substr(firstSlashPos + 1, lastSlashPos - firstSlashPos - 1);
    std::string year = date.substr(lastSlashPos + 1);
    if (month.size() == 1) month = "0" + month;
    if (day.size() == 1) day = "0" + day;

    // Concatena os elementos invertidos para formar a nova data
    std::string transformedDate = year + month + day;

    return transformedDate;
}

std::string getNextName(const std::string& name) {
    // joão
    // joãp

    // josé
    // josê
    // josê < josé fulano de tao > josé
    std::string result = name;

    if (!result.empty()) {
        // Encontra o índice do último byte do último caractere
        size_t lastIndex = result.size() - 1;
        while (lastIndex > 0 && (result[lastIndex] & 0xC0) == 0x80) {
            --lastIndex;
        }

        // Obtém o último caractere
        std::string lastCharacter = result.substr(lastIndex);

        // Calcula o sucessor do último caractere
        for (size_t i = lastCharacter.size() - 1; i >= 0; --i) {
            if (lastCharacter[i] < 0x7F) {
                ++lastCharacter[i];
                break;
            }
        }

        // Substitui o último caractere pelo seu sucessor
        result.replace(lastIndex, lastCharacter.size(), lastCharacter);
    }

    return result;
}

int main() {
    // Criação da instância da árvore com chave CPF
    RedBlackTree<std::string, const Person*> cpfTree;

    // Criação da instância da árvore com chave Nome
    RedBlackTree<std::string, const Person*> nameTree;

    // Criação da instância da árvore com chave Data
    RedBlackTree<std::string, const Person*> dateTree;

    std::string filename = "data.csv";
    CSVReader reader(filename);
    std::map<std::string, Person> people = reader.readData();
    // std::vector<Value> result;

    // Inserção dos dados nas árvores
    for (const auto& pair : people) {
        const std::string& cpf = pair.first;
        const Person& person = pair.second;

        cpfTree.add(cpf, &person);
        nameTree.add(person.getFirstName() + " " + person.getLastName(), &person);
        dateTree.add(transformDate(person.getBirthDate()), &person);
    }
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "Dados carregados com sucesso!" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    int option;
    std::string cpfToSearch;
    std::string nameToSearch;
    std::string dateToSearch1;
    std::string dateToSearch2;
    while (true) {
        Menu();
        std::cin >> option;
        if (option == 1) {
            std::cout << "Digite o CPF: ";
            std::cin >> cpfToSearch;
            try {
                const Person *person = cpfTree.get(cpfToSearch);
                std::cout << "---------------------------------------------" << std::endl;
                std::cout << "Dados encontrados usando CPF como chave:" << std::endl;
                std::cout << "CPF: " << person->getCPF() << std::endl;
                std::cout << "Nome: " << person->getFirstName() << " " << person->getLastName() << std::endl;
                std::cout << "Data de Nascimento: " << person->getBirthDate() << std::endl;
                std::cout << "Endereço: " << person->getAddress() << std::endl;
                std::cout << std::endl;
                std::cout << "---------------------------------------------" << std::endl;
            } catch (std::invalid_argument& e) {
                std::cout << "---------------------------------------------" << std::endl;
                std::cout << "Dados não encontrados usando CPF como chave." << std::endl;
                std::cout << "---------------------------------------------" << std::endl;
            }
        } else if (option == 2) {
            std::cout << "Digite o nome da pessoa: ";
            std::cin >> nameToSearch;
            std::vector<const Person*> persons = nameTree.getByRange(nameToSearch, getNextName(nameToSearch));
            if (persons.empty()) {
                std::cout << "---------------------------------------------" << std::endl;
                std::cout << "Não foi encontrando nenhum usuário com o nome " << nameToSearch << " como chave." << std::endl;
            }
            else {
                std::cout << "---------------------------------------------" << std::endl;
                std::cout << "Usuários encontrados usando o nome " << nameToSearch << " como chave:" << std::endl;
                for (auto person: persons) {
                    std::cout << "---------------------------------------------" << std::endl;
                    std::cout << "- CPF: " << person->getCPF() << std::endl;
                    std::cout << "- Nome: " << person->getFirstName() << " " << person->getLastName() << std::endl;
                    std::cout << "- Data de Nascimento: " << person->getBirthDate() << std::endl;
                    std::cout << "- Endereço: " << person->getAddress() << std::endl;
                    std::cout << std::endl;
                }
            }
        } else if (option == 3) {
            std::cout << "Digite a data de nascimento inicial: ";
            std::cin >> dateToSearch1;
            std::cout << "Digite a data de nascimento final: ";
            std::cin >> dateToSearch2;
            std::vector<const Person*> persons = dateTree.getByRange(transformDate(dateToSearch1), transformDate(dateToSearch2));
            if (persons.empty()) {
                std::cout << "---------------------------------------------" << std::endl;
                std::cout << "Não foi encontrando nenhum usuário com a data de nascimento entre " << dateToSearch1 << " e " << dateToSearch2 << " como chave." << std::endl;
            }
            else {
                std::cout << "Usuários encontrados usando Data como chave de ("<< dateToSearch1 <<") até (" << dateToSearch2 << ":" << std::endl;
                for (auto person: persons) {
                    std::cout << "---------------------------------------------" << std::endl;
                    std::cout << "- CPF: " << person->getCPF() << std::endl;
                    std::cout << "- Nome: " << person->getFirstName() << " " << person->getLastName() << std::endl;
                    std::cout << "- Data de Nascimento: " << person->getBirthDate() << std::endl;
                    std::cout << "- Endereço: " << person->getAddress() << std::endl;
                    std::cout << std::endl;
                }
            }
        } else if (option == 4) {
            break;
        }
    }
}
