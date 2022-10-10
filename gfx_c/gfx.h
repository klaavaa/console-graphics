#pragma once
#include <stdio.h>
#include <assert.h>
#include <Windows.h>
#include <stdbool.h>


#define GFX_BG_BLACK 0
#define GFX_BG_BLUE 0x0010
#define GFX_BG_GREEN  0x0020
#define GFX_BG_RED  0x0040
#define GFX_BG_PURPLE  GFX_BG_RED	|   GFX_BG_BLUE
#define GFX_BG_YELLOW  GFX_BG_GREEN |	GFX_BG_RED
#define GFX_BG_WHITE   GFX_BG_RED	|   GFX_BG_GREEN | GFX_BG_BLUE

#define GFX_FG_BLUE  0x0001
#define GFX_FG_GREEN  0x0002
#define GFX_FG_RED  0x0004
#define GFX_FG_PURPLE  GFX_FG_RED	| GFX_FG_BLUE
#define GFX_FG_YELLOW  GFX_FG_GREEN | GFX_FG_RED
#define GFX_FG_WHITE   GFX_FG_RED	| GFX_FG_GREEN | GFX_BG_BLUE

#define GFX_FG_INTENSITY  0x0008
#define GFX_BG_INTENSITY  0x0080


#define GFX_NONE  0
#define GFX_FULL_BLOCK  L'\x2588'
#define GFX_LIGHT_SHADE  L'\x2591'
#define GFX_MEDIUM_SHADE  L'\x2592'
#define GFX_DARK_SHADE  L'\x2593'


typedef struct
{
	float x;
	float y;
} gfx_vec2f;


typedef struct
{
	int x;
	int y;
} gfx_vec2i;


// You need to call this before any other gfx functions.
// You can define the row and column count
int gfx_init(int width, int height);
void gfx_destroy();

// Puts a pixel.
void gfx_put(gfx_vec2i p1, WORD color_flags, WORD block_type);
void gfx_draw_rect(gfx_vec2i pos, gfx_vec2i size, WORD color_flags, WORD block_type);
void gfx_draw_circle(gfx_vec2i pos, float radius, WORD color_flags, WORD block_type);


// Call refresh when you want to refresh the screen.
void gfx_refresh();

// Call clear when you want to clear the screen (make it black);
void gfx_clear();

// Sets the console size in rows and columns.
// See get_largest_possible_size() function for largest size.
void  gfx_set_console_size(int width, int height);
gfx_vec2i gfx_get_largest_possible_size();

// get the delta time in seconds
inline float gfx_get_delta();

// get the amount of rows and columns
gfx_vec2i gfx_get_console_size();


HANDLE get_handle()
{
	return GetStdHandle(STD_OUTPUT_HANDLE);
}
HWND get_hwnd()
{
	return GetConsoleWindow();
}

typedef struct cnsldata
{
	
	HANDLE hndl;
	HWND hwnd;
	int pixel_count;
	CHAR_INFO* lp_buffer;
	COORD dw_buf_size;
	COORD dw_buf_coord;
	CHAR_INFO EMPTY_CHAR;
	LONGLONG micro_last_time;
	LONGLONG micro_delta_time;
	bool inited;
} console_data;

console_data cnsl_data;


void check_error()
{
	assert(cnsl_data.inited && "gfx::init() not called");
}


CONSOLE_SCREEN_BUFFER_INFO get_screen_buffer_info()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(cnsl_data.hndl, &csbi);
	return csbi;
}


inline gfx_vec2i gfx_get_console_size()
{
	check_error();

	CONSOLE_SCREEN_BUFFER_INFO csbi = get_screen_buffer_info();

	int columns, rows;

	columns = csbi.srWindow.Right - csbi.srWindow.Left;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top;

	gfx_vec2i r = {columns, rows};

	return r;
}

inline float gfx_get_delta()
{
	LARGE_INTEGER ticks;
	QueryPerformanceCounter(&ticks);

	cnsl_data.micro_delta_time = ticks.QuadPart - cnsl_data.micro_last_time;

	cnsl_data.micro_last_time = ticks.QuadPart;

	return (float)(cnsl_data.micro_delta_time) * 0.0000001f;
}

inline gfx_vec2i gfx_get_largest_possible_size()
{
	COORD s = GetLargestConsoleWindowSize(cnsl_data.hndl);
	gfx_vec2i r = {s.X, s.Y};

	return r;
}
inline void gfx_set_console_size(int width, int height)
{
	check_error();


	SMALL_RECT display_area = { 0, 0, 0, 0 };


	display_area.Right = width;
	display_area.Bottom = height;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(cnsl_data.hndl, &csbi);

	short screen_buffer_width = width;
	short screen_buffer_height = height;

	COORD sbc;
	sbc.X = screen_buffer_width;
	sbc.Y = screen_buffer_height;

	SetConsoleScreenBufferSize(cnsl_data.hndl, sbc);

	SetConsoleWindowInfo(cnsl_data.hndl, TRUE, &display_area);


	cnsl_data.pixel_count = width * height;
	
	cnsl_data.lp_buffer = realloc(cnsl_data.lp_buffer, cnsl_data.pixel_count * sizeof(CHAR_INFO));

}
inline void gfx_put(gfx_vec2i p1, WORD color_flags, WORD block_type)
{
	check_error();

	int index = p1.y * cnsl_data.dw_buf_size.X + p1.x;
	if (index >= cnsl_data.pixel_count)
		return;
	cnsl_data.lp_buffer[index].Attributes = (WORD)color_flags;
	cnsl_data.lp_buffer[index].Char.UnicodeChar = (WCHAR)block_type;
}
inline void gfx_draw_rect(gfx_vec2i pos, gfx_vec2i size, WORD color_flags, WORD block_type)
{
	check_error();
	for (int i = 0; i < size.x; i++)
	{
		for (int j = 0; j < size.y; j++)
		{
			gfx_vec2i p = {pos.x + i, pos.y + j};
			gfx_put(p, color_flags, block_type);
		}
	}

}
inline void gfx_draw_circle(gfx_vec2i pos, float radius, WORD color_flags, WORD block_type)
{

	check_error();
	for (int i = pos.x - radius; i < pos.x + 2 * radius; i++)
	{
		for (int j = pos.y - radius; j < pos.y + 2 * radius; j++)
		{
			int dx = pos.x - i;
			int dy = pos.y - j;
			if (dx * dx + dy * dy < radius * radius)
			{
				gfx_vec2i p = {i, j};
				gfx_put(p, color_flags, block_type);
			}
		}
	}

}
inline void gfx_refresh()
{
	check_error();
	gfx_vec2i size = gfx_get_console_size();
	SMALL_RECT sr = { 0, 0, size.x, size.y };
	WriteConsoleOutputW(cnsl_data.hndl, &cnsl_data.lp_buffer[0], cnsl_data.dw_buf_size, cnsl_data.dw_buf_coord, &sr);

}
inline void gfx_clear()
{
	check_error();

	for (size_t i = 0; i < cnsl_data.pixel_count; i++)
	{
		cnsl_data.lp_buffer[i].Char.UnicodeChar = 0;
		cnsl_data.lp_buffer[i].Attributes = 0;
	}
}

inline int gfx_init(int width, int height)
{

	cnsl_data.dw_buf_coord.X = 0;
	cnsl_data.dw_buf_coord.Y = 0;

	cnsl_data.dw_buf_size.X = width;
	cnsl_data.dw_buf_size.Y = width;

	cnsl_data.EMPTY_CHAR.Char.UnicodeChar = 0;
	cnsl_data.EMPTY_CHAR.Attributes = 0;

	cnsl_data.micro_delta_time = 0;
	cnsl_data.micro_last_time = 0;

	cnsl_data.inited = false;

	cnsl_data.hndl = get_handle();
	cnsl_data.hwnd = get_hwnd();

	if (width == 0 && height == 0)
		cnsl_data.dw_buf_size = GetLargestConsoleWindowSize(cnsl_data.hndl);

	cnsl_data.pixel_count = cnsl_data.dw_buf_size.X * cnsl_data.dw_buf_size.Y;


	cnsl_data.inited = true;

	cnsl_data.lp_buffer = malloc(sizeof(CHAR_INFO) * cnsl_data.pixel_count);

	gfx_set_console_size(cnsl_data.dw_buf_size.X, cnsl_data.dw_buf_size.Y);


	SetConsoleDisplayMode(cnsl_data.hndl, CONSOLE_FULLSCREEN_MODE, 0);
	EnableScrollBar(cnsl_data.hwnd, SB_BOTH, ESB_DISABLE_BOTH | ESB_DISABLE_DOWN | ESB_DISABLE_RIGHT);
	ShowScrollBar(cnsl_data.hwnd, SB_BOTH, FALSE);
	SetWindowLongW(cnsl_data.hwnd, GWL_STYLE, WS_VISIBLE | WS_CAPTION | WS_SIZEBOX | WS_TILEDWINDOW);

	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(cnsl_data.hndl, &cci);
	gfx_get_delta();


	return 0;
}

void gfx_destroy()
{
	check_error();

	free(cnsl_data.lp_buffer);

}


