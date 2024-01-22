#include <fstream>
#include <filesystem>
#include <system_error>
#include <iostream>
#include <string>
#include <time.h>
#include <Windows.h>
#include <lmcons.h>
#include <stdio.h>

#pragma once

namespace fs = std::filesystem;

void copyFiles(const fs::path& source_dir, const fs::path& destination_dir) {
	std::ifstream source_file(source_dir, std::ios::binary);
	std::ofstream destination_file(destination_dir, std::ios::binary);

	if (!source_file || !destination_file) {
		std::cout << "Ошибка при получение файла." << std::endl;

		return;
	}

	destination_file << source_file.rdbuf();

	source_file.close();
	destination_file.close();
}

void copyDir(const fs::path& source_dir, const fs::path& destination_path) {
	try {
		fs::create_directories(destination_path);

		for (const auto& entry : fs::directory_iterator(source_dir)) {
			const fs::path& sourceFilePath = entry.path();
			const fs::path& destinationFilePath = destination_path / sourceFilePath.filename();

			if (fs::is_directory(sourceFilePath)) {
				copyDir(sourceFilePath, destinationFilePath);

				std::cout << sourceFilePath.string() << "\n";
			}
			else {
				copyFiles(sourceFilePath, destinationFilePath);
				std::cout << sourceFilePath.string() << "\n";
			}
		}
	}
	catch (fs::filesystem_error const& ex) {
		std::cout << "\nwhat():  " << ex.what() << '\n'
			<< "path1(): " << ex.path1() << '\n'
			<< "code().value():    " << ex.code().value() << '\n'
			<< "code().message():  " << ex.code().message() << '\n'
			<< "code().category(): " << ex.code().category().name() << '\n';
	}
}