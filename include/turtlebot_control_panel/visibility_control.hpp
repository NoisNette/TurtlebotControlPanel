#ifndef turtlebot_control_panel_VISIBILITY_CONTROL_HPP
#define turtlebot_control_panel_VISIBILITY_CONTROL_HPP

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
    #ifdef __GNUC__
        #define turtlebot_control_panel_EXPORT __attribute__((dllexport))
        #define turtlebot_control_panel_IMPORT __attribute__((dllimport))
    #else
        #define turtlebot_control_panel_EXPORT __declspec(dllexport)
        #define turtlebot_control_panel_IMPORT __declspec(dllimport)
    #endif
    #ifdef turtlebot_control_panel_BUILDING_LIBRARY
        #define turtlebot_control_panel_PUBLIC turtlebot_control_panel_EXPORT
    #else
        #define turtlebot_control_panel_PUBLIC turtlebot_control_panel_IMPORT
    #endif
    #define turtlebot_control_panel_PUBLIC_TYPE turtlebot_control_panel_PUBLIC
    #define turtlebot_control_panel_LOCAL
#else
    #define turtlebot_control_panel_EXPORT __attribute__((visibility("default")))
    #define turtlebot_control_panel_IMPORT
    #if __GNUC__ >= 4
        #define turtlebot_control_panel_PUBLIC __attribute__((visibility("default")))
        #define turtlebot_control_panel_LOCAL __attribute__((visibility("hidden")))
    #else
        #define turtlebot_control_panel_PUBLIC
        #define turtlebot_control_panel_LOCAL
    #endif
    #define turtlebot_control_panel_PUBLIC_TYPE
#endif

#endif // turtlebot_control_panel_VISIBILITY_CONTROL_HPP