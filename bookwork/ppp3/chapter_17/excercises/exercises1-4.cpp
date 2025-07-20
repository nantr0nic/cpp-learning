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
    
    // Traversal
    auto begin() { return data.begin(); }
    auto end() { return data.end(); }

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

bool operator==(const Matrix& m1, const Matrix& m2)
{
    // Check that the Matrices have the same dimensions (matching r and c)
    if (m1.get_cols() != m2.get_cols() || m1.get_rows() != m2.get_rows())
    {
        return false;
    }

    // If they have the same dimensions, then each data vector is same size
    // and we can check their respective elements
    for (size_t i = 0; i < m1.get_size(); ++i)
    {
        if (m1.get_index(i) != m2.get_index(i))
            return false;
    }

    // Failing to return false up to here means both matrices have same dimensions
    // and each element is the same as well, thus they're identical
    return true;
}

bool operator!=(const Matrix& m1, const Matrix& m2)
{
    return !(m1 == m2);
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

Matrix operator+(const Matrix& m1, const Matrix& m2)
{
    // First, check they have the same dimensions
    if (m1.get_cols() != m2.get_cols() || m1.get_rows() != m2.get_rows())
    {
        throw std::invalid_argument("Matrices must have the same dimensions!\n");
    }

    // Create object that will be returned
    Matrix temp(m1.get_rows(), m1.get_cols());

    for (int i = 0; i < temp.get_rows(); ++i)
    {
        for (int j = 0; j < temp.get_cols(); ++j)
        {
            temp[i,j] = m1[i,j] + m2[i,j];
        }
    }

    return temp;
}


/********************************************************************************
 *                                  main()                                      *
 *                                                                              *
 * Disclaimer: I used an AI to write the tests in main() to save time (its late)*
 *              and to make sure each operation is thoroughly tested            *
 *              but I did add a test to test features I added later             *
 * Also: to properly test all copy/move semantics, utilize multi-argument [],   *
 *       and make use of std::println / std::print, compile with the flags:     *
 * (if using g++)       -fno-elide-constructors -O0 -std=c++23                  *
 *                                                                              *
 ********************************************************************************/


int main()
{
try {
        // Test 1: Constructor and basic functionality
        std::println("=== Test 1: Constructor and Basic Operations ===");
        Matrix m1{3, 4};
        std::println("Created 3x4 matrix");
        std::println("Rows: {}, Cols: {}", m1.get_rows(), m1.get_cols());
        std::println("Size: {}", m1.get_size());
        std::println("");

        // Test 2: Element assignment and access
        std::println("=== Test 2: Element Assignment and Access ===");
        m1[0, 0] = 1.5;
        m1[1, 2] = 2.7;
        m1[2, 3] = 3.14;
        std::println("m1[0,0] = {}", m1[0, 0]);
        std::println("m1[1,2] = {}", m1[1, 2]);
        std::println("m1[2,3] = {}", m1[2, 3]);
        std::println("");

        // Test 2.5: the << operator
        std::println("=== Test 2.5: The << operator and println output");
        std::cout << m1;
        std::println("{}", m1);     // 'detects' and uses begin() and end() from Matrix

        // Test 2.7: the >> operator with std::cin
        std::println("Matrix m1 is 3x4, enter its values now:");
        std::cin >> m1;
        std::println("{}", m1);

        // Test 3: Copy constructor
        std::println("=== Test 3: Copy Constructor ===");
        Matrix m2{m1};
        std::println("Copied m1 to m2");
        std::println("m2[0,0] = {} (should be 1.5)", m2[0, 0]);
        std::println("m2[1,2] = {} (should be 2.7)", m2[1, 2]);
        std::println("");

        // Test 4: Assignment operator
        std::println("=== Test 4: Assignment Operator ===");
        Matrix m3{2, 2};
        m3[0, 0] = 99.9;
        std::println("Before assignment: m3[0,0] = {}", m3[0, 0]);
        m3 = m1;
        std::println("After assignment: m3[0,0] = {} (should be 1.5)", m3[0, 0]);
        std::println("");

        // Test 5: Equality operators
        std::println("=== Test 5: Equality Operators ===");
        std::println("m1 == m2: {} (should be true)", m1 == m2);
        std::println("m1 != m2: {} (should be false)", m1 != m2);
        
        Matrix m4{3, 4};
        m4[0, 0] = 999;
        std::println("m1 == m4: {} (should be false)", m1 == m4);
        std::println("");

        // Test 6: Addition operator
        std::println("=== Test 6: Addition Operator ===");
        Matrix m5{2, 2};
        Matrix m6{2, 2};
        
        m5[0, 0] = 1.0; m5[0, 1] = 2.0;
        m5[1, 0] = 3.0; m5[1, 1] = 4.0;
        
        m6[0, 0] = 5.0; m6[0, 1] = 6.0;
        m6[1, 0] = 7.0; m6[1, 1] = 8.0;
        
        Matrix result = m5 + m6;
        std::println("Result of addition:");
        std::println("[0,0] = {} (should be 6.0)", result[0, 0]);
        std::println("[0,1] = {} (should be 8.0)", result[0, 1]);
        std::println("[1,0] = {} (should be 10.0)", result[1, 0]);
        std::println("[1,1] = {} (should be 12.0)", result[1, 1]);
        std::println("");

        // Test 7: Move operations
        std::println("=== Test 7: Move Operations ===");
        Matrix m7{std::move(result)};  // Move constructor
        std::println("Moved result to m7");
        std::println("m7[0,0] = {} (should be 6.0)", m7[0, 0]);
        
        Matrix m8{1, 1};
        m8 = std::move(m7);  // Move assignment
        std::println("Move assigned m7 to m8");
        std::println("m8[0,0] = {} (should be 6.0)", m8[0, 0]);
        std::println("");

        // Test 8: Iterator support
        std::println("=== Test 8: Iterator Support ===");
        Matrix m9{2, 3};
        int counter = 1;
        for (auto it = m9.begin(); it != m9.end(); ++it) {
            *it = counter++;
        }
        std::println("Filled matrix using iterators:");
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 3; ++j) {
                std::print("{} ", m9[i, j]);
            }
            std::println("");
        }
        std::println("");

        // Test 9: Error handling - invalid dimensions
        std::println("=== Test 9: Error Handling ===");
        try {
            Matrix invalid{-1, 5};
        } catch (const std::exception& e) {
            std::println("Caught expected error for negative dimensions: {}", e.what());
        }

        // Test 10: Error handling - index out of bounds
        try {
            Matrix m10{2, 2};
            m10[5, 5] = 1.0;  // Should throw
        } catch (const std::exception& e) {
            std::println("Caught expected error for invalid index: {}", e.what());
        }

        // Test 11: Error handling - mismatched dimensions for addition
        try {
            Matrix m11{2, 2};
            Matrix m12{3, 3};
            Matrix bad_result = m11 + m12;  // Should throw
        } catch (const std::exception& e) {
            std::println("Caught expected error for dimension mismatch: {}", e.what());
        }

        std::println("");
        std::println("=== All Tests Completed Successfully! ===");

    } catch (const std::exception& e) {
        std::println("Unexpected error: {}", e.what());
        return 1;
    }

    return 0;
}



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