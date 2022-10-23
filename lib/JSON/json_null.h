#pragma once

namespace JSON {
    struct Null {
        Null();

        bool const operator==(Null const& other) const;

        bool const operator!=(Null const& other) const;
    };

};  // namespace JSON
