 #pragma once
#include "engine/Application.h"
#include "engine/core/io/Log.h"
#include "engine/core/Layer.h"
#include "engine/core/Timestep.h"

#include "engine/imgui/ImGuiLayer.h"

// --- Input ---
// -------------
// -------------

#include "engine/core/io/Input.h"
#include "engine/core/io/MouseButtonCodes.h"
#include "engine/core/io/KeyCodes.h"


// --- Rendering ---
// -----------------
// -----------------

#include "engine/renderer/Renderer.h"
#include "engine/renderer/RenderCommand.h"

#include "engine/renderer/Buffer.h"
#include "engine/renderer/Shader.h"
#include "engine/renderer/mesh/Texture.h"
#include "engine/renderer/mesh/Mesh.h"
#include "engine/renderer/VertexArray.h"

#include "engine/renderer/camera/OrthographicCamera.h"
#include "engine/renderer/camera/ThirdPersonCamera.h"
#include "engine/renderer/camera/CameraController.h"


// --- 3D ----------
// -----------------
// -----------------

#include "engine/game/Level.h"
#include "engine/game/KineticBody.h"

// --- Entry point ---
// -------------------
// -------------------

#include "engine/core/EntryPoint.h"
