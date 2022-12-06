project(
    'advent_of_code',
    'cpp',
    version : '0.0.1',
    default_options : [
        'cpp_std=c++20',
        'warning_level=3'
    ]
)

project_description = 'dcut answers to the Advent of Code 2022 challenge.'

build_args = [
    '-g3'
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

rock_paper_scissors = executable(
    meson.project_name() + '_rock_paper_scissors',
    sources : 'src/day2/rock_paper_scissors.cpp',
    dependencies: deps,
    include_directories : include_dir,
    install : false,
    c_args : build_args
)

rucksack_reorg = executable(
    meson.project_name() + '_rucksack_reorg',
    sources : 'src/day3/rucksack_reorg.cpp',
    dependencies: deps,
    include_directories : include_dir,
    install : false,
    c_args : build_args
)

camp_cleanup = executable(
    meson.project_name() + '_camp_cleanup',
    sources : 'src/day4/camp_cleanup.cpp',
    dependencies: deps,
    include_directories : include_dir,
    install : false,
    c_args : build_args
)

supply_stacks = executable(
    meson.project_name() + '_supply_stacks',
    sources : 'src/day5/supply_stacks.cpp',
    dependencies: deps,
    include_directories : include_dir,
    install : false,
    c_args : build_args
)

tuning_trouble = executable(
    meson.project_name() + '_tuning_trouble',
    sources : 'src/day6/tuning_trouble.cpp',
    dependencies: deps,
    include_directories : include_dir,
    install : false,
    c_args : build_args
)