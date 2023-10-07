#include "../headers/hash_table.h"

Chat::HashTable::HashTable() {
    count = 0;
    mem_size = 5;
    array = new Pair[mem_size];
    for (int i = 0; i < mem_size; i++) {
        array[i].login_[0] = '\0';
        array[i].pass_hash_ = -1;
        array[i].status_ = enPairStatus::free;
    }
}

Chat::HashTable::~HashTable () {
    delete[] array;
    array = nullptr;
}

// хэш функция, метод умножения
int Chat::HashTable::hash_func(ARRAY arr, int offset) {
    // вычисляем индекс
    int sum = 0;
    int i = 0;
    const double A = 0.7;
    for(; i < strlen(arr); i++) {
        sum += arr[i];
    }
    //sum = int((A*sum - int (A*sum)) + offset) % mem_size;
    sum = (sum % mem_size + offset * offset) % mem_size;
    return sum;
}

int Chat::HashTable::add(ARRAY login, int pass_hash) {
    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for(; i < mem_size; i++) {
        index = hash_func(login, i);
        if(array[index].status_ == enPairStatus::free) {
            // найдена пустая ячейка, занимаем ее
            array[index].status_ == enPairStatus::engaged;
            break;
        }
    }
    if(i < mem_size) {
        // кладем в свободную ячейку пару
        array[index] = Pair(login, pass_hash);
        count++;
        return array[index].pass_hash_;                           //FIX ME!!!
    }
    // все перебрали, нет места
    else if(i >= mem_size) {
        resize();
        return add(login, pass_hash);          //FIX ME!!!
    }
}

void Chat::HashTable::resize() {    
    Pair* save_arr = array;                     // Сохраняем указатель на старый массив
    int oldSize = mem_size;

    mem_size *= 2;                              // Увеличиваем размер в два раза
    count = 0;                                  // Обнуляем количество элементов
    array = new Pair[mem_size];                 // Выделяем новую память
    for (int i = 0; i < mem_size; i++) {
        array[i].pass_hash_ = -1;
        array[i].login_[0] = '\0';
        array[i].status_ = enPairStatus::free;
    }

    for (int i = 0; i < oldSize; i++) {
        // Перебираем все старые цепочки
        Pair current = save_arr[i];
        // Пересчитываем хеши и добавляем в новый массив
        if (current.status_ == enPairStatus::engaged) {
            add(current.login_, current.pass_hash_);
        }
    }
    // Чистим за собой
    delete[] save_arr;
}

void Chat::HashTable::del(ARRAY login, int pass_hash) {
    Pair *curr_pair = findPair(login, pass_hash);
    if (curr_pair != nullptr) {
        curr_pair->login_[0] = '\0';
        curr_pair->pass_hash_ = -1;
        curr_pair->status_ = enPairStatus::deleted;
    }
}

bool Chat::HashTable::test(int pass_hash, ARRAY login)
{
    Pair *curr_pair = findPair(login, pass_hash);
    if (curr_pair != nullptr) {
        return true;
    }
    return false;
}

Chat::HashTable::Pair* Chat::HashTable::findPair(ARRAY login, int pass_hash) {
    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for(; i < mem_size; i++) {
        index = hash_func(login, i);
        if(array[index].status_ == enPairStatus::free) {
            // попали на пустую ячейку значит элемента нет
            return nullptr;
        } else if(array[index].status_ == enPairStatus::engaged 
            && !strcmp(array[index].login_, login)
            && array[index].pass_hash_ == pass_hash) {
            return &array[index];                                           //FIX ME!!!
        }
    }
    return nullptr;
}

int Chat::HashTable::get_pass_hash(ARRAY arr) { 
    return hash_func(arr, 0); 
}