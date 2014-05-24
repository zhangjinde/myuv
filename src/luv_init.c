#include "luv_init.h"
#include <lualib.h>
#include <lauxlib.h>
#include "luv_native.h"
#include "luv_timer.h"


static const luaL_Reg loadedlibs[] = 
{
    {"native", luaopen_native},
    {"timer", luaopen_timer},
    {NULL, NULL}
};


int luv_init(lua_State *L, uv_loop_t* loop, int argc, char *argv[])
{
    int index;

    const luaL_Reg *lib;
    /* call open functions from 'loadedlibs' and set results to global table */
    for (lib = loadedlibs; lib->func; lib++) 
    {
        luaL_requiref(L, lib->name, lib->func, 1);
        lua_pop(L, 1);  /* remove lib */
    }

    /* Get argv */
    lua_createtable (L, argc, 0);
    for (index = 0; index < argc; index++) {
        lua_pushstring (L, argv[index]);
        lua_rawseti(L, -2, index);
    }
    lua_setglobal(L, "argv");

    luv_set_loop(L, loop);

    return 0;
}
