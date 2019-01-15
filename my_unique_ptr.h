#ifndef MY_UNIQUE_PTR_H_
#define MY_UNIQUE_PTR_H_

#include <utility>

namespace kapil {
  template <typename T>
  class unique_ptr final {
    private:
      T* ptr_;
      unique_ptr(const unique_ptr&) = delete;               // Make unique_ptr non copy constructible
      unique_ptr& operator = (const unique_ptr&) = delete;  // Make unique_ptr non copy assignable

    public:
      explicit unique_ptr (T* ptr = nullptr) noexcept
        : ptr_{ptr} { }

      unique_ptr(unique_ptr<T>&& rval) noexcept               // Move constructor
        : ptr_{rval.ptr_} {
        rval.ptr_ = nullptr;
      }

      unique_ptr& operator = (unique_ptr&& rhs) noexcept {   // Move assignment
        delete ptr_;
        ptr_ = rhs.ptr_;
        rhs.ptr_ = nullptr;
        return *this;
      }

      ~unique_ptr() noexcept {
        delete ptr_;
      }

      
      T* release() noexcept {
        T* old_ptr = ptr_;
        ptr_ = nullptr;
        return old_ptr;
      }

      void reset(T* ptr = nullptr) noexcept {
        delete ptr_;
        ptr_ = ptr;
      }

      void swap(unique_ptr& rhs) noexcept {
        std::swap(ptr_, rhs.ptr_);
      }

      T* get() const noexcept {
        return ptr_;
      }

      explicit operator bool() const noexcept {
        return (ptr_ != nullptr);
      }

      T& operator * () const {
        return *ptr_;
      }

      T* operator -> () const noexcept {
        return ptr_;
      }

      friend bool operator == (const unique_ptr& lhs, const unique_ptr& rhs) {
        return lhs.get() == rhs.get();
      }

      friend bool operator != (const unique_ptr& lhs, const unique_ptr& rhs) {
        return !(lhs == rhs);
      }
  };

  template <typename T>
  void swap(unique_ptr<T>& lhs, unique_ptr<T>& rhs) {
    lhs.swap(rhs);
  }
} //kapil

#endif
