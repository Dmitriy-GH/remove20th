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

int count = 0;

void start(int center, int sum, int lost) {
	int num17[17] = { 1, 2, 3, 4, 5, 7, 8, 9, 10, 11, 13, 14, 15, 16, 17, 19, 20 };
	int num15[15]; // Массив без center и lost
	int *x1 = &center, *x2 = &num15[0], *x3 = &num15[1], *x4 = &num15[2], *x5 = &num15[3], *x6 = &num15[4], *x7 = &num15[5], *x8 = &num15[6], *x9 = &num15[7]
			, *x10 = &num15[8], *x11 = &num15[9], *x12 = &num15[10], *x13 = &num15[11], *x14 = &num15[12], *x15 = &num15[13], *x16 = &num15[14];
	if (center < lost) {
		copy_arr(num17, 17, num15, center, lost);
	} else {
		copy_arr(num17, 17, num15, lost, center);
	}

	do {
		if (sum == 12 + *x12 + *x13 + *x14 + *x15 + *x16 // Внешний круг
			&& sum == 18 + 6 + *x8 + *x9 + *x10 + *x11 // Средний круг
			&& sum == *x2 + *x3 + *x4 + *x5 + *x6 + *x7 // Внутренний круг
			&& sum == 12 + *x2 + *x1 + *x5 + *x15 // Диаметр горизонтальный
			&& sum == *x14 + *x4 + *x1 + *x7 + *x12 // Диаметр cлева направо
			&& sum == *x13 + *x3 + *x1 + *x6 + *x16 // Диаметр cправа налево
			// Шесть кругов
			&& sum == 12 + *x9 + *x3 + *x6 + *x11 + *x12
			&& sum == 12 + *x13 + *x10 + *x4 + *x7 + *x8
			&& sum == *x13 + *x14 + 18 + *x5 + *x2 + *x9
			&& sum == *x14 + *x15 + 6 + *x6 + *x3 + *x10
			&& sum == *x15 + *x16 + *x11 + *x7 + *x4 + 18
			&& sum == *x16 + *x12 + *x8 + *x2 + *x5 + 6
			) {
			count++;
			printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", *x1, *x2, *x3, *x4, *x5, *x6, *x7, *x8, *x9, *x10, *x11, *x12, *x13, *x14, *x15, *x16, lost);
		}
	} while (std::next_permutation(num15, num15 + 15));
}

int main(int argc, char** argv)
{
	start(20, 60, 10);
	printf("count %d\n", count);
	start(19, 57, 20);
	printf("count %d\n", count);
	return 0;
}