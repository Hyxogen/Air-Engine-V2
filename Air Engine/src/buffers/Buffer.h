#pragma once
#include <glad\glad.h>
#include <unordered_map>

namespace engine {
	namespace buffer {

		class Buffer {
		protected:
			static std::unordered_map<GLuint, GLuint> boundBuffers;

			GLuint mBufferID, mType;
			
		public:
			virtual ~Buffer() = 0;

			virtual void bind() const = 0;

			virtual void unBind() const = 0;

			inline GLuint getBufferID() const { return mBufferID; }

			inline GLuint getType() const { return mType; }

			static inline bool isBound(GLuint target) { return boundBuffers[target] != 0; }
		};
} }