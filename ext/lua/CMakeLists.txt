set(LUA_CORE_SRCS src/lapi.c src/lcode.c src/ldebug.c src/ldo.c src/ldump.c 
	src/lfunc.c src/lgc.c src/llex.c src/lmem.c src/lobject.c src/lopcodes.c
	src/lparser.c src/lstate.c src/lstring.c src/ltable.c src/ltm.c src/lundump.c src/lvm.c src/lzio.c)

set(LUA_LIB_SRCS src/lauxlib.c src/lbaselib.c src/ldblib.c src/liolib.c
	src/lmathlib.c src/loslib.c src/ltablib.c src/lstrlib.c src/loadlib.c src/linit.c)

add_library(lua STATIC ${LUA_LIB_SRCS} ${LUA_CORE_SRCS})

target_include_directories(lua PUBLIC "src")

if (UNIX)
	target_link_libraries(lua m)
endif ()