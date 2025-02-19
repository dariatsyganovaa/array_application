#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <locale.h> 
#include <windows.h>
#include <conio.h>

#include "dmassive.h"  
#include "sort.h"  

#define MAIN_MENU_SIZE 8
#define INIT_MENU_SIZE 4
#define INSERT_MENU_SIZE 4
#define FOUND_MENU_SIZE 5
#define ERASE_MENU_SIZE 4
#define REPLACE_MENU_SIZE 4
#define SORT_MENU_SIZE 5
#define MODE_MENU_SIZE 3

#define ONE_ELEM_MODE 1
#define SEVERAL_ELEM_MODE 2


void start_main_menu(int** mass, int* size, int* deleted_count);
int start_init_menu(int** mass, int* size);
int start_insert_menu(int** mass, int* size);
int start_found_menu(int** mass, int* size); 
int start_erase_menu(int** mass, int* size, int* deleted_count);
int start_replace_menu(int** mass, int* size); 
int start_experiment_menu();
int start_one_experiment_menu();
int start_all_experiment_menu();
void show_array(int* mass, int size);

void get_user_input(int* user, int unit_count);
void start_mode_menu(int* mass, int size, int* mode);
void show_main_menu();
void show_init_menu();
void show_insert_menu();
void show_erase_menu();
void show_found_menu();
void show_replace_menu();
void show_mode_menu();
void show_start_experiment_menu();
void show_success_message(int* mass, int size); 
void show_user_init_message();

void start_replace_by_index(int* mass, int size);
void start_replace_by_value(int* mass, int size);
void start_replace_by_indexes(int* mass, int size, int* new_values);
void count_erase_elems(int* count);
void show_found_result(int* mass, int size, int* found);  
void get_new_size(int* size);
void get_value(int* value);
void get_values(int** values, int* count);
void get_bounds_for_rand_generation(int* min, int* max);
void get_pos(int* pos, int size);

int main() {
    setlocale(LC_ALL, "rus");
    srand(time(0));

    int* mass = NULL, size = 0, deleted_count = 0; 

    start_main_menu(&mass, &size, deleted_count);

    return 0;
}

void start_main_menu(int** mass, int* size, int* deleted_count) {
    int user_input, is_Exit = 0;
    while (1) {
        system("cls");
        show_array(*mass, *size);
        show_main_menu();
        get_user_input(&user_input, MAIN_MENU_SIZE);
        switch (user_input) {
        case 1:
            is_Exit = start_init_menu(mass, size);
            break;
        case 2:
            is_Exit = start_insert_menu(mass, size);
            break;
        case 3:
            is_Exit = start_found_menu(mass, size);
            break;
        case 4:
            is_Exit = start_erase_menu(mass, size, &deleted_count);
            break;
        case 5:
            is_Exit = start_replace_menu(mass, size);
            break;
        case 6:
            shuffle(*mass, *size);
            break;
        case 7:
            is_Exit = start_sort_menu(mass, size);
            break;
        case 8:
            is_Exit = start_experiment_menu(); 
            break;
        case 0:
            is_Exit = 1;
            break;
        }
        if (is_Exit) break;
    }
    clear_memory(*mass); 
}

void get_user_input(int* user, int unit_count) {
    printf("Ваш выбор: ");
    while (1) {
        scanf_s("%d", user);
        if ((*user >= 0) && (*user <= unit_count)) {
            break;
        }
        printf("Некорректный ввод, попробуй снова: ");
    }
}
int start_init_menu(int** mass, int* size) {
    int user_input;
    int isGeneration;
    int isExit = 0, isBack = 0;
    int min_val, max_val;

    system("cls"); 
    show_array(*mass, *size);
    show_init_menu();
    get_user_input(&user_input, INIT_MENU_SIZE);

    if (user_input != 0 && user_input != INIT_MENU_SIZE) {
        get_new_size(size);
        clear_memory(*mass);
        *mass = set_memory(*size);
    }
    switch (user_input) {
    case 1:
        default_init(*mass, *size);
        break;
    case 2:
        show_user_init_message();
        user_init(*mass, *size);
        break;
    case 3:
        get_bounds_for_rand_generation(&min_val, &max_val);
        rand_init(*mass, *size, min_val, max_val);
        show_array(*mass, *size);
        while (1) {
            printf("Перегенерировать? y/n \n");
            isGeneration = _getch();
            if (isGeneration == 'n') break;
            if (isGeneration == 'y') { shuffle(*mass, *size);  show_array(*mass, *size); continue; }
        }
        break;
    case 4:
        isBack = 1;
        break;
    case 0:
        isExit = 1;
        break;
    }
    show_success_message(*mass, *size);
    return isExit;
}
void start_mode_menu(int* mass, int size, int* mode) {
    int isExit = 0;
    show_array(mass, size);
    show_mode_menu();
    get_user_input(mode, MODE_MENU_SIZE);
}
int start_insert_menu(int** mass, int* size) {
    int user_input, mode;
    int isExit = 0, isBack = 0;
    int new_value = 0, count = 0, pos = 0;
    int* new_values = NULL;
    
    while (1) {
        system("cls");
        start_mode_menu(*mass, *size, &mode);
        if (mode == MODE_MENU_SIZE) break;
        if (mode == 0) { isExit = 1; break; }

        show_insert_menu();
        get_user_input(&user_input, INSERT_MENU_SIZE); 

        if (user_input != 0 && user_input != INSERT_MENU_SIZE) {
            if (mode == ONE_ELEM_MODE) {
                get_value(&new_value);  
                count = 1; 
            }
            else if (mode == SEVERAL_ELEM_MODE) { 
                get_values(&new_values, &count); 
            }
            *mass = reset_memory(*mass, *size, *size + count);
            *size += count; 
        }

        switch (user_input) {
        case 1:
            if (mode == ONE_ELEM_MODE) { push_front_elem(*mass, *size, new_value); }
            else if (mode == SEVERAL_ELEM_MODE) { push_front_elems(*mass, *size, new_values, count); } 
            break;
        case 2:
            if (mode == ONE_ELEM_MODE) { push_back_elem(*mass, *size, new_value); }
            else if (mode == SEVERAL_ELEM_MODE) { push_back_elems(*mass, *size, new_values, count); } 
            break;
        case 3:
            get_pos(&pos, *size);
            if (mode == ONE_ELEM_MODE) { insert_elem(*mass, *size, new_value, pos - 1); } // чтобы совпадала нумерация
            else if (mode == SEVERAL_ELEM_MODE) { insert_elems(*mass, *size, pos - 1, new_values, count);}
            break;
        case 4:
            isBack = 1;
            break;
        case 0:
            isExit = 1;
            break;
        }
        if (isBack) continue;
        if (isExit) break; 
        show_success_message(*mass, *size);
    }
    free(new_values); 
    return isExit;
}
int start_found_menu(int** mass, int* size) {
    int user_input;
    int i;
    int value = NULL, *values = NULL, count = 0, *found = NULL;
    int isExit = 0, isBack = 0;

    while (1) {
        system("cls"); 
        show_array(*mass, *size); 
        show_found_menu();
        get_user_input(&user_input, FOUND_MENU_SIZE);
        int* found = (int*)malloc((*size + count) * sizeof(int)); 
        switch (user_input) {
        case 1:
            get_value(&value);
            count = 1;
            found_first_elem(*mass, *size, value, found);
            show_found_result(*mass, *size, found);
            break;
        case 2:
            get_value(&value);
            count = 1;
            found_last_elem(*mass, *size, value, found);
            show_found_result(*mass, *size, found);
            break;
        case 3: 
            get_value(&value);
            count = 1;
            found_elem(*mass, *size, value, found); 
            show_found_result(*mass, *size, found);     
            break;
        case 4:
            get_values(&values, &count);
            found_elems(*mass, *size, values, count, found);
            show_found_result(*mass, *size, found); 
            break;
        case 5:
            isBack = 1;
            break;
        case 0:
            isExit = 1;
            break;
        }
        if (isBack || isExit) break;
    }
    free(values);
    return isExit;
}
int start_erase_menu(int** mass, int* size, int* deleted_count) {
    int user_input, mode;
    int isExit = 0, isBack = 0;
    int new_value = NULL, *new_values = NULL, count = NULL, pos = NULL;

    while (1) {
        system("cls");
        start_mode_menu(*mass, *size, &mode);
        if (mode == MODE_MENU_SIZE) break;
        if (mode == 0) { isExit = 1; break; }

        show_erase_menu();
        get_user_input(&user_input, ERASE_MENU_SIZE);

        switch (user_input) {
        case 1:
            if (mode == ONE_ELEM_MODE) {
                count = 1;
                pop_front_elem(*mass, *size);
            }
            else if (mode == SEVERAL_ELEM_MODE) {
                count_erase_elems(&count); 
                pop_front_elems(*mass, *size, count);
            }
            break;
        case 2:
            if (mode == ONE_ELEM_MODE) {
                count = 1; 
                pop_back_elem(*mass, *size);
            }
            else if (mode == SEVERAL_ELEM_MODE) {
                count_erase_elems(&count); 
                pop_back_elems(*mass, *size, count);
            }
            break;
        case 3:
            get_pos(&pos, *size); 
            if (mode == ONE_ELEM_MODE) {
                count = 1; 
                erase_elem(*mass, *size, pos);
            }
            else if (mode == SEVERAL_ELEM_MODE) {
                count_erase_elems(&count); 
                erase_elems(*mass, *size, pos, count); 
            }
            break;
        case 4:
            isBack = 1;
            break;
        case 0:
            isExit = 1;
            break;
        }
        if (isBack || isExit) break;
        (*deleted_count) += count;
        *mass = reset_memory_for_delete(*mass, size, *size - count, deleted_count);
        show_success_message(*mass, *size);
    }
    return isExit;
}
int start_replace_menu(int** mass, int* size) {
    int user_input;
    int value = NULL, * indexes = NULL, count = 0, pos = NULL, index = NULL, *new_values = NULL, new_value = 0;
    int isExit = 0, isBack = 0;

    while (1) {
        system("cls");
        show_array(*mass, *size);  
        show_replace_menu();
        get_user_input(&user_input, REPLACE_MENU_SIZE); 
        switch (user_input) { 
        case 1:
            start_replace_by_value(*mass, *size);  
            break;
        case 2:
            start_replace_by_index(*mass, *size); 
            break;
        case 3:
            start_replace_by_indexes(*mass, *size, &new_values); 
            break;
        case 4:
            isBack = 1;
            break;
        case 0:
            isExit = 1;
            break;
        }
        if (isBack || isExit) break; 
        show_success_message(*mass, *size); 
    }
    return isExit;
}
int start_sort_menu(int** mass, int* size) {
    int user_input;
    int isExit = 0, isBack = 0;
    while (1) {
        system("cls");
        show_array(*mass, *size);
        show_sort_menu();
        get_user_input(&user_input, SORT_MENU_SIZE);

        void(*sort_method)(int*, int, int*, int*) = NULL;

        switch (user_input) {
        case 1:
            sort_method = bubble_sort;
            break;
        case 2:
            sort_method = optimized_bubble_sort;
            break;
        case 3:
            sort_method = hoara_sort;
            break;
        case 4:
            sort_method = shell_sort;
            break;
        case 5:
            isBack = 1;
            break;
        case 0:
            isExit = 1;
            break;
        }
        if (isBack || isExit) break; 
        unsigned long long swps_count = 0, cmps_count = 0; 
        int time; 
        start_sort(sort_method, *mass, *size, &time, &swps_count, &cmps_count); 
        show_array(*mass, *size); 
        printf("Время сортировки: %d ms\n", time); 
        printf("Количество перестановок: %llu\n", swps_count); 
        printf("Количество сравнений: %llu\n", cmps_count); 
        system("pause"); 
        system("cls");
    }
    return isExit;
}
int start_experiment_menu() {
    int user_input;
    int isExit = 0, isBack = 0;
    while (1) {
        system("cls");
        show_start_experiment_menu();
        get_user_input(&user_input, MODE_MENU_SIZE); 

        switch (user_input) {
        case 1:
            isExit = start_one_experiment_menu();
            break;
        case 2:
            isExit = start_all_experiment_menu();
            break;
        case 3:
            isBack = 1;
            break;
        case 0:
            isExit = 1;
            break;
        }
        if (isBack || isExit) break;
    }
    return isExit;
}
int start_one_experiment_menu() {
    int user_input;
    int isExit = 0, isBack = 0;
    while (1) {
        system("cls");
        show_sort_menu();
        get_user_input(&user_input, SORT_MENU_SIZE);

        void(*sort_method)(int*, int, int*, int*) = NULL;

        switch (user_input) {
        case 1:
            sort_method = bubble_sort;
            break;
        case 2:
            sort_method = optimized_bubble_sort;
            break;
        case 3:
            sort_method = hoara_sort;
            break;
        case 4:
            sort_method = shell_sort;
            break;
        case 5:
            isBack = 1;
            break;
        case 0:
            isExit = 1;
            break;
        }
        if (isBack || isExit) break;
        int min_size, step_of_sizes, count_of_experiments;

        printf("Введите стартовый размер массива (>=10): ");
        scanf_s("%d", &min_size);
        printf("Введите шаг эксперимента (домножающий множитель для размера): ");
        scanf_s("%d", &step_of_sizes);
        printf("Введите количество экспериментов: ");
        scanf_s("%d", &count_of_experiments);

        start_experiment(sort_method, min_size, step_of_sizes, count_of_experiments);
    }
    return isExit;
}
int start_all_experiment_menu() {
    int user_input;
    int isExit = 0, isBack = 0;

    system("cls");
    int min_size, step_of_sizes, count_of_experiments;

    printf("Введите стартовый размер массива (>=10): ");
    scanf_s("%d", &min_size);
    printf("Введите шаг эксперимента (домножающий множитель для размера): ");
    scanf_s("%d", &step_of_sizes);
    printf("Введите количество экспериментов: ");
    scanf_s("%d", &count_of_experiments);

    start_sort_experiments(min_size, step_of_sizes, count_of_experiments);

    return isExit;
}
void show_found_result(int* mass, int size, int* found) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    printf("Найдено %d совпадений на следующих позициях: \n{ ", found[0]);
    for (int i = 1; i <= found[0]; i++) { 
        printf("%d", found[i] + 1); 
        if (i < found[0]) { 
            printf(", "); 
        }
    }
    printf(" }\n");

    if (found[0] != 0) {
        printf("Ваш массив (найденные элементы выделены красным цветом): \n");
        for (int i = 0, j = 1; i < size; i++) {
            if (j <= found[0] && i == found[j]) {
                SetConsoleTextAttribute(console, 0 * 16 + 4);
                printf("%d", mass[i]);
                j++;
            }
            else {
                SetConsoleTextAttribute(console, 0 * 16 + 7);
                printf("%d", mass[i]);
            }
            SetConsoleTextAttribute(console, 0 * 16 + 7);
            if (i != size - 1) printf(", ");
        }
        printf("\n");
    }
    system("pause");
    system("cls");
}
void start_replace_by_index(int* mass, int size) {
    int index, new_value;

    printf("Введите индекс заменяемого элемента: ");
    while (1) {
        scanf_s("%d", &index);
        if (index >= 0 && index < size) break;
        printf("Некорректный ввод, попробуйте снова: ");
    }
    printf("Введите новое значение: ");
    scanf_s("%d", &new_value);
    replace_by_index(mass, size, index, new_value);
}
void start_replace_by_value(int* mass, int size) {
    int value, new_value;

    printf("Введите значение заменяемого элемента: ");
    while (1) {
        scanf_s("%d", &value);
        if (value >= 0 && value < size) break;
        printf("Некорректный ввод, попробуйте снова: ");
    }
    printf("Введите новое значение: ");
    scanf_s("%d", &new_value);
    replace_by_value(mass, size, value, new_value);
}
void start_replace_by_indexes(int* mass, int size, int* new_values) {
    int* indexes = NULL, count = NULL;

    printf("Введите количество заменяемых элементов: ");
    while (1) {
        scanf_s("%d", &count);
        if (count > 0) break;
        printf("Некорректный ввод, попробуйте снова: ");
    }

    indexes = (int*)malloc(sizeof(int) * (count));
    printf("Введите индексы заменяемых элементов: ");
    for (int i = 0; i < count; i++) {
        scanf_s("%d", &(indexes)[i]);
    }

    new_values = (int*)malloc(sizeof(int) * (count));
    printf("Введите новые значения (через пробел): ");
    for (int i = 0; i < count; i++) {
        scanf_s("%d", &(new_values)[i]); 
    }

    replace_by_indexes(mass, size, indexes, count, new_values);
}
void show_user_init_message() {
    printf("Введите элементы массива (через пробел): ");
}
void get_bounds_for_rand_generation(int* min, int* max) {
    printf("Введите минимум и максимум для генерируемых значений (через пробел): ");
    while (1) {
        scanf_s("%d %d", min, max);
        if (*min < *max) {
            break;
        }
        printf("Некорректный ввод, проверьте порядок аргументов и попробуйте снова: ");
    }
}
void get_new_size(int* size) {
    printf("Введите размер массива: ");
    while (1) {
        scanf_s("%d", size);
        if (*size > 0) {
            break;
        }
        printf("Некорректный ввод, попробуйте снова: ");
    }
}
void get_value(int* value) {
    printf("Введите элемент: ");
    scanf_s("%d", value);  
}
void get_values(int** values, int* count) {
    if (*values != NULL) {
        free(*values);
    }
    printf("Введите количество элементов: ");
    while (1) {
        scanf_s("%d", count);
        if (*count > 0) break;
        printf("Некорректный ввод, попробуйте снова: ");
    }
    *values = (int*)malloc(sizeof(int) * (*count));
    printf("Введите элементы (через пробел): ");
    for (int i = 0; i < *count; i++) {
        scanf_s("%d", &(*values)[i]);
    }
}
void count_erase_elems(int* count) {
    printf("Введите количество элементов: ");
    scanf_s("%d", count);
}
void get_pos(int* pos, int size) {
    printf("Введите позицию: ");
    while (1) {
        scanf_s("%d", pos);
        if (*pos >= 0 && *pos < size) {
            break;
        }
        printf("Некорректный ввод, попробуйте снова: ");
    }
}
void show_array(int* mass, int size) {
    printf("Ваш массив: { ");
    print(mass, size, ',');
    printf(" }\n");
}
void show_success_message(int* mass, int size) {
    printf("Успех! Итоговый массив: { ");
    print(mass, size, ',');
    printf(" } \n");
    system("pause"); 
    system("cls"); 
}
void show_main_menu() {
    printf("ГЛАВНОЕ МЕНЮ\n\n");
    printf("\t1. Создать массив \n");
    printf("\t2. Вставка \n");
    printf("\t3. Поиск \n");
    printf("\t4. Удаление \n");
    printf("\t5. Замена \n");
    printf("\t6. Перемешать \n");
    printf("\t7. Отсортировать \n");
    printf("\t8. Провести эксперимент \n");
    printf("\t0. Выход \n\n");
}
void show_init_menu() {
    printf("ВЫБОР СПОСОБА ЗАПОЛНЕНИЯ\n\n");
    printf("\t1. Тривиальное заполнение \n");
    printf("\t2. Ручной ввод \n");
    printf("\t3. Случайное заполнение \n");
    printf("\t4. Назад \n");
    printf("\t0. Выход \n\n");
}
void show_insert_menu() {
    printf("ВЫБОР СПОСОБА ВСТАВКИ\n\n");
    printf("\t1. В начало массива \n");
    printf("\t2. В конец массива \n");
    printf("\t3. В середину массива \n");
    printf("\t4. Назад \n");
    printf("\t0. Выход \n\n");
}
void show_erase_menu() {
    printf("ВЫБОР СПОСОБА УДАЛЕНИЯ\n\n");
    printf("\t1. Первый элемент массива \n");
    printf("\t2. Последний элемент массива \n");
    printf("\t3. Заданный элемент массива \n");
    printf("\t4. Назад \n");
    printf("\t0. Выход \n\n");
}
void show_found_menu() {
    printf("ВЫБОР СПОСОБА ПОИСКА\n\n");
    printf("\t1. Первое вхождение \n");
    printf("\t2. Последнее вхождение \n");
    printf("\t3. Все вхождения \n");
    printf("\t4. Все вхождения нескольких элементов\n");
    printf("\t5. Назад\n");
    printf("\t0. Выход\n\n");
}
void show_replace_menu() {
    printf("ВЫБОР СПОСОБА ЗАМЕНЫ\n\n");
    printf("\t1. По значению \n");
    printf("\t2. По индексу \n");
    printf("\t3. По индексам \n");
    printf("\t4. Назад \n");
    printf("\t0. Выход \n\n");
}
void show_sort_menu() {
    printf("ВЫБОР СПОСОБА СОРТИРОВКИ\n\n");
    printf("\t1. Пузырьковая \n");
    printf("\t2. Пузырьковая (модифицированная) \n");
    printf("\t3. Хоара \n");
    printf("\t4. Шелла (последовательность Шелла) \n");
    printf("\t5. Назад \n");
    printf("\t0. Выход \n\n");
}
void show_start_experiment_menu() {
    printf("ВЫБОР РЕЖИМА РАБОТЫ\n\n");
    printf("\t1. Один эксперимент \n");
    printf("\t2. Несколько экспериментов \n");
    printf("\t3. Назад \n");
    printf("\t0. Выход \n\n");
}
void show_mode_menu() {
    printf("ВЫБОР РЕЖИМА РАБОТЫ\n\n");
    printf("\t1. Один элемент \n");
    printf("\t2. Несколько элементов \n");
    printf("\t3. Назад \n");
    printf("\t0. Выход \n\n");
}