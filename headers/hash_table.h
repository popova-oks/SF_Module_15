#ifndef HASHTABLE_2_H
#define HASHTABLE_2_H

#include "chat.h"
#include <string.h>

typedef char ARRAY [LENGTH]; // псевдоним массива char [NAMELENGTH]

class Chat::HashTable { // хеш-таблица
  private:
    struct Pair;
    
    
  public:
    int count;

    int mem_size;
    Pair* array; // массив пар          // убрать в private

    HashTable();
    ~HashTable();
    int add(ARRAY login, int pass_hash);
    void del(ARRAY login, int pass_hash);
    int get_pass_hash(ARRAY arr);
    bool test(int pass_hash, ARRAY login);

  private:
    enum enPairStatus { //перечисление
        free,           //свободен = 0
        engaged,        //занят = 1
        deleted         //удален = 2
    };

    struct Pair { // пара ключ-значение
        Pair()
            : // конструктор по умолчанию
              login_(""), pass_hash_(-1), status_(enPairStatus::free) {}
        Pair(ARRAY login, int pass_hash)
            : // конструктор с параметрами
              pass_hash_(pass_hash), status_(enPairStatus::engaged) {
            strcpy(login_, login);
        }
        Pair& operator=(const Pair& other) { // оператор присваивания
            pass_hash_ = other.pass_hash_;
            strcpy(login_, other.login_);
            status_ = other.status_;

            return *this;
        }
        ARRAY login_;         // имя фрукта (ключ)
        int pass_hash_;       // количество фрукта (значение)
        enPairStatus status_; // состояние ячейки
    };

    int hash_func(ARRAY arr, int offset);
    Pair* findPair(ARRAY login, int pass_hash);
    void resize();
};

#endif // HASHTABLE_2_H