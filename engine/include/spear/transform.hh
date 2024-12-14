#ifndef SPEAR_TRANSFORM_HH
#define SPEAR_TRANSFORM_HH

#include <glm/gtc/matrix_transform.hpp>

namespace spear
{

class Transform
{
public:
    Transform();
    virtual void translate(const glm::vec3& position);
    virtual void rotate(float speed, const glm::vec3& direction);
    virtual void scale(const glm::vec3& scale);
    const glm::mat4& getModel()
    {
        return m_model;
    }
    glm::vec3 getPosition() const;

protected:
    glm::mat4 m_model;
};

} // namespace spear

#endif
