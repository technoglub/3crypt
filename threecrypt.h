#ifndef THREECRYPT_H
#define THREECRYPT_H
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <stdlib.h>
#include <symm/common.h>
#include <shim/macros.h>
#ifdef THREECRYPT_EXT_ENABLE_DRAGONFLY_V1
#	include <symm/dragonfly_v1.h>
#else
#	error "THREECRYPT_ENABLE_DRAGONFLY_V1 not defined... Currently the only supported crypto method."
#endif
#if    defined (SHIM_OS_UNIXLIKE) || defined (SHIM_OS_WINDOWS)
#	if    defined (SHIM_OS_UNIXLIKE)
#		ifdef __NetBSD__
#			include <ncurses/ncurses.h>
#		else
#			include <ncurses.h>
#		endif
#	elif  defined (SHIM_OS_WINDOWS)
#		include <shim/errors.h>
#		include <windows.h>
#		include <conio.h>
#	else
#		error "Critical error. Not unixlike or windows, as already detected."
#	endif
#else
#	error "Unsupported OS."
#endif /* ~ if defined (SHIM_OS_UNIXLIKE) || defined (SHIM_OS_WINDOWS) */
#ifdef THREECRYPT_EXT_TERM_BUFFER_SIZE
#	define THREECRYPT_TERM_BUFFER_SIZE	THREECRYPT_EXT_TERM_BUFFER_SIZE
#else
#	define THREECRYPT_TERM_BUFFER_SIZE	120
#endif
#define THREECRYPT_MODE_NONE		0
#define THREECRYPT_MODE_SYMMETRIC_ENC	(THREECRYPT_MODE_NONE + 1)
#define THREECRYPT_MODE_SYMMETRIC_DEC	(THREECRYPT_MODE_SYMMETRIC_ENC + 1)
#define THREECRYPT_MODE_DUMP		(THREECRYPT_MODE_SYMMETRIC_DEC + 1)
#define THREECRYPT_ARGMAP_MAX_COUNT	100
#define THREECRYPT_METHOD_NONE		0
#define THREECRYPT_METHOD_DRAGONFLY_V1	(THREECRYPT_METHOD_NONE + 1)
#define THREECRYPT_MIN_ID_STRING_BYTES	sizeof(SYMM_DRAGONFLY_V1_ID)
#define THREECRYPT_MAX_ID_STRING_BYTES	sizeof(SYMM_DRAGONFLY_V1_ID)
#define THREECRYPT_NUMBER_METHODS	1

typedef struct SHIM_PUBLIC {
	Symm_Catena_Input catena_input;
	Shim_Map          input_map;
	Shim_Map          output_map;
	char const *      input_filename;
	char const *      output_filename;
	size_t            input_filename_size;
	size_t            output_filename_size;
	int               mode;
} Threecrypt;
typedef struct SHIM_PUBLIC {
	char const ** strings;
	size_t *      sizes;
	size_t        max_string_size;
	int           count;
} Threecrypt_Arg_Map;

SHIM_BEGIN_DECLS

void SHIM_PUBLIC
threecrypt (int const, char const *[]);

SHIM_END_DECLS

#endif /* ~ THREECRYPT_H */