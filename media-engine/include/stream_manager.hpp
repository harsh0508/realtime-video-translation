#pragma once

#include <atomic>
#include <cstdint>

namespace media {

class StreamManager
{
public:

    using StreamId = std::uint64_t;

    StreamId create_stream();

private:

    std::atomic<StreamId> next_stream_id_ {1};
};

}
