#pragma once

#include "InariKonKon/Graphics/OpenGL/glad/gl.h"
#include "InariKonKon/Window/Context/Context.hpp"

#define gl ikk::priv::Context::getInstance().getActiveContext()