#pragma once

namespace JSON {
    struct Null {
        bool operator==(JSON::Null const& other) const;
        bool operator!=(JSON::Null const& other) const;
    };
};  // namespace JSON
