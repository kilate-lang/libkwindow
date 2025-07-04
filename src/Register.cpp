#include <cstdlib>
#include <string.h>
#include <iostream>

#include <kilate/cpp/native.hpp>

#include "Register.hpp"
#include "KwWindow.hpp"

extern "C" {

  #include <kilate/native.h>

  klt_node* kw_create_window(klt_native_fndata* data) {
    if (data->params->size == 5) {
      std::string name = kilate::native::getFnDataString(data, 0);
      int width        = kilate::native::getFnDataInt(data, 1);
      int height       = kilate::native::getFnDataInt(data, 2);
      int x            = kilate::native::getFnDataInt(data, 3);
      int y            = kilate::native::getFnDataInt(data, 4);
      kwlib::KwWindow* window = new kwlib::KwWindow(name.c_str(), width, height, x, y);
      free(data);
      return kilate::node::createReturnNode(
          NODE_VALUE_TYPE_LONG,
          (void*)(long)window);
    }
    free(data);
    return kilate::node::createReturnNode(
        NODE_VALUE_TYPE_LONG,
        0L);
  }

  klt_native_fnentry* kw_get_create_window_fnentry() {
    // Required params
    klt_str_vector* reqParams = klt_vector_make(sizeof(klt_str*));
    kilate::native::addParam(reqParams, "string");
    kilate::native::addParam(reqParams, "number");
    kilate::native::addParam(reqParams, "number");
    kilate::native::addParam(reqParams, "number");
    kilate::native::addParam(reqParams, "number");
    klt_native_fnentry* entry =
        kilate::native::createFnEntry("kw_create_window",
                                      reqParams,
                                      kw_open_window);
    return entry;
  }

  klt_node* kw_open_window(klt_native_fndata* data) {
    if (data->params->size == 1) {
      long ptr = kilate::native::getFnDataLong(data, 0);
      if (ptr == 0) {
        std::cout << "Window pointer is 0(null)" << std::endl;
        free(data);
        return nullptr;
      }
      kwlib::KwWindow* window = (kwlib::KwWindow*)ptr;
      window->show();
    }
    free(data);
    return nullptr;
  }

  klt_native_fnentry* kw_get_open_window_fnentry() {
    // Required params
    klt_str_vector* reqParams = klt_vector_make(sizeof(klt_str*));
    kilate::native::addParam(reqParams, "long");
    klt_native_fnentry* entry =
        kilate::native::createFnEntry("kw_open_window",
                                      reqParams,
                                      kw_open_window);
    return entry;
  }
}