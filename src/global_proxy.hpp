#pragma once

template<typename T>
class GlobalProxy {
public:
    explicit GlobalProxy(T *address) {
        m_address = address;
    }

    GlobalProxy& operator=(T value) {
        *m_address = value;
        return *this;
    }

private:
    T *m_address;
};
