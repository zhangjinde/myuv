#include "luv.h"
#include <malloc.h>
#include <lualib.h>
#include <lauxlib.h>


static void on_timer_callback(uv_timer_t* handle)
{

}

static int timer_new(lua_State* L)
{
    uv_timer_t* timer = luv_create_timer(L);
    uv_timer_init(uv_default_loop(), timer);
    return 1;
}

static int timer_start(lua_State* L)
{
    int r = 0;
    uv_timer_t* handle = (uv_timer_t*)luv_checkudata(L, 1);
    int64_t timeout = (int64_t)luaL_checknumber(L, 2);
    int64_t repeat = (int64_t)luaL_checknumber(L, 3);
    luaL_checktype(L, 5, LUA_TFUNCTION);
    r = uv_timer_start(handle, on_timer_callback, timeout, repeat);
    if (r == 0)
    {
        luaL_ref(L, 4);
    }
    lua_pushboolean(L, r);
    return 1;
}

static int timer_tostring(lua_State* L)
{
    uv_timer_t* handle = (uv_timer_t*)luv_checkudata(L, 1);
    lua_pushfstring(L, "timer* (0x%p)", handle);
    return 1;
}

static int timer_close(lua_State* L)
{
    uv_close(luv_checkudata(L, 1), NULL);
    return 0;
}

static int timer_gc(lua_State* L)
{
    uv_timer_t* handle = (uv_timer_t*)luv_checkudata(L, 1);
    return 0;
}

static void create_meta(lua_State* L)
{
    static const luaL_Reg metalib[] = 
    {
        {"start", timer_start},
        {"close", timer_close},
        {"__gc", timer_gc},
        {"__tostring", timer_tostring},
        {NULL, NULL}
    };
    luaL_newmetatable(L, LUA_FILEHANDLE);
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_setfuncs(L, metalib, 0);
    lua_pop(L, 1);
}

int luaopen_timer(lua_State *L)
{
    static const luaL_Reg timerlib[] = 
    {
        {"new", timer_new},
        {NULL, NULL}
    };
    luaL_newlib(L, timerlib);  /* new module */
    create_meta(L);
    return 1;
}