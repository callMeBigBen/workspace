source_dirs = [
    ".",
    "wheels/"
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

common_cppflags = [
    "-std=c++14",
    "-g",
    "-O0"
]


dep_libs = [
    #"cpp3rdlib/folly:v2018.08.20.00@//cpp3rdlib/folly:folly",
    #"cpputil/common:1.0.0@//cpputil/common:common_utils",
    "cpputil/pool:1.1.2@//cpputil/pool:pool",
    "#pthread",
]

cc_binary(
    name="px_test",
    srcs=[d+"/*.cpp" for d in source_dirs],
    deps=dep_libs,
    incs=source_dirs,
    bundle_path="./bundle/",
    extra_cppflags=common_cppflags
)