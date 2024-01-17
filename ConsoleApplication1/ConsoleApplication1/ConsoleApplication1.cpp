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

// Получаем текущего пользователя в Windows, wchar_t
const std::wstring currentUser() {
	TCHAR username[UNLEN + 1];
	DWORD size = UNLEN + 1;

	GetUserName((TCHAR*)username, &size);

	return username;
}

int main() {
	setlocale(LC_ALL, "RU");

	// Основные пути и переменные 
	std::wstring username(currentUser());
	std::string username_str(username.begin(), username.end());

	std::string src = "C:\\Users\\";

	std::string dst = "\\\\192.168.0.202\\Backup\\" + username_str + "\\BackupData_" + currentDateTime();
	std::vector<std::string> Folders{ "\\Desktop", "\\Downloads", "\\Documents"};

	// Добавление даты к пути
	const fs::path destinationPath = dst;

	src.append(username_str);

	for (int i = 0; i < 3; i++) {
		std::cout << "[!] Попытка копирования [" << src + Folders[i] << "]\n";
		std::cout << "[!] Пользователь: [" << username_str << "]" << "\n";

		const fs::path sourcePath = src + Folders[i];
		copyDir(sourcePath, destinationPath);
	}

	system("pause");

	return 0;
}