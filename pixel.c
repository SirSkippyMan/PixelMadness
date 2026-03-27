/**
 * PIXEL MADNESS!!!
 * A colorful grid animation that reacts to mouse movement and clicks.
 * See README.md for instructions and controls.
 * 
 * WARNING: This program contains bright flashing colours that may
 * cause seizures in some people. Viewer discretion is advised.
 * 
 * @author: Josh Nygaard (joshdn03@gmail.com)
 * @version: 1.0
 */

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>

// Configuration constants
#define WIDTH 800
#define HEIGHT 600
#define PIXEL_SIZE 20
#define MIN_CYCLE 30
#define MAX_CYCLE 3200
#define MIN_SPEED 0.5
#define MAX_SPEED 30
#define CYCLE_STEP 5

// Modes
#define MODE_RADIAL 0
#define MODE_HORIZONTAL 1
#define MODE_VERTICAL 2
#define MODE_DIAGONAL 3
#define MODE_SPIRAL 4
#define MODE_RINGS 5
#define MODE_COUNT 6

int db = 0;

// Default values for animation(can be reset with number keys)
float speed = 2; // How fast the colours move in animation mode
float cycleLength = 150; // Colour frequency (smaller = more waves)
float hueOffset = 0; // Shifts colours for animation effect

int mode = MODE_RADIAL; // Default mode when the program starts

/**
 * debug()
 * Prints debug statements if debug mode is enabled.
 * 
 * @param s - The string to be printed, allowing formatting
 */
void debug(const char* s, ...) {
    if (!db) return;
    va_list args;
    va_start(args, s);
    printf("DEBUG: ");
    vprintf(s, args);
    printf("\n");
    va_end(args);
}

/**
 * clamp()
 * Utility function to constrain a value between a minimum and maximum.
 * 
 * @param value - The value to clamp
 * @param min - The minimum value
 * @param max - The maximum value
 */
float clamp(float value, float min, float max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

/**
 * reset()
 * Resets animation parameters to their default values.
 */
void reset() {
    speed = 2;
    cycleLength = 150;
    hueOffset = 0;
}

/**
 * colourConvert()
 * Converts HSV color values to RGB format.
 * 
 * @param h - Hue (0-360)
 * @param s - Saturation (0-1)
 * @param v - Value (0-1)
 * @param r - Pointer to store resulting red value (0-255)
 * @param g - Pointer to store resulting green value (0-255)
 * @param b - Pointer to store resulting blue value (0-255)
 */
void colourConvert(float h, float s, float v, Uint8* r, Uint8* g, Uint8* b) {
    float c = v * s;
    float x = c * (1 - fabsf(fmodf(h / 60.0f, 2) - 1));
    float m = v - c;

    float r1, g1, b1;

    if (h < 60) { 
        r1 = c; 
        g1 = x; 
        b1 = 0; 
    } else if (h < 120) { 
        r1 = x; 
        g1 = c; 
        b1 = 0; 
    } else if (h < 180) { 
        r1 = 0; 
        g1 = c; 
        b1 = x; 
    } else if (h < 240) { 
        r1 = 0; 
        g1 = x; 
        b1 = c; 
    } else if (h < 300) { 
        r1 = x; 
        g1 = 0; 
        b1 = c; 
    } else { 
        r1 = c; 
        g1 = 0; 
        b1 = x; 
    }

    *r = (Uint8)((r1 + m) * 255);
    *g = (Uint8)((g1 + m) * 255);
    *b = (Uint8)((b1 + m) * 255);
}

int main(int argc, char** argv) {
    if (argc > 1 && strcmp(argv[1], "debug") == 0) {
        db = 1;
        printf(
            "===== DEBUG MODE =====\n"
            "In debug mode, actions such as mode switching and setting\n"
            "changes will be documented. To disable, end the program\n"
            "and restart as normal.\n\n"
        );
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "ERROR: Could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }
    debug("SDL successfully initialized.");

    SDL_Window* win = SDL_CreateWindow("PIXEL MADNESS!!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (!win) {
        fprintf(stderr, "ERROR: Could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    debug("Window successfully created.");

    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!ren) {
        fprintf(stderr, "ERROR: Could not create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    debug("Renderer successfully created.\n");

    printf(
        "========== PIXEL MADNESS ==========\n"
        "Create stunning pixel animations with your imagination!\n\n"
        "===== ANIMATION MODES =====\n"
        "Press a number key from 1-6 that corresponds to a mode:\n"
        "\t1. Radial mode\n"
        "\t2. Horizontal mode\n"
        "\t3. Vertical mode\n"
        "\t4. Diagonal mode\n"
        "\t5. Spiral mode\n"
        "\t6. Rings mode\n\n"
        "===== ANIMATION CONTROLS =====\n"
        "\t- Use the left and right arrow keys to adjust animation speed.\n"
        "\t- Use up and down arrow keys to adjust colour frequency.\n"
        "\t- Hold down the mouse for colour animation shifting.\n"
        "\t- Move your mouse around for movement.\n\n"
        "WARNING: This program contains very bright colours and flashing\n"
        "lights, which may cause seizures in some people. Viewer\n"
        "discretion is advised.\n\n"
    );

    int running = 1;
    SDL_Event event;
    int leftDown = 0;
    int rightDown = 0;
    float direction = 1;
    debug("Starting animation...");
    while (running) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                // Animation modes when mouse is clicked
                if (event.button.button == SDL_BUTTON_LEFT) {
                    debug("Left mouse - animation forward");
                    leftDown = 1;
                    direction = 1;
                }
                if (event.button.button == SDL_BUTTON_RIGHT) {
                    debug("Right mouse - animation backward");
                    rightDown = 1;
                    direction = -1;
                }
            }
            if (event.type == SDL_MOUSEBUTTONUP) {
                // Stop animating when mouse is released
                if (event.button.button == SDL_BUTTON_LEFT) {
                    debug("Animation stopped");
                    leftDown = 0;
                }
                if (event.button.button == SDL_BUTTON_RIGHT) {
                    debug("Animation stopped");
                    rightDown = 0;
                }
            }
            if (event.type == SDL_KEYDOWN) {
                // Up and down keys control frequency.
                if (event.key.keysym.sym == SDLK_UP) {
                    debug("Increased frequency: %.2f", cycleLength);
                    cycleLength -= CYCLE_STEP;  // more waves
                    cycleLength = clamp(cycleLength, MIN_CYCLE, MAX_CYCLE);
                }
                if (event.key.keysym.sym == SDLK_DOWN) {
                    debug("Decreased frequency: %.2f", cycleLength);
                    cycleLength += CYCLE_STEP;  // fewer waves
                    cycleLength = clamp(cycleLength, MIN_CYCLE, MAX_CYCLE);
                }

                // Left and right keys control animation speed.
                if (event.key.keysym.sym == SDLK_RIGHT) {
                    debug("Increased speed: %.2f", speed);
                    speed += 0.5f;  // faster
                    speed = clamp(speed, MIN_SPEED, MAX_SPEED);
                }
                if (event.key.keysym.sym == SDLK_LEFT) {
                    debug("Decreased speed: %.2f", speed);
                    speed -= 0.5f;  // slower
                    speed = clamp(speed, MIN_SPEED, MAX_SPEED);
                }

                // Number keys switch modes.
                if (event.key.keysym.sym == SDLK_1) {
                    debug("Radial mode");
                    reset();
                    mode = MODE_RADIAL;
                }
                if (event.key.keysym.sym == SDLK_2) {
                    debug("Horizontal mode");
                    reset();
                    mode = MODE_HORIZONTAL;
                }
                if (event.key.keysym.sym == SDLK_3) {
                    debug("Vertical mode");
                    reset();
                    mode = MODE_VERTICAL;
                }
                if (event.key.keysym.sym == SDLK_4) {
                    debug("Diagonal mode");
                    reset();
                    mode = MODE_DIAGONAL;
                }
                if (event.key.keysym.sym == SDLK_5) {
                    debug("Spiral mode");
                    reset();
                    mode = MODE_SPIRAL;
                }
                if (event.key.keysym.sym == SDLK_6) {
                    debug("Rings mode");
                    reset();
                    cycleLength = 800;
                    mode = MODE_RINGS;
                }
            }
            
        }

        int mouseX, mouseY; // Mouse positions
        SDL_GetMouseState(&mouseX, &mouseY);

        if (leftDown || rightDown) { // Animation control
            hueOffset += speed * direction;
        }

        // Render loop
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        for (int y = 0; y < HEIGHT; y += PIXEL_SIZE) {
            for (int x = 0; x < WIDTH; x += PIXEL_SIZE) {
                float dx = (x + PIXEL_SIZE / 2) - mouseX;
                float dy = (y + PIXEL_SIZE / 2) - mouseY;
                float dist;
                float radius;
                switch (mode) {
                    case MODE_RADIAL:
                        dist = sqrtf(dx * dx + dy * dy);
                        break;
                    case MODE_HORIZONTAL:
                        dist = (float)y - mouseY;
                        break;
                    case MODE_VERTICAL:
                        dist = (float)x - mouseX;
                        break;
                    case MODE_DIAGONAL:
                        dist = (float)(x + y) - (mouseX + mouseY) * 0.7;
                        break;
                    case MODE_SPIRAL:
                        float angle = atan2f(dy, dx);
                        radius = sqrtf(dx * dx + dy * dy);
                        dist = radius + angle * 150;
                        break;
                    case MODE_RINGS:
                        radius = sqrtf(dx * dx + dy * dy);
                        dist = sinf(radius * 0.05f) * 300.0f;
                        break;
                    default:
                        dist = 0; // dummy
                }

                float waveValue = dist + hueOffset;

                float wrapped = fmodf(waveValue, cycleLength);
                if (wrapped < 0) {
                    wrapped += cycleLength;
                }

                float hue = wrapped / cycleLength * 360.0f;
                float saturation = 1;
                float value = 1;

                Uint8 r, g, b;
                colourConvert(hue, saturation, value, &r, &g, &b);

                SDL_Rect rect = { x, y, PIXEL_SIZE, PIXEL_SIZE };
                SDL_SetRenderDrawColor(ren, r, g, b, 255);
                SDL_RenderFillRect(ren, &rect);
                SDL_SetRenderDrawColor(ren, r / 3, g / 3, b / 3, 255);
                SDL_RenderDrawRect(ren, &rect);
            }
        }

        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }

    // Cleanup
    debug("Exiting program");
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
