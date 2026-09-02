#pragma once

#include <cstdint>
#include <vector>

namespace media {

using StreamId = std::uint64_t;
using Timestamp = std::int64_t;

enum class MediaType
{
    Audio,
    Video
};

struct StreamPacket
{
    StreamId stream_id {};
    Timestamp timestamp_us {};
    std::uint64_t sequence_number {};

    MediaType media_type {};

    std::vector<std::uint8_t> data;
};

}
