#include <stdexcept>
#include <vector>
#include <print>
#include <iostream>

class Matrix
{
public:
    Matrix(int r, int c);

    Matrix(const Matrix& orig);             // Copy constructor
    Matrix& operator=(const Matrix& orig);  // Copy assignment
    Matrix(Matrix&& m);                     // Move constructor
    Matrix& operator=(Matrix&& m);          // Move assignment
    // Destructor isn't necessary because vector handles itself

    // Getters
    int get_rows() const { return rows; }
    int get_cols() const { return cols; }
    size_t get_size() const { return data.size(); }
    const double& get_index(size_t i) const { return data[i]; }

public:
    // Overloaded operators
    double& operator[](int r, int c) {
        if (r >= rows || c >= cols || r < 0 || c < 0) {
            throw std::invalid_argument("Not a valid index!\n");
        } 
        return data[static_cast<size_t>(r * cols + c)]; 
    }

    const double& operator[](int r, int c) const {
        if (r >= rows || c >= cols || r < 0 || c < 0) {
            throw std::invalid_argument("Not a valid index!\n");
        } 
        return data[static_cast<size_t>(r * cols + c)]; 
    }

    void operator+=(double i) {
        for (double& d : data)
            d += i;
    }
    
    void operator-=(double i) {
        for (double& d : data)
            d -= i;
    }

    void operator*=(double i) {
        for (double& d : data)
            d *= i;
    }

    void operator/=(double i) {
        if (i == 0)
            throw std::invalid_argument("Can't divide by zero!\n");
        for (double& d : data)
            d /= i;
    }

    // Traversal
    auto begin() { return data.begin(); }
    auto end() { return data.end(); }
    auto begin() const { return data.begin(); }
    auto end() const { return data.end(); }

public:
    // Row/Column extractors
    std::vector<double> row(int r) const {
        if (r < 0 || r >= rows)
            throw std::invalid_argument("Row is out of bounds!\n");

        std::vector<double> temp;
        temp.reserve(static_cast<size_t>(cols));

        for (int j = 0; j < cols; ++j)
            temp.push_back(data[static_cast<size_t>(r * cols + j)]);
        
        return temp;
    }

    std::vector<double> column(int c) const {
        if (c < 0 || c >= cols)
            throw std::invalid_argument("Column is out of bounds!\n");

        std::vector<double> temp;
        temp.reserve(static_cast<size_t>(rows));

        for (int i = 0; i < rows; ++i)
            temp.push_back(data[static_cast<size_t>(i * cols + c)]);

        return temp;
    }

private:
    // Calculate data size and validate r and c
    static size_t calc_size(int r, int c) {
        if (r <= 0 || c <= 0) {
            throw std::invalid_argument("Matrix dimensions must be positive!\n");
        }
        return static_cast<size_t>(r * c);
    }

private:
    std::vector<double> data;
    int rows;
    int cols;
};



bool operator==(const Matrix& lhs, const Matrix& rhs)
{
    // Check that the Matrices have the same dimensions (matching r and c)
    if (lhs.get_cols() != rhs.get_cols() || lhs.get_rows() != rhs.get_rows())
    {
        return false;
    }

    // If they have the same dimensions, then each data vector is same size
    // and we can check their respective elements
    for (size_t i = 0; i < lhs.get_size(); ++i)
    {
        if (lhs.get_index(i) != rhs.get_index(i))
            return false;
    }

    // Failing to return false up to here means both matrices have same dimensions
    // and each element is the same as well, thus they're identical
    return true;
}

bool operator!=(const Matrix& lhs, const Matrix& rhs)
{
    return !(lhs == rhs);
}

bool operator<(const Matrix& lhs, const Matrix& rhs)
{
    // I think it makes more sense to compare matrices' values with same
    // dimensions -- so return "invalid argument" for different sized m's
    if (lhs.get_cols() != rhs.get_cols() || lhs.get_rows() != rhs.get_rows())
        throw std::invalid_argument("Matrices have same dimensions to be compared!\n");

    /*
     * I don't know what makes most sense to compare between matrices,
     * but after (just a little) consideration what makes sense to me
     * is comparing the number of elements that are greater rather than
     * comparing the sum of all elements in each matrix. If you want to
     * compare the former, it would be simple to add the value of the 
     * elements in lhs / rhs and compare them.
     */

    size_t greater_num = 0;   
    size_t half_of_elements = (lhs.get_size() / 2);

    // Check corresponding elements e.g. lhs[2,3] & rhs[2,3]
    for (size_t i = 0; i < lhs.get_size(); ++i)
    {
        if (lhs.get_index(i) < rhs.get_index(i))
            ++greater_num;
    }

    return greater_num > half_of_elements;
}

bool operator>(const Matrix& lhs, const Matrix& rhs)
{
    return rhs < lhs;
}

bool operator<=(const Matrix& lhs, const Matrix& rhs)
{
    if (lhs.get_cols() != rhs.get_cols() || lhs.get_rows() != rhs.get_rows())
        throw std::invalid_argument("Matrices must have same dimensions to be compared!\n");

    size_t greater_num = 0;   
    size_t half_of_elements = (lhs.get_size() / 2);

    for (size_t i = 0; i < lhs.get_size(); ++i)
    {
        if (lhs.get_index(i) < rhs.get_index(i))
            ++greater_num;
    }

    return greater_num >= half_of_elements;
}

bool operator>=(const Matrix& lhs, const Matrix& rhs)
{
    return rhs <= lhs;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
    os << "Matrix (" << m.get_rows() << "x" << m.get_cols() << "):\n";
    for (int i = 0; i < m.get_rows(); ++i)
    {
        for (int j = 0; j < m.get_cols(); ++j)
        {
            os << "[" << i << "," << j << "]" << " = " << m[i,j] << "\n";
        }
    }
    return os;
}

std::istream& operator>>(std::istream& is, Matrix& m)
// A basic implementation strictly for a user to enter (using std::cin)
// values into a matrix of a given size
// the error checking isn't good (come back to it)
{
    double input = 0;

    for (int i = 0; i < m.get_rows(); ++i)
    {
        for (int j = 0; j < m.get_cols(); ++j)
        {
            std::cout << "[" << i << "," << j << "]" << "= ";
            while (!(is >> input))
            {
                is.clear();

                char ch;
                while (is.get(ch) && ch != '\n') 
                {
                    // Keep reading and discarding characters
                }

                std::cout << "Invalid input! Please enter a valid number.\n";
                std::cout << "[" << i << "," << j << "]" << "= ";
            }
            m[i,j] = input;
        }
    }

    return is;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
    // First, check they have the same dimensions
    if (lhs.get_cols() != rhs.get_cols() || lhs.get_rows() != rhs.get_rows())
    {
        throw std::invalid_argument("Matrices must have the same dimensions!\n");
    }

    // Create object that will be returned
    Matrix temp(lhs.get_rows(), lhs.get_cols());

    for (int i = 0; i < temp.get_rows(); ++i)
    {
        for (int j = 0; j < temp.get_cols(); ++j)
        {
            temp[i,j] = lhs[i,j] + rhs[i,j];
        }
    }

    return temp;
}


/********************************************************************************
 *                                  main()                                      *
 *                                                                              *
 * Disclaimer: I used an AI to write the tests in main() to save time (its late)*
 *              and to make sure each operation is thoroughly tested.           *
 * Also: to properly test all copy/move semantics, utilize multi-argument [],   *
 *       and make use of std::println / std::print, compile with the flags:     *
 * (if using g++)       -fno-elide-constructors -O0 -std=c++23                  *
 *                                                                              *
 ********************************************************************************/


int main()
{
    try {
        // Test 1: Basic Matrix Creation and Assignment
        std::println("=== Test 1: Basic Matrix Setup ===");
        Matrix m1{2, 3};  // Smaller matrix for easier testing
        Matrix m2{2, 3};
        
        // Fill m1 with values [1, 2, 3, 4, 5, 6]
        m1[0, 0] = 1.0; m1[0, 1] = 2.0; m1[0, 2] = 3.0;
        m1[1, 0] = 4.0; m1[1, 1] = 5.0; m1[1, 2] = 6.0;
        
        // Fill m2 with values [2, 1, 4, 3, 6, 5] 
        m2[0, 0] = 2.0; m2[0, 1] = 1.0; m2[0, 2] = 4.0;
        m2[1, 0] = 3.0; m2[1, 1] = 6.0; m2[1, 2] = 5.0;
        
        std::println("m1: {}", m1);
        std::println("m2: {}", m2);
        std::println("");

        // Test 2: Compound Assignment Operators
        std::println("=== Test 2: Compound Assignment Operators ===");
        Matrix test_matrix{2, 2};
        test_matrix[0, 0] = 10.0; test_matrix[0, 1] = 20.0;
        test_matrix[1, 0] = 30.0; test_matrix[1, 1] = 40.0;
        
        std::println("Original matrix: {}", test_matrix);
        
        test_matrix += 5.0;
        std::println("After += 5.0: {}", test_matrix);
        
        test_matrix -= 3.0;
        std::println("After -= 3.0: {}", test_matrix);
        
        test_matrix *= 2.0;
        std::println("After *= 2.0: {}", test_matrix);
        
        test_matrix /= 4.0;
        std::println("After /= 4.0: {}", test_matrix);
        std::println("");

        // Test 3: Division by Zero Protection
        std::println("=== Test 3: Division by Zero Protection ===");
        Matrix div_test{2, 2};
        div_test[0, 0] = 10.0; div_test[0, 1] = 20.0;
        div_test[1, 0] = 30.0; div_test[1, 1] = 40.0;
        
        std::println("Testing division by valid numbers:");
        std::println("Before /= 2.0: {}", div_test);
        div_test /= 2.0;
        std::println("After /= 2.0: {}", div_test);
        
        std::println("Testing division by zero protection:");
        try {
            div_test /= 0.0;  // Should throw exception
            std::println("ERROR: Division by zero should have thrown an exception!");
        } catch (const std::exception& e) {
            std::println("Caught expected divide-by-zero error: {}", e.what());
        }
        
        // Verify matrix wasn't modified by failed division
        std::println("Matrix after failed division (should be unchanged): {}", div_test);
        
        // Test with very small numbers (near zero)
        try {
            div_test /= 0.000001;  // Very small but not zero
            std::println("Division by very small number succeeded");
            std::println("After /= 0.000001: {}", div_test);
        } catch (const std::exception& e) {
            std::println("Unexpected error with small number: {}", e.what());
        }
        std::println("");

        // Test 4: Comparison Operators - Your "Majority Rules" Logic
        std::println("=== Test 4: Comparison Operators (Majority Rules) ===");
        Matrix comp1{2, 2};
        Matrix comp2{2, 2};
        
        // comp1: [1, 2, 3, 4]
        comp1[0, 0] = 1.0; comp1[0, 1] = 2.0;
        comp1[1, 0] = 3.0; comp1[1, 1] = 4.0;
        
        // comp2: [2, 1, 4, 3] - comp2 has 2 elements greater than comp1 (2>1, 4>3)
        comp2[0, 0] = 2.0; comp2[0, 1] = 1.0;
        comp2[1, 0] = 4.0; comp2[1, 1] = 3.0;
        
        std::println("comp1: {}", comp1);
        std::println("comp2: {}", comp2);
        std::println("Elements in comp2 > comp1: 2 out of 4 (50%)");
        std::println("comp1 < comp2: {} (should be false - not > 50%)", comp1 < comp2);
        std::println("comp1 <= comp2: {} (should be true - >= 50%)", comp1 <= comp2);
        std::println("");

        // Test 5: Clear Majority Case
        std::println("=== Test 5: Clear Majority Case ===");
        Matrix maj1{2, 2};
        Matrix maj2{2, 2};
        
        // maj1: [1, 1, 1, 1]
        maj1[0, 0] = 1.0; maj1[0, 1] = 1.0;
        maj1[1, 0] = 1.0; maj1[1, 1] = 1.0;
        
        // maj2: [2, 2, 2, 1] - maj2 has 3 elements greater than maj1 (75%)
        maj2[0, 0] = 2.0; maj2[0, 1] = 2.0;
        maj2[1, 0] = 2.0; maj2[1, 1] = 1.0;
        
        std::println("maj1: {}", maj1);
        std::println("maj2: {}", maj2);
        std::println("Elements in maj2 > maj1: 3 out of 4 (75%)");
        std::println("maj1 < maj2: {} (should be true)", maj1 < maj2);
        std::println("maj1 <= maj2: {} (should be true)", maj1 <= maj2);
        std::println("maj1 > maj2: {} (should be false)", maj1 > maj2);
        std::println("maj1 >= maj2: {} (should be false)", maj1 >= maj2);
        std::println("");

        // Test 6: All Comparison Operators Consistency
        std::println("=== Test 6: Comparison Operators Consistency ===");
        Matrix equal1{2, 2};
        Matrix equal2{2, 2};
        
        // Both matrices identical
        equal1[0, 0] = 5.0; equal1[0, 1] = 5.0;
        equal1[1, 0] = 5.0; equal1[1, 1] = 5.0;
        
        equal2[0, 0] = 5.0; equal2[0, 1] = 5.0;
        equal2[1, 0] = 5.0; equal2[1, 1] = 5.0;
        
        std::println("equal1: {}", equal1);
        std::println("equal2: {}", equal2);
        std::println("equal1 == equal2: {} (should be true)", equal1 == equal2);
        std::println("equal1 < equal2: {} (should be false)", equal1 < equal2);
        std::println("equal1 <= equal2: {} (should be true)", equal1 <= equal2);
        std::println("equal1 > equal2: {} (should be false)", equal1 > equal2);
        std::println("equal1 >= equal2: {} (should be true)", equal1 >= equal2);
        std::println("");

        // Test 7: Stream Input/Output Operators
        std::println("=== Test 7: Stream Input/Output ===");
        std::println("Testing output operator with formatted matrix:");
        Matrix io_test{2, 2};
        io_test[0, 0] = 1.5; io_test[0, 1] = 2.5;
        io_test[1, 0] = 3.5; io_test[1, 1] = 4.5;
        std::cout << io_test;
        
        // Uncomment the next lines to test input operator interactively
        // std::println("Enter 4 values for a 2x2 matrix:");
        // std::cin >> io_test;
        // std::println("You entered: {}", io_test);
        std::println("");

        // Test 8: Error Handling for Comparisons
        std::println("=== Test 8: Error Handling for Different Dimensions ===");
        try {
            Matrix small{2, 2};
            Matrix large{3, 3};
            bool result = small < large;  // Should throw
        } catch (const std::exception& e) {
            std::println("Caught expected error for dimension mismatch: {}", e.what());
        }

        try {
            Matrix small{2, 2};
            Matrix large{3, 3};
            bool result = small <= large;  // Should throw
        } catch (const std::exception& e) {
            std::println("Caught expected error for <= with different dimensions: {}", e.what());
        }

        // Test 9: Compound Operations with Edge Cases
        std::println("=== Test 9: Compound Operations Edge Cases ===");
        Matrix edge_test{2, 2};
        edge_test[0, 0] = -10.0; edge_test[0, 1] = 0.0;
        edge_test[1, 0] = 5.5; edge_test[1, 1] = -3.14;
        
        std::println("Testing with negative numbers and zero:");
        std::println("Original: {}", edge_test);
        
        edge_test += -2.5;
        std::println("After += -2.5: {}", edge_test);
        
        edge_test *= -1.0;
        std::println("After *= -1.0: {}", edge_test);
        
        // Test dividing by negative number
        edge_test /= -2.0;
        std::println("After /= -2.0: {}", edge_test);
        
        // Test multiple divide by zero attempts
        std::println("Testing multiple divide by zero scenarios:");
        
        try {
            edge_test /= 0;
            std::println("ERROR: Should have thrown!");
        } catch (const std::exception& e) {
            std::println("First divide by zero caught: {}", e.what());
        }
        
        try {
            edge_test /= 0.0;
            std::println("ERROR: Should have thrown!");
        } catch (const std::exception& e) {
            std::println("Second divide by zero caught: {}", e.what());
        }
        
        std::println("Matrix remains unchanged after failed divisions: {}", edge_test);
        std::println("");
        
        // Test 9.5: Row and Column Extraction Functions
        std::println("=== Test 9.5: Row and Column Extraction Functions ===");

        // Create a test matrix with known values
        Matrix extract_test{3, 4};
        int value = 1;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 4; ++j) {
                extract_test[i, j] = value++;
            }
        }

        std::println("Test matrix (3x4):");
        std::println("{}", extract_test);

        // Test row extraction
        std::println("Testing row extraction:");
        try {
            auto row0 = extract_test.row(0);
            std::println("Row 0: {}", row0);  // Should be [1, 2, 3, 4]
            
            auto row1 = extract_test.row(1);
            std::println("Row 1: {}", row1);  // Should be [5, 6, 7, 8]
            
            auto row2 = extract_test.row(2);
            std::println("Row 2: {}", row2);  // Should be [9, 10, 11, 12]
            
            // Verify specific elements
            std::println("Row 0 size: {} (should be 4)", row0.size());
            std::println("Row 1[2]: {} (should be 7)", row1[2]);
            
        } catch (const std::exception& e) {
            std::println("Error during row extraction: {}", e.what());
        }

        // Test column extraction
        std::println("Testing column extraction:");
        try {
            auto col0 = extract_test.column(0);
            std::println("Column 0: {}", col0);  // Should be [1, 5, 9]
            
            auto col1 = extract_test.column(1);
            std::println("Column 1: {}", col1);  // Should be [2, 6, 10]
            
            auto col3 = extract_test.column(3);
            std::println("Column 3: {}", col3);  // Should be [4, 8, 12]
            
            // Verify specific elements
            std::println("Column 0 size: {} (should be 3)", col0.size());
            std::println("Column 3[1]: {} (should be 8)", col3[1]);
            
        } catch (const std::exception& e) {
            std::println("Error during column extraction: {}", e.what());
        }

        // Test error handling for out-of-bounds indices
        std::println("Testing bounds checking:");

        // Test invalid row index
        try {
            auto invalid_row = extract_test.row(5);  // Should throw
            std::println("ERROR: Should have thrown exception for row 5!");
        } catch (const std::exception& e) {
            std::println("Caught expected row bounds error: {}", e.what());
        }

        try {
            auto negative_row = extract_test.row(-1);  // Should throw
            std::println("ERROR: Should have thrown exception for row -1!");
        } catch (const std::exception& e) {
            std::println("Caught expected negative row error: {}", e.what());
        }

        // Test invalid column index
        try {
            auto invalid_col = extract_test.column(7);  // Should throw
            std::println("ERROR: Should have thrown exception for column 7!");
        } catch (const std::exception& e) {
            std::println("Caught expected column bounds error: {}", e.what());
        }

        try {
            auto negative_col = extract_test.column(-2);  // Should throw
            std::println("ERROR: Should have thrown exception for column -2!");
        } catch (const std::exception& e) {
            std::println("Caught expected negative column error: {}", e.what());
        }

        // Test with edge case: single element matrix
        Matrix single{1, 1};
        single[0, 0] = 42.0;
        std::println("Testing with 1x1 matrix:");
        auto single_row = single.row(0);
        auto single_col = single.column(0);
        std::println("Single row: {} (should be [42])", single_row);
        std::println("Single column: {} (should be [42])", single_col);

        std::println("");

        // Test 10: Constructor and Basic Error Handling
        std::println("=== Test 10: Constructor and Basic Error Handling ===");
        try {
            Matrix invalid{-1, 5};
        } catch (const std::exception& e) {
            std::println("Caught expected error for negative dimensions: {}", e.what());
        }

        try {
            Matrix m10{2, 2};
            m10[5, 5] = 1.0;  // Should throw
        } catch (const std::exception& e) {
            std::println("Caught expected error for invalid index: {}", e.what());
        }

        try {
            Matrix m11{2, 2};
            Matrix m12{3, 3};
            Matrix bad_result = m11 + m12;  // Should throw
        } catch (const std::exception& e) {
            std::println("Caught expected error for dimension mismatch in addition: {}", e.what());
        }

        std::println("");
        std::println("=== All Tests Including Divide-by-Zero Protection Completed Successfully! ===");

    } catch (const std::exception& e) {
        std::println("Unexpected error: {}", e.what());
        return 1;
    }

    return 0;
}



/*********************************
 *                               *
 *   The "Essential Operations"  *
 *                               *
 *********************************/


// two argument constructor
Matrix::Matrix(int r, int c)
    : data(calc_size(r, c))
    , rows{ r }
    , cols{ c }
{
    std::println("## 2-arg constructor called ##");
}

// Copy constructor
Matrix::Matrix(const Matrix& orig)
    : data{ orig.data }
    , rows{ orig.rows }
    , cols{ orig.cols }
{
    std::println("## Copy constructor called ##");
}

// Copy assignment
Matrix& Matrix::operator=(const Matrix& orig)
{
    std::println("## Copy assignment called ##");
    if (this != &orig)
    {
        data = orig.data;
        rows = orig.rows;
        cols = orig.cols;
        return *this;
    }
    else
    {
        return *this;
    }
}

// Move constructor
Matrix::Matrix(Matrix&& m)
    : data{ std::move(m.data) }
    , rows{ m.rows }
    , cols{ m.cols }
{
    std::println("## Move constructor called ##");
    // set m's data to null values
    m.rows = 0;
    m.cols = 0;
}

// Move assignment
Matrix& Matrix::operator=(Matrix&& m)
{
    std::println("## Move assignment called ##");
    if (this != &m)
    {
        // move data
        data = std::move(m.data);
        rows = m.rows;
        cols = m.cols;
        // set m's data to null values
        m.rows = 0;
        m.cols = 0;
        return *this;
    }
    else
    {
        return *this;
    }
}
