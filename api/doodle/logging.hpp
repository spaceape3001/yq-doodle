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

#define doodleAlert                    yAlert("doodle")
#define doodleCritical                 yCritical("doodle")
#define doodleDebug                    yDebug("doodle")
#define doodleError                    yError("doodle")
#define doodleEmergency                yEmergency("doodle")
#define doodleFatal                    yFatal("doodle")
#define doodleInfo                     yInfo("doodle")
#define doodleNotice                   yNotice("doodle")
#define doodleWarning                  yWarning("doodle")

#define doodleFirstAlert(...)          yLogFirstAlert("doodle", __VA_ARGS__)
#define doodleFirstCritical(...)       yLogFirstCritical("doodle", __VA_ARGS__)
#define doodleFirstDebug(...)          yLogFirstDebug("doodle", __VA_ARGS__)
#define doodleFirstError(...)          yLogFirstError("doodle", __VA_ARGS__)
#define doodleFirstEmergency(...)      yLogFirstEmergency("doodle", __VA_ARGS__)
#define doodleFirstFatal(...)          yLogFirstFatal("doodle", __VA_ARGS__)
#define doodleFirstInfo(...)           yLogFirstInfo("doodle", __VA_ARGS__)
#define doodleFirstNotice(...)         yLogFirstNotice("doodle", __VA_ARGS__)
#define doodleFirstWarning(...)        yLogFirstWarning("doodle", __VA_ARGS__)
