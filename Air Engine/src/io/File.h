#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

			const char* readFile();

			const std::vector<std::string> readFileLines();

			const std::string readLine();

			void write(const std::string& data);

			void write(const char* data);

			long long file_size();

			static const char* readFile(const std::string& path);
		};
} }