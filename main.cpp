#include"mips.h"

int main(){

    MIPS mips;
    mips.file_convert("assembly.txt","machine.txt");
    cout<<mips.convert("j 10000");
    return 0;
}
