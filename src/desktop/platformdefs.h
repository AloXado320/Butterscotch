#pragma once

#include <stdbool.h>

#include "runner.h"
#include "input_recording.h"

bool platformInit(int32_t reqW, int32_t reqH, const char *title, bool headless);
void platformInitFunctions(Runner *);
void platformExit(void);
void platformSwapBuffers(void);
void *platformGetProcAddress(const char *name);
double platformGetTime(void);
bool platformHandleEvents(void);
void platformGetMousePos(double *xPos, double *yPos);
bool platformGetWindowSize(int32_t* outW, int32_t* outH);
bool platformGetScaledWindowSize(int32_t* outW, int32_t* outH);
void platformSetWindowSize(int32_t width, int32_t height);
void platformSetWindowTitle(const char* title);
void platformSleepUntil(uint64_t time);

// Some games call platformSetWindowSize every frame so this avoids redundant resizing
#define PLATFORM_CACHE_WINDOW_SIZE(width, height) \
    do {                                          \
        static int32_t last_width = -1;           \
        static int32_t last_height = -1;          \
        if (width == last_width && height == last_height) return; \
        last_width = width;                       \
        last_height = height;                     \
    } while (0)

// Some games call an initial resolution larger than the screen so resize properly
#define PLATFORM_GET_BEST_FIT_RES(reqW, reqH, screenW, screenH, finalW, finalH) \
    do {                                                                        \
        if ((float)(reqW) / (reqH) > (float)(screenW) / (screenH)) {            \
            (finalH) = (screenH);                                               \
            (finalW) = (screenW);                                               \
        } else {                                                                \
            float scaleX = (float)(screenW) / (reqW);                           \
            float scaleY = (float)(screenH) / (reqH);                           \
            float scale = (scaleX < scaleY) ? scaleX : scaleY;                  \
            (finalW) = (int)((reqW) * scale);                                   \
            (finalH) = (int)((reqH) * scale);                                   \
        }                                                                       \
    } while(0)

enum GraphicsAPI {
    SOFTWARE,
    MODERN_GL,
    LEGACY_GL
};

extern enum GraphicsAPI gfx;

extern InputRecording *globalInputRecording;
