#pragma once

namespace JSON {
    struct Null {
        Null();

        bool operator==(JSON::Null const& other) const;
        // Inequality JSON::Data::operator
        bool operator!=(JSON::Null const& other) const;
    };

};  // namespace JSON
