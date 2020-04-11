#include "SandboxApp.h"

Engine::Application* Engine::CreateApplication(){
  return new Sandbox();
}

Sandbox::Sandbox()
{
  PushLayer(new ExampleLayer());
  //PushLayer(new Engine::Level("Level 0-0"));
  PushLayer(new GameWorld());
}

inline ExampleLayer::ExampleLayer()
  : Layer("Example")
  , m_SquarePosition(0.0f)
{
  m_VertexArray.reset(Engine::VertexArray::Create());

  float vertices[] = { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
                        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

                        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

                        -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

                        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
                        0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
                        0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

                        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f };
  Engine::Ref<Engine::VertexBuffer> triangleVB;
  triangleVB.reset(Engine::VertexBuffer::Create(vertices, sizeof(vertices)));

  Engine::BufferLayout layout = {
    { Engine::ShaderDataType::Float3, "position" },
    { Engine::ShaderDataType::Float2, "texture" },
  };

  triangleVB->SetLayout(layout);
  m_VertexArray->AddVertexBuffer(triangleVB);

  uint32_t indices[36] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 };

  Engine::Ref<Engine::IndexBuffer> triangleIA;
  triangleIA.reset(Engine::IndexBuffer::Create(indices, sizeof(indices)));
  m_VertexArray->SetIndexBuffer(triangleIA);

  m_SquareVA.reset(Engine::VertexArray::Create());

  float squareVertices[5 * 4] = { -0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f, -0.5f, 1.0f, 0.0f, 0.5f, 0.0f, 0.5f, 1.0f, 1.0f, -0.5f, 0.0f, 0.5f, 0.0f, 1.0f };

  Engine::Ref<Engine::VertexBuffer> squareVB;
  squareVB.reset(Engine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
  squareVB->SetLayout({ { Engine::ShaderDataType::Float3, "position" },{ Engine::ShaderDataType::Float2, "textCord" } });
  m_SquareVA->AddVertexBuffer(squareVB);


  uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
  Engine::Ref<Engine::IndexBuffer> squareIA;
  squareIA.reset(Engine::IndexBuffer::Create(squareIndices, sizeof(squareIndices)));
  m_SquareVA->SetIndexBuffer(squareIA);

  m_Shader = Engine::Shader::Create("sandbox/assets/shaders/Default.glsl");
  m_FlatColorShader = Engine::Shader::Create("sandbox/assets/shaders/FlatColor.glsl");
  auto textureShader = m_ShaderLibrary.Load("Texture", "sandbox/assets/shaders/Texture.glsl");

  m_Texture = Engine::Texture2D::Create(textureSrc);
  m_PortalTexture = Engine::Texture2D::Create(textureSrc2);
  m_Suzanne = Engine::Mesh::Create("sandbox/assets/models/Suzanne.obj", "sandbox/assets/shaders/Suzanne.glsl");
  m_Cube = Engine::Mesh::Create("sandbox/assets/models/Example.obj", "sandbox/assets/shaders/Example.glsl");
  m_Cube6 = Engine::Mesh::Create("sandbox/assets/models/cube6.obj", "sandbox/assets/shaders/Example.glsl");
  m_Models.push_back(Engine::Mesh::Create("sandbox/assets/models/Light.obj", "sandbox/assets/shaders/Light.glsl"));
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(0.5f, 1.0f, 0.0f));

  m_Shader->Bind();
  m_Shader->UploadUniformMat4("model", model);
  textureShader->Bind();
  textureShader->UploadUniformInt("u_Texture", 0);
}

inline void ExampleLayer::OnUpdate(Engine::Timestep ts)
{
  const float ts_float = ts.count();
  Engine::Renderer::BeginScene(m_PlayerCameraLayer.GetCamera());
  {
    if (Engine::Input::IsKeyPressed(BE_KEY_J)) { m_SquarePosition.x += m_SquareMoveSpeed * ts_float; }
    else if (Engine::Input::IsKeyPressed(BE_KEY_L))
    {
      m_SquarePosition.x -= m_SquareMoveSpeed * ts_float;
    }
    if (Engine::Input::IsKeyPressed(BE_KEY_I)) { m_SquarePosition.y -= m_SquareMoveSpeed * ts_float; }
    else if (Engine::Input::IsKeyPressed(BE_KEY_K))
    {
      m_SquarePosition.y += m_SquareMoveSpeed * ts_float;
    }
  }
  Engine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
  Engine::RenderCommand::Clear();

  glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

  m_FlatColorShader->Bind();
  m_FlatColorShader->UploadUniformFloat3("u_Color", m_SquareColor);

  glm::mat4 model = glm::mat4(1.0f);
  m_Shader->Bind();
  m_Shader->UploadUniformMat4("model", model);
  if (objects[Objects::Cube3DMan]) { Engine::Renderer::Submit(m_VertexArray, m_FlatColorShader, glm::mat4(1.0f)); }
  // TODO: Goal
  //Engine::MaterialRef material = new Engine::Material(m_FlatColorShader);
  //Engine::MaterialInstanceRef ml = new Engine::MaterialInstance(material);
  //ml->Set("u_Color", redColor);
  //squareMesh->SetMaterial(ml);


  if (objects[Objects::Grid])
  {
    // Grid
    for (int y = -15; y < 30; ++y)
    {
      for (int x = -15; x < 30; ++x)
      {
        glm::vec3 pos(x * 0.1f, 0.0f, y * 0.1f);
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
        Engine::Renderer::Submit(m_SquareVA, m_FlatColorShader, transform);
      }
    }
  }
  auto textureShader = m_ShaderLibrary.Get("Texture");
  if (objects[Objects::ImageTexture])
  {
    m_Texture->Bind();
    Engine::Renderer::Submit(m_SquareVA, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
    m_PortalTexture->Bind();
    Engine::Renderer::Submit(m_SquareVA, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
  }
  if (objects[Objects::Cube2D])
  {
    Engine::Renderer::Submit(m_SquareVA, textureShader, glm::translate(glm::mat4(1.0f), glm::vec3(0.25f, -0.25f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
  }

  if (objects[Objects::Triangle]) glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * scale;

  if (objects[Objects::Cube3D]) m_Cube->OnUpdate(ts);
  if (objects[Objects::Cube3D6]) m_Cube6->OnUpdate(ts);
  if (objects[Objects::Suzanne]) m_Suzanne->OnUpdate(ts);
  //      for(const auto& obj : m_Models){
  //        obj->OnUpdate(ts_float);
  //      }
  m_PlayerCameraLayer.OnUpdate(ts);

  Engine::Renderer::EndScene();
}

inline void ExampleLayer::OnEvent(Engine::Event& event)
{
  Engine::EventDispatcher dispatcher(event);

  dispatcher.Dispatch<Engine::KeyPressedEvent>(BE_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
  m_PlayerCameraLayer.OnEvent(event);
}

inline void ExampleLayer::OnImGuiRender()
{
  {
    // Admin panel
    ImGui::Begin("Admin");
    ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::Checkbox("Suzanne", &objects[Objects::Suzanne]);
    ImGui::Checkbox("Triangle", &objects[Objects::Triangle]);
    ImGui::Checkbox("Cube3D", &objects[Objects::Cube3D]);
    ImGui::Checkbox("Cube3D6", &objects[Objects::Cube3D6]);
    ImGui::Checkbox("Cube2D", &objects[Objects::Cube2D]);
    ImGui::Checkbox("Grid", &objects[Objects::Grid]);
    ImGui::Checkbox("ImageTexture", &objects[Objects::ImageTexture]);
    ImGui::Checkbox("Cube3DMan", &objects[Objects::Cube3DMan]);
    ImGui::End();
  }
  m_PlayerCameraLayer.OnImGuiRender();
  // Mesh panel
  {
    ImGui::Begin("Meshs");
    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_FittingPolicyDefault_ | ImGuiTabBarFlags_Reorderable;
    if (ImGui::BeginTabBar("##tabs", tab_bar_flags))
    {
      m_Suzanne->OnImGuiRender();
      m_Cube->OnImGuiRender();
      for (const auto& obj : m_Models) { obj->OnImGuiRender(); }
      ImGui::EndTabBar();
    }
    ImGui::End();
  }
}
