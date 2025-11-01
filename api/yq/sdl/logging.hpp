////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Logging.hpp>
#include <yq/core/LogFilter.hpp>
#include <yq/text/format.hpp>
#include <yq/trait/is_pointer.hpp>

#define sdlAlert                    yAlert("sdl")
#define sdlCritical                 yCritical("sdl")
#define sdlDebug                    yDebug("sdl")
#define sdlError                    yError("sdl")
#define sdlEmergency                yEmergency("sdl")
#define sdlFatal                    yFatal("sdl")
#define sdlInfo                     yInfo("sdl")
#define sdlNotice                   yNotice("sdl")
#define sdlWarning                  yWarning("sdl")

#define sdlFirstAlert(...)          yLogFirstAlert("sdl", __VA_ARGS__)
#define sdlFirstCritical(...)       yLogFirstCritical("sdl", __VA_ARGS__)
#define sdlFirstDebug(...)          yLogFirstDebug("sdl", __VA_ARGS__)
#define sdlFirstError(...)          yLogFirstError("sdl", __VA_ARGS__)
#define sdlFirstEmergency(...)      yLogFirstEmergency("sdl", __VA_ARGS__)
#define sdlFirstFatal(...)          yLogFirstFatal("sdl", __VA_ARGS__)
#define sdlFirstInfo(...)           yLogFirstInfo("sdl", __VA_ARGS__)
#define sdlFirstNotice(...)         yLogFirstNotice("sdl", __VA_ARGS__)
#define sdlFirstWarning(...)        yLogFirstWarning("sdl", __VA_ARGS__)
