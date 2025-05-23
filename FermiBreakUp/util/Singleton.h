//
// Created by Artem Novikov on 17.02.2024.
//

#ifndef FERMIBREAKUP_UTILITIES_SINGLETON_H
#define FERMIBREAKUP_UTILITIES_SINGLETON_H

#include <memory>

#include "Logger.h"

namespace fbu {
  template <typename T>
  class Singleton {
  public:
    Singleton() {
      if (FERMI_UNLIKELY(instance_ == nullptr)) {
        instance_ = std::make_unique<T>();
      }
    }

    template <typename... Args>
    Singleton(Args&& ... args) {
      Reset(std::forward<Args>(args)...);
    }

    Singleton(T* ptr) {
      Reset(ptr);
    }

    ~Singleton() = default;

    template <typename... Args>
    static void Reset(Args&& ... args) {
      instance_ = std::make_unique<T>(std::forward<Args>(args)...);
    }

    static void Reset(T* ptr) {
      instance_.reset(ptr);
    }

    static T& Instance() {
      if (FERMI_UNLIKELY(instance_ == nullptr)) {
        instance_ = std::make_unique<T>();
      }
      return *instance_;
    }

    T& operator*() {
      return *instance_;
    }

    const T& operator*() const {
      return *instance_;
    }

    T* operator->() {
      return instance_.get();
    }

    const T& operator->() const {
      return *instance_;
    }

  private:
    static inline std::unique_ptr<T> instance_;
  };
} // namespace fbu

#endif // FERMIBREAKUP_UTILITIES_SINGLETON_H
