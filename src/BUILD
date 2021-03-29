source_dirs = [
    ".",
    #"./code_practice/",
    #"./concurrency/",
    #"./move/",
    #"./pimpl/",
    #"./smart_pointer/",
    #"./template/",
    #"./future/",
    #"./virtual_inheritance/",
    #".",
]

OPTIMIZE = ["-DARCHON", "-Ofast", "-fopenmp", "-g", "-Wall", "-Wextra", "-Werror", "-Wno-sign-compare"]

dep_libs = [
    #"cpp3rdlib/folly:v2018.08.20.00@//cpp3rdlib/folly:folly",
    "cpputil/common:1.0.0@//cpputil/common:common_utils",
]

cc_binary(
    name="px_test",
    srcs=[d+"/*.cpp" for d in source_dirs],
    deps=dep_libs,
    incs=source_dirs,
    bundle_path="./bundle/",
    optimize=OPTIMIZE
)