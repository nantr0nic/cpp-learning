#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>
#include <exception>

using std::string, std::cout, std::cerr, std::vector;

enum class Genre
{
    undefined, fiction, nonfiction, periodical, biography, children
};

string printGenre(Genre gg)
{
    switch (gg)
    {
        case Genre::undefined: return "Undefined";
        case Genre::fiction: return "Fiction";
        case Genre::nonfiction: return "Nonfiction";
        case Genre::periodical: return "Periodical";
        case Genre::biography: return "Biography";
        case Genre::children: return "Children";
        default: return "null!";
    }
}

// Book class
class Book
{
    public:
        // Constructors
        Book() { };     // without parameters, use 'default' or 'null' values
        Book(string i, string t, string a, int c, Genre g);  // Books are available by default
        // Functions
        void check() { available = !available; }  // Function to check the book in/out
        bool validISBN();
        // Getters
        string getISBN() const { return ISBN; }
        string getTitle() const { return title; }
        string getAuthor() const { return author; }
        int getCopyright() const { return copyright; }
        string getGenre() const { return printGenre(genre); }
        bool getAvailable() const { return available; }

    private:
        string ISBN {"0-0-0-x"};
        string title {"Title"};
        string author {"Author"};
        int copyright {0000};
        Genre genre = Genre::undefined;
        bool available {true};  // Whether book is available to check out
};

Book::Book(string i, string t, string a, int c, Genre g)
    : ISBN{i}, title{t}, author{a}, copyright{c}, genre{g}
    { 
        if (!validISBN())
        {
            cerr << "The ISBN you entered: \"" << i << "\" is invalid!\n";
            throw std::runtime_error("Invalid ISBN.\n");
        }
    }

// checks if ISBN is valid (follows n-n-n-x format)
bool Book::validISBN()
{
    int section = 0;    // section of string (0, 1, 2, or 3)
    bool isNumber = false;   // is the char in first 3 sections a number

    for (char c : ISBN)
    {
        if (section < 3)
        {
            if (isdigit(c))
            {
                isNumber = true;
            }
            else if (c == '-' && isNumber)
            {
                section++;  // moving to next section
                isNumber =  false;  // reset isNumber for next section
            }
            else
            {
                return false;   // found a non-digit in the first 3 sections
            }
        }
        else if (section == 3)
        {
            if (isalnum(c) && c == ISBN.back())
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    return false;
}

// Function for checking out a book
void checking(Book& book)
{
    book.check();
}

// Function for bool to return 'yes' and 'no' instead of '1' and '0'
string boolToString(bool b)
{
    return b ? "Yes" : "No";
}

// Overload == operator to check whether ISBN numbers match for two books
bool operator==(const Book& book1, const Book& book2)
{
    return (book1.getISBN() == book2.getISBN()) ? true : false;
}

// Overload != operator to check whether ISBN numbers do NOT match for two books
bool operator!=(const Book& book1, const Book& book2)
{
    return !(book1.getISBN() == book2.getISBN());
}

std::ostream& operator<<(std::ostream& os, const Book& book)
{
    os << "Title: " << book.getTitle() << "\n";
    os << "Author: " << book.getAuthor() << "\n";
    os << "ISBN: " << book.getISBN() << "\n";
    os << "Genre: " << book.getGenre() << "\n";
    os << "Available: " << boolToString(book.getAvailable()) << "\n";
    return os;
}

// Patron class
class Patron
{
    public:
        Patron(string n, int c, int f);
        // Getters
        string getName() const { return name; }
        int getCardNum() const { return card_num; }
        int getFeesOwed() const { return fees_owed; }
        // Functions
        bool owesFee() const { return (getFeesOwed() != 0) ? true : false; }
        void setFee(int fee) { fees_owed = fee; }
    
    private:
        string name;
        int card_num {};
        int fees_owed {};
};

Patron::Patron(string n, int c, int f)
    : name{n}, card_num{c}, fees_owed{f}
    { }

class Library
{
    public:
        struct Transaction {
            Book book;
            Patron patron;
            string date;
        };

        void addBook(const Book& book) { books.push_back(book); }
        void addPatron(const Patron& patron) { patrons.push_back(patron); }
        void checkBook(Book& book, Patron& patron);     // write this function

    private:
        vector<Book> books;
        vector<Patron> patrons;
        vector<Transaction> transactions;
};

void Library::checkBook(Book& book, Patron& patron)
{
    // Write this function
}

int main()
{
    try
    {
        Book book1 {"54-11202-127-a", "The Grapes of Wrath", "John Steinbeck", 1938, Genre::fiction};
        Book book2 {"6-6-6-6", "Satanic Bible", "BLAH!", 666, Genre::nonfiction};
        cout << book1;
        cout << book2;
        cout << "Are book 1 and 2 the same? > " << boolToString(book1==book2) << "\n";
        return 0;
    }
    catch (const std::runtime_error& e)
    {
        cerr << "Runtime error: " << e.what() << "\n";
        return 1;
    }
    catch (const std::exception& e)
    {
        cerr << "Unexpected error: "<< e.what() << "\n";
        return 2;
    }
    catch (...)
    {
        cerr << "Unknown exception.\n";
        return 2;
    }
}
