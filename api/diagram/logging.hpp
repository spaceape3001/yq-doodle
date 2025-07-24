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

#define diagramAlert                    yAlert("diagram")
#define diagramCritical                 yCritical("diagram")
#define diagramDebug                    yDebug("diagram")
#define diagramError                    yError("diagram")
#define diagramEmergency                yEmergency("diagram")
#define diagramFatal                    yFatal("diagram")
#define diagramInfo                     yInfo("diagram")
#define diagramNotice                   yNotice("diagram")
#define diagramWarning                  yWarning("diagram")

#define diagramFirstAlert(...)          yLogFirstAlert("diagram", __VA_ARGS__)
#define diagramFirstCritical(...)       yLogFirstCritical("diagram", __VA_ARGS__)
#define diagramFirstDebug(...)          yLogFirstDebug("diagram", __VA_ARGS__)
#define diagramFirstError(...)          yLogFirstError("diagram", __VA_ARGS__)
#define diagramFirstEmergency(...)      yLogFirstEmergency("diagram", __VA_ARGS__)
#define diagramFirstFatal(...)          yLogFirstFatal("diagram", __VA_ARGS__)
#define diagramFirstInfo(...)           yLogFirstInfo("diagram", __VA_ARGS__)
#define diagramFirstNotice(...)         yLogFirstNotice("diagram", __VA_ARGS__)
#define diagramFirstWarning(...)        yLogFirstWarning("diagram", __VA_ARGS__)
