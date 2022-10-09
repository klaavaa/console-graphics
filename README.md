# Single header file for graphics in the command prompt!

NOTE: C++ WINDOWS ONLY

Example usage:
''' c++
  int main()
  {
    gfx::init();  
    // if you dont specify a size it will automatically make it the largest size possible which is depended on your hardware and software.
    
    while (true)
    {
    
    float dt = gfx::get_delta();
    gfx::clear();
    
    gfx::draw_rect({ 0, 0 }, { 300, 300 }, gfx::COLOR_FLAGS::FG_WHITE | gfx::COLOR_FLAGS::BG_BLACK, gfx::BLOCK_TYPE::LIGHT_SHADE);
		gfx::draw_circle({ (int)pos.x, (int)pos.y }, 20, 
                     gfx::COLOR_FLAGS::FG_GREEN | gfx::COLOR_FLAGS::FG_INTENSITY | gfx::COLOR_FLAGS::BG_BLACK, 
                     gfx::make_block(L'\x25BA')); 
                     // You can put your own unicode as the string by using the make block method. You must pass it as a wchar_t (L) prefix
    
    gfx::refresh();
    
    }
    
    return 0;
  }
'''
