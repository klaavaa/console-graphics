# Single header file for graphics in the command prompt!

NOTE: C OR C++ WINDOWS ONLY

Example usage of C++:
``` c++
#include "gfx.hpp"

int main()
{

	// you must call init before calling other gfx functions
	gfx::init();
	// If you dont specify a size,
	// it will automatically make it the largest size possible,
	// which is depended on your hardware and software.

	gfx::vec2f pos = { 0.f, 25.f };

	while (true)
	{
		float dt = gfx::get_delta();
		gfx::clear();

		//		  pos	   size		coloring related flags	  character to display
		gfx::draw_rect({ 0, 0 }, { 300, 300 }, GFX_FG_WHITE | GFX_BG_BLACK, GFX_LIGHT_SHADE);

		gfx::draw_circle(pos.get_ints(), 20,
			GFX_FG_GREEN | GFX_FG_INTENSITY | GFX_BG_BLACK, L'\x25BA');
		// You can pass your own unicode to display as the text.
		// You must pass it as a wchar_t (L) prefix

		pos += { 2.f * dt, 1.f * dt };
		// move the x - position by 2 blocks per second

		gfx::refresh();

	}

	return 0;
}
```


Example usage of C

```c
#include "gfx.h"

int main()
{

	gfx_init(0, 0);
	// If you set the size as (0, 0),
	// it will automatically make it the largest size possible,
	// which is depended on your hardware and software.
	
	
	gfx_vec2f circle_pos = { 0.f, 15.f };

	while (true)
	{
		float dt = gfx_get_delta();
		gfx_clear();

		gfx_vec2i rect_pos = {0, 0};
	

		gfx_vec2i rect_size = { 300, 300 };
	
		//		    pos		size		coloring related flags			character to display
		gfx_draw_rect(rect_pos, rect_size, GFX_FG_WHITE | GFX_BG_BLACK, GFX_LIGHT_SHADE);

		gfx_vec2i int_circle_pos = { (int)circle_pos.x, (int)circle_pos.y };
		gfx_draw_circle(int_circle_pos, 20, GFX_FG_GREEN | GFX_FG_INTENSITY | GFX_BG_BLACK, L'\x25BA');
		// You can pass your own unicode to display as the text.
		// You must pass it as a wchar_t (L) prefix

		circle_pos.x += 1.f * dt;
		// move the x position by 1 block per second

		gfx_refresh();

	}

	return 0;
}
```

