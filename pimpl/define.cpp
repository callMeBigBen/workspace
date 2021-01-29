#include "define.h"
#include "string"

struct Man::Impl{
    std::string name;
};

Man::Man():impl(std::make_unique<Man::Impl>()){}