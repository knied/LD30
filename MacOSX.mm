#include "MacOSX.h"
#include <Cocoa/Cocoa.h>

std::string macosx_resources_path() {
    return std::string([[[NSBundle mainBundle] resourcePath] UTF8String]) + "/";
}