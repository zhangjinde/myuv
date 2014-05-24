#include "luv_native.h"
#include "luv.h"
#include <assert.h>
#include <lualib.h>
#include <lauxlib.h>


static int luv_run(lua_State* L)
{
    int r = 0;
    int args = lua_gettop(L);
    uv_run_mode mode = UV_RUN_DEFAULT;
    assert(args >= 0 && args <= 1);
    if (args == 1)
    {
        const char* smode = luaL_checkstring(L, 1);
        if (strcmp(smode, "once") == 0)
        {
            mode = UV_RUN_ONCE;
        }
        else if (strcmp(smode, "nowait") == 0)
        {
            mode = UV_RUN_NOWAIT;
        }
    }
    r = uv_run(luv_get_loop(L), mode);
    lua_pushinteger(L, r);
    return 1;
}

static int luv_now(lua_State* L)
{
    uint64_t now = uv_now(luv_get_loop(L));
    lua_pushnumber(L, (lua_Number)now);
    return 1;
}

int luaopen_native(lua_State* L)
{
    static const luaL_Reg nativelib[] =
    {
        {"run", luv_run},
        {"now", luv_now},
        {NULL, NULL},
    };
    luaL_newlib(L, nativelib);
    return 1;
}
