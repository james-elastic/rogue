#include <string>
#include <cstdint>

class LTexture {
public:
  //Initializes variables
  LTexture();
  
  //Deallocates memory
  ~LTexture();
  
  //Loads image at specified path
  bool loadFromFile( SDL_Renderer* renderer,
		     std::string path);
  bool loadFromFile( SDL_Renderer* renderer,
		     std::string path,
		     uint8_t red,
		     uint8_t green,
		     uint8_t blue);
  bool loadFromFile( SDL_Renderer* renderer,
		     std::string path,
		     uint8_t red,
		     uint8_t green,
		     uint8_t blue,
		     bool enable_keying);

  //Deallocates texture
  void free();

  //Renders texture at given point
  void render( SDL_Renderer* renderer, int x, int y );

  //Gets image dimensions
  int getWidth();
  int getHeight();

private:
  //The actual hardware texture
  SDL_Texture* mTexture;
  
  //Image dimensions
  int mWidth;
  int mHeight;
};
