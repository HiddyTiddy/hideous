#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

/* 
  version 0.1.0
*/
std::vector<long long> factorize(long long number)
{
    // brute force ig but yknow
    // c++ is fast
    // it'll manage don't you think
    std::vector<long long> out;
    long long n = number;
    for (long long i = 2; i * i < number; i++)
    {
        while (!(n % i))
        // loop until all factors are found
        {
            out.push_back(i);
            n /= i;
        }
    }

    if (n > 1)
    {
        out.push_back(n);
    }

    return out;
}


/* 
  version 1.0.0
*/
std::vector<long long> halfassedButHopefullyFasterFactorize(long long number)
{

    // maybe faster
    // actually is faster
  
    std::vector<long long> out;

    // remove factors of 2 explicitly
    while (!(number % 2))
    {
        out.push_back(2);
        number /= 2;
    }

    // long long last = 2;

    // number will not be even: no need to check for even numbers -> skip them
    /*
        todo : find an efficient way of skipping factors > 2        
    */
    for (long long i = 3; i * i <= number; i += 2)
    {
        while (!(number % i))
        {
            out.push_back(i);
            number /= i;
        }
    }

    if (number > 1)
    {
        out.push_back(number);
    }

    return out;
}

std::string helpmsg(std::string call)
{
    return "factorizes a number\nUsage: " + call + " <number>\nOptions:\n -h\t show this message\n -v\t display current version\n -a\t show author";
}

std::string author(){
    return "author Hyde";
}

std::string version(){
    return "version 1.0.0";
}

enum STR2INT_ERROR
{
    S2I_SUCCESS,
    S2I_OVERFLOW,
    S2I_UNDERFLOW,
    S2I_INCONVERTIBLE
};

STR2INT_ERROR str2int(long long &i, char const *s, int base = 0)
{
    char *end;
    long long l;
    errno = 0;
    l = strtoll(s, &end, base);
    if ((errno == ERANGE && l == __LONG_LONG_MAX__) || l > __LONG_LONG_MAX__)
    {
        return S2I_OVERFLOW;
    }
    if ((errno == ERANGE && l == LONG_MIN) || l < LONG_MIN)
    {
        return S2I_UNDERFLOW;
    }
    if (*s == '\0' || *end != '\0')
    {
        return S2I_INCONVERTIBLE;
    }
    i = l;
    return S2I_SUCCESS;
}


bool cmdOptionExists(char **begin, char **end, const std::string &option)
{
    return std::find(begin, end, option) != end;
}

int main(int argc, char *argv[])
{
    long long id = 710350894138654732;

    if (cmdOptionExists(argv, argv + argc, "-h"))
    {
        std::cout << helpmsg(argv[0]) << std::endl;
        return 0;
    }

    if (cmdOptionExists(argv, argv+argc, "-v")){
        std::cout << version() << std::endl;
        return 0;
    }
    if (cmdOptionExists(argv, argv+argc, "-a")){
        std::cout << author() << std::endl;
        return 0;
    }

    long long val;
    STR2INT_ERROR err;

    // support for usage like `factorize <number>`
    if (argc > 1)
    {
        err = str2int(val, argv[1]);
        // std::cout << "\033[35m"<< val << "  \033[1;31m" << err << "\033[0m" << std::endl;
    }
    // support for usage like `echo <number> | factorize`
    else
    {
        std::string input;
        while (std::cin >> input)
        {
            const char * in = input.c_str();
            err = str2int(val, in);
            break;
        }
    }

    // invalid input
    if (err == STR2INT_ERROR::S2I_INCONVERTIBLE)
    {
        // [1;31m = red, bold
        std::cout << "\033[1;31mError: cannot convert input\033[0m" << std::endl;
        return 3;
    }
    // number too large
    else if (err == STR2INT_ERROR::S2I_OVERFLOW)
    {
        std::cout << "\033[1;31mOverflowError\033[0m" << std::endl;
        return 1;
    }
    // number too small (negative overflow)
    else if (err == STR2INT_ERROR::S2I_UNDERFLOW)
    {
        std::cout << "\033[1;31mUnderflowError\033[0m" << std::endl;
        return 2;
    }

    std::vector<long long> factorization = halfassedButHopefullyFasterFactorize(val);

    for (size_t i = 0; i < factorization.size(); i++)
    {
        std::cout << factorization.at(i);
        if (i != factorization.size() - 1)
            std::cout << " ";
    }
    std::cout << std::endl;
    return 0;

}
