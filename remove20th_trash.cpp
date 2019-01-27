#include <cstdio>

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

// Проверка что массив отсортирован
bool is_sort(int* arr, size_t size) {
	for (size_t i = 1; i != size; i++) {
		if (arr[i] <= arr[i - 1]) return false;
	}
	return true;
}

int count = 0; // Счетчик правильных решений

void start(int center, int sum, int lost) {
	int num17[17] = { 1, 2, 3, 4, 5, 7, 8, 9, 10, 11, 13, 14, 15, 16, 17, 19, 20 };
	int num15[15]; // Массив без center и lost
	if (center < lost) {
		copy_arr(num17, 17, num15, center, lost);
	}
	else {
		copy_arr(num17, 17, num15, lost, center);
	}
	// Заполнение среднего круга по 4 из 15
	size_t ic[4]; // Индексы выбранных элементов
	for (ic[0] = 0; ic[0] < 15; ic[0]++) {
	for (ic[1] = ic[0] + 1; ic[1] < 15; ic[1]++) {
	for (ic[2] = ic[1] + 1; ic[2] < 15; ic[2]++) {
	for (ic[3] = ic[2] + 1; ic[3] < 15; ic[3]++) {
		if (sum != 18 + 6 + num15[ic[0]] + num15[ic[1]] + num15[ic[2]] + num15[ic[3]]) continue;
		int num11[11];
		copy_arr(num15, 15, num11, num15[ic[0]], num15[ic[1]], num15[ic[2]], num15[ic[3]]);
		// Заполнение внешнего круга по 5 из 11
		size_t ie[5]; // Индексы выбранных элементов
		for (ie[0] = 0; ie[0] < 11; ie[0]++) {
		for (ie[1] = ie[0] + 1; ie[1] < 11; ie[1]++) {
		for (ie[2] = ie[1] + 1; ie[2] < 11; ie[2]++) {
		for (ie[3] = ie[2] + 1; ie[3] < 11; ie[3]++) {
		for (ie[4] = ie[3] + 1; ie[4] < 11; ie[4]++) {
			if (sum != 12 + num11[ie[0]] + num11[ie[1]] + num11[ie[2]] + num11[ie[3]] + num11[ie[4]]) continue;
			// Внутреннее кольцо
			int num_i[6];
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
			// Нумерация х в соответствии с https://www.sql.ru/forum/actualutils.aspx?action=gotomsg&tid=1308126&msg=21793805
			 // Внешнее кольцо
			int num_e[5];
			for (size_t i = 0; i != 5; i++) num_e[i] = num11[ie[i]];
			if (!is_sort(num_e, 5)) {
				printf("!!! ERROR sort num_e !!!\n");
				return;
			}
			// Среднее кольцо
			int num_c[4]; 
			for (size_t i = 0; i != 4; i++) num_c[i] = num15[ic[i]];
			if (!is_sort(num_c, 4)) {
				printf("!!! ERROR sort num_c !!!\n");
				return;
			}

			int x1 = center;
			// Вращение внутреннего кольца
			size_t iri[6];
			for(iri[0] = 0; iri[0] != 6; iri[0]++) {
			for (iri[1] = 0; iri[1] != 6; iri[1]++) { if (iri[1] == iri[0]) continue;
			for (iri[2] = 0; iri[2] != 6; iri[2]++) { if (iri[2] == iri[0] || iri[2] == iri[1]) continue;
			for (iri[3] = 0; iri[3] != 6; iri[3]++) { if (iri[3] == iri[0] || iri[3] == iri[1] || iri[3] == iri[2]) continue;
			for (iri[4] = 0; iri[4] != 6; iri[4]++) { if (iri[4] == iri[0] || iri[4] == iri[1] || iri[4] == iri[2] || iri[4] == iri[3]) continue;
			for (iri[5] = 0; iri[5] != 6; iri[5]++) { if (iri[5] == iri[0] || iri[5] == iri[1] || iri[5] == iri[2] || iri[5] == iri[3] || iri[5] == iri[4]) continue;
				int x2 = num_i[iri[0]], x3 = num_i[iri[1]], x4 = num_i[iri[2]], x5 = num_i[iri[3]], x6 = num_i[iri[4]], x7 = num_i[iri[5]];
				// Вращение внешнего кольца
				size_t ire[5];
				for(ire[0] = 0; ire[0] != 5; ire[0]++) {
				for (ire[1] = 0; ire[1] != 5; ire[1]++) { if (ire[1] == ire[0]) continue;
				for (ire[2] = 0; ire[2] != 5; ire[2]++) { if (ire[2] == ire[0] || ire[2] == ire[1]) continue;
				for (ire[3] = 0; ire[3] != 5; ire[3]++) { if (ire[3] == ire[0] || ire[3] == ire[1] || ire[3] == ire[2]) continue;
				for (ire[4] = 0; ire[4] != 5; ire[4]++) { if (ire[4] == ire[0] || ire[4] == ire[1] || ire[4] == ire[2] || ire[4] == ire[3]) continue;
					int x12 = num_e[ire[0]], x13 = num_e[ire[1]], x14 = num_e[ire[2]], x15 = num_e[ire[3]], x16 = num_e[ire[4]];
					// Проверка диаметров
					// Горизонтальный
					if (sum != 12 + x2 + x1 + x5 + x15) continue;
					// Справа налево
					if (sum != x14 + x4 + x1 + x7 + x12) continue;
					// Слева направо
					if (sum != x13 + x3 + x1 + x6 + x16) continue;
					// Вращение среднего кольца
					size_t irc[4];
					for(irc[0] = 0; irc[0] != 4; irc[0]++) {
					for (irc[1] = 0; irc[1] != 4; irc[1]++) { if (irc[1] == irc[0]) continue;
					for (irc[2] = 0; irc[2] != 4; irc[2]++) { if (irc[2] == irc[0] || irc[2] == irc[1]) continue;
					for (irc[3] = 0; irc[3] != 4; irc[3]++) { if (irc[3] == irc[0] || irc[3] == irc[1] || irc[3] == irc[2]) continue;
						int x8 = num_c[irc[0]], x9 = num_c[irc[1]], x10 = num_c[irc[2]], x11 = num_c[irc[3]];
						// Проверка шести кругов
						if (sum != 12 + x9 + x3 + x6 + x11 + x12) continue;
						if (sum != 12 + x13 + x10 + x4 + x7 + x8) continue;
						if (sum != x13 + x14 + 18 + x5 + x2 + x9) continue;
						if (sum != x14 + x15 + 6 + x6 + x3 + x10) continue;
						if (sum != x15 + x16 + x11 + x7 + x4 + 18) continue;
						if (sum != x16 + x12 + x8 + x2 + x5 + 6) continue;

						count++;
						printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, lost);
					}}}}
				}}}}}
			}}}}}}
		}}}}}
	}}}}
}

int main(int argc, char** argv)
{
	start(19, 57, 20);
	printf("count %d\n", count);
	start(20, 60, 10);
	printf("count %d\n", count);
	return 0;
}