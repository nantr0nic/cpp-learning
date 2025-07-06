//$ ----- vector drills ----- //
#include <vector>
#include <print>

// #1
std::vector<int> gv {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};

// #2 and #3
void f(std::vector<int> v)
{
    std::vector<int> lv(v.size());

    for (size_t i = 0; i < lv.size(); ++i)
        lv[i] = gv[i];

    std::println("{}", lv);

    std::vector<int> lv2 = v;

    std::println("{}", lv2);
}

// #4
int main()
{
    f(gv);

    std::vector<int> vv {1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};

    f(vv);

    return 0;
}