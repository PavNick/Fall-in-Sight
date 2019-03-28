#pragma once

// libs

#pragma comment(lib, "opengl32.lib")

// additional

#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>
#include <SFML\Audio.hpp>
#include <TGUI\TGUI.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <json.hpp>
#include <Box2D\Box2D.h>

// embedded

#include <map>
#include <cstring>
#include <list>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <sstream>

// self-written

#include "Constants.h"

#ifdef _DEBUG
	#include <iostream>
#endif // !_DEBUG
