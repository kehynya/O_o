#include <stdio.h>
#include <string.h>
#include <locale.h>
 
void letterscounting(FILE* _file, FILE* file_) {
	int cO = 0, co = 0;
	char let[1000];
	int kol;
	char* anotherline;
	kol = fread(let, 1, sizeof(let) - 1, _file);
	while (kol) {
		for (int i = 0; i < kol; i++) {
			if (let[i] != '\n') {
				if (let[i] == 'O') cO++;
				else if (let[i] == 'o') co++;
			}
			else {
				fprintf(file_, "O - %d, o - %d\n", cO, co);
				cO = co = 0;
			}
		}
		if (let[kol - 1] != '\n') {
			anotherline = strrchr(let, '\n');
			if (anotherline) {
				for (unsigned i = anotherline - let + 1; i < kol; i++) {
					if (let[i] == 'O') cO++;	
					else if (let[i] == 'o') co++;
				}
			}
		}
		kol = fread(let, 1, sizeof(let) - 1, _file);
	}
	if (cO > 0 || co > 0) fprintf(_file, "O: %d, o: %d\n", cO, co);
}

void readprint(char* filename) {
	char buf[1000];
	FILE* file = fopen(filename, "r");
	if (!file) {
		printf("Ошибка открытия файла");
		return;
	}
	printf("Содержимое файла %s:\n", filename);
	while (fgets(buf, 1000, file)) {
		printf("%s", buf);
	}
}

int main() {
	setlocale(LC_ALL, "Rus");
	FILE* _file = fopen("lab4-test-file.txt", "r");
	if (!_file) {
		printf("Ошибка открытия файла");
		return 1;
	}
	FILE* file_ = fopen("bruh.txt", "w");
	if (!file_) {
		printf("Ошибка открытия файла");
		return 1;
	}
	letterscounting(_file, file_);
	fclose(file_);
	readprint("bruh.txt");
	return 0;
}