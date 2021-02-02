source_dirs = [
    ".",
    "./code_practice/",
    "./concurrency/",
    "./move/",
    "./pimpl/",
    "./smart_pointer/",
    "./template/",
    "./future/",
    ".",
]

OPTIMIZE = ["-DARCHON", "-O3", "-fopenmp", "-g", "-Wall", "-Wextra", "-Werror", "-Wno-sign-compare"]

dep_libs = [
    "cpp3rdlib/folly:v2018.08.20.00@//cpp3rdlib/folly:folly",
]

cc_binary(
    name="px_test",
    srcs=[d+"/*.cpp" for d in source_dirs],
    deps=dep_libs,
    incs=source_dirs,
    bundle_path="/opt/tiger/motor/channel_sorter/lib",
    optimize=OPTIMIZE
)