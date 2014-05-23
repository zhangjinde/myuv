#pragma once

#include "config.h"
#include <uv.h>
#include <lua.h>

/*
 * luv handles are used as the userdata type that points to uv handles.
 */
typedef struct 
{
    uv_handle_t*    handle; /* The actual uv handle. memory managed by lua */
    int             ref;
}luv_handle_t;


#define LUV_HANDLE          "luv.handle"
#define LUV_TIMER_NAME      "luv.timer"
#define LUV_TCP_NAME        "luv.tcp"
#define LUV_UDP_NAME        "luv.udp"
#define LUV_FS_NAME         "luv.fs"
#define LUV_PIPE_NAME       "luv.pipe"
#define LUV_PROCESS_NAME    "luv.process"


/* Create a new luv_handle.  Input is the lua state and the size of the desired 
 * uv struct.  A new userdata is created and pushed onto the stack.  The luv
 * handle and the uv handle are interlinked.
 */
luv_handle_t*   luv_handle_create(lua_State* L, size_t size, const char* name);
uv_handle_t*    luv_checkudata(lua_State* L, int index);

INLINE uv_timer_t* luv_create_timer(lua_State* L)
{
    luv_handle_t* timer = luv_handle_create(L, sizeof(uv_timer_t), LUV_TIMER_NAME);
    return (uv_timer_t*)timer->handle;
}

void luv_set_loop(lua_State* L, uv_loop_t* loop);
uv_loop_t* luv_get_loop(lua_State *L);

int luaopen_timer(lua_State *L);