# c99-game-template

C99 Template for writing games, Made with love and passion!

It contains set of libraries can be used to develop games with great approach, All that can be done with C99!

### Included Libraries

1. [GLAD](https://github.com/Dav1dde/glad)
2. [GLFW](https://github.com/glfw/glfw)
3. [Physac](https://github.com/victorfisac/physac)
4. [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h)
5. [stb_truetype](https://github.com/nothings/stb/blob/master/stb_truetype.h)
6. [tinyobjloader-c](https://github.com/syoyo/tinyobjloader-c)
7. [miniaudio](https://github.com/mackron/miniaudio)
8. [miniaudio_engine](https://github.com/mackron/miniaudio/blob/ae88112e4f4d15e554967a6dfa1a2ac7699bcdf0/research/miniaudio_engine.h)
9. [enet](https://github.com/zpl-c/enet)

### Building

Clone this repo and build it with CMake, Then use C compiler of your choice (GCC, Visual Studio's MSVC, etc...)

### Usage

The template code is just one file which is `main.c`, This makes it easy to modify and write game code without headaches and hassle...

- At beginning of the `main.c` you would find game configuration, Which used for game definitions...

These are current definitions available to use...

```c
//////////////////////////////////////////////////////////////////////////////////////
// Game Config
//////////////////////////////////////////////////////////////////////////////////////
#define VSYNC_ENABLED                   // Enable VSync
#define ANTIALIASING_ENABLED            // Enable Antialiasing
#define ANTIALIASING_SAMPLES 4          // Set antialiasing samples (If antialiasing enabled)
#define EXIT_WITH_ESCAPE                // Allows to exit game with escape key
#define WINDOW_RESIZABLE                // Allows window to be resizable
#define WINDOW_FULLSCREEN               // Launch game in fullscreen mode
```

- You can also find "Game Properies" section in `main.c`

```c
//////////////////////////////////////////////////////////////////////////////////////
// Game Properties
//////////////////////////////////////////////////////////////////////////////////////
int window_width = 800;                 // Game window width
int window_height = 450;                // Game window height
bool window_fullscreen = false;         // Game fullscreen?
const char* window_title = "MYGAME";    // Game window title
int game_fps = 60;                      // Game frames per second
```

- In "Game Variables" section, You can write game variables used for game...

```c
//////////////////////////////////////////////////////////////////////////////////////
// Game Variables: Put here your game variables
//////////////////////////////////////////////////////////////////////////////////////
int player_x = 100;
int player_y = 100;
int player_width = 50;
int player_height = 50;
```

- If you want to write something before game starts, `init` function provided to be used simply...

```c
//////////////////////////////////////////////////////////////////////////////////////
// Initialize: Write code before game runs!
//////////////////////////////////////////////////////////////////////////////////////
void init(int argc, char** argv) {

}
```

- The `update` function is used to update game logic, Along with `input` function which can be used to write input code away of `update` function...

```c
//////////////////////////////////////////////////////////////////////////////////////
// Update: Here update variables if doesn't use input
//////////////////////////////////////////////////////////////////////////////////////
void update(int argc, char** argv) {

}
```

```c
//////////////////////////////////////////////////////////////////////////////////////
// Input: Here you write input checking code
//////////////////////////////////////////////////////////////////////////////////////
void input(int argc, char** argv) {
    if (keyboard_keys[GLFW_KEY_LEFT]) player_x -= 5;
    if (keyboard_keys[GLFW_KEY_RIGHT]) player_x += 5;
    if (keyboard_keys[GLFW_KEY_UP]) player_y -= 5;
    if (keyboard_keys[GLFW_KEY_DOWN]) player_y += 5;
}
```

> NOTE: You can write code of `input` function inside `update` function, It's up to you...

- The `render` function used to write OpenGL code (OpenGL provided by glad)

```c
//////////////////////////////////////////////////////////////////////////////////////
// Rendering: Here you write OpenGL code
//////////////////////////////////////////////////////////////////////////////////////
void draw(int argc, char** argv) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_QUADS);
    glColor4ub(0, 0, 255, 255);
    glVertex2i(player_x, player_y);
    glVertex2i(player_x + player_width, player_y);
    glVertex2i(player_x + player_width, player_y + player_height);
    glVertex2i(player_x, player_y + player_height);
    glEnd();
}
```

- If your game are about to close, Function `close` provided so you can write what should happens when game closes...

```c
//////////////////////////////////////////////////////////////////////////////////////
// Close: What should happens when your game closed...
//////////////////////////////////////////////////////////////////////////////////////
void close(int argc, char** argv) {

}
```

### Variables and Structs

These are structs provided to make development easier...

```c
//////////////////////////////////////////////////////////////////////////////////////
// Structs
//////////////////////////////////////////////////////////////////////////////////////
typedef struct joystick {
    int index;                      // Joystick index
    const char* name;               // Joystick name
    unsigned char* buttons;         // Joystick buttons
    unsigned char* hats;            // Joystick hats
    float* axes;                    // Joystick analog axes
    int* buttons_count;             // Number of joystick buttons joystick has
    int* axes_count;                // Number of axes joystick has
    int* hats_count;                // Number of hats joystick has
} joystick;


typedef struct rect {
    float x;                        // Rectangle x
    float y;                        // Rectangle y
    float w;                        // Rectangle width
    float h;                        // Rectangle height
} rect;


typedef struct spritefont {
    char* src;                      // Font source file
    rect* chars;                    // Font rectangles (For each letter in image)
} spritefont;


typedef struct color {
    unsigned int r;                 // Red (0 - 255)
    unsigned int g;                 // Green (0 - 255)
    unsigned int b;                 // Blue (0 - 255)
    unsigned int a;                 // Alpha (0 - 255)
} color;
```

These are variables you can use around your game...

```c
int window_width;                   // Game window width
int window_height;                  // Game window height
bool window_fullscreen;             // Game fullscreen?
const char* window_title;           // Game window title
int game_fps;                       // Game frames per second
int error_code;                     // Error code if game failed to do something
char* error_description;            // Error description if game failed to do something
double dt;                          // DeltaTime (Can be used, Useful...)

int keyboard_keys[512];             // Array of keyboard keys if still pressed or down (Multiple keys control)

int mouse_buttons[8];               // Array of mouse buttons with their states
double mouse_x;                     // Mouse X position
double mouse_y;                     // Mouse Y position
double scroll_x;                    // Mouse wheel delta X
double scroll_y;                    // Mouse wheel delta Y

joystick joysticks[16];             // Joysticks

const char** dropped_files;         // Array of dropped files paths (If file dropped to game window)
int dropped_files_count;            // Dropped files count (Number of files dropped to game window)
```

### Utilities

Utilities are functions provided in the template to simplify some parts...

```c
//////////////////////////////////////////////////////////////////////////////////////
// Utilities
//////////////////////////////////////////////////////////////////////////////////////
void play_audio(char* src);
void set_audio_volume(float volume);
void set_audio_gain(float gain);
void pause_audio(void);
void resume_audio(void);

int charcode(char ch);                                          // Converts char to int
void draw_texture(char* src, rect srcRec, rect dstRec, color tint);
void draw_text(spritefont font, char* text, float x, float y, float size, color tint);

void storage_init(void);                                        // Initializes storage if game.data not found...
void storage_save_string(char* string, unsigned int position);
void storage_save_var(double var, unsigned int position);       // Same as previous one for numbers
char* storage_load_string(unsigned int position);
double storage_load_var(unsigned int position);                 // Same as previous one but for numbers
void storage_remove_var(unsigned int position);                 // Can remove variable from index (String or number allowed)
void storage_clear(void);
```

> NOTE: Storage content written to file called `game.data`.

### License

Template license can be found in [`LICENSE.txt`](https://github.com/Rabios/c99-game-template/blob/main/LICENSE.txt) and third party libs licenses can be found in [`LICENSES.txt`](https://github.com/Rabios/c99-game-template/blob/main/LICENSES.txt).
