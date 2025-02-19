//выбор нескольких опорных элементов для хоара (первый, последний, рандомный, из интернета)
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
#include <time.h> 
#include <locale.h>
#include <Windows.h>
#include <string.h>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"
#include "sort.h"  

void swap(int* first_num, int* second_num) {
	int tmp = *first_num;
	*first_num = *second_num;
	*second_num = tmp;
}
void shuffle(int* mass, int size) {
	for (int i = 0; i < size - 1; i++) {
		int rand_i = rand() % size;
		swap(&mass[i], &mass[rand_i]);
	}
}
void start_sort(void(*sort)(int*, int, unsigned long long*, unsigned long long*), int* mass, int size, int* time, unsigned long long* swps, unsigned long long* cmps) {
	printf("Сортировка началась...\n");
	clock_t start = clock();
	sort(mass, size, swps, cmps);
	clock_t end = clock();
	*time = (int)(end - start) / (CLOCKS_PER_SEC / 1000);
	printf("Сортировка закончилась...\n");
}
void bubble_sort(int* mass, int size, unsigned long long* swps, unsigned long long* cmps) { 
	*swps = 0; *cmps = 0; 
	for (int i = 0; i < size; i++) { 
		for (int j = 0; j < size - 1; j++) { 
			(*cmps)++; 
			if (mass[j] > mass[j + 1]) {
				swap(&mass[j], &mass[j + 1]);
				(*swps)++;
			}
		}
	}
}
void optimized_bubble_sort(int* mass, int size, unsigned long long* swps, unsigned long long* cmps){
	*swps = 0; *cmps = 0;
	for (int i = size - 1; i > 0; i--) {
		int isSorted = 1;
		for (int j = 0; j < i; j++) {
			(*cmps)++;
			if (mass[j] > mass[j + 1]) {
				(*swps)++;
				swap(&mass[j], &mass[j + 1]);
				isSorted = 0;
			}
		}
		if (isSorted) break;
	}
}
void hoara_sort_rec(int* mass, int left, int right, unsigned long long* swps, unsigned long long* cmps) {
	if (left < right) {
		int l = left;
		int r = right;

		// Используем медиану для выбора базового значения
		int base_value = mass[(left + right) / 2];

		while (l <= r) {
			while (mass[l] < base_value) {
				l++;
				(*cmps)++;
			}
			while (mass[r] > base_value) {
				r--;
				(*cmps)++;
			}

			if (l <= r) {
				// Размена элементов
				(*swps)++;
				swap(&mass[l], &mass[r]);
				l++;
				r--;
			}
		}

		// Рекурсивно сортируем подмассивы
		if (left < r) {
			hoara_sort_rec(mass, left, r, swps, cmps);
		}
		if (l < right) {
			hoara_sort_rec(mass, l, right, swps, cmps);
		}
	}
}
void hoara_sort(int* mass, int size, unsigned long long* swps, unsigned long long* cmps) {
	hoara_sort_rec(mass, 0, size - 1, swps, cmps);
}
void shell_sort(int* mass, int size, unsigned long long* swps, unsigned long long* cmps) {
	int i, j, step;
	int tmp;

	// Инициализация счетчиков
	*swps = 0;
	*cmps = 0;

	// Начинаем с интервала, равного половине размера массива
	for (step = size / 2; step > 0; step /= 2) {
		// Сортировка вставками для текущего интервала
		for (i = step; i < size; i++) {
			tmp = mass[i];
			for (j = i; j >= step; j -= step) {
				(*cmps)++; // Увеличиваем счетчик сравнений
				if (tmp < mass[j - step]) {
					mass[j] = mass[j - step];
					(*swps)++; // Увеличиваем счетчик обменов
				}
				else {
					break; // Если порядок правильный, выходим из цикла
				}
			}
			mass[j] = tmp;
			if (j != i) {
				(*swps)++; // Увеличиваем счетчик обменов, если произошел сдвиг
			}
		}
	}
}
void show_sort_result(int* mass, int size, int time, unsigned long long swps_count, unsigned long long cmps_count) {
	show_array(*mass, size);
	printf("Время сортировки: %d ms\n", time);
	printf("Количество перестановок: %llu\n", swps_count);
	printf("Количество сравнений: %llu\n", cmps_count);
}
void generate_array(int* array, int size) {
	for (int i = 0; i < size; i++) {
		array[i] = rand() % 100;
	}
}
int* copy_mass(int* mass, int size) {
	int* copy = (int*)malloc(sizeof(int) * size);

	for (int i = 0; i < size; i++) {
		copy[i] = mass[i];
	}
	return copy;
}
void start_experiment(void(*sort)(int*, int, unsigned long long*, unsigned long long*), int min_size, int step_of_sizes, int count_of_experiments) {
	unsigned long long** characteristics = (unsigned long long**)malloc(count_of_experiments * sizeof(unsigned long long*));
	for (int i = 0; i < count_of_experiments; i++) {
		characteristics[i] = (unsigned long long*)malloc(5 * sizeof(unsigned long long)); // 5 - это количеcтво характеристик
	}
	printf(" ================================ EXPERIMENT MODE ================================ \n");
	for (int i = 1; i <= count_of_experiments; i++) {
		start_test(i, sort, characteristics, min_size, step_of_sizes);
	}
	show_table_with_experiments_results(characteristics, min_size, step_of_sizes, count_of_experiments);
	printf(" ================================================================================= \n");
	system("pause");
	// Освобождение памяти
	for (int i = 0; i < count_of_experiments; i++) { 
		free(characteristics[i]); 
	}
	free(characteristics); 
}
int check_sorting(int* mass, int size) {
	for (int i = 0; i < size - 1; i++) {
		if (mass[i] > mass[i + 1]) { return 0; }
	}
	return 1;
}
void start_test(int num, void(*sort)(int*, int, unsigned long long*, unsigned long long*), unsigned long long** characteristics, int min_size, int step_of_sizes) {
	int size = min_size * pow(step_of_sizes, num - 1);
	int* array = (int*)malloc(sizeof(int) * size);
	
	printf("[TEST_%d      ]", num);
	printf("[         RUN] \n");
	printf("[CREATE DATA ]");
	printf("[         RUN] \n");

	generate_array(array, size);

	printf("              [      FINISH] \n");
	printf("[SORTING     ]");
	printf("[         RUN] \n");

	unsigned long long swps_count = 0, cmps_count = 0;
	clock_t start = clock();
	sort(array, size, &swps_count, &cmps_count);
	clock_t end = clock();
	printf("              [      FINISH] \n");

	int success = check_sorting(array, size);
	characteristics[num - 1][0] = size; 
	characteristics[num - 1][1] = (unsigned long long)((end - start) * 1000 / CLOCKS_PER_SEC);
	characteristics[num - 1][2] = swps_count; 
	characteristics[num - 1][3] = cmps_count; 
	characteristics[num - 1][4] = success; 
	printf("[TEST FINISH ]");
	if (success) {
		printf("[     %sSUCCESS%s] \n", GREEN, RESET);
		printf("\n");
	}
	else {
		printf("[       %sERROR%s] \n", RED, RESET);  
		printf("\n"); 
	}
}
 
void start_sort_experiments(int min_size, int step_of_sizes, int count_of_experiments) {
	char dir[100] = "C:\\Users\\Владелец\\Documents\\";
	char filename_out[100] = "result.txt"; 
	char filepath_out[200];
	strcpy_s(filepath_out, sizeof(filepath_out), dir);
	strncat_s(filepath_out, 100, filename_out, 100);

	FILE* output_file = NULL;
	errno_t error; 
	error = fopen_s(&output_file, filepath_out, "w+");
	fclose(output_file); 

	// Выделяем память для характеристик
	unsigned long long** characteristics = (unsigned long long**)malloc(count_of_experiments * sizeof(unsigned long long*));
	for (int i = 0; i < count_of_experiments; i++) {
		characteristics[i] = (unsigned long long*)malloc(5 * sizeof(unsigned long long)); // 5 - это количество характеристик
	}

	for (int i = 0; i < count_of_experiments; i++) {
		printf("[TEST_%d      ]", i + 1);
		printf("[         RUN] \n");

		int size = min_size * (int)pow(step_of_sizes, i); // Приведение к int
		int* bubble_mass = (int*)malloc(size * sizeof(int));
		rand_init(bubble_mass, size, 1, size);
		int* bubble_mod_mass = copy_mass(bubble_mass, size);
		int* hoara_mass = copy_mass(bubble_mass, size);
		int* shell_mass = copy_mass(bubble_mass, size);
		printf("              [      FINISH] \n");

		// Запускаем тесты для каждой сортировки
		start_test_all(bubble_sort, bubble_mass, size, characteristics, 0);
		start_test_all(optimized_bubble_sort, bubble_mod_mass, size, characteristics, 1);
		start_test_all(hoara_sort, hoara_mass, size, characteristics, 2);
		start_test_all(shell_sort, shell_mass, size, characteristics, 3);

		// Освобождение памяти для текущего теста
		free(bubble_mass);
		free(bubble_mod_mass);
		free(hoara_mass);
		free(shell_mass);

		printf("[TEST FINISH ]\n");
	}
	show_table_with_all_experiments_results(characteristics, min_size, step_of_sizes, count_of_experiments); 
	printf("Результаты были записаны в result.txt \n");
	system("pause");
	// Освобождение выделенной памяти для характеристик
	for (int i = 0; i < count_of_experiments; i++) {
		free(characteristics[i]);
	}
	free(characteristics);
}

void start_test_all(void(*sort)(int*, int, unsigned long long*, unsigned long long*), int* mass, int size, unsigned long long** characteristics, int num_sort) {
	printf("[SORTING     ]");
	printf("[         RUN] \n");

	unsigned long long swps_count = 0, cmps_count = 0;
	clock_t start = clock();
	sort(mass, size, &swps_count, &cmps_count);
	clock_t end = clock();
	printf("              [      FINISH] \n");

	int success = check_sorting(mass, size);
	characteristics[num_sort][0] = size;
	characteristics[num_sort][1] = (unsigned long long)((end - start) * 1000 / CLOCKS_PER_SEC);
	characteristics[num_sort][2] = swps_count;
	characteristics[num_sort][3] = cmps_count;
	characteristics[num_sort][4] = success;
	printf("[TEST FINISH ]");
	if (success) {
		printf("[     %sSUCCESS%s] \n", GREEN, RESET);
	}
	else {
		printf("[       %sERROR%s] \n", RED, RESET);
	}
}
void show_table_with_all_experiments_results(unsigned long long** characteristics, int min_size, int step_of_sizes, int count_of_experiments) {
	char dir[100] = "C:\\Users\\Владелец\\Documents\\";
	char filename_out[100] = "result.txt";
	char filepath_out[200];
	strcpy_s(filepath_out, sizeof(filepath_out), dir);
	strncat_s(filepath_out, sizeof(filepath_out), filename_out, sizeof(filename_out));

	FILE* output_file = NULL;
	errno_t error;

	error = fopen_s(&output_file, filepath_out, "a+"); // Открываем файл для добавления данных
	if (error != 0) {
		printf("Error in open of output file. Error code %d\n", error);
		return;
	}
	else {
		printf("File %s open\n", filepath_out);

		// Запись заголовка для времени
		fprintf(output_file, "\t time(ms) \n");
		fprintf(output_file, "+------+-------------+-----------------------+------------+------------+ \n");
		fprintf(output_file, "| test | Bubble sort | Optimized bubble sort | Hoara sort | Shell sort | \n");
		fprintf(output_file, "+------+-------------+-----------------------+------------+------------+ \n");

		// Запись времени
		for (int i = 0; i < count_of_experiments; i++) {
			fprintf(output_file, "| %4d | %12llu | %12llu | %12llu | %12llu | \n",
				i + 1,
				characteristics[i][1], // Время для Bubble Sort 
				characteristics[i][2], // Время для Optimized Bubble Sort 
				characteristics[i][3], // Время для Hoara Sort 
				characteristics[i][4]); // Время для Shell Sort
		}
		fprintf(output_file, "+------+-------------+-----------------------+------------+------------+ \n\n");

		// Запись заголовка для обменов
		fprintf(output_file, "\t swaps \n");
		fprintf(output_file, "+------+-------------+-----------------------+------------+------------+ \n");
		fprintf(output_file, "| test | Bubble sort | Optimized bubble sort | Hoara sort | Shell sort | \n");
		fprintf(output_file, "+------+-------------+-----------------------+------------+------------+ \n");

		// Запись количества обменов
		for (int i = 0; i < count_of_experiments; i++) {
			fprintf(output_file, "| %4d | %12llu | %12llu | %12llu | %12llu | \n",
				i + 1,
				characteristics[i][2], // Обмены для Bubble Sort
				characteristics[i][3], // Обмены для Optimized Bubble Sort
				characteristics[i][4], // Обмены для Hoara Sort
				characteristics[i][5]); // Обмены для Shell Sort
		}
		fprintf(output_file, "+------+-------------+-----------------------+------------+------------+ \n\n");

		// Запись заголовка для сравнений
		fprintf(output_file, "\t comps \n");
		fprintf(output_file, "+------+-------------+-----------------------+------------+------------+ \n");
		fprintf(output_file, "| test | Bubble sort | Optimized bubble sort | Hoara sort | Shell sort | \n");
		fprintf(output_file, "+------+-------------+-----------------------+------------+------------+ \n");

		// Запись количества сравнений
		for (int i = 0; i < count_of_experiments; i++) {
			fprintf(output_file, "| %4d | %12llu | %12llu | %12llu | %12llu | \n",
				i + 1,
				characteristics[i][3], // Сравнения для Bubble Sort
				characteristics[i][4], // Сравнения для Optimized Bubble Sort
				characteristics[i][5], // Сравнения для Hoara Sort
				characteristics[i][6]); // Сравнения для Shell Sort
		}
		fprintf(output_file, "+------+-------------+-----------------------+------------+------------+ \n\n");

		// Запись заголовка для состояния
		fprintf(output_file, "\t state \n");
		fprintf(output_file, "+------+-------------+-----------------------+------------+------------+ \n");
		fprintf(output_file, "| test | Bubble sort | Optimized bubble sort | Hoara sort | Shell sort | \n");
		fprintf(output_file, "+------+-------------+-----------------------+------------+------------+ \n");

		// Запись состояния
		for (int i = 0; i < count_of_experiments; i++) {
			fprintf(output_file, "| %4d | %12s | %12s | %12s | %12s | \n",
				i + 1,
				(characteristics[i][1] ? "SUCCESS" : "ERROR"), // Состояние для Bubble Sort 
				(characteristics[i][2] ? "SUCCESS" : "ERROR"), // Состояние для Optimized Bubble Sort 
				(characteristics[i][3] ? "SUCCESS" : "ERROR"), // Состояние для Hoara Sort
				(characteristics[i][4] ? "SUCCESS" : "ERROR")); // Состояние для Shell Sort
		}
		fprintf(output_file, "+------+-------------+-----------------------+------------+------------+ \n");

		fclose(output_file); // Закрываем файл
	}
}


void show_table_with_experiments_results(unsigned long long** characteristics, int min_size, int step_of_sizes, int count_of_experiments) {
	printf("+------+--------------+--------------+--------------+--------------+--------------+ \n");
	printf("| test |        array |      time(ms)|        swaps |        comps |        state | \n");
	printf("+------+--------------+--------------+--------------+--------------+--------------+ \n");
	for (int i = 0; i < count_of_experiments; i++) {
		printf("| %4d | %12d | %12llu | %12llu | %12llu | %12s | \n", i + 1,
			characteristics[i][0],
			characteristics[i][1],
			characteristics[i][2],
			characteristics[i][3],
			(characteristics[i][4] ? "SUCCESS" : "ERROR"));
	}
	printf("+------+--------------+--------------+--------------+--------------+--------------+ \n");
}
