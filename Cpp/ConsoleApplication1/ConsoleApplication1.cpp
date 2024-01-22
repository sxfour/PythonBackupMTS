#include "Header.h"

// Получение времени на текущую дату
const std::string currentDateTime() {
	time_t			now = time(0);
	struct tm		tstruct;
	char			buf[80];

	localtime_s(&tstruct, &now);
	strftime(buf, sizeof(buf), "%d-%m-%Y", &tstruct);

	return buf;
}

// Получаем текущего пользователя в Windows
const std::string currentUser() {
	DWORD username_len = UNLEN + 1;
	char username_lc[UNLEN + 1];

	GetUserNameA(username_lc, &username_len);

	return username_lc;
}

int main() {
	setlocale(LC_ALL, "RU");

	// Основные пути и переменные 
	std::string username(currentUser());
	std::string src = "C:\\Users\\";
	std::string dst = "\\\\192.168.0.202\\Backup\\" + username + "\\BackupData_" + currentDateTime();
	std::vector<std::string> Folders{ "\\Desktop", "\\Downloads", "\\Documents"};

	// Добавление даты к пути
	const fs::path destinationPath = dst;

	src.append(username);

	for (int i = 0; i < 3; i++) {
		std::cout << "[!] Попытка копирования [" << src + Folders[i] << "]\n";
		std::cout << "[!] Пользователь: [" << username << "]" << "\n";

		const fs::path sourcePath = src + Folders[i];
		copyDir(sourcePath, destinationPath);
	}

	system("pause");

	return 0;
}