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

std::string ToHex(std::uint64_t digit) noexcept
{
    static constexpr char hex_chars[] = "0123456789abcdef";
    std::string res(16, '0');

    for (int i = 15; i >= 0; --i)
    {
        // Add to res last 4 bits
        res[i] = hex_chars[digit & 0xf];
        digit >>= 4;
    }

    return res;
}

std::string Uuid()
{
    std::string res;
    std::random_device rd;
    std::uniform_int_distribution<std::uint64_t> dist(0, std::numeric_limits<std::uint64_t>::max());

    // Gen fully random 64 bit number
    std::string a = ToHex(dist(rd));

    // Gen random number with two first bits: 10. This is equal 1 uuid variant
    std::string b = ToHex((dist(rd) >> 2) | (1ull << 63));

    // xxxxxxxx
    res += a.substr(0, 8);
    res += "-";

    // xxxxxxxx-xxxx
    res += a.substr(8, 4);
    res += "-4";

    // xxxxxxxx-xxxx-4xxx
    res += a.substr(13, 3);
    res += "-";

    // xxxxxxxx-xxxx-4xxx-{89ab}xxx
    res += b.substr(0, 4);
    res += "-";
    
    // xxxxxxxx-xxxx-4xxx-{89ab}xxx-xxxxxxxxxxxx
    res += b.substr(4, 12);

    return res;
}

int main()
{
    // std::cout << UuidGen4() << std::endl;

    std::cout << Uuid() << std::endl;
}
