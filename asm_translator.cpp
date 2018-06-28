#include "asm_translator.h"

const char *fore_block = "%include 'handy/handy.inc'\n"
                         "\n"
                         "segment .text\n"
                         "\tglobal _main\n"
                         "\n"
                         "_main:\n"
                         "\tpush\tesi\n"
                         "\tpush\tedi\n"
                         "\tpush\tebp\n\n\n";

const char *end_block = "\n\n\n\tcall\tprint_int\n"
                        "\tpop\tebp\n"
                        "\tpop\tedi\n"
                        "\tpop\tesi\n"
                        "\tmov\teax,\t0\n"
                        "\tret";

const std::string reg_table[] = {"esi", "ebx", "ecx", "edx", "eax", "edi", "ebp"};

std::string translator(const std::string &pseudo_code) {
    std::stringstream ss(pseudo_code);
    std::string tok;
    std::string result;
    int reg1, reg2, reg3, address, num;
    char label_buf[64];

    while (std::getline(ss, tok)) {
        if (tok.back() == ':') {
            result.append(tok + "\n");
        } else {
            const char *ctok = tok.c_str();

            switch (ctok[0]) {
                case 'A':   // ADD
                    sscanf_s(ctok, "ADD Reg#%d, Reg#%d, Reg#%d", &reg1, &reg2, &reg3);
                    result.append("\n\tmov\t" + reg_table[reg1] + ",\t" + reg_table[reg2]);  // Reg#1 = Reg#2
                    result.append("\n\tadd\t" + reg_table[reg1] + ",\t" + reg_table[reg3] + "\n");  // Reg#1 += Reg#3
                    break;
                case 'C':   // CALL
                    break;
                case 'J':
                    if (ctok[4] == 'F') {    // JUMPF
                        sscanf_s(ctok, "JUMPF Reg#%d %s", &reg1, label_buf, 64);
                        result.append("\n\tcmp\t" + reg_table[reg1] + ", 0\n");
                        result.append("\tje\t" + std::string(label_buf) + "\n");
                    } else if (ctok[4] == 'T') {     //JUMPT
                        sscanf_s(ctok, "JUMPT Reg#%d %s", &reg1, label_buf, 64);
                        result.append("\n\tcmp\t" + reg_table[reg1] + ", 0\n");
                        result.append("\tjne\t" + std::string(label_buf) + "\n");
                    } else {        // JUMP
                        sscanf_s(ctok, "JUMPT %s", label_buf, 64);
                        result.append("\n\tjmp\t" + std::string(label_buf) + "\n");
                    }
                    break;
                case 'L':
                    if (ctok[1] == 'D') {  // LD
                        if (tok.find('$') == std::string::npos) {
                            sscanf_s(ctok, "LD Reg#%d, %d", &reg1, &address);
                            result.append("\n\tpush\tebp\n");
                            result.append("\tmov\tebp,\t" + std::to_string(address));
                            result.append("\n\tadd\tebp,\tesp\n");
                            result.append("\tmov\t" + reg_table[reg1] + ",\t[ebp]\n");
                            result.append("\tpop\tebp\n");
                        } else {
                            sscanf_s(ctok, "LD Reg#%d, $%d", &reg1, &num);
                            result.append("\n\tmov\t" + reg_table[reg1] + ",\t" + std::to_string(num) + "\n");
                        }
                    } else {    // LT
                        sscanf_s(ctok, "LT Reg#%d, Reg#%d, Reg#%d", &reg1, &reg2, &reg3);
                        result.append("\n\tmov\t" + reg_table[reg1] + ",\t0\n");
                        result.append("\tcmp\t" + reg_table[reg3] + "\t" + reg_table[reg2]);
                        result.append("\n\tcmov\t" + reg_table[reg1] + ",\t1\n");
                    }
                    break;
                case 'M':
                    if (ctok[1] == 'U') {  // MUL
                        sscanf_s(ctok, "MUL Reg#%d, Reg#%d, Reg#%d", &reg1, &reg2, &reg3);
                        result.append("\n\tpush\teax\n");  // store %eax, gonna be used for multiplication.
                        result.append("\tmov\teax,\t" + reg_table[reg2]);  // %eax = Reg#2
                        result.append("\n\tmul\t" + reg_table[reg3]);  // %eax *= Reg#3
                        result.append("\n\tmov\t" + reg_table[reg1] + ",\teax");  // store the result into reg1
                        result.append("\n\tpop\teax\n");   // restore %eax
                        break;
                    } else {  // MV
                        sscanf_s(ctok, "MV Reg#%d, Reg#%d", &reg1, &reg2);
                        result.append("\n\tmov\t" + reg_table[reg2] + ",\t" + reg_table[reg1]);
                    }
                    break;
                case 'S': // ST
                    sscanf_s(ctok, "ST %d, Reg#%d", &address, &reg1);
                    result.append("\n\tpush\tebp\n");
                    result.append("\tmov\tebp,\t" + std::to_string(address));
                    result.append("\n\tadd\tebp,\tesp\n");
                    result.append("\tmov\t" + std::string("[ebp],\t") + reg_table[reg1]);
                    result.append("\n\tpop\tebp\n");
                    break;
                case 'P':
                    if (ctok[2] == 'S') { // PUSH
                        sscanf_s(ctok, "PUSH Reg#%d", &reg1);
                        result.append("\n\tpush\t" + reg_table[reg1]);
                    } else if (ctok[2] == 'P') {  // POP
                        sscanf_s(ctok, "POP Reg#%d", &reg1);
                        result.append("\n\tpop\t" + reg_table[reg1]);
                    }
                    break;
                default:
                    std::cerr << "Maybe The Pseudo Code is broken, or Translator is broken" << std::endl;

            }
        }
    }

    //std::cout << result << std::endl;

    return fore_block + result + end_block;
}
