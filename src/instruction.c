#include "./../include/instruction.h"
#include "./../include/error.h"


Instruction decode(word_t* w, word_t* limit)
{
    if(w >= limit) {
        error(1, __func__, "program memory limit reaches!\n");
    }

    //todo
}
