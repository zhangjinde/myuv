#include "luv.h"

static const luaL_Reg loadedlibs[] = 
{
    {"timer", luaopen_timer},
    {NULL, NULL}
};

static int luv_init(lua_State *L, uv_loop_t* loop, int argc, char *argv[])
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
}

int luvit_run(lua_State *L) 
{

}

int main(int argc, char* argv[])
{
    lua_State* L = NULL;
    uv_loop_t* loop;

    argv = uv_setup_args(argc, argv);
    L = luaL_newstate();
    if (L == NULL)
    {
        fprintf(stderr, "luaL_newstate() failed.\n");
        return 1;
    }
    luaL_openlibs(L);
    loop = uv_default_loop();
    luv_init(L, loop, argc, argv);

    return 0;
}
