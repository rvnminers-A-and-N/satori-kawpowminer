#pragma once

#include <utility>

#if __cplusplus >= 201703L
    #include <optional>
    template<typename T>
    using optional_t = std::optional<T>;
    #define NULLOPT_T std::nullopt
#else
    // Simple optional implementation for C++14
    struct nullopt_type {};
    static constexpr nullopt_type NULLOPT_T{};
    
    template<typename T>
    class optional_t {
    private:
        bool has_value_;
        alignas(T) unsigned char data_[sizeof(T)];
        
    public:
        optional_t() : has_value_(false) {}
        optional_t(nullopt_type) : has_value_(false) {}
        optional_t(const T& value) : has_value_(true) {
            new(data_) T(value);
        }
        optional_t(T&& value) : has_value_(true) {
            new(data_) T(std::move(value));
        }
        
        ~optional_t() {
            reset();
        }
        
        void reset() {
            if (has_value_) {
                reinterpret_cast<T*>(data_)->~T();
                has_value_ = false;
            }
        }
        
        template<typename... Args>
        T& emplace(Args&&... args) {
            reset();
            new(data_) T(std::forward<Args>(args)...);
            has_value_ = true;
            return *reinterpret_cast<T*>(data_);
        }
        
        bool has_value() const { return has_value_; }
        operator bool() const { return has_value_; }
        
        T& value() {
            return *reinterpret_cast<T*>(data_);
        }
        
        const T& value() const {
            return *reinterpret_cast<const T*>(data_);
        }
        
        T& operator*() { return value(); }
        const T& operator*() const { return value(); }
        
        T* operator->() { return reinterpret_cast<T*>(data_); }
        const T* operator->() const { return reinterpret_cast<const T*>(data_); }
    };
#endif