project(
    'advent_of_code',
    'cpp',
    version : '0.0.1',
    default_options : [
        'cpp_std=c++20',
        'buildtype=debug',
        'warning_level=3'
    ]
)

project_description = 'dcut answers to the Advent of Code 2022 challenge.'

build_args = [
]

# --------------------------------------------------

# ======
# Target
# ======

include_dir = include_directories('include')

deps = [
    dependency('threads')
]

build_args += [
    '-DPROJECT_NAME=' + meson.project_name(),
    '-DPROJECT_VERSION=' + meson.project_version()
]

calorie_counting = executable(
    meson.project_name() + '_calorie_counting',
    sources : 'src/day1/calorie_counting.cpp',
    dependencies: deps,
    include_directories : include_dir,
    install : false,
    c_args : build_args
)
