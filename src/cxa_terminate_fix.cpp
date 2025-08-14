// Cross-platform C++ ABI compatibility fixes
// Addresses different exception handling and memory management across platforms

#ifdef _WIN32
    // Windows/MSVC specific implementations
    #include <cstdlib>
    #include <exception>
    
    // MSVC exception handling compatibility
    extern "C" void __cxa_pure_virtual() {
        std::terminate();
    }
    
    extern "C" void __cxa_deleted_virtual() {
        std::terminate();
    }

#elif defined(__APPLE__) && defined(__MACH__)
    // macOS/Darwin specific implementations
    #include <cstdlib>
    #include <exception>
    
    // Darwin exception handling
    extern "C" void __cxa_pure_virtual() {
        std::terminate();
    }

#else
    // Linux/GCC specific implementations
    #include <cstdlib>
    #include <exception>
    
    // GCC libstdc++ compatibility
    extern "C" void __cxa_pure_virtual() {
        std::terminate();
    }
    
    // Additional GCC exception handling
    extern "C" void __cxa_deleted_virtual() {
        std::terminate();
    }

#endif

// Cross-platform memory alignment helpers
namespace movici {
namespace platform {

#ifdef _WIN32
    // Windows alignment
    void* aligned_alloc(size_t alignment, size_t size) {
        return _aligned_malloc(size, alignment);
    }
    
    void aligned_free(void* ptr) {
        _aligned_free(ptr);
    }
#else
    // POSIX alignment (Linux, macOS)
    void* aligned_alloc(size_t alignment, size_t size) {
        void* result = nullptr;
        if (posix_memalign(&result, alignment, size) != 0) {
            return nullptr;
        }
        return result;
    }
    
    void aligned_free(void* ptr) {
        free(ptr);
    }
#endif

} // namespace platform
} // namespace movici