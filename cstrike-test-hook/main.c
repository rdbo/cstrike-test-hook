#include "libmem/libmem.h"
mem_module_t            libSDL2;
mem_voidptr_t           p_SDL_GL_SwapWindow;
const mem_uintptr_t     off_SDL_GL_SwapWindow = 0x916fb;
const mem_size_t        sz_SDL_GL_SwapWindow = 5;
const mem_detour_int_t  m_SDL_GL_SwapWindow = method5;

void hack()
{
    system("zenity --info --title=\"cstrike-test-hook\" --text=\"hooked!\"");
    return;
}

const mem_uint8_t hk_SDL_GL_SwapWindow[] = { 
    0x60,                     //pusha
    0xB8, 0x0, 0x0, 0x0, 0x0, //mov eax, 0x00000000
    0xFF, 0xD0,               //call eax
    0x61,                     //popa
    //original code
    0x8b, 0x1c, 0x24,         //mov ebx, [esp]
    0xc3                      //ret
};

__attribute__((constructor))
void dl_main()
{
    system("zenity --info --title=\"cstrike-test-hook\" --text=\"injected!\"");
    libSDL2 = mem_in_get_module(mem_string_new("/libSDL2"));
    p_SDL_GL_SwapWindow = (mem_voidptr_t)((mem_uintptr_t)libSDL2.base + off_SDL_GL_SwapWindow + 4);
    mem_in_protect((mem_voidptr_t)hk_SDL_GL_SwapWindow, sizeof(hk_SDL_GL_SwapWindow), PROT_EXEC | PROT_READ | PROT_WRITE);
    *(mem_uint32_t*)((mem_uintptr_t)hk_SDL_GL_SwapWindow + 2) = (mem_uint32_t)&hack;
    mem_in_detour(p_SDL_GL_SwapWindow, (mem_voidptr_t)((mem_uintptr_t)hk_SDL_GL_SwapWindow), sz_SDL_GL_SwapWindow, m_SDL_GL_SwapWindow, NULL);
}