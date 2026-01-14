#pragma once

#include <string>

class Picture;

bool SavePPM(const Picture& picture, const std::string& filename);
