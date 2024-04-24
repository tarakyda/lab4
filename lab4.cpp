#include <iostream>
#include <fstream>
#include <deque>
#include <list>
#include <algorithm>

class Book {
private:
    std::string authorName;
    std::string title;
    std::string publisher;
    int publicationYear;
    int pageCount;

public:
    // Конструкторы
    Book() : publicationYear(0), pageCount(0) {}
    Book(const std::string& author, const std::string& title, const std::string& publisher, int year, int pages)
        : authorName(author), title(title), publisher(publisher), publicationYear(year), pageCount(pages) {}

    // Перегрузка операции вставки в поток <<
    friend std::ostream& operator<<(std::ostream& os, const Book& book) {
        os << "Author: " << book.authorName << ", Title: " << book.title << ", Publisher: " << book.publisher
           << ", Year: " << book.publicationYear << ", Pages: " << book.pageCount;
        return os;
    }

    // Перегрузка оператора сравнения для сортировки по ФИО автора
    bool operator<(const Book& other) const {
        return authorName < other.authorName;
    }
};

int main() {
    // Чтение данных из файла
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open input file!" << std::endl;
        return 1;
    }

    // Создание исходного контейнера deque
    std::deque<Book> originalDeque;
    std::string author, title, publisher;
    int year, pages;

    while (inputFile >> author >> title >> publisher >> year >> pages) {
        originalDeque.emplace_back(author, title, publisher, year, pages);
    }
    inputFile.close();

    // Сортировка исходного контейнера по ФИО автора
    std::sort(originalDeque.begin(), originalDeque.end());

    // Копирование исходного контейнера deque в контейнер list
    std::list<Book> copiedList(originalDeque.begin(), originalDeque.end());

    // Вывод в выходной файл
    std::ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open output file!" << std::endl;
        return 1;
    }

    // Вывод исходного контейнера deque
    outputFile << "Original Container (deque):\n";
    for (const auto& book : originalDeque) {
        outputFile << book << std::endl;
    }
    outputFile << std::endl;

    // Вывод исходного контейнера после сортировки
    outputFile << "Sorted Container (deque):\n";
    for (const auto& book : originalDeque) {
        outputFile << book << std::endl;
    }
    outputFile << std::endl;

    // Вывод скопированного контейнера list
    outputFile << "Copied Container (list):\n";
    for (const auto& book : copiedList) {
        outputFile << book << std::endl;
    }

    outputFile.close();
    return 0;
}
