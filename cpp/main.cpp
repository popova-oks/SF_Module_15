#include <iostream>
#include <string.h>
#include "../headers/chat.h"
#include "../headers/hash_table.h"

int main () {
    Chat *chat = new Chat();

    chat->reg ((char*)"user1", (char*)"123456");
    chat->reg ((char*)"user2", (char*)"234567");
    chat->reg ((char*)"user3", (char*)"345678");
    chat->reg ((char*)"user4", (char*)"456789");
    chat->reg ((char*)"user5", (char*)"567891");

    chat->print();

    std::cout << chat->login((char*)"user2", (char*)"23456") << std::endl;

    chat->remove ((char*)"user2", (char*)"234567");
    chat->print();

    std::cout << chat->login((char*)"user2", (char*)"23456") << std::endl;

    delete chat;
    return 0;
}