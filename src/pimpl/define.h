#include <memory>

struct Impl;
class Man {
public:
    Man();
    std::unique_ptr<Impl> get_ptr();
private:
    std::unique_ptr<Impl> impl;
};