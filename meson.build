project('3crypt',
	'c',
	default_options: ['c_std=c18', 'optimization=3', 'buildtype=release', 'strip=true'])
_PROJECT = '3crypt'
_LANG    = 'c'
_UNIXLIKE_OPERATING_SYSTEMS  = ['openbsd', 'freebsd', 'netbsd', 'darwin', 'linux']
_SUPPORTED_OPERATING_SYSTEMS = _UNIXLIKE_OPERATING_SYSTEMS + ['windows']
_GCC_COMPATIBLE_COMPILERS    = ['gcc', 'clang']
_SUPPORTED_COMPILERS         = _GCC_COMPATIBLE_COMPILERS + ['msvc']

compiler = meson.get_compiler(_LANG)
os = host_machine.system()
shim_static = get_option('shim_static')
symm_static = get_option('symm_static')
assert (os in _SUPPORTED_OPERATING_SYSTEMS, 'You are trying to build 3crypt using an unsupported operating system!')
assert (compiler.get_id() in _SUPPORTED_COMPILERS, 'You are trying to build 3crypt using an unsupported compiler!')

if os == 'windows' and compiler.get_id() == 'msvc'
  _D_PREFIX = '/D'
else
  _D_PREFIX = '-D'
endif
src = [
  'threecrypt.c',
  'main.c',
  'dragonfly_v1.c',
  'args.c'
  ]
include = [
  ]
lib_dir = [
  ]
lib_depends = [
  ]
lang_flags = [
  ]
gcc_compatible_flags = [
  '-fvisibility=hidden',
  '-fstrict-aliasing',
  '-Wall',
  '-funroll-loops'
  ]
if shim_static
  lang_flags += _D_PREFIX + 'SHIM_EXT_STATIC_LIB'
endif
if symm_static
  lang_flags += _D_PREFIX + 'SYMM_EXT_STATIC_LIB'
endif
if os != 'netbsd' and compiler.get_id() != 'clang'
  gcc_compatible_flags += '-flto'
endif
if os == 'darwin'
  _flag = _D_PREFIX + '__STDC_WANT_LIB_EXT1__=1'
  lang_flags += _flag
endif
if os in _UNIXLIKE_OPERATING_SYSTEMS and compiler.get_id() in _GCC_COMPATIBLE_COMPILERS
  lang_flags += gcc_compatible_flags
endif
is_gcc_compatible = (compiler.get_id() in _GCC_COMPATIBLE_COMPILERS)
if os == 'openbsd' or os == 'freebsd' or os == 'darwin'
  include += '/usr/local/include'
  lib_dir += '/usr/local/lib'
elif os == 'netbsd'
  include  += '/usr/local/include'
  include  += '/usr/pkg/include'
  lib_dir += '/usr/local/lib'
  lib_dir += '/usr/pkg/lib'
elif os == 'linux'
  include += '/usr/include'
  if compiler.get_id() == 'gcc'
    lang_flags += '-flto'
  endif
elif os == 'windows'
  include += 'C:/include'
  lib_dir += 'C:/lib'
endif
if get_option('enable_dragonfly_v1')
  _flag = _D_PREFIX + 'THREECRYPT_EXT_ENABLE_DRAGONFLY_V1'
  lang_flags += _flag
  if get_option('dragonfly_v1_default_garlic') != 23
    _garlic = get_option('dragonfly_v1_default_garlic').to_string()
    _flag   = _D_PREFIX + 'THREECRYPT_EXT_DRAGONFLY_V1_DEFAULT_GARLIC=' + _garlic
    lang_flags += _flag
  endif
endif
if get_option('strict_arg_processing')
  _flag = _D_PREFIX + 'THREECRYPT_EXT_STRICT_ARG_PROCESSING'
  lang_flags += _flag
endif
if compiler.get_id() in _GCC_COMPATIBLE_COMPILERS
  if get_option('native_optimize')
    lang_flags += '-march=native'
  endif
  if get_option('use_debug_symbols')
    lang_flags += '-g'
  endif
endif
if os in ['openbsd', 'freebsd', 'darwin', 'netbsd']
  lib_depends += compiler.find_library('shim', dirs: lib_dir, static: shim_static)
  lib_depends += compiler.find_library('symm', dirs: lib_dir, static: symm_static)
  if shim_static
    lib_depends += compiler.find_library('ncurses')
  endif
elif os == 'linux'
  lib_depends += compiler.find_library('shim', static: shim_static)
  lib_depends += compiler.find_library('symm', static: symm_static)
  if shim_static
    lib_depends += compiler.find_library('ncurses')
    lib_depends += compiler.find_library('tinfo')
  endif
elif os == 'windows'
  lib_depends += compiler.find_library('shim', dirs: lib_dir, static: shim_static)
  lib_depends += compiler.find_library('symm', dirs: lib_dir, static: symm_static)
endif

if os != 'windows'
  executable('3crypt', sources: src, dependencies: lib_depends,
	     include_directories: include, install: true,
	     c_args: lang_flags)
  install_man('3crypt.1')
else
  executable('3crypt', sources: src, dependencies: lib_depends,
	     include_directories: include, install: true,
	     c_args: lang_flags, install_dir: 'C:/bin')
endif
