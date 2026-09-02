#include "stream_manager.hpp"

namespace media {

StreamManager::StreamId StreamManager::create_stream()
{
    return next_stream_id_.fetch_add(
        1,
        std::memory_order_relaxed
    );
}

}
