#include <iostream>
#include <string.h>

std::string brainfuck(std::string code)
{
    char cells[1024] = {0};
    int p = 0;
    std::string out = "";
    for (size_t i = 0; i < code.length(); i++)
    {
        // brainfuck only has 8 commands, all of which are one character
        // therefore a simple switch statement is enough
        switch (code.at(i))
        {
        case '>':
            // move pointer to the right
            p++;
            break;
        case '<':
            // move pointer to the left
            p--;
            break;
        case '+':
            // increment cell at pointer
            cells[p]++;
            break;
        case '-':
            // decrement cell at pointer
            cells[p]--;
            break;
        case '.':
            // add cell character value to output string (don't print, only buffer to return in the end)
            out += cells[p];
            break;
        case ',':
            // insert input character into cell at pointer
            std::cin>>cells[p];
            break;
        case ']':
            // jump back to corresponding opening bracket
            if (cells[p])
            {
                int depth = 1;
                while (depth)
                {
                    i--;
                    if (code.at(i) == ']')
                        depth++;
                    else if (code.at(i) == '[')
                        depth--;
                }
            }
            break;
        default:
            // ignore everything else
            break;
        }
    }

    return out;
}


// short version for the funs
std::string bf_min(std::string code) { 
 char c[1024]={0};int p=0;std::string o="";for(int i=0;i<code.length();i++){switch(code.at(i)){case '>':p++;break;case '<':p--;break;case '+':c[p]++;break;case '-':c[p]--;break;case '.':o+=c[p];break;case ',':std::cin>>c[p];break;case ']':if(c[p]){int d=1;while(d){i--;if(code.at(i)==']')d++;else if(code.at(i)=='[')d--;}}break;default:break;}}return o; 
}

int main(int argc, char* argv[])
{
    std::string code;
    if (argc==1){
        std::string in;
        while (std::cin >> in){
            code += in;
        }
    }
    else {
        code="";
        for (size_t i = 1; i < argc; i++)
        {
            code.append(argv[i]).append(" ");
        }
    }

    std::string res = brainfuck(code);
    printf("%s\n", res.c_str());
    return 0;
}
