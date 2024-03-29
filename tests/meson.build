project(
  'test_suite', ['c', 'cpp'],
  version : '1.0.0',
  license : 'MIT',
  default_options : [
    'cpp_std=c++20',
    'warning_level=3',
    'optimization=2',
  ],
  meson_version : '>= 0.60.0'
)

result = [ 'Passed options:' ]

c = meson.get_compiler('c')
cpp = meson.get_compiler('cpp')
c_id = c.get_id()
cpp_id = cpp.get_id()
cross = meson.is_cross_build()
sh = find_program('sh')

builddir = meson.current_build_dir()
sourcedir = meson.current_source_dir()
package = meson.project_name()
version = meson.project_version()

ldflags_add = []
cflags_add = []

ldflags_opt = []
cflags_opt = []

cflags_opt += [
  [ '-ggdb' ],

  # enabled by warning_level=3
  #[ '-Wall' ],
  #[ '-Wextra' ],
  #[ '-Werror' ],

  # Not enabled by Wall
  [ '-Weffc++' ],
  [ '-pedantic' ],
  [ '-pedantic-errors' ],
  #[ '-Waggregate-return' ],
  [ '-Wcast-qual' ],
  [ '-Wchar-subscripts' ],
  [ '-Wcomment' ],
  #[ '-Wconversion' ],
  [ '-Wdisabled-optimization' ],
  #[ '-Wdouble-promotion' ],
  #[ '-Wfloat-equal' ],
  [ '-Wformat' ],
  [ '-Wformat=2' ],
  #[ '-Wformat-truncation' ],
  [ '-Wformat-nonliteral' ],
  [ '-Wformat-security' ],
  [ '-Wformat-y2k' ],
  #[ '-Wimplicit' ],
  [ '-Wimplicit-fallthrough' ],
  [ '-Wimport' ],
  #[ '-Wint-conversion' ],
  [ '-Winit-self' ],
  #[ '-Winline' ],
  [ '-Winvalid-pch' ],
  #[ '-Wlong-long' ],
  #[ '-Wmissing-braces' ],
  [ '-Wmissing-field-initializers' ],
  [ '-Wmissing-format-attribute' ],
  [ '-Wmissing-include-dirs' ],
  [ '-Wmissing-noreturn' ],
  [ '-Wparentheses' ],
  [ '-Wpointer-arith' ],
  [ '-Wredundant-decls' ],
  [ '-Wreturn-type' ],
  [ '-Wsequence-point' ],
  [ '-Wshadow' ],
  [ '-Wsign-compare' ],
  [ '-Wstack-protector' ],
  [ '-Wstrict-aliasing' ],
  [ '-Wstrict-aliasing=2' ],
  [ '-Wswitch' ],
  [ '-Wswitch-default' ],
  [ '-Wswitch-enum' ],
  [ '-Wtrigraphs' ],
  [ '-Wundef' ],
  [ '-Wuninitialized' ],
  [ '-Wunknown-pragmas' ],
  [ '-Wunreachable-code' ],
  [ '-Wunused' ],
  [ '-Wunused-function' ],
  [ '-Wunused-label' ],
  [ '-Wunused-parameter' ],
  [ '-Wunused-value' ],
  [ '-Wunused-variable' ],
  [ '-Wvariadic-macros' ],
  [ '-Wvla' ],
  [ '-Wwrite-strings' ],

  # Sanitizer
  #[ '-fsanitize=undefined,address' ],
]
ldflags_opt += [
  [ '-Wl,-O2' ],
  [ '-Wl,--as-needed' ],
]

add_global_arguments(cflags_opt, language: ['c', 'cpp'])
add_global_link_arguments(ldflags_opt, language: ['c', 'cpp'])

dep_gtest = dependency('gtest')

sources = [
  'src/main.cxx',

  'src/sort.cxx',
]

target_name = 'test_suite'
target_type = 'executable'

test_suite = build_target(
  target_name,
  sources,
  target_type: target_type,
  install : false,
  dependencies: [
    dep_gtest,
  ],
)
