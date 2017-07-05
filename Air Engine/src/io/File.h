#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "..\DataTypes.h"

namespace engine {
	namespace io {

		struct File {

		private:
			std::fstream mFile;
			std::string mPath;
			long long size;

		public:
			File(const std::string& path);

			~File();

			void open(int mode = std::ios::in | std::ios::out);

			void close();

			inline bool exists() const { return &mFile != nullptr; };

			void createFile();

			uint8* readFile();

			std::vector<std::string> readFileLines();

			std::string readLine();

			void write(const std::string& data);

			void write(const char* data);

			long long file_size();

			static uint8* readFile(const std::string& path);
		};
} }