#include <iostream>
#include <string>
#include <stdexcept>
class Book {
    std::string title;
    int copies;
    std::string author;
public:
    Book() : Book("Untitled", 0, "Unknown") {}
    explicit Book(const std::string& t) : Book(t, 1, "Unknown") {}
    Book(const std::string& t, int c) : Book(t, c, "Unknown") {}
    Book(const std::string& t, int c, const std::string& a)
        : title(t), copies(validate(c)), author(a) {}
    static int validate(int c) {
        if (c < 0) throw std::invalid_argument("number of copies cannot be negative");
        return c;
    }
    void print() const {
        std::cout << "Title: " << title << ", Copies: " << copies
                  << ", Author: " << author << '\n';
    }
};
int main() {
    Book empty;
    Book donated("The Alchemist");
    Book full("Clean Code", 4, "Robert C. Martin");
    empty.print(); donated.print(); full.print();
    try { Book invalid("Invalid Book", -2, "Unknown"); invalid.print(); }
    catch (const std::invalid_argument& e) { std::cout << "Rejected: " << e.what() << '\n'; }
}