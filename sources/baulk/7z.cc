//
#include <bela/path.hpp>
#include "process.hpp"
#include "fs.hpp"

namespace baulk::sevenzip {
//
inline std::optional<std::wstring> lookup_sevenzip() {
  std::wstring s7z;
  if (bela::ExecutableExistsInPath(L"7z.exe", s7z)) {
    return std::make_optional(std::move(s7z));
  }
  bela::error_code ec;
  auto self = bela::ExecutablePath(ec);
  if (!self) {
    return std::nullopt;
  }
  s7z = bela::StringCat(*self, L"\\7z.exe");
  if (!bela::PathExists(s7z)) {
    return std::nullopt;
  }
  return std::make_optional(std::move(s7z));
}

bool decompress(std::wstring_view src, std::wstring_view outdir,
                bela::error_code &ec) {
  auto s7z = lookup_sevenzip();
  if (!s7z) {
    ec = bela::make_error_code(ERROR_NOT_FOUND, L" 7z not install");
    return false;
  }
  baulk::Process process;
  if (process.Execute(*s7z, L"e -spf -y \"", src, L"\" \"-o", outdir, L"\"") !=
      0) {
    return false;
  }
  return true;
}
bool initialize(std::wstring_view path) {
  //
  return true;
}
} // namespace baulk::sevenzip