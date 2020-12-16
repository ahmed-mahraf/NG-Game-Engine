/** \file engine.h
* A header file which includes relevant headers for development
*/

#pragma once
#include "core/base.h"
#include "core/application.h"
#include "layers/Layer.h"
#include "systems/MyLogger.h"

#include "core/Timestep.h"

#include "platforms/GLFW/GLFWInputPoller.h"
#include "platforms/GLFW/GLFWCodes.h"				// mouse button codes included
#include "rendering/OrthoCameraController.h"

#include "ImGui/ImGuiLayer.h"

// ---Renderer------------------------
#include "rendering/Renderer.h"
#include "rendering/renderer2D.h"
#include "rendering/RenderCommand.h"

#include "rendering/Shader.h"
#include "rendering/Texture.h"
#include "rendering/VertexArray.h"
#include "rendering/VertexBuffer.h"
#include "rendering/IndexBuffer.h"

#include "rendering/OrthoCamera.h"
// -----------------------------------
