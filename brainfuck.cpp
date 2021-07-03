#include <iostream>
#include <string.h>

std::string brainfuck(std::string code)
{
    char cells[1024] = {0};
    int p = 0;
    std::string out = "";
    for (size_t i = 0; i < code.length(); i++)
    {
        switch (code.at(i))
        {
        case '>':
            p++;
            break;
        case '<':
            p--;
            break;
        case '+':
            cells[p]++;
            break;
        case '-':
            cells[p]--;
            break;
        case '.':
            out += cells[p];
            break;
        case ',':
            std::cin>>cells[p];
            break;
        case ']':
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
