#include "Programs.h"

std::vector<int> Programs::program1() {
    return { 0x2001, 0x2102, 0x2203, 0x2304, 0x2405,
             0x5501, 0x5552, 0x5553, 0x5554,
             0x3500, 0xC000 };
}

std::vector<int> Programs::program2() {
    return { 0x2006, 0x5100, 0x5210, 0x3200, 0xC000 };
}

std::vector<int> Programs::program3() {
    return { 0x200A, 0x3100, 0xC000 };
}

std::vector<int> Programs::program4() {
    return { 0x2003, 0x2105, 0x5201, 0x3200, 0xC000 };
}

std::vector<int> Programs::program5() {
    return { 0x2001, 0x2102, 0x5701, 0x3700, 0xC000 };
}

std::vector<int> Programs::program6() {
    return { 0x2003, 0x2101, 0x5801, 0x3800, 0xC000 };
}

std::vector<int> Programs::program7() {
    return { 0x2006, 0x2103, 0x5901, 0x3900, 0xC000 };
}

std::vector<int> Programs::program8() {
    return { 0x200F, 0x3100, 0xC000 };
}

std::vector<int> Programs::program9() {
    return { 0x2001, 0x2102, 0x5301, 0x3300, 0xC000 };
}

std::vector<int> Programs::program10() {
    return { 0x2005, 0x210A, 0x5401, 0x3400, 0xC000 };
}

std::vector<std::vector<int>> Programs::allPrograms() {
    return { program1(), program2(), program3(), program4(), program5(),
             program6(), program7(), program8(), program9(), program10() };
}
