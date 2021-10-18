// gcc lang.cpp -o lang


#include <iostream>
#include <string.h>
#include <fstream>
#include <stack>

char *get_code(char *filename, int *width, int *height, int *x0, int *y0)
{
    std::string src = "";
    std::string line;
    std::ifstream fp(filename);
    *width = 0;
    *height = 0;
    int w = 0;
    while (getline(fp, line))
    {
        (*height)++;
        for (size_t i = 0; i < line.length(); i++)
        {
            w++;
            if (line.at(i) == '.')
            {
                *x0 = i;
                *y0 = *height - 1;
            }
        }
        if (w > *width)
        {
            *width = w;
            w = 0;
        }
        src += line + "\n";
    }
    (*width)++;

    char *grid = new char[*height * *width];

    int y = 0;
    int x = 0;
    for (size_t i = 0; i < src.length(); i++)
    {
        *(grid + x + (*width) * y) = src.at(i);
        x++;
        if (src.at(i) == '\n')
        {
            x = 0;
            y++;
        }
    }

    fp.close();
    return grid;
}

char pop(std::stack<char> *stck)
{
    char out = stck->top();
    stck->pop();
    return out;
}

int lang(char *grid, int width, int height, int x0, int y0)
{

    int ptr_x = x0;
    int ptr_y = y0;

    bool done = false;
    int momentum_x = 1;
    int momentum_y = 0;
    bool escaped = false;
    bool in_str = false;
    std::stack<char> stck;
    char a;
    char b;

    while (!done)
    {
        ptr_x += momentum_x;
        ptr_y += momentum_y;
        if (ptr_x > width || ptr_x < 0 || ptr_y > height || ptr_y < 0)
            return -1;
        char ch = *(grid + ptr_x + width * ptr_y);
        //printf("\n%c (%d %d) %d", ch, ptr_x, ptr_y);
        // if (!stck.empty()) printf("\n%d", stck.top());
        // printf("%c %d\n", ch, ch);
        if (in_str)
        {
            if (escaped)
            {
                switch (ch)
                {
                case '\\':
                    stck.push('\\');
                    break;
                case 'n':
                    stck.push('\n');
                    break;
                case 't':
                    stck.push('\t');
                    break;
                case 'r':
                    stck.push('\r');
                    break;
                case '"':
                    stck.push('"');
                    break;
                default:
                    break;
                }
                escaped = false;
                continue;
            }
            if (ch == '"')
            {
                in_str = false;
            }
            else
            {
                if (ch == '\\')
                {
                    escaped = true;
                }
                else
                {
                    stck.push(ch);
                }
            }
            continue;
        }

        switch (ch)
        {
        case 'v':
            if (momentum_y == 0)
            {
                momentum_y = 1;
                momentum_x = 0;
            }
            break;
        case '<':
            if (momentum_x == 0)
            {
                momentum_y = 0;
                momentum_x = -1;
            }
            break;
        case '^':
            if (momentum_y == 0)
            {
                momentum_y = -1;
                momentum_x = 0;
            }
            break;
        case '>':
            if (momentum_x == 0)
            {
                momentum_y = 0;
                momentum_x = 1;
            }
            break;
        case '+':
            a = pop(&stck);
            b = pop(&stck);
            stck.push(b + a);
            break;
        case '*':
            a = pop(&stck);
            b = pop(&stck);
            stck.push(b * a);
            break;
        case '/':
            a = pop(&stck);
            b = pop(&stck);
            stck.push(b / a);
            break;
        case '-':
            a =pop(&stck); 
            b =pop(&stck); 
            stck.push(b - a);
            break;
        case '%':
            a =pop(&stck); 
            b =pop(&stck); 
            stck.push(b % a);
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            stck.push(ch - '0');
            break;
        case ',':
            std::cout <<pop(&stck); 
            break;
        case '"':
            in_str = true;
            break;
        case ';':
            return pop(&stck); 
            break;
        case '!':
            a =pop(&stck); 
            stck.push(a == 0);
            break;
        case '`':
            a =pop(&stck); 
            b =pop(&stck); 
            stck.push(b > a);
            break;
        case ':':
            stck.push(stck.top());
            break;
        case '$':
            stck.pop();
            break;
        case '|':
            if (pop(&stck) != 0 && momentum_x != 0)
            {
                momentum_x = -momentum_x; // = 0
                momentum_y = momentum_y;
            }
            break;
        case '_':
            if (pop(&stck) != 0 && momentum_y != 0)
            {
                momentum_x = momentum_x; // = 0
                momentum_y = -momentum_y;
            }
            break;

        default:
            break;
        }
    }

    delete[] grid;
    return 0;
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        fprintf(stderr, "[ERROR] not enough args");
        return 1;
    }
    int height;
    int width;
    int x0, y0;
    char *grid = get_code(argv[1], &width, &height, &x0, &y0);

    return lang(grid, width, height, x0, y0);
}
