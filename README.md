Daydream libs & Engine
===
The Daydream libs are a warper of OpenGL API. And it also provide methods to manage resources(k-v like database), construct UI(In Qt like API), use Signal and slots system, use log system, etc. I also used this lib build a Small Engine. **This project is a part of Computer Graphics lecture's Final project. It aims to implement various algorithms for convenient purpose, so it is not quite robustness from engineering perspective.**

## Libs provided by Daydream
There r 4 basic parts of daydream: UI, Core, Renderer and Event. The patterns/organization of this libs and how to use them r illustrate below.
### UI
This lib is dynamic libs by default, and this lib is rely on **Core, Render, Event**.

The UI lib is quite small and easily to use. There r 3 abstracts contained in this lib: Widget, Layer and Window. 

The Window abstraction will maintain the `glfw`'s contexture. And using ImGui as the ui backend. All applications build by this lib should use `Window` abstraction first.

`Window` will organize all `Layer`s belong to it. And it is responsible for call the `Layer`s' `render` and `update` functions by sequential.

The `Layer` abstraction is a container of all `widget`, and a `layer` works like a sub-docker window in the application(or to say, MainWindow).

### Core
### Renderer
### Event