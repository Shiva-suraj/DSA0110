#include <string>
struct Book { std::string title; Book(const std::string& t):title(t){} };
int main(){ Book shelf[3]; } // Intentionally fails: Book has no default constructor.
