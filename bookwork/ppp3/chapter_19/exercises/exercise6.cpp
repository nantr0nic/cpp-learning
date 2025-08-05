/*==============================================================*
*                          Exercise 6                           *
*                                                               *
*Write a find-and-replace operation for Documents based on §19.5*
 *==============================================================*/

import std;

// We're going to use lists to hold lines, each line (demarcated with a newline)
// will be an element of the list -- but each line itself will be a vector<char>

using Line = std::vector<char>;         // a line is a vector of characters

/*=======================================================*
**                                                       **
**            This is the Text_iterator class            **
**                                                       **
 *=======================================================*/

class Text_iterator
// keep track of line and character position within a line 
{
private:
    std::list<Line>::iterator ln;
    Line::iterator pos;

public:
    Text_iterator(std::list<Line>::iterator ll, Line::iterator pp)  
    // line ll's character position pp
        : ln{ ll }
        , pos{ pp }
        { }

    char& operator*() { return *pos; }
    Text_iterator& operator++();
    bool operator==(const Text_iterator& other) const {
        return ln==other.ln && pos == other.pos;
    }
    bool operator!=(const Text_iterator& other) const {
        return !(*this==other);
    }

    auto get_ln() -> std::list<Line>::iterator { return ln; }
    auto get_pos() -> Line::iterator           { return pos; }

};

Text_iterator& Text_iterator::operator++()
{
    ++pos;                  // proceed to next character
    if (pos == ln->end())
    {
        ++ln;               // proceed to next line
        pos = ln->begin();  // bad if ln==line.end(); so make sure it isn't
    }
    return *this;
}

/*=======================================================*
**                                                       **
**              This is the Document class               **
**                                                       **
 *=======================================================*/

struct Document 
{
    std::list<Line> line;               // a document is a list of Lines
    Document() { line.push_back(Line{}); }

    Text_iterator begin() {
        return Text_iterator { line.begin(), line.begin()->begin() };
    }

    Text_iterator end() {
        auto last = line.end();
        --last;
        return Text_iterator{ last, (*last).end() };
    }

};

std::istream& operator>>(std::istream& is, Document& d)
{
    for (char ch = 0; is.get(ch); )
    {
        d.line.back().push_back(ch);       // add the character
        if (ch == '\n')
        {
            d.line.push_back(Line{});      // add another line
        }
    }
    if (d.line.back().size())
    {
        d.line.push_back(Line{}); // add final empty line
    }
    return is;
}

/********************************************************************
**                                                                  **
**These are some possible functions using Document and Text_iterator**
**                                                                  **
 ********************************************************************/

void print(Document& d)
{
    for (auto p : d)
    {
        std::cout << p;
    }
}

void erase_line(Document& d, int n)
{
    if (!(0 <= n && n < d.line.size()))
    {
        return;
    }

    auto p = d.line.begin();
    advance(p, n);
    d.line.erase(p);
}

// advance() is a standard-library function but we could have implemented it ourselves:
template<std::bidirectional_iterator Iter>
void advance(Iter& p, int n)
{
    while (0 < n)
    {
        ++p;
        --n;
    }
    // "Try This" exercise on 845
    // make sure to change forward_iterator to bidirectional_iterator lol
    while (0 > n)
    {
        --p;
        ++n;
    }
}

bool match(Text_iterator first, Text_iterator last, const std::string& s)
{
    auto p{first};
    
    for (const char c : s)
    {
        if (p == last || *p != c)
        {
            return false; 
        }
        ++p;
    }
    
    return true; 
}

Text_iterator find_txt(Text_iterator first, Text_iterator last, const std::string& s)
// find s in [first:last)
{
    if (s.empty())
    {
        return last;
    }

    const char first_char = s[0];

    auto p = last;
    for (p = std::find(first, last, first_char);
        !(p == last || match(p, last, s)); ++p)
    {
        // do nothing
    }
    return p;
}

//$ -----  This is exercise 6  -----
// This will only work for words of the same length or shorter
Text_iterator find_replace(Text_iterator first, Text_iterator last, 
                           const std::string& find, const std::string& replace)
{
    auto word_front = find_txt(first, last, find); // pointer to the first letter of the found word

    if (word_front == last) // if not found, return last
    {
        return last;
    }

    auto p = word_front;

    for (std::size_t i = 0; i < find.length(); ++i)
    {
        if (i < replace.length())
        {
            *p = replace[i];
        }
        else
        {
            *p = ' '; // replace with white space if replace is shorter than find
        }
        ++p;
    }
        
    return word_front;
}