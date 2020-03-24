# Minimal project setup

In `src/Minimal.cpp` you can find a minimal project setup.
Containing a `Engine::Application` instance.
This instance is required to start the application.


### From here:
From here you can use the `Engine`-Api. All sources are available within the `Engine` namespace.

### Tutorials:

# Renderer:

- Inherit `Engine::Layer`

>For this example we focus on `Engine::Layer::OnUpdate`.

```c++
class ExampleLayer: public Engine::Layer
{
  public:
    ExampleLayer():Layer("Example"){}
    void OnUpdate(Engine::Timestep ts) override {}
};
```
- add camera layer
```c++
class ExampleLayer: public Engine::Layer
{
  public:
    ExampleLayer():Layer("Example"){}
    void OnUpdate(Engine::Timestep ts) override;
  private:
    Engine::OrthographicCameraController cameraLayer;
};
```

- Add implementation of `ExampleLayer::OnUpdate`

```c++
...
void ExampleLayer::OnUpdate(Engine::Timestep ts) override 
{
    Engine::Renderer::BeginScene(cameraLayer.GetCamera());
    Engine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1});
    Engine::RenderCommand::Clear();
    // TODO: Your render here
    cameraLayer.OnUpdate(ts);
    Engine::Renderer::EndScene();
}
...
```

With this setup we can explore the long dark =)

Use `W`, `A`, `S`, `D` to navigate

# (single/multiple) Mesh usage

> We continue with the previous setup

- extend `ExampleLayer` with Mesh instances
```
class ExampleLayer: public Engine::Layer
{
  public:
    ExampleLayer();
    void OnUpdate(Engine::Timestep ts) override;
  private:
    Engine::OrthographicCameraController cameraLayer;
    std::vector<Engine::Ref<Engine::Mesh>> models;
    Engine::Ref<Engine::Mesh> mesh;

};
ExampleLayer::ExampleLayer()
:Layer("Example")
{
    mesh = Engine::Mesh::Create("sandbox/assets/models/Example.obj",
                                "sandbox/assets/shaders/Example.glsl");
    models.push_back(Engine::Mesh::Create("sandbox/assets/models/Light.obj",
                                          "sandbox/assets/shaders/Light.glsl"));
}
...
```

- render Meshes in `ExampleLayer::OnUpdate`
```c++
...
void ExampleLayer::OnUpdate(Engine::Timestep ts) override 
{
    Engine::Renderer::BeginScene(cameraLayer.GetCamera());
    Engine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1});
    Engine::RenderCommand::Clear();

    mesh->OnUpdate(ts);
    for(const auto& obj : models){
        obj->OnUpdate(ts);
    }

    cameraLayer.OnUpdate(ts);
    Engine::Renderer::EndScene();
}
...
```
