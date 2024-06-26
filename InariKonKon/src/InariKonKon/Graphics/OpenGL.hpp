#pragma once

#include "glad/gl.h"

#include "InariKonKon/Window/Context/Context.hpp"

#define gl ikk::priv::Context::getInstance().getActiveContext()