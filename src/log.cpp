#include <stdio.h>
#include <SDL2/SDL.h>

#include "log.h"

/*
 * We wrap all SDL_Log* messages as a simple way to achieve the concept of a
 * "partial" function binding in a functional language. Also, it helps clean
 * up the user-level code a bit at the cost of creating bloat here.
 */

void Log::Debug(const char *debugStr) {
  Log::Debug(SDL_LOG_CATEGORY_APPLICATION,
	     debugStr);
  return;
}

void Log::Debug(int category,
		const char *debugStr) {
  SDL_LogMessage(category,
		 SDL_LOG_PRIORITY_DEBUG,
		 "%s",
		 debugStr);
  return;
}

void Log::Error(const char *errorStr) {
  Log::Error(SDL_LOG_CATEGORY_APPLICATION,
	     errorStr);
  return;
}

void Log::Error(int category,
		const char *errorStr) {
  SDL_LogMessage(category,
		 SDL_LOG_PRIORITY_ERROR,
		 "%s",
		 errorStr);
  return;
}
