# Single header file for graphics in the command prompt!

NOTE: C++ WINDOWS ONLY

Example usage:
``` c++

#include "gfx.hpp"

int main()
{

	// you must call init before calling other gfx functions
	gfx::init();  
	// If you dont specify a size,
	// it will automatically make it the largest size possible,
	// which is depended on your hardware and software.

	vec2f pos = {0.f, 0.f};

	while (true)
	{

	float dt = gfx::get_delta();
	gfx::clear();

	//		    pos		size		coloring related flags					character to display
	gfx::draw_rect({ 0, 0 }, { 300, 300 }, gfx::COLOR_FLAGS::FG_WHITE | gfx::COLOR_FLAGS::BG_BLACK, gfx::BLOCK_TYPE::LIGHT_SHADE);

	gfx::draw_circle(pos.get_ints(), 20, 
		     gfx::COLOR_FLAGS::FG_GREEN | gfx::COLOR_FLAGS::FG_INTENSITY | gfx::COLOR_FLAGS::BG_BLACK, 
		     gfx::make_block(L'\x25BA')); 
		     // You can put your own unicode as the string by using the make block method. 
		     // You must pass it as a wchar_t (L) prefix

	pos += { 2.f * dt, 0.f };
	// move pos by 2 blocks per second

	gfx::refresh();

	}

	return 0;
}
```
