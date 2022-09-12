#include "KVBase.hpp"

namespace daydream {
namespace resource {

KVBase* KVBase::m_s_instance = nullptr;

KVBase::~KVBase() {
  for (auto item : m_data) { delete item.second; }
}

bool KVBase::FindByPath(const std::string& f) {
  auto it = m_data.find(Hashing(f));
  if (it != m_data.end()) { return true; }
  return false;
}

void KVBase::InsertTexture(const REF(Texture2D) & a, const std::string& name,
                           const std::string& f) {
  if (FindByPath(f)) { return; }
  m_data[Hashing(f)] = new TextureComponent(a, name, f);
}

REF(Texture2D) KVBase::FindTexture(const std::string& f) {
  if (FindByPath(f)) {
    return static_cast<TextureComponent*>(m_data.find(Hashing(f))->second)->Item();
  }
  return nullptr;
}

uint32_t KVBase::Hashing(const std::string& n) {
  std::hash<std::string> HashString;
  return HashString(n);
}

KVBase* getKVBaseInstance() { return KVBase::m_s_instance; }

}  // namespace resource
}  // namespace daydream