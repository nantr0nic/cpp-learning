/*========================================================================*
*                         Exercise 12 (and 13...)                         *
*                                                                         *
* [12] Define a File_handle class with a constructor that takes a string  *
* argument (the file name), opens the file in the constructor and closes  *
*                          it in the destructor.                          *
* [13] Write a Tracer class where its constructor prints a string and its *
* destructor prints a string. Give the strings as constructor arguments.  *
*  Use it to see where RAII management objects will do their job (i.e.,   *
*    experiment with Tracers as local objects, member objects, global     *
*  objects, objects allocated by new, etc.). Then add a copy constructor  *
*  and a copy assignment so that you can use Tracer objects to see when   *
*                            copying is done.                             *
*                                                                         *
*I implemented the mechanics of "Tracer" in quite a few classes, including*
*   this one, because it is helpful to know when different parts of the   *
*"essential operations" are being called. Consequently, I won't implement *
*  them separately to save time and move on. So many more books to read!  *
 *========================================================================*/

import std;

class File_handle
{
private:
    std::string file_name{};
    std::ifstream ifs;

public:
    File_handle() : file_name{""}, ifs{} {}
    File_handle(const std::string& file)
        : file_name{ file }
        , ifs{ file }
    {
        if (!ifs)
        {
            throw std::invalid_argument{"Failed to open: " + file};
        }
    }

    File_handle(const File_handle& orig)
        : file_name{ orig.file_name }
    {
        if (orig.ifs.is_open())
        {
            open_file(orig.file_name);
        }
        std::println("[!] Copy constructor called.");
    }
    File_handle& operator=(const File_handle& orig)
    {
        if (this == &orig) 
        {
            return *this;
        }
        
        if (ifs.is_open())
        {
            close_file();
        }
        
        file_name = orig.file_name;
        
        if (orig.ifs.is_open()) 
        {
            open_file(file_name);
        }
        
        return *this;
    }
    
    File_handle(File_handle&& orig)
        : file_name{ std::move(orig.file_name) }
        , ifs{ std::move(orig.ifs) }
    {
        orig.file_name.clear();
        std::println("Move constructor called. \"{}\" re-assigned", file_name);
    }

    File_handle& operator=(File_handle&& orig)
    {
        if (this != &orig)
        {
            std::println("[!] Move assignment operator called");
            if (ifs.is_open())
            {
                std::println("Closing {} before move operations.", file_name);
                close_file();
            }

            file_name = std::move(orig.file_name);
            ifs = std::move(orig.ifs);

            orig.file_name.clear();

            std::println("{} has been moved!", file_name);
        }
        return *this;
    }
    
    ~File_handle() 
    {
        if (ifs.is_open())
        {
            ifs.close();
            std::println("Destructor called: {} was open and is now closed!", file_name);
        }
        else {
            std::println("No file was open but destructor called.");
        }
    }

public:
    void open_file(const std::string& file) {

        if (ifs.is_open()) {
            std::println("File already open: {}", file_name);
            return;
        }

        file_name = file;
        try {
            ifs.open(file_name);
            if (ifs)
            {
                std::println("{} opened!", file_name);
            }
            if (!ifs)
            {
                std::println("[open] {} didn't open. Does it exist?", file_name);
                file_name = "";
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error: " << e.what();
        }
        
    }

    void print_file() {
        if (file_name.empty())
        {
            std::println("[print] No file provided.");
            return;
        }

        if (!ifs.is_open())
        {
            std::println("[print] No file is open.");
            return;
        }

        // Reset to beginning of file
        ifs.clear();  // Clear any error flags
        ifs.seekg(0, std::ios::beg);

        std::string line;
        int line_count{ 0 };
        while (std::getline(ifs, line))
        {
            ++line_count;
            std::println("{}: {}", line_count, line);
        }
    }

    void close_file() {
        if (ifs.is_open())
        {
            ifs.close();
            std::println("File '{}' closed!", file_name);
            file_name = "";
        }
        else if (!ifs.is_open() || file_name == "")
        {
            std::println("[close] No file is open or specified.");
        }
    }

    bool is_open() const 
    {
        return ifs.is_open();
    }
    
    const std::string& get_filename() const 
    {
        return file_name;
    }

};

// Tests for move semantics
void test_move_constructor();
void test_move_assignment();
void test_move_assignment_active_target();


int main()
{
    File_handle file_hand;

    std::println("Opening first file.");
    file_hand.open_file("test_file.txt");
    file_hand.print_file();

    std::println("\nCopy constructing file_hand2 on an open file");
    File_handle file_hand2{ file_hand };
    file_hand2.print_file();
    file_hand2.close_file();

    std::println("\nCopy constructing file_hand3 on an empty File_handle");
    File_handle file_hand3{ file_hand2 };
    file_hand3.print_file();
    file_hand3.close_file();

    std::println("\nCopy assigning file_hand3 to file_hand.");
    file_hand3 = file_hand;
    file_hand3.print_file();

    std::println("\nTrying to open a non-existent file on an already used File_handle");
    file_hand3.open_file("not_a_real_file!");
    file_hand3.close_file();

    std::println("\nTrying to open a (new) non-existent file on unused File_handle");
    file_hand3.open_file("not_a_real_file!");
    file_hand3.print_file();
    file_hand3.close_file();

    // Destructor closes file_hand!


    // using the AI-generated tests for move semantics
    test_move_constructor();
    test_move_assignment();
    test_move_assignment_active_target();

    return 0;
}


// Disclaimer: the bottom 3 tests were written by AI.
// They're written to test move semantics.

void test_move_constructor()
{
    std::println("=== Testing Move Constructor ===");
    
    // Create original file handle
    File_handle original{"test_file.txt"};
    std::println("Original created - file open: {}", original.is_open());
    
    // Move construct new handle
    File_handle moved{std::move(original)};
    
    std::println("After move construction:");
    std::println("  Original file open: {}", original.is_open());  // Should be false
    std::println("  Moved file open: {}", moved.is_open());        // Should be true
    std::println("  Original filename: '{}'", original.get_filename());  // Should be empty
    std::println("  Moved filename: '{}'", moved.get_filename());  // Should be "test_file.txt"
    
    // Verify moved object works
    moved.print_file();
}

void test_move_assignment()
{
    std::println("\n=== Testing Move Assignment ===");
    
    // Create source and target handles
    File_handle source{"test_file.txt"};
    File_handle target{};  // Empty handle
    
    std::println("Before move assignment:");
    std::println("  Source file open: {}", source.is_open());
    std::println("  Target file open: {}", target.is_open());
    
    // Move assign
    target = std::move(source);
    
    std::println("After move assignment:");
    std::println("  Source file open: {}", source.is_open());     // Should be false
    std::println("  Target file open: {}", target.is_open());     // Should be true
    std::println("  Source filename: '{}'", source.get_filename()); // Should be empty
    std::println("  Target filename: '{}'", target.get_filename()); // Should be "test_file.txt"
    
    // Verify target works
    target.print_file();
}

void test_move_assignment_active_target()
{
    std::println("\n=== Testing Move Assignment (Active Target) ===");
    
    // Create source file handle
    File_handle source{"test_file.txt"};
    std::println("Source created - filename: '{}'", source.get_filename());
    
    // Create target with a DIFFERENT active file
    File_handle target{};
    target.open_file("another_file.txt");  // Now target has an active file
    
    std::println("Before move assignment:");
    std::println("  Source filename: '{}'", source.get_filename());
    std::println("  Target filename: '{}'", target.get_filename());
    std::println("  Both files should be open");
    
    // Move assign - this should close target's current file first
    target = std::move(source);
    
    std::println("After move assignment:");
    std::println("  Source filename: '{}'", source.get_filename()); // Should be empty
    std::println("  Target filename: '{}'", target.get_filename()); // Should be "test_file.txt"
    
    // Verify target works with the moved file
    std::println("Testing moved target:");
    target.print_file();
}