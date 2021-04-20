#include <iostream>
#include <string>
#include <unistd.h>

#define LEN 36
#define BUFFERLEN 16

/**
 * @brief Yggdrasil's --ship command
 * @details takes in two names of type <std::string> and returns a calculated ship score <int> 
 */
int ship(std::string A, std::string B)
{
    int out = 0;
    for (size_t i = 0; i < A.size(); i++)
        out += A.at(i);
    {
    }
    for (size_t i = 0; i < B.size(); i++)
    {
        out += B.at(i);
    }
    return (out - 69) % 101;
}

class Bruteforce
{
private:
    char charset[LEN];
    uint16_t buffer[BUFFERLEN];
    void update_buffer(int pos);
    bool done;
    int len;

public:
    Bruteforce(int len);
    ~Bruteforce();
    std::string next();
    bool isDone();
};

Bruteforce::Bruteforce(int len)
{
    // char chars[] = "0123456789abcdefghijklmnopqrstuvwxyz!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
    char chars[] = "abcdefghijklmnopqrstuvwxyz0123456789";

    this->len = len;

    for (size_t i = 0; i < LEN; i++)
    {
        charset[i] = chars[i];
    }

    for (size_t i = 0; i < len; i++)
    {
        buffer[i] = 0;
    }

    done = false;
}

Bruteforce::~Bruteforce()
{
}

std::string Bruteforce::next()
{
    std::string out = "";
    for (size_t i = 0; i < len; i++)
    {
        out += *(charset + *(buffer + i));
    }

    update_buffer(len - 1);

    return out;
}

bool Bruteforce::isDone()
{
    return done;
}

void Bruteforce::update_buffer(int pos)
{
    if (pos < 0)
    {
        done = true;
        return;
    }
    buffer[pos]++;
    if (buffer[pos] == LEN)
    {
        buffer[pos] = 0;
        update_buffer(pos - 1);
    }
}

namespace StringToInt
{
    enum STR2INT_ERROR
    {
        STR2INT_SUCCESS,
        STR2INT_OVERFLOW,
        STR2INT_UNDERFLOW,
        STR2INT_INCONVERTIBLE
    };
    /*
        https://stackoverflow.com/questions/194465/how-to-parse-a-string-to-an-int-in-c
        man's doin god's work 
    */
    STR2INT_ERROR str2int(int &i, char const *s, int base = 0)
    {
        char *end;
        long l;
        errno = 0;
        l = strtol(s, &end, base);
        if ((errno == ERANGE && l == LONG_MAX) || l > INT_MAX)
        {
            return StringToInt::STR2INT_OVERFLOW;
        }
        if ((errno == ERANGE && l == LONG_MIN) || l < INT_MIN)
        {
            return StringToInt::STR2INT_UNDERFLOW;
        }
        if (*s == '\0' || *end != '\0')
        {
            return StringToInt::STR2INT_INCONVERTIBLE;
        }
        i = l;
        return StringToInt::STR2INT_SUCCESS;
    }
} // namespace StringToInt


int main(int argc, char *argv[])
{

    if (argc==2){

        std::string arg = argv[1];

        if (arg=="help"){
            std::cout << "Utility to calculate perfect --ship commands\n\n[Usage]: " << argv[0] << " <first name> <second name> <number of characters to try>\n\noptions:\n" 
            << argv[0] << " help\tdisplay this message and exit\n" 
            << argv[0] << " version\tdisplay version\n" 
            << argv[0] << " author\tdisplay current version"
            << std::endl;
        }

        if (arg=="version"){
            std::cout << "version 0.1.0" << std::endl;
        } 
        if (arg=="author"){
            std::cout << "author: Hyde (aka hiddy tiddy)" << std::endl;
        }

        return 2;
    }

    if (argc != 4)
    {
        std::cout << "[Usage]: " << argv[0] << " <first name> <second name> <number of characters to try>\n" << std::endl;
        return 1;
    }

    std::string first_arg = argv[1];
    std::string second_arg = argv[2];
    int length;
    StringToInt::STR2INT_ERROR err = StringToInt::str2int(length, argv[3]);
    if (err!=StringToInt::STR2INT_SUCCESS){
        return -1;
    }

    if (length < 0){
        return -1;
    }


    Bruteforce generator(length);

    int count = 0;
    while (!generator.isDone())
    {
        std::string candidate = generator.next();
        if (ship(first_arg + candidate, second_arg) == 100)
        {
            count++;
            std::cout << "--ship " << first_arg << " " << second_arg << candidate << "\n";
            if (count % 100 == 0)
                std::cout << std::endl;
        }
    }

    return 0;
}
