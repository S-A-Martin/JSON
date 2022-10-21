#pragma once

namespace JSON {
    struct Null {
        Null();

        bool const operator==(JSON::Null const& other) const;
        // Inequality JSON::Data::operator
        bool const operator!=(JSON::Null const& other) const;
    };

};  // namespace JSON
