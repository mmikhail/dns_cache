#pragma once

namespace common {

template <typename T>
class TSingleton final {
public:
    typedef T Object;

    static Object& Instance() {
        static Object object;
        return object;
    }

    TSingleton() = delete;
    TSingleton& operator= (const TSingleton&) = delete;
};

}