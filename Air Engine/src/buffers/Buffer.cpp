#include "Buffer.h"

namespace engine {
	namespace buffer {

		std::unordered_map<GLuint, GLuint> Buffer::boundBuffers;

		Buffer::~Buffer() {

		}
} }