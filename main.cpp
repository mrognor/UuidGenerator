#include <iostream>
#include <random>

std::string UuidGen4()
{
    std::string res;
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 15);

    char chars[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

    for (int i = 0; i < 32; i++)
    {
        int a = dist(rd);

        if (i == 12)
        {
           res += std::to_string(0b0100);
           continue;
        }

        if (i == 16)
        {
            a |= 0b1000;
            a &= ~(0b0100);
        }

        res += chars[a];

        if (i == 7 || i == 11 || i == 15 || i == 19)
            res += "-";
    }

    return res;
}

int main()
{
    std::cout << UuidGen4() << std::endl;
}
