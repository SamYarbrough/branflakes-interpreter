#include <iostream>
#include <string>
#include <fstream>

void branflakes(char prgm[], int prgm_size, char in_stream[], int in_stream_size) {
    int instruction_ptr = 0;
    int data_ptr = 0;
    char data[32768] {0};
    int in_stream_ptr = 0;

    while (instruction_ptr < prgm_size - 1) {
        char current_instruction = prgm[instruction_ptr];

        switch (current_instruction) {
            case '>':
                data_ptr++;
                instruction_ptr++;
                break;
            case '<':
                data_ptr--;
                instruction_ptr++;
                break;
            case '+':
                data[data_ptr]++;
                instruction_ptr++;
                break;
            case '-':
                data[data_ptr]--;
                instruction_ptr++;
                break;
            case '.':
                std::cout << data[data_ptr];
                instruction_ptr++;
                break;
            case ',':
                data[data_ptr] = in_stream[in_stream_ptr];
                in_stream_ptr++;
                instruction_ptr++;
                break;
            case '[':
                if (data[data_ptr] == 0) {
                    int temp = instruction_ptr;
                    int match_count = 0;
                    while (true) {
                        temp++;
                        char temp_instruction = prgm[temp];
                        if (temp_instruction == '[') { match_count++; }
                        else if (temp_instruction == ']') {
                            if (match_count == 0) break;
                            match_count--;
                        }
                    }
                    instruction_ptr = temp;
                } else {
                    instruction_ptr++;
                }
                break;
            case ']':
                if (data[data_ptr] != 0) {
                    int temp = instruction_ptr;
                    int match_count = 0;
                    while (true) {
                        temp--;
                        char temp_instruction = prgm[temp];
                        if (temp_instruction == ']') { match_count++; }
                        else if (temp_instruction == '[') {
                            if (match_count == 0) break;
                            match_count--;
                        }
                    }
                    instruction_ptr = temp;
                } else {
                    instruction_ptr++;
                }
                break;
            default:
                break;
        }
    }
}

int main(int argc, char* argv[]) {
    const std::string valid = "+-<>[],.";

    //select bf file, hello world by default
    std::string filename = "programs/helloworld.bf";
    if (argc > 1) {
        filename = argv[1];
    }

    std::ifstream raw_file;
    raw_file.open(filename);

    std::string raw_prgm = "";
    std::string file_line;

    while (std::getline(raw_file, file_line)) {
        for (int ind = 0; ind < file_line.length(); ind++) {
            char curr = file_line[ind];
            if (valid.find(curr)<valid.length()) {
                raw_prgm += curr;
            }
        }
    }

    raw_file.close();

    char prgm[raw_prgm.length() + 1];
    for (int ind = 0; ind < raw_prgm.length(); ind++) {
        prgm[ind] = raw_prgm[ind];
    }
    prgm[raw_prgm.length()] = '\0';


    //char prgm[] = "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.";
    int prgm_size = sizeof(prgm)/sizeof(prgm[0]);

    char in_stream[] = "abcdef";
    int in_stream_size = sizeof(in_stream)/sizeof(in_stream[0]);

    std::cout << "branflakes program: \n";
    std::cout << prgm << "\n";
    std::cout << "(" << (prgm_size-1) << " chars)\n";
    std::cout << "in stream: \n";
    std::cout << in_stream << "\n";
    std::cout << "(" << (in_stream_size-1) << " chars)\n\n";
    std::cout << "branflakes out stream: \n";

    branflakes(prgm, prgm_size, in_stream, in_stream_size);
    return 0;
}