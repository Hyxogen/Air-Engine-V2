#pragma once
#include <glad\glad.h>
#include <unordered_map>
#include "..\DataTypes.h"

namespace engine {
	namespace buffer {

		class Buffer {
		protected:
			static std::unordered_map<uint32, uint32> boundBuffers;

			uint32 mBufferID, mType;
			
		public:
			virtual ~Buffer() = 0;

			virtual void bind() const = 0;

			virtual void unBind() const = 0;

			virtual void bindTarget(uint32 target) const;

			virtual void unBindTarget(uint32 target) const;

			inline uint32 getBufferID() const { return mBufferID; }

			inline uint32 getType() const { return mType; }

			static inline bool isBound(uint32 target) { return boundBuffers[target] != 0; }
		};
} }