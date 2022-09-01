#include <pybind11/pybind11.h>
#include "d_ui/window/window.hpp"

namespace py = pybind11;
using namespace daydream::ui;

PYBIND11_MODULE(pydaydream, m) {
  py::class_<imgui_window>(m, "DWindow").def(py::init<>()).def("exec", &imgui_window::exec);
}
