#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>
#include <exception>
#include <chrono>

using std::string, std::cout, std::cerr, std::vector;

// Book Genres
enum class Genre
{
    undefined, fiction, nonfiction, periodical, biography, children
};

// Returns the genre of a book as a string
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

// Returns the current date and time as a string
//      in the format "2025-04-23 18:50:00"
string getCurrentDateTime(const char* format = "%Y-%m-%d")
{
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), format, std::localtime(&time_t_now));
    
    return string(buffer);
}

// Function for bool to return 'yes' and 'no' instead of '1' and '0'
string boolToString(bool b)
{
    return b ? "Yes" : "No";
}

//////////////////////////////
///////// Book class /////////
//////////////////////////////
// This creates "Book" objects for individual books in the Library
class Book
{
    public:
        // Constructors
        Book() { };     // without parameters, use 'default' or 'null' values
        Book(string i, string t, string a, int c, Genre g);  // Books are available by default
        // Functions
        void check() { available = !available; }  // Function to check the book in/out
        bool validISBN();   // Checks if ISBN follows correct format
        // Getters
        string getISBN() const { return ISBN; }
        string getTitle() const { return title; }
        string getAuthor() const { return author; }
        int getCopyright() const { return copyright; }
        string getGenre() const { return printGenre(genre); }
        bool getAvailable() const { return available; }

    private:
        string ISBN {"0-0-0-x"};    // Format: N-N-N-A (N is number, A is alpha-numeral)
        string title {"Title"};
        string author {"Author"};
        int copyright {0000};
        Genre genre = Genre::undefined;
        bool available {true};  // Whether book is available to check out
};

// Create books with ISBN, Title, and Author as strings
//      and copyright as int, Genre as enum class type
Book::Book(string i, string t, string a, int c, Genre g)
    : ISBN{i}, title{t}, author{a}, copyright{c}, genre{g}
    { 
        if (!validISBN())
        {
            cerr << "The ISBN you entered: \"" << i << "\" is invalid!\n";
            throw std::runtime_error("Invalid ISBN.\n");
        }
    }

// Checks if ISBN is valid (follows N-N-N-A format)
bool Book::validISBN()
{
    int section = 0;    // section of string (0, 1, 2, or 3)
    bool isNumber = false;   // is the char in first 3 sections a number
    // Loop through each character in the provided ISBN
    for (const char& c : ISBN)
    {
        // If in the first 3 sections (0, 1, and 2)...
        if (section < 3)
        {
            // Set flag to true if character is a digit
            if (isdigit(c))
            {
                isNumber = true;
            }
            // If character is '-' and isNumber is true, proceed to next section
            else if (c == '-' && isNumber)
            {
                section++;  // moving to next section
                isNumber =  false;  // reset isNumber for next section
            }
            // If character is not a digit then
            else
            {
                return false;   // found a non-digit in the first 3 sections
            }
        }
        // If in the last section, check if character is alphanumeral
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

// Function for checking in/out a book
// Don't use this... just use checkBook instead.
void checking(Book& book)
{
    book.check();
}

// Overload == operator to check whether ISBN numbers match for two books
bool operator==(const Book& book1, const Book& book2)
{
    return (book1.getISBN() == book2.getISBN()) ? true : false;
}

// Overload != operator to check whether ISBN numbers do NOT match for two books
// (requires the overloaded == operator)
bool operator!=(const Book& book1, const Book& book2)
{
    return !(book1.getISBN() == book2.getISBN());
}

// Overload << operator to print Book objects
std::ostream& operator<<(std::ostream& os, const Book& book)
{
    os << "Title: " << book.getTitle() << "\n";
    os << "Author: " << book.getAuthor() << "\n";
    os << "ISBN: " << book.getISBN() << "\n";
    os << "Genre: " << book.getGenre() << "\n";
    os << "Available: " << boolToString(book.getAvailable()) << "\n";
    return os;
}

////////////////////////////////
///////// Patron class /////////
////////////////////////////////
// This creates individual users for the Library
class Patron
{
    public:
        Patron(string n, int c);
        // Functions
        // Returns bool for whether a user owes fees
        bool owesFee() const { return (getFeesOwed() != 0) ? true : false; }
        void setFee(int fee) { fees_owed = fee; }
        // Getters
        string getName() const { return name; }
        int getCardNum() const { return card_num; }
        double getFeesOwed() const { return fees_owed; }

    private:
        string name;
        int card_num {};    // 6 digit number (000001)
        double fees_owed {};   // will be 0.0 format
};

// Include name and card number. Fees owed will default to $0
// because idk how'd someone would owe fees before having an account lol
Patron::Patron(string n, int c)
    : name{n}, card_num{c}
    { }

// Overload == operator to compare patron card numbers
// (People with the same name will have different card numbers)
bool operator==(const Patron& patron1, const Patron& patron2)
{
    return (patron1.getCardNum() == patron2.getCardNum()) ? true : false;
}

// Overload << operator to output Patron info (just name and card #)
std::ostream& operator<<(std::ostream& os, const Patron& p)
{
    os << "Name: " << p.getName() << "\n";
    os << "Card number: " << p.getCardNum() << "\n";
    return os;
}

class Library
{
    public:
        // Transactions = checking book in / out
        struct Transaction {
            Transaction(Book& b, Patron& p, const string& d); 
            Book& book;
            Patron& patron;
            string date;
        };
        // Functions
        void addBook(const Book& book) { books.push_back(book); } // adds Book object to Library
        void addPatron(const Patron& patron) { patrons.push_back(patron); } // adds Patron to Library
        void checkBook(Book& book, Patron& patron);     // Check book in/out (creates Transaction)
        vector<string> checkOwedFees();     // Check if user (card #) owes fees
        void listTransaction();     // Prints transactions vector

    private:
        vector<Book> books;
        vector<Patron> patrons;
        vector<Transaction> transactions;
};

Library::Transaction::Transaction(Book& b, Patron& p, const string& d)
    : book{b}, patron{p}, date{d}
    { }

// Overload << operator to print Transaction objects / Transaction vector
std::ostream& operator<<(std::ostream& os, const Library::Transaction& t)
{
    os << "Book: " << t.book << "\n";
    os << "User: " << t.patron << "\n";
    os << "Date: " << t.date << "\n";
    return os;
}

// Lists Transactions record in Transactions vector
void Library::listTransaction()
{
    if (transactions.empty())
    {
        cout << "Transactions list is empty!\n";
    }
    int index = 1;
    for (const auto& entry : transactions)
    {
        cout << "<<< #" << index << " transaction information >>>\n\n";
        cout << entry.book << "\n";
        cout << entry.patron << "\n";
        cout << "Date of transaction: " << entry.date << "\n";
        ++index;
    }
}

// Function to check Books in/out and create Transaction if successful
void Library::checkBook(Book& book, Patron& patron)
{
    // Check if the user is in the library's system.
    // This will simply check if the user exists.
    bool user_exists = false;
    // Loop through users in the "patrons" vector member of Library
    for (const auto& user : patrons)
    {
        // Change flag if the patron from the function parameter is found in patrons vector
        if (patron == user)
        {
            user_exists = true;
            break; // break out if user is found in the system
        }
    }
    // If user_exists is still false then they're not in the system.
    if (!user_exists)
    {
        throw std::runtime_error("User doesn't exist in the library system!\n");
    }

    // Now check to make sure the book is in the library (and available?)
    bool book_exists = false;
    for (const auto& title : books)
    {
        if (book == title)
        {
            book_exists = true;
            break;
        }
    }
    if (!book_exists)
    {
        throw std::runtime_error("That book doesn't exist in the library.\n (Or it's been checked out already!)\n");
    }

    // Now check if the user owes fees.
    if (patron.owesFee())
    {
        throw std::runtime_error("This user owes fees and cannot check out books.\n");
    }

    // Alright! The user and book both exist, the book is available, AND the user doesn't
    // owe fees so let's create that transaction!
    // Date stamp will look like: 2025-04-23 18:50:00
    string date_time = getCurrentDateTime("%Y-%m-%d %H:%M:%S");
    // Flip the book's availability
    book.check(); // <-- Manipulates Book object but NOT the Books in Library
    /*
    For simplicity, if the book is checked out let's simply remove it from the books vector,
        if it is being checked back in then we'll (back) to the vector.
    This is NOT elegant and it won't allow us to tell the User if the book
        doesn't exist at all or if its currently checked out...
    But for time's sake and for staying within the confines of the concepts covered
        in chapters 7 and 8 we'll go with this.
    An additional consideration is in an ideal world (>_>) the function of checking a book IN
        and OUT would be separate functions. But I'm following Bjarne's exercise instructions.
    */
    if (book.getAvailable())
    {
        auto it = std::find(books.begin(), books.end(), book);
        if (it != books.end())
        {
            books.erase(it);
        }
    }
    else if (!book.getAvailable())
    {
        books.push_back(book);
    }
    Transaction t {book, patron, date_time};
    transactions.push_back(t);
    cout << "Transaction successful!\n";
}

// Return a vector of user's names who owe fees
vector<string> Library::checkOwedFees()
{
    vector<string> users_who_owe;
    for (const auto& patron : patrons)
    {
        if (patron.owesFee())
        {
            users_who_owe.push_back(patron.getName());
        }
    }
    if (users_who_owe.empty())
    {
        cout << "Nobody owes any fees! Fantastic!\n";
        return users_who_owe;
    }
    return users_who_owe;
}

int main()
{
    try
    {
        // TEST 1: Book class constructors and basic functionality
        cout << "TEST 1: Testing Book class basics\n";
        cout << "-----------------------------------\n";
        
        // Test default constructor
        Book defaultBook;
        cout << "Default Book:\n" << defaultBook << "\n";
        
        // Test parameterized constructor with valid ISBN
        Book book1{"54-11202-127-a", "The Grapes of Wrath", "John Steinbeck", 1938, Genre::fiction};
        cout << "Book 1:\n" << book1 << "\n";
        
        // Test book availability and check-in/check-out functionality
        cout << "Book 1 initially available: " << boolToString(book1.getAvailable()) << "\n";
        checking(book1); // Check out the book
        cout << "Book 1 after checking: " << boolToString(book1.getAvailable()) << "\n";
        checking(book1); // Check in the book
        cout << "Book 1 after checking again: " << boolToString(book1.getAvailable()) << "\n";
        
        // Test book comparison operators
        Book book2{"12-34567-890-x", "Moby Dick", "Herman Melville", 1851, Genre::fiction};
        Book book3{"54-11202-127-a", "The Grapes of Wrath (Reprint)", "John Steinbeck", 2002, Genre::fiction};
        
        cout << "Book 1 == Book 2: " << boolToString(book1 == book2) << "\n"; // Should be false
        cout << "Book 1 != Book 2: " << boolToString(book1 != book2) << "\n"; // Should be true
        cout << "Book 1 == Book 3: " << boolToString(book1 == book3) << "\n"; // Should be true (same ISBN)
        
        // TEST 2: Patron class functionality
        cout << "\nTEST 2: Testing Patron class\n";
        cout << "-----------------------------------\n";
        
        Patron patron1{"John Doe", 123456};
        Patron patron2{"Jane Smith", 654321};
        
        cout << "Patron 1 Name: " << patron1.getName() << "\n";
        cout << "Patron 1 Card Number: " << patron1.getCardNum() << "\n";
        cout << "Patron 1 Fees Owed: " << patron1.getFeesOwed() << "\n";
        cout << "Patron 1 Owes Fees: " << boolToString(patron1.owesFee()) << "\n";
        
        // Test setting fees
        patron1.setFee(10);
        cout << "After setting fee, Patron 1 Fees Owed: " << patron1.getFeesOwed() << "\n";
        cout << "After setting fee, Patron 1 Owes Fees: " << boolToString(patron1.owesFee()) << "\n";
        
        // Test patron comparison - now using card numbers instead of names
        Patron patron3{"John Doe", 123456}; // Same name AND same card number
        Patron patron4{"John Doe", 111111}; // Same name but different card
        cout << "Patron 1 == Patron 2: " << boolToString(patron1 == patron2) << "\n"; // Should be false (different card numbers)
        cout << "Patron 1 == Patron 3: " << boolToString(patron1 == patron3) << "\n"; // Should be true (same card number)
        cout << "Patron 1 == Patron 4: " << boolToString(patron1 == patron4) << "\n"; // Should be false (different card numbers)
        
        // TEST 3: Library class functionality
        cout << "\nTEST 3: Testing Library class\n";
        cout << "-----------------------------------\n";
        
        Library library;
        
        // Add books to library
        library.addBook(book1);
        library.addBook(book2);
        cout << "Added books to library\n";
        
        // Add patrons to library
        library.addPatron(patron1);
        library.addPatron(patron2);
        cout << "Added patrons to library\n";
        
        // Test fee checking
        vector<string> feeOwers = library.checkOwedFees();
        cout << "Number of patrons owing fees: " << feeOwers.size() << "\n";
        if (!feeOwers.empty()) {
            cout << "Patrons owing fees:\n";
            for (const auto& name : feeOwers) {
                cout << "- " << name << "\n";
            }
        }
        
        // Reset patron1's fee for checkout test
        patron1.setFee(0);
        
        // Test book checkout
        cout << "Checking out book to patron...\n";
        library.checkBook(book1, patron2); // This should work
        cout << "Checkout successful!\n";
        
        // NEW TEST: Test listTransaction() function
        cout << "\nTEST 3.1: Testing listTransaction() function\n";
        cout << "-----------------------------------\n";
        cout << "Listing all transactions:\n";
        library.listTransaction(); // Should show the transaction we just created
        
        // NEW TEST: Multiple transactions
        cout << "\nTEST 3.2: Testing multiple transactions\n";
        cout << "-----------------------------------\n";
        
        // Create a new book and patron for additional transaction
        Book book4{"98-76543-210-x", "The Great Gatsby", "F. Scott Fitzgerald", 1925, Genre::fiction};
        Patron patron5{"Alice Johnson", 789012};
        
        // Add them to the library
        library.addBook(book4);
        library.addPatron(patron5);
        cout << "Added another book and patron to library\n";
        
        // Create another transaction
        cout << "Creating another transaction...\n";
        library.checkBook(book4, patron5);
        cout << "Second checkout successful!\n";
        
        // List all transactions
        cout << "Listing all transactions after second checkout:\n";
        library.listTransaction(); // Should show both transactions
        
        // TEST 4: Error handling tests (commented out by default)
        cout << "\nTEST 4: Error handling tests (uncomment to test)\n";
        cout << "-----------------------------------\n";
        
        // Uncomment these to test error handling
        
        /*
        // Test invalid ISBN
        cout << "Testing invalid ISBN:\n";
        Book invalidBook{"invalid-isbn", "Bad Book", "No Author", 2000, Genre::undefined};
        */
        // ^^ Works!
        /*
        // Test checking out to non-existent patron
        cout << "Testing non-existent patron checkout:\n";
        Patron nonExistentPatron{"Nobody", 999999};
        library.checkBook(book1, nonExistentPatron);
        */
        // ^^ Works!
        /*
        // Test checking out non-existent book
        cout << "Testing non-existent book checkout:\n";
        Book nonExistentBook{"9-9-9-x", "Imaginary Book", "Imaginary Author", 2023, Genre::fiction};
        library.checkBook(nonExistentBook, patron2);
        */
        // ^^ Works!
        /*
        // Test checking out when owing fees
        cout << "Testing checkout with fees owed:\n";
        patron2.setFee(5);
        library.checkBook(book2, patron2);
        */
        // ^^ Works!
        
        /*
        // Test checking out already checked out book
        cout << "Testing already checked out book:\n";
        // checking(book1); // Check out the book first
        library.checkBook(book1, patron2);
        */
        // ^^ Doesn't work :(
        
        // NEW TEST: Transaction after checkout
        cout << "\nTEST 4.1: Transaction verification after checkout\n";
        cout << "-----------------------------------\n";
        
        /*
        // Uncomment to test checking out a book and then verifying it's unavailable
        Book book5{"11-22333-444-x", "To Kill a Mockingbird", "Harper Lee", 1960, Genre::fiction};
        library.addBook(book5);
        cout << "Book 5 initially available: " << boolToString(book5.getAvailable()) << "\n";
        library.checkBook(book5, patron5);
        cout << "Book 5 after checkout through library: " << boolToString(book5.getAvailable()) << "\n";
        // This should throw an error because book5 is already checked out
        // library.checkBook(book5, patron2);
        */
        // ^^ Works!
        
        cout << "\nAll tests completed successfully!\n";
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