#ifndef PLATFORM_DETECTION_H_
#define PLATFORM_DETECTION_H_

#if defined(_WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#define HA_PLATFORM_WINDOWS
#elif defined(__linux__)
#define HA_PLATFORM_LINUX
#else
#error "Hard engine doesn't support this platform"
#endif

#endif
