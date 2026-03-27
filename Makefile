all:
  gcc pixel.c -o pixelMadness -lSDL2 -lm
clean:
  rm pixelMadness
