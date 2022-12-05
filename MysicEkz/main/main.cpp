#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <stdlib.h>

using namespace std;

struct infSong {
	string name;
	string executor;
	string text;
	int year;
};

int length = 0;
infSong* list;
fstream file;
string filename = "mysc.txt";

void addToEnd(infSong*& arr, int& length, infSong value);
void addSongByKeyboard();
void addSongByFile();
void deleteToPlace(infSong*& arr, int& length, int placeIndex);
int searchByName(const infSong* const arr, const int const length, const string const name);
void printSongsText(const infSong* const arr, const int const length, const string const name);
void changeSongsText(infSong* arr, const int const length, const string const name);
void saveSongs();
void openSongs(infSong*& arr, int& length);
void printMenu();

int main()
{
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	while (true){
		system("cls");
		printMenu();
		for (size_t i = 0; i < length; i++){cout << list[i].text << "\n";}
		system("pause");
	}
	system("cls");
	return 0;
}

void addToEnd(infSong*& arr, int& length, infSong value) {
	infSong* newArray = new infSong[length + 1];
	for (int i = 0; i < length; i++){newArray[i] = arr[i];}
	newArray[length] = value;
	delete[]arr;
	arr = newArray;
	length++;
}
void addSongByKeyboard() {
	infSong tempSong;
	cout << "Введіть назву пісні : ";
	cin >> tempSong.name;
	cout << "Введіть автора : ";
	cin >> tempSong.executor;
	cout << "Введіть текст : ";
	cin >> tempSong.text;
	cout << "Введіть рік : ";
	cin >> tempSong.year;

	addToEnd(list, length, tempSong);
}
void addSongByFile() {
	infSong tempSong;
	string filename;
	ifstream fileIn;
	while (true){
		cout << "Введіть назву файла:";
		cin >> filename;
		filename += ".txt";
		fileIn.open(filename);
		if (fileIn.fail()){
			cout << "Error opening file!\aНе вдалось відкрити файл";
			system("cls");
			continue;
		}

		getline(fileIn, tempSong.name);
		getline(fileIn, tempSong.executor);
		string year;
		getline(fileIn, year);
		tempSong.year = atoi(year.c_str());

		while (!fileIn.eof()){
			string line;
			getline(fileIn, line);
			tempSong.text += line + "\n";
		}
		fileIn.close();
		addToEnd(list, length, tempSong);
		break;
	}
}
void deleteToPlace(infSong*& arr, int& length, int placeIndex) {
	infSong* newArray = new infSong[length--];
	for (int i = 0, j = 0; i < length; i++, j++) {
		if (placeIndex == i) {j++;}
		newArray[i] = arr[j];
	}
	delete[]arr; 
	arr = newArray; 
}
int searchByName(const infSong* const arr, const int const length, const string const name) {
	for (int i = 0; i < length; i++) { if (arr[i].name == name) return i; }
	return -1;
}
void printSongsText(const infSong* const arr, const int const length, const string const name) {
	int index = searchByName(arr, length, name);
	cout << arr[index].text;
}
void changeSongsText(infSong* arr, int length, const string const name) {
	infSong tempSong;
	cout << "Введіть новій текст : ";
	cin >> tempSong.text;
	addToEnd(list, length, tempSong);
}
void saveSongs() {
	cout << "Якщо хочете зберегти у старий каталог натисніть 1"
		"інакшу введіть ім'я шснуючого файлу : ";
	string inputText;
	cin >> inputText;
	if (inputText != "1") { filename = inputText + ".txt"; }
	file.open(filename);
	for (size_t i = 0; i < length; i++) {
		file << list[i].name << "\n";
		file << list[i].executor << "\n";
		file << list[i].year << "\n";
		file << list[i].text << "\n";
		file << "\n";
		if (i == length - 1) { file << "***"; }
		else{file << "***\n";}
	}
	file.close();
	system("cls");
	cout << "Пісні успішно завантажені";
}
void openSongs(infSong*& arr, int& length) {
	file.open(filename);
	length = 0;
	arr = new infSong[length];
	while (!file.eof()) {
		infSong tempSong;
		string line;
		string text;
		getline(file, line);
		tempSong.name = line;
		getline(file, line);
		tempSong.executor = line;
		getline(file, line);
		tempSong.year = atoi(line.c_str());
		while (line != "***") {
			getline(file, line);
			tempSong.text += line + "\n";
		}
		addToEnd(arr, length, tempSong);
	}
	file.close();
}
void printMenu() {
	string country;
	int mainMenuIndex;
	int indexToSearch;

	cout << "---Каталог пісень 2022---\n";
	cout << "1. Додати пісню\n";
	cout << "2. Видалити пісню\n";
	cout << "3. Змінити текст пісні\n";
	cout << "4. Відображення текста пісні\n";
	cout << "5. Зберегти пісню\n";
	cout << "6. Відобразити весь каталог\n";
	cout << "8. Вихід\n";
	cout << "Оберіть варіант дії: ";
	cin >> mainMenuIndex;
	switch (mainMenuIndex)
	{
	case 1:
		cout << "1. Додати текст вручну\n";
		cout << "2. Звгрузити інформацію з файла \n";
		cout << "Оберіть дію : ";
		int j;
		cin >> j;
		system("cls");
		switch (j){
		case 1:
			cout << "Заповніть наступні поля\n ";
			addSongByKeyboard();
			system("cls");
			break;
		case 2:
			addSongByFile();
			system("cls");
			break;
		default:
			cout << "О-ой щось не те, спробуйте знову\n";
			Sleep(1000);
			system("cls");
			break;
		}
		break;

	case 2:
		cout << "Видалення тексту\n";
		cout << "Укажіть назву пісні що потрібно відалити : ";
		cin >> country;
		indexToSearch = searchByName(list, length, country);
		deleteToPlace(list, length, indexToSearch);
		system("cls");
		break;
	case 3:
		cout << "Зміна тексту\n";
		cout << "Укажіть назву що потрібно змінити ";
		cin >> country;
		changeSongsText(list, length, country);
		system("pause");
		system("cls");
		break;
	case 4:
		cout << "Відображення текста пісні\n";
		cout << "Введіть назву пісні : ";
		cin >> country;
		printSongsText(list, length, country);
		system("pause");
		system("cls");
		break;
	case 5:
		saveSongs();
		system("pause");
		system("cls");
		break;
	case 6:
		openSongs(list, length);
		system("pause");
		system("cls");
		break;
	case 8:
		exit(3);
		break;
	default:
		cout << "О-ой щось не те, спробуйте знову\n";;
		Sleep(1000);
		system("cls");
		break;
	}
}