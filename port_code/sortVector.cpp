#include <vector>

void sortVector(std::vector<double>& vec)
{
    for (int i {0}; i < vec.size() - 1; ++i)
    {
        for (int j {0}; j < vec.size() - i - 1; ++j)
        {
            if (vec[j] > vec[j + 1])
            {
                double temp {vec[j]};
                vec[j] = vec[j + 1];
                vec[j + 1] = temp;
            }
        }
    }
}