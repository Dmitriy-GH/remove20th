#include <cstdio>
#include <algorithm>

// Копирование сортированного массива с пропуском заданных значений skipX (в порядке возрастания)
void copy_arr(const int* source, size_t size, int* dest, int skip0, int skip1 = 99, int skip2 = 99, int skip3 = 99, int skip4 = 99, int skip5 = 99) {
	const int *end = source + size;
	while (source < end && *source < skip0) *dest++ = *source++;
	source++;
	while (source < end && *source < skip1) *dest++ = *source++;
	source++;
	while (source < end && *source < skip2) *dest++ = *source++;
	source++;
	while (source < end && *source < skip3) *dest++ = *source++;
	source++;
	while (source < end && *source < skip4) *dest++ = *source++;
	source++;
	while (source < end && *source < skip5) *dest++ = *source++;
}

// Следующая комбинация элементов массива. false - больше нет
bool next_combination(size_t *idx, size_t size, size_t max) {
	for (size_t i = 0; i != size; i++) {
		idx[i]++;
		if (i + 1 == size) { // Последний
			if (idx[i] == max) {
				idx[i - 1] = i - 1;
				idx[i] = i;
				return false;
			}
		} else { // Не последний
			if (idx[i] == idx[i + 1]) {
				idx[i] = i;
			} else {
				break;
			}
		}
	}
	return true;
}

// Проверка что массив отсортирован
bool is_sort(int* arr, size_t size) {
	for (size_t i = 1; i != size; i++) {
		if (arr[i] <= arr[i - 1]) return false;
	}
	return true;
}

int count = 0;

void start(int center, int sum, int lost) {
	int num17[17] = { 1, 2, 3, 4, 5, 7, 8, 9, 10, 11, 13, 14, 15, 16, 17, 19, 20 };
	int num15[15]; // Массив без center и lost
	if (center < lost) {
		copy_arr(num17, 17, num15, center, lost);
	} else {
		copy_arr(num17, 17, num15, lost, center);
	}
	// Заполнение среднего круга по 4 из 15
	size_t ic[4] = {0, 1, 2, 3}; // Индексы выбранных элементов
	do { // Перебор по 4 из 15
		if (sum == 18 + 6 + num15[ic[0]] + num15[ic[1]] + num15[ic[2]] + num15[ic[3]]) {
			int num11[11];
			copy_arr(num15, 15, num11, num15[ic[0]], num15[ic[1]], num15[ic[2]], num15[ic[3]]);
			// Заполнение внешнего круга по 5 из 11
			size_t ie[5] = { 0, 1, 2, 3, 4}; // Индексы выбранных элементов
			do {
				if (sum == 12 + num11[ie[0]] + num11[ie[1]] + num11[ie[2]] + num11[ie[3]] + num11[ie[4]]) {
					int num_i[6]; // Внутреннее кольцо
					copy_arr(num11, 11, num_i, num11[ie[0]], num11[ie[1]], num11[ie[2]], num11[ie[3]], num11[ie[4]]);
					// Проверка суммы внутреннего кольца
					if (sum != num_i[0] + num_i[1] + num_i[2] + num_i[3] + num_i[4] + num_i[5]) {
						printf("!!! ERROR sum !!!\n");
						return;
					}
					if (!is_sort(num_i, 6)) {
						printf("!!! ERROR sort num_i !!!\n");
						return;
					}
					// Проверка диаметров
					// Нумерация х в соответствии с https://www.sql.ru/forum/actualutils.aspx?action=gotomsg&tid=1308126&msg=21793805
					int *x2 = &num_i[0], *x3 = &num_i[1], *x4 = &num_i[2], *x5 = &num_i[3], *x6 = &num_i[4], *x7 = &num_i[5];
					int num_e[5]; // Внешнее кольцо
					int *x12 = &num_e[0], *x13 = &num_e[1], *x14 = &num_e[2], *x15 = &num_e[3], *x16 = &num_e[4];
					for (size_t i = 0; i != 5; i++) num_e[i] = num11[ie[i]];
					if (!is_sort(num_e, 5)) {
						printf("!!! ERROR sort num_e !!!\n");
						return;
					}
					int num_c[4]; // Среднее кольцо
					int *x8 = &num_c[0], *x9 = &num_c[1], *x10 = &num_c[2], *x11 = &num_c[3];
					for (size_t i = 0; i != 4; i++) num_c[i] = num15[ic[i]];
					if (!is_sort(num_c, 4)) {
						printf("!!! ERROR sort num_c !!!\n");
						return;
					}

					int *x1 = &center;
					do { // Вращение внутреннего кольца
						do { // Вращение внешнего кольца
							// Горизонтальный
							if (sum == 12 + *x2 + *x1 + *x5 + *x15) {
								// Справа налево
								if (sum == *x14 + *x4 + *x1 + *x7 + *x12) {
									// Слева направо
									if (sum == *x13 + *x3 + *x1 + *x6 + *x16) {
										do { // Вращение среднего кольца
											// Шесть кругов
											if (sum == 12 + *x9 + *x3 + *x6 + *x11 + *x12) {
												if (sum == 12 + *x13 + *x10 + *x4 + *x7 + *x8) {
													if (sum == *x13 + *x14 + 18 + *x5 + *x2 + *x9) {
														if (sum == *x14 + *x15 + 6 + *x6 + *x3 + *x10) {
															if (sum == *x15 + *x16 + *x11 + *x7 + *x4 + 18) {
																if (sum == *x16 + *x12 + *x8 + *x2 + *x5 + 6) {
																	count++;
																	printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", *x1, *x2, *x3, *x4, *x5, *x6, *x7, *x8, *x9, *x10, *x11, *x12, *x13, *x14, *x15, *x16, lost);
																}
															}
														}
													}
												}
											}
										} while (std::next_permutation(num_c, num_c + 4));
									}
								}
							}
						} while (std::next_permutation(num_e, num_e + 5));
					} while (std::next_permutation(num_i, num_i + 6));
					
				}
			} while (next_combination(ie, 5, 11));
		}
	} while (next_combination(ic, 4, 15));
}

int main(int argc, char** argv[])
{
	start(19, 57, 20);
	printf("count %d\n", count);
	start(20, 60, 10);
	printf("count %d\n", count);
	return 0;
}