#include "../headers/chat.h"
#include "../headers/hash_table.h"
#include <iostream>

Chat::Chat() {
    hash_table_ = new HashTable();
    data_count = 0;
}

Chat::~Chat() {
    for(int i = 0; i < data_count; i++) {
        if(data[i] != nullptr) {
            delete data[i];
        }
    }
    delete hash_table_;
}

void Chat::reg(char _login[], char _pass[]) {
    // Ваш код
    int pass_hash = hash_table_->get_pass_hash(_pass);
    hash_table_->add(_login, pass_hash);
    AuthData* auth_data = new AuthData(_login);
    data[data_count] = auth_data;
    data_count++;
}

bool Chat::login(char _login[], char _pass[]) {
    int pass_hash = hash_table_->get_pass_hash(_pass);
    if(is_user(_login)) {
        return hash_table_->test(pass_hash, _login);
    }
}

Chat::AuthData& Chat::AuthData::operator=(const AuthData& other) {
    strcpy(login_, other.login_);
    return *this;
}

bool Chat::is_user(char login[]) {
    for(int i = 0; i < data_count; i++) {
        if(data[i] != nullptr) {
            if(!strcmp(data[i]->login_, login)) {
                return true;
            }
        }
    }
    return false;
}

void Chat::remove(char _login[], char _pass[]) {
    int pass_hash = hash_table_->get_pass_hash(_pass);
    for(int i = 0; i < data_count; i++) {
        if(!strcmp(data[i]->login_, _login)) {
            delete data[i];
            data[i] = nullptr;
        }
    }
    hash_table_->del(_login, pass_hash);
}