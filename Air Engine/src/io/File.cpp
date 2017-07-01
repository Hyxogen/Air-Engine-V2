#include "File.h"

namespace engine {
	namespace io {

		File::File(const std::string& path) {
			mPath = path;
			mFile = std::fstream(path);
		}

		File::~File() {
			close();
		}

		const char* File::readFile() {
			if (!mFile.is_open()) open(std::ios::in | std::ios::binary);

			std::streampos length = file_size();
			mFile.seekg(0, std::ios::beg);

			char* buffer = new char[length];
			memset(buffer, 0, length);
			//buffer[length] = 0;

			mFile.read(buffer, length);

			return buffer;
		}

		const std::vector<std::string> File::readFileLines() {
			if (!mFile.is_open()) open(std::ios::in);
			std::vector<std::string> out;
			mFile.seekg(0, std::ios::beg);

			std::string buffer;
			while ((buffer == readLine()))
				out.push_back(buffer);

			return out;
		}

		void File::write(const std::string& data) {
			if (!mFile.is_open()) open(std::ios::out);
			mFile << data;
		}
		
		void File::write(const char* data) {
			if (!mFile.is_open()) open(std::ios::out | std::ios::binary);
			mFile << data;
		}

		void File::createFile() {
			std::ofstream stream(mPath);
			mFile = std::fstream(mPath);

			stream.close();
		}

		const std::string File::readLine() {
			if (!mFile.is_open()) open(std::ios::in);
			std::string buffer;
			std::getline(mFile, buffer);
			return buffer;
		}

		void File::open(int mode) {
			mFile.open(mPath, mode);
		}

		void File::close() {
			mFile.close();
		}

		long long File::file_size() {
			if (!mFile.is_open()) open(std::ios::in);
			mFile.seekg(0, std::ios::end);
			return mFile.tellg();
		}

		const char* File::readFile(const std::string& path) {
			File file(path);
			if (!file.exists()) return nullptr;

			return file.readFile();
		}
	}
}