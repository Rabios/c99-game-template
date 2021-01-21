// Written by Rabia Alhaffar in 29/December/2020
// C99 game template ready for game development...
// Updated: 21/January/2021


//////////////////////////////////////////////////////////////////////////////////////
// Game Config
//////////////////////////////////////////////////////////////////////////////////////
#define VSYNC_ENABLED                   // Enable VSync
#define ANTIALIASING_ENABLED            // Enable Antialiasing
#define ANTIALIASING_SAMPLES 4          // Set antialiasing samples (If antialiasing enabled)
#define EXIT_WITH_ESCAPE                // Allows to exit game with escape key
#define WINDOW_RESIZABLE                // Allows window to be resizable


//////////////////////////////////////////////////////////////////////////////////////
// Definitions
//////////////////////////////////////////////////////////////////////////////////////
#define MINIAUDIO_IMPLEMENTATION         // Implement miniaudio library with engine
#define STB_IMAGE_IMPLEMENTATION         // Implement stb_image library
#define STB_TRUETYPE_IMPLEMENTATION      // Implement stb_truetype library
#define ENET_IMPLEMENTATION              // Implement enet library
#define TINYOBJ_LOADER_C_IMPLEMENTATION	 // Implement tinyobjloader-c library
#define PHYSAC_IMPLEMENTATION            // Implement Physac
#define PHYSAC_STANDALONE                // Use Physac standalone without using raylib
#define PHYSAC_NO_THREADS                // Use Physac with no threads
#define PHYSAC_STATIC                    // Allow to build Physac as static library


// Implement bool type when not found
#if !defined(_STDBOOL_H)
typedef enum { false, true } bool;
#define _STDBOOL_H
#endif


// This intended to prevent windows.h from including WinSock v1
// NOTE: Including WinSock v1 causes errors for enet library when compiling...
#ifdef _WIN32 || WIN32
#define WIN32_LEAN_AND_MEAN
#endif


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


//////////////////////////////////////////////////////////////////////////////////////
// Includings: Libraries to work within your game
//////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>                       // C Standard IO library
#include <stdlib.h>                      // C Standard library
#include <string.h>                      // C String library
#include <glad/glad.h>                   // GLAD library (OpenGL loader)
#include <GLFW/glfw3.h>                  // GLFW library (Window and Input)
#include <miniaudio/miniaudio.h>         // miniaudio library (For audio)
#include <miniaudio/miniaudio_engine.h>  // miniaudio engine (Audio engine)
#include <tinyobj/tinyobj_loader_c.h>    // tinyobjloader-c (OBJ loading)
#include <physac/physac.h>               // Physac library (2D physics)
#include <stb/stb_truetype.h>            // stb_truetype (TTF and text)
#include <stb/stb_image.h>               // stb_image (Texture rendering)
#include <enet/enet.h>                   // ENet library (reliable UDP networking library)


//////////////////////////////////////////////////////////////////////////////////////
// Game Properties
//////////////////////////////////////////////////////////////////////////////////////
int window_width = 800;                 // Game window width
int window_height = 450;                // Game window height
bool window_fullscreen = false;         // Game fullscreen?
const char* window_title = "MYGAME";    // Game window title
int game_fps = 60;                      // Game frames per second


//////////////////////////////////////////////////////////////////////////////////////
// Variables
//////////////////////////////////////////////////////////////////////////////////////
GLFWwindow* window;                     // Primary Game window
GLFWvidmode* window_video_mode;	        // GLFW Window video mode

double t1;                              // First time
double t2;                              // Second time
double dt;                              // DeltaTime (Can be used, Useful...)

int* glfw_window_width;                 // Pointer to game window width when created
int* glfw_window_height;                // Pointer to game window height when created
int* glfw_window_x;                     // Pointer to game window x position when created
int* glfw_window_y;                     // Pointer to game window y position when created

FILE* game_data;                        // File to write game data to...
char loaded_variable_value[256];        // Temp string to return game loaded variable from...


//////////////////////////////////////////////////////////////////////////////////////
// Functions
//////////////////////////////////////////////////////////////////////////////////////
void start(int argc, char** argv);       // Initializes game
void loop(int argc, char** argv);        // Updates all game functions
void init(int argc, char** argv);        // Before game creation...
void draw(int argc, char** argv);        // Renders graphics (OpenGL)
void update(int argc, char** argv);      // Game logic
void input(int argc, char** argv);       // Game input
void close(int argc, char** argv);       // When game closes


//////////////////////////////////////////////////////////////////////////////////////
// Utilities
//////////////////////////////////////////////////////////////////////////////////////
void play_audio(char* src);
void set_audio_volume(float volume);
void set_audio_gain(float gain);
void pause_audio(void);
void resume_audio(void);

int charcode(char ch);
void draw_texture(char* src, rect srcRec, rect dstRec, color tint);
void draw_text(spritefont font, char* text, float x, float y, float size, color tint);

void storage_init(void);
void storage_save_string(char* string, unsigned int position);
void storage_save_var(double var, unsigned int position);
char* storage_load_string(unsigned int position);
double storage_load_var(unsigned int position);
void storage_clear(void);
void storage_remove_var(unsigned int position);


//////////////////////////////////////////////////////////////////////////////////////
// Callback functions
//////////////////////////////////////////////////////////////////////////////////////
static void error(int error, const char* description);
static void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
static void mouse(GLFWwindow* window, int button, int action, int mods);
static void cursor(GLFWwindow* window, double xpos, double ypos);
#ifdef WINDOW_RESIZABLE
static void window_resize(GLFWwindow* window, int new_width, int new_height);
#endif
static void file_drop(GLFWwindow* window, int count, const char** paths);


//////////////////////////////////////////////////////////////////////////////////////
// Callback Variables
//////////////////////////////////////////////////////////////////////////////////////
int keyboard_keys[512];                 // Array of keyboard keys if still pressed or down (Multiple keys control)

int mouse_buttons[8];                   // Array of mouse buttons with their states
double mouse_x;                         // Mouse X position
double mouse_y;                         // Mouse Y position
double scroll_x;                        // Mouse wheel delta X
double scroll_y;                        // Mouse wheel delta Y

joystick joysticks[16];                 // Joysticks

const char** dropped_files;             // Array of dropped files paths (If file dropped to game window)
int dropped_files_count;                // Dropped files count (Number of files dropped to game window)

ma_result audio_engine_init_result;     // Result of audio engine initialization
ma_engine audio_engine;                 // audio engine itself (miniaudio_engine.h)


//////////////////////////////////////////////////////////////////////////////////////
// Initialization: This holds creation of game window and assigns callbacks
//////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv) {
	init(argc, &argv);
	start(argc, &argv);
	return 0;
}


void start(int argc, char** argv) {
    //////////////////////////////////////////////////////////////////////////////////
    // Networking Initialization (enet.h)
    //////////////////////////////////////////////////////////////////////////////////
    if (enet_initialize() == 0) {
        printf("GAME: NETWORKING INITIALIZED SUCCESSFULLY!\n");
    }


    //////////////////////////////////////////////////////////////////////////////////
    // Physics Initialization (physac.h)
    //////////////////////////////////////////////////////////////////////////////////
    InitPhysics();


    //////////////////////////////////////////////////////////////////////////////////
    // Audio Initialization (miniaudio.h)
    //////////////////////////////////////////////////////////////////////////////////
    printf("GAME: INITIALIZING AUDIO ENGINE...\n");

    audio_engine_init_result = ma_engine_init(NULL, &audio_engine);
    if (audio_engine_init_result != MA_SUCCESS) {
        printf("GAME: AUDIO ENGINE INITIALIZATION FAILED!\n");
        return -1;
    }

    printf("GAME: AUDIO ENGINE INITIALIZED SUCCESSFULLY!\n");


    //////////////////////////////////////////////////////////////////////////////////
    // Window + OpenGL Initialization
    //////////////////////////////////////////////////////////////////////////////////
#ifdef WINDOW_FULLSCREEN
    window_fullscreen = true;
#endif
    printf("GAME: STARTING...\n");
    glfwSetErrorCallback(error);
    if (glfwInit()) {
        t1 = glfwGetTime();
        t2 = 0;
        dt = 0;

        printf("GAME: CREATING DISPLAY WINDOW...\n");
#ifdef ANTIALIASING_ENABLED
        printf("GAME: ANTIALIASING ENABLED!\n");
        glfwWindowHint(GLFW_SAMPLES, ANTIALIASING_SAMPLES);
#endif
#ifdef __APPLE__
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
        window = glfwCreateWindow(window_width, window_height, window_title, window_fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
#ifndef WINDOW_RESIZABLE
        glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_FALSE);
#endif
        if (!window) {
            printf("GAME: FAILED TO CREATE DISPLAY WINDOW!\n");
            glfwTerminate();
            exit(error_code);
        }
        printf("GAME: DISPLAY WINDOW CREATED SUCCESSFULLY!\n");
        glfwSetKeyCallback(window, keyboard);
        glfwSetMouseButtonCallback(window, mouse);
        glfwSetCursorPosCallback(window, cursor);
        glfwSetDropCallback(window, file_drop);
#ifdef WINDOW_RESIZABLE
        glfwSetWindowSizeCallback(window, window_resize);
#endif
        glfwGetWindowPos(window, &glfw_window_x, &glfw_window_y);
        glfwGetWindowSize(window, &glfw_window_width, &glfw_window_height);
        for (int i = 0; i < 16; i++) {
            joysticks[i].index = i;
        }
#ifdef VSYNC_ENABLED
        glfwSwapInterval(1);
#else
        glfwSwapInterval(0);
#endif
        glfwMakeContextCurrent(window);
        gladLoadGL(glfwGetProcAddress);
        printf("%s%s\n", "GAME: USED OPENGL ", glGetString(GL_VERSION));
        loop(argc, &argv);
    }
    else {
        printf("GAME: FAILED TO CREATE DISPLAY WINDOW!\n");
        glfwTerminate();
        exit(error_code);
    }
}


//////////////////////////////////////////////////////////////////////////////////////
// Loop: Where game loop lies
//////////////////////////////////////////////////////////////////////////////////////
void loop(int argc, char** argv) {
    while (!glfwWindowShouldClose(window)) {
        RunPhysicsStep();

        for (int i = 0; i < 16; i++) {
            joysticks[i].name = glfwGetJoystickName(joysticks[i].index);
            joysticks[i].buttons = glfwGetJoystickButtons(joysticks[i].index, &joysticks[i].buttons_count);
            joysticks[i].axes = glfwGetJoystickAxes(joysticks[i].index, &joysticks[i].axes_count);
            joysticks[i].hats = glfwGetJoystickHats(joysticks[i].index, &joysticks[i].hats_count);
        }

        /*
        if (window_fullscreen) {
            glfwSetWindowMonitor(window, window_fullscreen ? glfwGetPrimaryMonitor() : NULL, 0, 0, glfw_window_width, glfw_window_height, GLFW_REFRESH_RATE);
        } else {
            glfwSetWindowMonitor(window, NULL, glfw_window_x, glfw_window_y, glfw_window_width, glfw_window_height, GLFW_DONT_CARE);
        }
        */

        if (window_fullscreen) glfwSetWindowMonitor(window, window_fullscreen ? glfwGetPrimaryMonitor() : NULL, 0, 0, glfw_window_width, glfw_window_height, GLFW_REFRESH_RATE);

        glfwGetFramebufferSize(window, &window_height, &window_height);

        t2 = glfwGetTime();
        dt = t2 - t1;

        if (dt >= (1.0 / game_fps)) {
            printf("GAME: UPDATING...\n");
            update(argc, &argv);
            printf("GAME: RECEIEVING GAME INPUT...\n");
            input(argc, &argv);
            t1 = t2;
        }

        printf("GAME: RENDERING...\n");
        glViewport(0, 0, window_width, window_height);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glOrtho(0, window_width, 0, window_height, -1, 1);
        glScalef(1, -1, 1);
        glTranslatef(0, -window_height, 0);

        draw(argc, &argv);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    printf("GAME: CLOSING DISPLAY WINDOW...\n");
    close(argc, &argv);
    glfwDestroyWindow(window);
    glfwTerminate();
    ma_engine_uninit(&audio_engine);
    ClosePhysics();
    enet_deinitialize();
    printf("GAME: CLOSED SUCCESSFULLY!\n");
    exit(0);
}


//////////////////////////////////////////////////////////////////////////////////////
// Game Variables: Put here your game variables
//////////////////////////////////////////////////////////////////////////////////////
int player_x = 100;
int player_y = 100;
int player_width = 50;
int player_height = 50;


//////////////////////////////////////////////////////////////////////////////////////
// Initialize: Write code before game runs!
//////////////////////////////////////////////////////////////////////////////////////
void init(int argc, char** argv) {

}


//////////////////////////////////////////////////////////////////////////////////////
// Update: Here update variables if doesn't use input
//////////////////////////////////////////////////////////////////////////////////////
void update(int argc, char** argv) {

}


//////////////////////////////////////////////////////////////////////////////////////
// Rendering: Here you write OpenGL code
//////////////////////////////////////////////////////////////////////////////////////
void draw(int argc, char** argv) {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_QUADS);
    glColor4ub(0, 0, 255, 255);
    glVertex2i(player_x, player_y);
    glVertex2i(player_x + player_width, player_y);
    glVertex2i(player_x + player_width, player_y + player_height);
    glVertex2i(player_x, player_y + player_height);
    glEnd();
}


//////////////////////////////////////////////////////////////////////////////////////
// Input: Here you write input checking code
//////////////////////////////////////////////////////////////////////////////////////
void input(int argc, char** argv) {
    if (keyboard_keys[GLFW_KEY_LEFT]) player_x -= 5;
    if (keyboard_keys[GLFW_KEY_RIGHT]) player_x += 5;
    if (keyboard_keys[GLFW_KEY_UP]) player_y -= 5;
    if (keyboard_keys[GLFW_KEY_DOWN]) player_y += 5;
}


//////////////////////////////////////////////////////////////////////////////////////
// Close: What should happens when your game closed...
//////////////////////////////////////////////////////////////////////////////////////
void close(int argc, char** argv) {

}


//////////////////////////////////////////////////////////////////////////////////////
// Callbacks
//////////////////////////////////////////////////////////////////////////////////////
static void error(int code, const char* description) {
    error_code = code;
    error_description = description;
}


static void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
    keyboard_keys[key] = action;

#ifdef EXIT_WITH_ESCAPE
    if (keyboard_keys[GLFW_KEY_ESCAPE]) glfwSetWindowShouldClose(window, GLFW_TRUE);
#endif
}


static void mouse(GLFWwindow* window, int button, int action, int mods) {
    mouse_buttons[button] = action;
}


static void cursor(GLFWwindow* window, double xpos, double ypos) {
    mouse_x = xpos;
    mouse_y = ypos;
}


static void scroll(GLFWwindow* window, double xoffset, double yoffset) {
    scroll_x = xoffset;
    scroll_y = yoffset;
}


static void file_drop(GLFWwindow* window, int count, const char** paths) {
    dropped_files = paths;
    dropped_files_count = count;
}


#ifdef WINDOW_RESIZABLE
static void window_resize(GLFWwindow* window, int new_width, int new_height) {
     window_width = new_width;
     window_height = new_height;
}
#endif


//////////////////////////////////////////////////////////////////////////////////////
// Utilities
//////////////////////////////////////////////////////////////////////////////////////
int charcode(char ch) {
    return (int)ch;
}

void play_audio(char* src) {
    ma_engine_play_sound(&audio_engine, src, NULL);
}


void set_audio_volume(float volume) {
    ma_engine_set_volume(&audio_engine, volume);
}


void set_audio_gain(float gain) {
    ma_engine_set_gain_db(&audio_engine, gain);
}


void pause_audio(void) {
    ma_engine_stop(&audio_engine);
}


void resume_audio(void) {
    ma_engine_start(&audio_engine);
}


void draw_texture(char* src, rect srcRec, rect dstRec, color tint) {
    printf("GAME: LOADING TEXTURE %s\n", src);
	
    GLuint texture;
    int width, height, nrChannels;
    unsigned char* data = stbi_load(src, &width, &height, &nrChannels, STBI_rgb_alpha);
    if (data) {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE0);

        glColor4f(tint.r, tint.g, tint.b, tint.a);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glBlendFunc(GL_ONE, GL_ONE_MINUS_DST_ALPHA);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glGenerateMipmap(GL_TEXTURE_2D);

        if (!srcRec.w) srcRec.w = (float) width;
        if (!srcRec.h) srcRec.h = (float)height;
        if (!dstRec.w) dstRec.w = (float) width;
        if (!dstRec.h) dstRec.h = (float) height;

        float ix1 = (float) srcRec.x / width;
        float ix2 = (float) (srcRec.w + srcRec.x) / width;
        float iy1 = (float) srcRec.y / height;
        float iy2 = (float) (srcRec.h + srcRec.y) / height;

        glBegin(GL_QUADS);
        glTexCoord2f(ix1, iy1);
        glVertex2i(dstRec.x, dstRec.y);
        glTexCoord2f(ix2, iy1);
        glVertex2i(dstRec.x + dstRec.w, dstRec.y);
        glTexCoord2f(ix2, iy2);
        glVertex2i(dstRec.x + dstRec.w, dstRec.y + dstRec.h);
        glTexCoord2f(ix1, iy2);
        glVertex2i(dstRec.x, dstRec.y + dstRec.h);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, 0);
        glDeleteTextures(1, &texture);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);

        printf("GAME: UNLOADING TEXTURE %s\n", src);
        stbi_image_free(data);
    } else {
        printf("GAME: FAILED TO LOAD TEXTURE %s!\n", src);
    }
}


void draw_text(spritefont font, char* text, float x, float y, float size, color tint) {
    size_t c = 0;
    while (text[c] != "\0") {
        draw_texture(font.src, font.chars[(int)text[c]], (rect) { x, y, size, size }, tint);
        c++;
    }
}


void storage_init(void) {
    printf("GAME: INITIALIZING STORAGE...\n");
    if ((game_data = fopen("game.data", "r"))) {
        fclose(game_data);
    } else {
        game_data = fopen("game.data", "w");
        fclose(game_data);
    }
    printf("GAME: STORAGE INITIALIZED SUCCESSFULLY!\n");
}


void storage_save_string(char* string, unsigned int position) {
    storage_remove_var(position);
    game_data = fopen("game.data", "a");
    for (int i = 0; i < position; i++) fprintf(game_data, "\0\n");
    fprintf(game_data, "%s", string);
    fclose(game_data);
}


void storage_save_var(double var, unsigned int position) {
    storage_remove_var(position);
    char var_tostr[64];
    snprintf(var_tostr, 64, "%f", var);
    storage_save_string(var_tostr, position);
}


char* storage_load_string(unsigned int position) {
    memset(&loaded_variable_value[0], 0, sizeof(loaded_variable_value));
    char line[256] = { 0 };
    unsigned int line_count = 0;
    game_data = fopen("game.data", "r");
    while (fgets(line, 256, game_data))
    {
        ++line_count;
        if (line_count == position) {
            strcpy(loaded_variable_value, line);
            break;
        }
    }
    fclose(game_data);
    strcpy(loaded_variable_value, line);
    return loaded_variable_value;
}

double storage_load_var(unsigned int position) {
    return atof(storage_load_string(position));
}


void storage_remove_var(unsigned int position) {
    unsigned int ctr = 0;
    char str[256];
    FILE* temp_data;
    game_data = fopen("game.data", "r");
    temp_data = fopen("temp.data", "w");
    while (!feof(game_data))
    {
        strcpy(str, "\0");
        fgets(str, 256, game_data);
        if (!feof(game_data))
        {
            ctr++;
            if (ctr != position) fprintf(temp_data, str);
        }
    }
    fclose(game_data);
    fclose(temp_data);
    storage_clear();
    rename("temp.data", "game.data");
}


void storage_clear(void) {
    /*
    game_data = fopen("game.data", "w");
    fclose(game_data);
    */
	
    remove("game.data");
}
