#ifndef CHAT_H
#define CHAT_H
#include "string.h"

#define SIZE 100  // максимальный размер чата
#define LENGTH 10 // зафиксируем длину логина и пароля

class Chat {
  private:
    class HashTable;
    struct AuthData;

    AuthData* data[SIZE];
    HashTable* hash_table_;
    int data_count;

  public:
    Chat();
    ~Chat();
    void reg(char _login[], char _pass[]);
    bool login(char _login[], char _pass[]);
    void remove(char _login[], char _pass[]);
    void print();

  private:
    struct AuthData {
        char login_[LENGTH]; //имя логина
        AuthData() : login_("\0") {}
        ~AuthData() {
            if (this != nullptr) {
                login_[0] = '\0';
            }
        }
        //конструктор с параметрами передаем логин и пароль
        AuthData(char _login[]) {
            strcpy(login_, _login); //копируем _login в login
        }
        AuthData& operator=(const AuthData& other);
    };

    bool is_user (char login[]);
};

#endif // CHAT_H