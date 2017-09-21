#include <string>
#include <cstdint>

class LTexture {
public:
  //Initializes variables
  LTexture( SDL_Renderer* gRenderer );
  
  //Deallocates memory
  ~LTexture();
  
  //Loads image at specified path
  bool loadFromFile( std::string path,
		     uint8_t red,
		     uint8_t green,
		     uint8_t blue);

  //Deallocates texture
  void free();

  //Renders texture at given point
  void render( int x, int y );

  //Gets image dimensions
  int getWidth();
  int getHeight();

private:
  //The actual hardware texture
  SDL_Texture* mTexture;
  SDL_Renderer* mRenderer;
  
  //Image dimensions
  int mWidth;
  int mHeight;
};
