#pragma once

#include <memory>

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <entt/entity/component.hpp>

struct Transform {
	friend class Scene;
public:
	glm::vec3 get_position() const
	{
		if (p_parent != nullptr)
		{
			return p_parent->get_world_matrix() * glm::vec4(p_local_position, 1.0);
		}
		else
		{
			return p_local_position;
		}
	}
	glm::vec3 get_local_position() const
	{
		return p_local_position;
	}
	void set_local_position(glm::vec3 new_position)
	{
		p_local_position = new_position;
		p_recalculate_matrix = true;
		p_set_requires_scene_update();
	}
	glm::quat get_rotation() const
	{
		if (p_parent != nullptr)
		{
			return p_parent->get_rotation() * p_local_rotation;
		}
		else
		{
			return p_local_rotation;
		}
	}
	glm::quat get_local_rotation() const
	{
		return p_local_rotation;
	}
	void set_local_rotation(glm::quat new_rotation)
	{
		p_local_rotation = new_rotation;
		p_recalculate_matrix = true;
		p_set_requires_scene_update();
	}
	glm::vec3 get_local_scale() const
	{
		return p_local_scale;
	}
	void set_local_scale(glm::vec3 new_scale)
	{
		p_local_scale = new_scale;
		p_recalculate_matrix = true;
		p_set_requires_scene_update();
	}
	glm::mat4 get_local_matrix()
	{
		if (p_recalculate_matrix)
		{
			p_calculate_matrix();
			p_recalculate_matrix = false;
		}
		return p_cached_matrix;
	}
	glm::mat4 get_world_matrix()
	{
		if (p_parent != nullptr)
		{
			return p_parent->get_world_matrix() * get_local_matrix();
		}
		else
		{
			return get_local_matrix();
		}
	}

	void set_parent(Transform* new_parent)
	{
		if (p_parent != nullptr)
		{
			p_parent->p_erase_child(this);
		}
		new_parent->p_children.push_back(this);
		p_parent = new_parent;
		p_set_requires_scene_update();
	}

	Transform* const get_parent() const
	{
		return p_parent;
	}

	void add_child(Transform* child)
	{
		child->set_parent(this);
	}

	bool is_ancestor(Transform* other) const
	{
		Transform* current_ancestor_to_check = p_parent;
		while (current_ancestor_to_check != nullptr)
		{
			if (current_ancestor_to_check == other)
			{
				return true;
			}
			else
			{
				current_ancestor_to_check = current_ancestor_to_check->p_parent;
			}
		}
		return false;
	}

	bool get_requires_scene_update() const
	{
		return p_requires_scene_update;
	}

private:
	glm::vec3 p_local_position = glm::vec3(0,0,0);
	glm::quat p_local_rotation = glm::quat();
	glm::vec3 p_local_scale = glm::vec3(1, 1, 1);
	glm::mat4 p_cached_matrix;
	bool p_recalculate_matrix = true;

	Transform* p_parent;
	std::vector<Transform*> p_children;

	bool p_requires_scene_update = true;

	void p_set_requires_scene_update()
	{
		p_requires_scene_update = true;
		for (auto child : p_children)
		{
			child->p_set_requires_scene_update();
		}
	}

	void p_calculate_matrix()
	{
		p_cached_matrix = glm::translate(p_local_position) * glm::toMat4(p_local_rotation) * glm::scale(p_local_scale);
	}

	void p_erase_child(Transform* child)
	{
		p_children.erase(
			std::find(p_children.begin(), p_children.end(), child)
		);
	}

};

template<>
struct entt::component_traits<Transform> : entt::basic_component_traits
{
	using in_place_delete = std::true_type;
};