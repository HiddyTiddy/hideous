// this is a small brainfuck compiler i wrote
// so far only works on linux (i hope, only tested on arch tbh)
// requires nasm(1) and ld(1)
// enjoy :)


// also pls dont mind the messy string jank
// im working on it

// (im not)

// !! potential security issue with the nasm and ld parts !!
// if the bfc binary is run as root (thru sudo), it is possible to escalate privileges
// reason: im too lazy to make the paths to nasm and ld absolute oops

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

std::string read_file(char* filename){
    std::ifstream file(filename);
    std::string out ("");
    std::string line;
    if (file.is_open()){
        while (std::getline(file, line)){
            out += line;
        }
    }
    file.close();
    return out;
}

void write(std::string assembly, std::string ofile){
    std::string filename = ofile;
    filename.push_back('.');
    filename.push_back('s');
    std::ofstream file(filename );
    if (file.is_open()){
        file << assembly;
    }
    file.close();
}

int compile(char* filename, std::string ofilename){
    std::string source_code = read_file(filename);

    std::string START = "global _start\n\n"
        "section .text\n\n"
        "_start:\n"
        "    mov rsi,x\n";

    std::string END = "mov rax,60\n"
        "mov rdi,0\n"
        "syscall\n";

    std::string DATA = "section .data\n"
        "global x\n"
        "x times 1024 db 0\n";

    std::map<int, std::string> labels;
    std::string output = "";

    output += START;

    for (int i=0;i<source_code.length(); i++){
        char s = source_code.at(i);

        int pos;
        int depth;
        switch (s) {
            case '+': 
                output += "    inc byte [rsi]\n";
                break; 
            case '-': 
                output += "    dec byte [rsi]\n";
                break; 
            case '>': 
                output += "    add rsi,1\n";
                break;
            case '<':
                output += "    sub rsi,1\n";
                break;
            case '[':
                // std::string label="pos_"+std::to_string(i);
                labels[i] = "pos_"+std::to_string(i);
                output += "pos_"+std::to_string(i) + ":\n";
                break;
            case ']':
                depth = 1;
                pos = i;
                while (depth > 0){
                    pos--;
                    if (source_code.at(pos) == ']') depth++;
                    if (source_code.at(pos) == '[') depth--;
                }
                output += "    cmp [rsi],byte 0\n";
                output += "    jne " + labels[pos];
                output += "\n";
                break;
            case '.':
                output += "    mov rax,1\n";
                output += "    mov rdi,1\n";
                output += "    mov rdx,1\n";
                output += "    syscall\n";
                break;
            case ',': // not implemented
                break;
            default: break;
        }
    }

    output += END;
    output += "\n";
    output += DATA;

    write(output, ofilename);
  
    std::string cmd = "nasm -f elf64 -o ";
    cmd += std::string(ofilename);
    cmd += std::string(".o ") + std::string(ofilename) + ".s";
    int c = std::system(cmd.c_str()); // no idea lol
    if (c != 0) return c;
    // lol this is so messy
    c = std::system((std::string("ld -o ") + std::string(ofilename) + 
                std::string(" ") + std::string(ofilename)
                +std::string(".o")).c_str());
    ;
    if (c != 0) return c;

    std::system((std::string("rm ") + std::string(ofilename) 
            + std::string(".o ") + std::string(ofilename) + 
            std::string(".s ")).c_str());

    return 0;
}

std::string help_msg(char* prog){
    std::string out = "Usage : ";
    out += prog;
    out += " [options] file\n";
    out += "BRAINFUCK COMPILER\n";

    out += "Options:\n";
    out += "-h --help       Display this information\n";
    out += "-o --output     Name of the compiled output file\n";

    return out;
}

int main(int argc, char** argv){

  
    char *filename;
    int opti;
    std::string ofilename = std::string("a.out");

    /* TODO fix the mess of std::string 
     * i was lazy :pepepray:
     * */

    for (opti = 1; opti< argc; opti++){
        if (std::string(argv[opti]) == std::string("-h") 
                || std::string(argv[opti]) == std::string("--help")) {
            fprintf(stdout, "%s", help_msg(argv[0]).c_str());
            return 0;
        }
        else if (std::string(argv[opti])  == std::string("-o")
                || std::string(argv[opti]) == std::string("--output")) {
            opti++;
            if (opti == argc) {
                fprintf(stderr,
                        "%s: error: missing filename after -o\n", argv[0]);
                return -1;
            }
            ofilename = argv[opti];
        }
        else {
            filename = argv[opti];
        }
    }

    if (!filename) {
        fprintf(stderr,
                        "%s: error: missing filename\n", argv[0]);
        return -1;
    }

    return compile(filename, ofilename);
}
