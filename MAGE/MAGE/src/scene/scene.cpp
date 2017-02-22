//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"
#include "scripting\behavior_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SharedPtr< BehaviorScript > Scene::GetScript(const string &name) const {
		set< SharedPtr< BehaviorScript > >::const_iterator it = m_scripts.cbegin();
		while (it != m_scripts.cend()) {
			if ((*it)->GetName() == name) {
				return (*it);
			}
			else {
				++it;
			}
		}
		return nullptr;
	}
	bool Scene::HasScript(const SharedPtr< BehaviorScript > script) const {
		set< SharedPtr< BehaviorScript > >::const_iterator it = m_scripts.cbegin();
		while (it != m_scripts.cend()) {
			if ((*it) == script) {
				return true;
			}
			else {
				++it;
			}
		}
		return false;
	}
	void Scene::AddScript(SharedPtr< BehaviorScript > script, bool load) {
		if (!script) {
			return;
		}

		m_scripts.insert(script);

		if (load) {
			script->Load();
		}
	}
	void Scene::RemoveScript(const string &name, bool close) {
		set< SharedPtr< BehaviorScript > >::iterator it = m_scripts.begin();
		while (it != m_scripts.end()) {
			if ((*it)->GetName() == name) {
				if (close) {
					(*it)->Close();
				}
				it = m_scripts.erase(it);
				break;
			}
			else {
				++it;
			}
		}
	}
	void Scene::RemoveScript(SharedPtr< BehaviorScript > script, bool close) {
		set< SharedPtr< BehaviorScript > >::iterator it = m_scripts.begin();
		while (it != m_scripts.end()) {
			if ((*it) == script) {
				if (close) {
					(*it)->Close();
				}
				it = m_scripts.erase(it);
				break;
			}
			else {
				++it;
			}
		}
	}
	void Scene::RemoveAllScripts(bool close) {
		set< SharedPtr< BehaviorScript > >::iterator it = m_scripts.begin();
		if (close) {
			while (it != m_scripts.end()) {
				(*it)->Close();
				it = m_scripts.erase(it);
			}
		}
		else {
			while (it != m_scripts.end()) {
				it = m_scripts.erase(it);
			}
		}
	}

	void Scene::Load() {
		for (set< SharedPtr< BehaviorScript > >::iterator it = m_scripts.begin(); it != m_scripts.end(); ++it) {
			(*it)->Load();
		}
	}
	void Scene::Update(double elapsed_time) {
		for (set< SharedPtr< BehaviorScript > >::iterator it = m_scripts.begin(); it != m_scripts.end(); ++it) {
			(*it)->Update(elapsed_time, *this);
		}
	}
	void Scene::Render(ComPtr< ID3D11DeviceContext2 > device_context) {
		TransformBuffer transform_buffer;
		transform_buffer.world_to_view      = XMMatrixTranspose(GetCamera().GetTransform().GetWorldToObjectMatrix());
		transform_buffer.view_to_projection = XMMatrixTranspose(GetCamera().GetViewToProjectionMatrix());

		//@TODO
		const XMVECTOR p_eye = XMVectorSet(0.0f, 3.0f, -6.0f, 1.0f);
		const XMVECTOR p_focus = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
		const XMVECTOR d_up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		transform_buffer.world_to_view = XMMatrixTranspose(XMMatrixLookAtLH(p_eye, p_focus, d_up));

		m_world->Render(device_context, transform_buffer);
	}
	void Scene::Close() {
		RemoveAllScripts(true);
	}
}