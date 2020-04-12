#pragma once
#include "engine/Application.h"
#include "engine/Log.h"
#include "engine/Layer.h"
#include "engine/core/Timestep.h"

#include "engine/imgui/ImGuiLayer.h"

// --- Input ---
// -------------
// -------------

#include "engine/Input.h"
#include "engine/MouseButtonCodes.h"
#include "engine/KeyCodes.h"


// --- Rendering ---
// -----------------
// -----------------

#include "engine/renderer/Renderer.h"
#include "engine/renderer/RenderCommand.h"

#include "engine/renderer/Buffer.h"
#include "engine/renderer/Shader.h"
#include "engine/renderer/Texture.h"
#include "engine/renderer/Mesh.h"
#include "engine/renderer/VertexArray.h"

#include "engine/renderer/OrthographicCamera.h"
#include "engine/renderer/OrthographicCameraController.h"


// --- 3D ----------
// -----------------
// -----------------

#include "engine/game/Level.h"

// --- Entry point ---
// -------------------
// -------------------

#ifdef ENGINE_ENTRY_POINT
#include "engine/EntryPoint.h"
#endif //ENGINE_ENTRY_POINT
