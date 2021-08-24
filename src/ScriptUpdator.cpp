#include "ScriptUpdator.h"

#include "ScriptRef.h"
#include "Debug.h"

void ScriptUpdator::Update(entt::registry& registry, float dt) {
	auto view = registry.view<ScriptRef>();
	for (auto entity : view) {
		auto& script = registry.get<ScriptRef>(entity);
		script.callback.call(dt);
	}
}
