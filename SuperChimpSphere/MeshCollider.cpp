#include "MeshCollider.h"

MeshCollider::MeshCollider(Transform& _transform, Mesh* _mesh, Physics* _physics) : Collider(ColliderType::MESH, _transform, _physics), mesh(_mesh)
{
}
