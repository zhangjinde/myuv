#include <stdio.h>
#include <lualib.h>
#include <lauxlib.h>
#include "luv_init.h"


int main(int argc, char* argv[])
{
    lua_State* L = NULL;
    uv_loop_t* loop;
    const char* chunk = "luv.lua";
    if (argc > 1)
    {
        chunk = argv[1];
    }
    L = luaL_newstate();
    if (L == NULL)
    {
        fprintf(stderr, "luaL_newstate() failed.\n");
        return 1;
    }
    luaL_openlibs(L);
    loop = uv_default_loop();
    luv_init(L, loop, argc, argv);
    if (luaL_dofile(L, chunk) != 0)
    {
        fprintf(stderr, lua_tostring(L, -1));
        return 1;
    }

    return 0;
}
