#include <memory>

class Man {
public:
    std::unique_ptr<Impl> get_ptr();
private:
    struct Impl;
    std::unique_ptr<Impl> impl;
}