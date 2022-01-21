#include <sstream>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/numpy.h>
#include <pybind11/eigen.h>

#include "libmotioncapture/motioncapture.h"
#include "libmotioncapture/testmocap.h"
#include "libmotioncapture/optitrack.h"

using namespace libmotioncapture;

// PYBIND11_MAKE_OPAQUE(std::array<uint8_t, CRTP_MAXSIZE>)

namespace py = pybind11;
using namespace pybind11::literals;

// template<class T>
// std::string toString(const T& x) 
// {
//   std::stringstream sstr;
//   sstr << x;
//   return sstr.str();
// }

PYBIND11_MODULE(motioncapture, m) {

  m.attr("__version__") = version();

  m.def("connect", &MotionCapture::connect);

  // Quaternions
  py::class_<Eigen::Quaternionf>(m, "Quaternion")
      .def_property_readonly("x", py::overload_cast<>(&Eigen::Quaternionf::x, py::const_))
      .def_property_readonly("y", py::overload_cast<>(&Eigen::Quaternionf::y, py::const_))
      .def_property_readonly("z", py::overload_cast<>(&Eigen::Quaternionf::z, py::const_))
      .def_property_readonly("w", py::overload_cast<>(&Eigen::Quaternionf::w, py::const_));

  // RigidBody
  py::class_<RigidBody>(m, "RigidBody")
      .def_property_readonly("name", &RigidBody::name)
      .def_property_readonly("position", &RigidBody::position)
      .def_property_readonly("rotation", &RigidBody::rotation);

  py::class_<MotionCaptureTest>(m, "MotionCaptureTest")
      .def(py::init<float, const std::vector<RigidBody>&>())//, const pcl::PointCloud<pcl::PointXYZ>::Ptr>())
      .def("waitForNextFrame", &MotionCaptureTest::waitForNextFrame, py::call_guard<py::gil_scoped_release>())
      .def_property_readonly("rigidBodies", &MotionCaptureTest::rigidBodies);

  //
  py::class_<MotionCapture>(m, "MotionCapture")
      .def("waitForNextFrame", &MotionCapture::waitForNextFrame, py::call_guard<py::gil_scoped_release>())
      .def_property_readonly("rigidBodies", &MotionCapture::rigidBodies);

  //
  py::class_<MotionCaptureOptitrack>(m, "MotionCaptureOptitrack")
      .def(py::init<const std::string &>())
      .def("waitForNextFrame", &MotionCaptureOptitrack::waitForNextFrame, py::call_guard<py::gil_scoped_release>())
      .def_property_readonly("rigidBodies", &MotionCaptureOptitrack::rigidBodies);

  // // Packet
  // py::class_<Packet>(m, "Packet", py::buffer_protocol())
  //     .def(py::init<>())
  //     .def_property("channel", &Packet::channel, &Packet::setChannel)
  //     .def_property("port", &Packet::port, &Packet::setPort)
  //     // .def_property(
  //     //     "data", [](Packet &p) -> py::array {
  //     //       auto dtype = py::dtype(py::format_descriptor<uint8_t>::format());
  //     //       auto base = py::array(dtype, {p.size()}, {sizeof(uint8_t)});
  //     //       return py::array(
  //     //           dtype, {p.size()}, {sizeof(uint8_t)}, p.data(), base); }, [](Packet &) {})
  //     .def_buffer([](Packet &p) -> py::buffer_info {
  //       return py::buffer_info(p.payload(), p.payloadSize(), /*readonly*/ false);
  //     })
  //     .def("__len__", [](const Packet &p) {
  //       return p.payloadSize();
  //     })
  //     .def("__getitem__", [](const Packet &p, py::ssize_t i) {
  //       if (i >= (long int)p.payloadSize())
  //         throw py::index_error();
  //       return p.payload()[i];
  //     })
  //     .def("__setitem__", [](Packet &p, py::ssize_t i, int v) {
  //       if (i >= (long int)p.payloadSize())
  //         throw py::index_error();
  //       if (v < 0 || v > 255)
  //         throw py::value_error();
  //       return p.payload()[i] = v;
  //     })
  //     .def_property("payload",
  //       [](const Packet &p) -> py::bytes {
  //         return py::bytes(reinterpret_cast<const char*>(p.payload()), p.payloadSize());
  //       },
  //       [](Packet &p, py::bytes value) {
  //         char *buffer;
  //         ssize_t length;
  //         PYBIND11_BYTES_AS_STRING_AND_SIZE(value.ptr(), &buffer, &length);
  //         p.setPayloadSize(length);
  //         std::memcpy(p.payload(), buffer, length);
  //       })
  //     .def_property("size", &Packet::payloadSize, &Packet::setPayloadSize)
  //     .def_property_readonly("valid", &Packet::valid)
  //     .def("__repr__", &toString<Packet>);

  // //
  // py::class_<Connection::Statistics>(m, "ConnectionStatistics")
  //     .def_readonly("sent_count", &Connection::Statistics::sent_count)
  //     .def_readonly("ack_count", &Connection::Statistics::ack_count)
  //     .def("__repr__", &toString<Connection::Statistics>);

  // // Connection
  // py::class_<Connection>(m, "Connection")
  //     .def(py::init<
  //          const std::string &>())
  //     .def_static("scan", &Connection::scan, py::arg("address") = 0xE7E7E7E7E7, py ::call_guard<py::gil_scoped_release>())
  //     .def_static("scan_selected", &Connection::scan_selected, py ::call_guard<py::gil_scoped_release>())
  //     .def("send", &Connection::send, py::call_guard<py::gil_scoped_release>())
  //     .def("recv", &Connection::recv, py::arg("timeout"), py::call_guard<py::gil_scoped_release>())
  //     .def("close", &Connection::close, py::call_guard<py::gil_scoped_release>())
  //     .def_property_readonly("uri", &Connection::uri)
  //     .def_property_readonly("statistics", &Connection::statistics)
  //     .def("__repr__", &toString<Connection>);
}
