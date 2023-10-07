cmake_minimum_required(VERSION 3.22.1) # Укажите версию CMake

project(Module_15) # Замените "MyProject" на имя вашего проекта

# Укажите исходные файлы вашего проекта
set(SOURCES
    cpp/main.cpp
    cpp/chat.cpp
    cpp/hash_table.cpp
)

# Добавьте исполняемый файл
add_executable(module_15 ${SOURCES})
target_compile_options(module_15 PRIVATE -g -O0)


# Укажите дополнительные настройки и библиотеки, если необходимо
# target_link_libraries(my_app your_library)

# Укажите директории для поиска заголовочных файлов, если необходимо
# target_include_directories(my_app PUBLIC include)

# Установите параметры компиляции, если необходимо
# target_compile_options(my_app PRIVATE -Wall -Wextra)