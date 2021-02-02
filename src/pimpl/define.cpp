#include "define.h"
#include "string"

struct Impl{
    std::string name;
};

Man::Man():impl(std::make_unique<Impl>()){}