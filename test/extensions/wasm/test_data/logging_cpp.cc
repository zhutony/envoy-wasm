// NOLINT(namespace-envoy)
#include <string>

#include "proxy_wasm_intrinsics.h"

extern "C" PROXY_WASM_KEEPALIVE uint32_t proxy_on_configure(uint32_t, uint32_t) {
  const char* configuration = nullptr;
  size_t size;
  proxy_get_configuration(&configuration, &size);
  logWarn(std::string("warn " + std::string(configuration, size)));
  ::free((void*)configuration);
  return 1;
}

extern "C" PROXY_WASM_KEEPALIVE uint32_t proxy_on_vm_start(uint32_t, uint32_t) {
  logTrace("test trace logging");
  logDebug("test debug logging");
  logError("test error logging");
  return 1;
}

extern "C" PROXY_WASM_KEEPALIVE void proxy_on_tick(uint32_t) {
  const char* root_id = nullptr;
  size_t size;
  proxy_get_property("plugin_root_id", sizeof("plugin_root_id") - 1, &root_id, &size);
  logInfo("test tick logging" + std::string(root_id, size));
  proxy_done();
}

extern "C" PROXY_WASM_KEEPALIVE uint32_t proxy_on_done(uint32_t) {
  logInfo("onDone logging");
  return 0;
}

extern "C" PROXY_WASM_KEEPALIVE void proxy_on_delete(uint32_t) { logInfo("onDelete logging"); }
