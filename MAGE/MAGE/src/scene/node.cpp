//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Node::Node(string name)
		: m_transform(),
		m_parent(nullptr),
		m_childs(),
		m_components(),
		m_state(State::Active),
		m_this(),
		m_name(std::move(name)) {}

	Node::Node(const Node &node) = default;

	Node::Node(Node &&node) noexcept
		: m_transform(std::move(node.m_transform)),
		m_parent(std::move(node.m_parent)),
		m_childs(std::move(node.m_childs)),
		m_components(std::move(node.m_components)),
		m_state(node.m_state),
		m_this(std::move(node.m_this)),
		m_name(std::move(node.m_name)) {}

	Node::~Node() {
		RemoveAllChilds();
	}

	Node &Node::operator=(Node &&node) noexcept = default;

	void Node::Set(NodePtr ptr) noexcept {
		m_this = std::move(ptr);

		m_transform.SetOwner(m_this);

		ForEachComponent([this](Component &component) noexcept {
			component.SetOwner(m_this);
		});

		ForEachChild([this](Node &node) noexcept {
			node.m_parent = m_this;
		});
	}

	//-------------------------------------------------------------------------
	// Member Methods: Graph
	//-------------------------------------------------------------------------

	void Node::AddChild(NodePtr node) {
		if (  nullptr == node
			|| m_this == node
			|| m_this == node->m_parent
			|| State::Terminated == m_state
			|| State::Terminated == node->m_state) {
			return;
		}

		if (node->m_parent) {
			node->m_parent->RemoveChild(node);
		}

		node->m_parent = m_this;
		node->m_transform.SetDirty();

		m_childs.push_back(std::move(node));
	}

	void Node::RemoveChild(NodePtr node) {
		if (  nullptr == node
			|| m_this != node->m_parent) {
			return;
		}

		node->m_parent = nullptr;
		node->m_transform.SetDirty();

		if (const auto it = std::find(m_childs.begin(), m_childs.end(), node); 
			it != m_childs.end()) {

			m_childs.erase(it);
		}
		else {
			Fatal("Node connections are broken.");
		}
	}

	void Node::RemoveAllChilds() noexcept {

		ForEachChild([](Node &node) noexcept {
			node.m_parent = nullptr;
			node.m_transform.SetDirty();
		});

		m_childs.clear();
	}

	//-------------------------------------------------------------------------
	// Member Methods: Components
	//-------------------------------------------------------------------------

	void Node::AddComponent(ComponentPtr component) {
		if (nullptr == component
			|| component->HasOwner()
			|| State::Terminated == m_state
			|| State::Terminated == component->GetState()) {
			return;
		}

		component->SetOwner(m_this);

		m_components.emplace(typeid(*component), std::move(component));
	}

	//-------------------------------------------------------------------------
	// Member Methods: State
	//-------------------------------------------------------------------------

	void Node::SetState(State state) noexcept {
		if (State::Terminated == state
			|| m_state == state) {
			return;
		}

		m_state = state;

		ForEachComponent([state](Component &component) noexcept {
			component.SetState(state);
		});

		ForEachChild([state](Node &node) noexcept {
			node.SetState(state);
		});
	}
}