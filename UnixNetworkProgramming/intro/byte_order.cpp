#include <iostream>
#include <cstdlib>
#define CPU_VENDOR_OS "x86_64-linux-gnu"
int main() {
    typedef union {
        short s;
        char  c[sizeof(short)];
    } byte_order_t;

    byte_order_t un;
    un.s = 0x0102;
    std::cout << CPU_VENDOR_OS << ": ";
    if (sizeof(short) == 2) {
        if (un.c[0] == 0x01 && un.c[1] == 0x02) {
            std::cout << "big-endian\n";
        } else if (un.c[0] == 0x02 && un.c[1] == 0x01) {
            std::cout << "little-endian\n";
        } else {
            std::cout << "unknown\n";
        }
    } else {
        std::cout << "sizeof(short) = " << sizeof(short) << "\n";
    }
    exit(0);
}