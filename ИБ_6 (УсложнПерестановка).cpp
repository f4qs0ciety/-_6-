#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

void encrypt() {
	int n, m; //Длина и высота блока шифрования
	cout << "Введите размеры блока шифрования (длина и высота через пробел): ";
	cin >> n >> m;
	cout << "Введите ключ шифрования: ";
	string key; //Основной ключ - указывает, в каком порядке читать столбцы блока
	key.resize(n);
	cin >> key;
	cout << "Введите дополнительный ключ шифрования: ";
	string key2; //Дополнительный ключ - указывает, какие элементы блока пусты (число от 1 до n * m)
	cin >> key2;
	cout << "Введите текст: ";
	string temp_input; //Введённый текст
	string input[2]; //Таблица для линейной шифровки: в верхнем ряду - номера столбцов, в нижнем - текст
	cin.ignore();
	getline(cin, temp_input);
	if (temp_input.length() % (m * n) != 0) { //Изменение размеров input[1] для разбиения по блокам
		input[1].resize(temp_input.length() + ((temp_input.length() / (m * n) + 1) * key2.length()), ' '); }
	else { input[1].resize(temp_input.length() + temp_input.length() / (m * n) * key2.length(), ' '); }
	if (input[1].length() % (m * n) != 0) 
		input[1].resize((input[1].length() / (m * n) + 1) * m * n, ' ');
	input[0].resize(input[1].length()); //Изменение размеров input[0] для разбиения по блокам
	for (int i = 0; i < input[0].length();) { //Заполнение input[0] номерами столбцов из основного ключа
		for (int j = 0; j < n; j++) {
			input[0][i] = key[j];
			i++;
			if (i == input[0].length()) break;
		}
	}
	for (int i = 0; i < key2.length(); i++) { //Заполнение input[1] пустыми элементами из доп. ключа
	int block_checkpoint = 0;
		for (int j = 0; j < input[0].length(); j++) {
			if (j > (block_checkpoint + 1) * m * n) block_checkpoint++;
			if (j - block_checkpoint * m * n + 1 == key2[i] - '0') input[1][j] = '=';
		}
	}
	int count = 0; //Счётчик элементов введённого текста
	for (int i = 0; i < input[1].length(); i++) {
		if (input[1][i] != '=') { input[1][i] = temp_input[count]; count++; }
		if (count > temp_input.length() - 1) break;
	}
	/*for (int i = 0; i < input[0].length(); i++) cout << input[0][i] << '\t';
	cout << endl;
	for (int i = 0; i < input[1].length(); i++) cout << input[1][i] << '\t';
	cout << endl;*/ //Промежуточная проверка работы функции
	cout << endl << "Зашифрованный текст: ";
	for (int block_counter = 0; block_counter < input[1].length() / (m * n); block_counter++) { //Вывод результата
		for (int j = 1; j <= n; j++) {
			for (int i = block_counter * n * m; i < (block_counter + 1) * n * m; i++) {
				if (input[0][i] - '0' == j && input[1][i] != '=') cout << input[1][i];
			}
		}
	} cout << endl;
}

void decrypt() {
	int n, m; //Длина и высота блока шифрования
	cout << "Введите размеры блока шифрования (длина и высота через пробел): ";
	cin >> n >> m;
	cout << "Введите ключ шифрования: ";
	string key; //Основной ключ - указывает, в каком порядке читать столбцы блока
	key.resize(n);
	cin >> key;
	cout << "Введите дополнительный ключ шифрования: ";
	string key2; //Дополнительный ключ - указывает, какие элементы блока пусты (число от 1 до n * m)
	key2.resize(n);
	cin >> key2;
	cout << "Введите текст: ";
	string temp_input; //Введённый текст
	string input[2]; //Таблица для линейной шифровки: в верхнем ряду - номера столбцов, в нижнем - текст
	cin.ignore();
	getline(cin, temp_input);
	if (temp_input.length() % (m * n) != 0) { //Изменение размеров input[1] для разбиения по блокам
		input[1].resize(temp_input.length() + ((temp_input.length() / (m * n) + 2) * key2.length()), ' ');
	}
	else { input[1].resize(temp_input.length() + (temp_input.length() / (m * n) + 1) * key2.length(), ' '); }
	if (input[1].length() % (m * n) != 0)
		input[1].resize((input[1].length() / (m * n) + 1) * m * n, ' ');
	input[0].resize(input[1].length()); //Изменение размеров input[0] для разбиения по блокам
	temp_input.resize(input[1].length()); //Изменение размеров temp_input для разбиения по блокам
	for (int i = 0; i < input[1].length();) { //Заполнение input[0] номерами столбцов из основного ключа
		for (int j = 0; j < key.length(); j++) {
			input[0][i] = key[j];
			i++;
		}
	}
	for (int i = 0; i < key2.length(); i++) { //Заполнение input[1] пустыми элементами из доп. ключа
		int block_checkpoint = 0;
		for (int j = 0; j < input[0].length();) {
			if (j > (block_checkpoint + 1) * m * n) block_checkpoint++;
			if (j - block_checkpoint * m * n + 1 == key2[i] - '0') {
				input[1][j] = '=';
				j++;
			}
			else j++;
		}
	}
	int count = 0;
	for (int block_counter = 0; block_counter < input[1].length() / (m * n); block_counter++) { //Заполнение свободных символов введённым текстом в порядке расшифрования
		for (int j = 1; j <= key.length(); j++) {
			for (int i = block_counter * n * m; i < (block_counter + 1) * n * m; i++) {
				if (input[0][i] == j + '0' && input[1][i] != '=') { 
					input[1][i] = temp_input[count]; 
					count++; 
					if (count > temp_input.length()) break;
				}
			}
		}
	}
	/*cout << input[0] << endl;
	cout << input[1] << endl;*/ //Промежуточная проверка работы функции
	cout << endl << "Расшифрованный текст: "; //Вывод результата
	for (int i = 0; i < input[1].length(); i++) {
		if (input[1][i] != '=') cout << input[1][i];
	} cout << endl;
};

void main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int option; //Выбор опции меню
	bool stop = false; //Индикатор остановки программы
	do {
		cout << endl << "Выберите режим работы: " << endl << "[1] Шифровка текста" << endl << "[2] Дешифровка текста" << endl << "[3] Выход" << endl << "Выбор: ";
		cin >> option;
		switch (option) {
		case 1: {encrypt(); break; }
		case 2: {decrypt(); break; }
		case 3: stop = true;
		}
	} while (stop != true);
}