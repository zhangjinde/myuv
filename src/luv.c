#include "luv.h"
#include <malloc.h>
#include <lauxlib.h>

luv_handle_t* luv_handle_create(lua_State* L, size_t size, const char* name)
{
    luv_handle_t* udata = (luv_handle_t*)lua_newuserdata(L, sizeof(luv_handle_t));
    udata->handle = (uv_handle_t*)malloc(size);
    udata->ref = LUA_NOREF;
    luaL_setmetatable(L, name);
    return udata;
}

uv_handle_t* luv_checkudata(lua_State* L, int index)
{
    luv_handle_t* udata = NULL;
    luaL_checktype(L, index, LUA_TUSERDATA);
    udata = (luv_handle_t*)lua_touserdata(L, index);
    return (udata ? udata->handle : NULL);
}

void luv_set_loop(lua_State* L, uv_loop_t* loop)
{
    lua_pushlightuserdata(L, loop);
    lua_setfield(L, LUA_REGISTRYINDEX, "loop");
}

uv_loop_t* luv_get_loop(lua_State *L) 
{
    uv_loop_t* loop = NULL;
    lua_getfield(L, LUA_REGISTRYINDEX, "loop");
    loop = lua_touserdata(L, -1);
    lua_pop(L, 1);
    return loop;
}