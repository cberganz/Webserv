#include <fstream>
#include <string>
#include <iostream>

int main() {
    std::ifstream image("toulouseparis.jpg", std::ios::in | std::ios::binary);
    std::ofstream binary("binary.txt", std::ios::out | std::ios::binary);

    char ch;
    while(!image.eof()) {
        ch = image.get();
        binary.put(ch);
        std::cout << ch;
    }
    return 0;
}