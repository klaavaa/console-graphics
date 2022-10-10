#pragma once
#include <iostream>
#include <cassert>
#include <Windows.h>

#include <vector>

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


namespace gfx
{

	template<typename T>
	struct vec2
	{
		T x, y;

		vec2(T x, T y)
			: x(x), y(y) {}

		vec2()
			: x(0), y(0) {}

		vec2(const vec2<T>& other)
			:
			x(other.x), y(other.y)
		{}

		vec2<int> get_ints()
		{
			return vec2<int>{ (int)x, (int)y };
		}

		T lenght()
		{
			return sqrt(this->x * this->x + this->y * this->y);
		}

		void normalize()
		{
			this->operator/=(this->lenght());
		}

		float dot(const vec2<T>& other)
		{
			return this->x * other.x + this->y * other.y;
		}


		vec2<T>& operator=(const vec2<T>& other)
		{
			this->x = other.x;
			this->y = other.y;
			return *this;
		}

		vec2<T> operator+(const vec2<T>& other)
		{
			return vec2<T>(this->x + other.x, this->y + other.y);
		}
		vec2<T> operator-(const vec2<T>& other)
		{
			return vec2<T>(this->x - other.x, this->y - other.y);
		}
		vec2<T> operator*(const vec2<T>& other)
		{
			return vec2<T>(this->x * other.x, this->y * other.y);
		}
		vec2<T> operator/(const vec2<T>& other)
		{
			return vec2<T>(this->x / other.x, this->y / other.y);
		}

		vec2<T>& operator+=(const vec2<T>& other)
		{
			this->x += other.x;
			this->y += other.y;
			return *this;
		}
		vec2<T>& operator-=(const vec2<T>& other)
		{
			this->x -= other.x;
			this->y -= other.y;
			return *this;
		}vec2<T>& operator*=(const vec2<T>& other)
		{
			this->x *= other.x;
			this->y *= other.y;
			return *this;
		}vec2<T>& operator/=(const vec2<T>& other)
		{
			this->x /= other.x;
			this->y /= other.y;
			return *this;
		}

		vec2<T> operator+(const T& value)
		{
			return vec2<T>(this->x + value, this->y + value);
		}
		vec2<T> operator-(const T& value)
		{
			return vec2<T>(this->x - value, this->y - value);
		}
		vec2<T> operator*(const T& value)
		{
			return vec2<T>(this->x * value, this->y * value);
		}
		vec2<T> operator/(const T& value)
		{
			return vec2<T>(this->x / value, this->y / value);
		}

		vec2<T>& operator+=(const T& value)
		{
			this->x += value;
			this->y += value;
			return *this;
		}
		vec2<T>& operator-=(const T& value)
		{
			this->x -= value;
			this->y -= value;
			return *this;
		}vec2<T>& operator*=(const T& value)
		{
			this->x *= value;
			this->y *= value;
			return *this;
		}
		vec2<T>& operator/=(const T& value)
		{
			if (value == 0) return *this;
			this->x /= value;
			this->y /= value;
			return *this;
		}

		vec2<T> operator-()
		{
			return vec2<T>(-this->x, -this->y);
		}

	};

	template <typename T>
	std::ostream& operator<<(std::ostream& os, const vec2<T>& other)
	{
		os << other.x << " " << other.y;
		return os;
	}

	typedef vec2<int> vec2i;
	typedef vec2<float> vec2f;


	// You need to call this before any other gfx functions.
	// You can define the row and column count
	int init(int width = 0, int height = 0);
	
	// Puts a pixel.
	void put(vec2i p1, WORD color_flags, WORD block_type = GFX_NONE);
	void draw_rect(vec2i pos, vec2i size, WORD color_flags, WORD block_type = GFX_NONE);
	void draw_circle(vec2i pos, float radius, WORD color_flags, WORD block_type = GFX_NONE);


	// Call refresh when you want to refresh the screen.
	void refresh();

	// Call clear when you want to clear the screen (make it black);
	void clear();

	// Sets the console size in rows and columns.
	// See get_largest_possible_size() function for largest size.
	void set_console_size(int width, int height);
	vec2i get_largest_possible_size();


	// get the delta time in seconds
	inline float get_delta();
	
	// get the amount of rows and columns
	vec2i get_console_size();
	
	
	HANDLE get_handle()
	{
		return GetStdHandle(STD_OUTPUT_HANDLE);
	}
	HWND get_hwnd()
	{
		return GetConsoleWindow();
	}
	struct console_data
	{
		bool inited = false;
		HANDLE hndl;
		HWND hwnd;
		int pixel_count;
		std::vector<CHAR_INFO> lp_buffer;
		COORD dw_buf_size;
		COORD dw_buf_coord = { 0, 0 };
		CHAR_INFO EMPTY_CHAR = { {0}, 0 };
		LONGLONG micro_last_time = 0;
		LONGLONG micro_delta_time = 0.f;
	};
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
	
}

inline gfx::vec2i gfx::get_console_size()
{
	check_error();

	CONSOLE_SCREEN_BUFFER_INFO csbi = get_screen_buffer_info();

	int columns, rows;

	columns = csbi.srWindow.Right - csbi.srWindow.Left;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top;



	return { columns, rows };
}
inline float gfx::get_delta()
{
	LARGE_INTEGER ticks;
	QueryPerformanceCounter(&ticks);

	cnsl_data.micro_delta_time = ticks.QuadPart - cnsl_data.micro_last_time;

	cnsl_data.micro_last_time = ticks.QuadPart;

	return (float)(cnsl_data.micro_delta_time) * 0.0000001f;
}
inline gfx::vec2i gfx::get_largest_possible_size()
{
	COORD s = GetLargestConsoleWindowSize(cnsl_data.hndl);
	return { s.X, s.Y };
}
inline void gfx::set_console_size(int width, int height)
{
	check_error();


	SMALL_RECT display_area = { 0, 0, 0, 0 };


	display_area.Right = width;
	display_area.Bottom = height;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(cnsl_data.hndl, &csbi);

	short screen_buffer_width = width;
	short screen_buffer_height = height;

	SetConsoleScreenBufferSize(cnsl_data.hndl, { screen_buffer_width, screen_buffer_height });

	SetConsoleWindowInfo(cnsl_data.hndl, TRUE, &display_area);

}
inline void gfx::put(vec2i p1, WORD color_flags, WORD block_type)
{
	check_error();

	int index = p1.y * cnsl_data.dw_buf_size.X + p1.x;
	if (index >= cnsl_data.lp_buffer.size())
		return;
	cnsl_data.lp_buffer[index].Attributes = (WORD)color_flags;
	cnsl_data.lp_buffer[index].Char.UnicodeChar = (WCHAR)block_type;
}
inline void gfx::draw_rect(vec2i pos, vec2i size, WORD color_flags, WORD block_type)
{
	check_error();
	for (int i = 0; i < size.x; i++)
	{
		for (int j = 0; j < size.y; j++)
		{
			put({ pos.x + i, pos.y + j }, color_flags, block_type);
		}
	}

}
inline void gfx::draw_circle(vec2i pos, float radius, WORD color_flags, WORD block_type)
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
				put({ i, j }, color_flags, block_type);
			}
		}
	}
}
inline void gfx::refresh()
{
	check_error();
	vec2i size = get_console_size();
	SMALL_RECT sr = { 0, 0, size.x, size.y };
	WriteConsoleOutputW(cnsl_data.hndl, &cnsl_data.lp_buffer[0], cnsl_data.dw_buf_size, cnsl_data.dw_buf_coord, &sr);

}
inline void gfx::clear()
{
	check_error();
	std::fill(cnsl_data.lp_buffer.begin(), cnsl_data.lp_buffer.end(), cnsl_data.EMPTY_CHAR);
}
inline int gfx::init(int width, int height)
{


	cnsl_data.hndl = get_handle();
	cnsl_data.hwnd = get_hwnd();

	if (width == 0 && height == 0)
		cnsl_data.dw_buf_size = GetLargestConsoleWindowSize(cnsl_data.hndl);

	cnsl_data.pixel_count = cnsl_data.dw_buf_size.X * cnsl_data.dw_buf_size.Y;


	cnsl_data.inited = true;

	cnsl_data.lp_buffer.resize(cnsl_data.pixel_count);

	set_console_size(cnsl_data.dw_buf_size.X, cnsl_data.dw_buf_size.Y);


	SetConsoleDisplayMode(cnsl_data.hndl, CONSOLE_FULLSCREEN_MODE, 0);
	EnableScrollBar(cnsl_data.hwnd, SB_BOTH, ESB_DISABLE_BOTH | ESB_DISABLE_DOWN | ESB_DISABLE_RIGHT);
	ShowScrollBar(cnsl_data.hwnd, SB_BOTH, FALSE);
	SetWindowLongW(cnsl_data.hwnd, GWL_STYLE, WS_VISIBLE | WS_CAPTION | WS_SIZEBOX | WS_TILEDWINDOW);

	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(cnsl_data.hndl, &cci);
	get_delta();


	return 0;
}


