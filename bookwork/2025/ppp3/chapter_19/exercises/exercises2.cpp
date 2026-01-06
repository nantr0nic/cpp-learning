//$ ----- Exercises 2 - 4 for Chapter 19 ----- //
import std;

/*===================================================================*
*                             Exercise 2                             *
*                                                                    *
*Get the Jack-and-Jill example from §19.2.1 to work. Use input from a*
*                 couple of small files to test it.                  *
 *===================================================================*/
template<std::forward_iterator Iter>
Iter high(Iter first, Iter last)
// return an iterator the element in [first:last) that has the highest value
{
    Iter high = first;
    for (Iter p = first; p != last; ++p)
    {
        if (*high < *p)
        {
            high = p;
        }
    }
    return high;
}

double* get_from_jack(int* count)
// Jack fills an array and puts the number of elements in *count
{
    const std::string file_name{ "jack_data.txt" };
    std::ifstream ifs{ file_name };

    if (!ifs)
    {
        *count = 0;
        return nullptr;
    }

    double temp{};
    int reading_count = 0;
    while (ifs >> temp)
    {
        ++reading_count;
    }

    // reset file reading
    ifs.clear();
    ifs.seekg(0, std::ios::beg);

    auto data_entries = new double[reading_count];

    int i = 0;
    while (ifs >> data_entries[i])
    {
        ++i;
    }

    *count = reading_count;
    return data_entries;
}

std::vector<double> get_from_jill()
// Jill fills the vector
{
    std::vector<double> temp;
    double speed_reading{};

    const std::string file_name{ "jill_data.txt" };
    std::ifstream ifs{ file_name };
    
    while (ifs >> speed_reading)
    {
        temp.push_back(speed_reading);
    }

    return temp;
}

void fct()
{
    int jack_count = 0;
    double* jack_data = get_from_jack(&jack_count);
    std::vector<double> jill_data = get_from_jill();

    double* jack_high = high(jack_data, jack_data + jack_count);
    auto jill_high = high(jill_data.begin(), jill_data.end());

    std::println("Jill's high: {}; Jack's high: {}", *jill_high, *jack_high);
    delete[] jack_data;
}

int main()
{
    fct();

    return 0;
}