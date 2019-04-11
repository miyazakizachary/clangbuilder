////////
#ifndef CBUI_VSSEARCH_HPP
#define CBUI_VSSEARCH_HPP
#include <string>
#include <vector>
#include <string_view>
#include "vsinstance.hpp"

class VisualStudioSeacher {
public:
  using container_t = std::vector<vssetup::VSInstance>;
  VisualStudioSeacher() = default;
  VisualStudioSeacher(const VisualStudioSeacher &) = delete;
  VisualStudioSeacher &operator=(const VisualStudioSeacher &) = delete;
  bool Execute(std::wstring_view root);
  const container_t &Instances() const { return instances; }
  int Index() const {
    if (instances.empty()) {
      return 0;
    }
    return static_cast<int>(instances.size() - 1);
  }
  size_t Size() const { return instances.size(); }
  const wchar_t *Version(int i) const {
    if (i < 0 || i >= instances.size()) {
      return L"";
    }
    return instances[i].Version.data();
  }

  std::wstring_view InstallVersion(int i) const {
    if (i < 0 || i >= instances.size()) {
      return L"0";
    }
    return instances[i].Version;
  }
  std::wstring_view InstanceId(int i) const {
    if (i < 0 || i >= instances.size()) {
      return L"-";
    }
    return instances[i].InstanceId;
  }

private:
  container_t instances;
  bool EnterpriseWDK(std::wstring_view root, vssetup::VSInstance &vsi);
};

#endif