#include "../include/quaternions.hpp"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>


namespace andromeda::math
{
    namespace
    {
        inline glm::quat to_glm(const Quaternion& q)
        {
            return glm::quat(q.w, q.x, q.y, q.z);
        }

        inline Quaternion from_glm(const glm::quat& gq)
        {
            return Quaternion(gq.w, gq.x, gq.y, gq.z);
        }

        inline glm::vec3 to_glm(const Vec3& v)
        {
            return glm::vec3(v.data[0], v.data[1], v.data[2]);
        }

        inline Vec3 from_glm(const glm::vec3& gv)
        {
            return Vec3(gv.x, gv.y, gv.z);
        }

        inline glm::mat4 to_glm(const Mat4& m)
        {
            glm::mat4 gm(1.0f);
            for (int c = 0; c < 4; ++c)
            {
                for (int r = 0; r < 4; ++r)
                {
                    gm[c][r] = m[c][r];
                }
            }
            return gm;
        }

        inline Mat4 from_glm(const glm::mat4& gm)
        {
            Mat4 m(1.0f);
            for (int c = 0; c < 4; ++c)
            {
                for (int r = 0; r < 4; ++r)
                {
                    m[c][r] = gm[c][r];
                }
            }
            return m;
        }
    }

    Quaternion QuaternionOps::identity()
    {
        return Quaternion::identity();
    }

    Quaternion QuaternionOps::from_axis_angle(const Vec3& axis, float angle_radians)
    {
        glm::vec3 g_axis = to_glm(axis);
        glm::quat gq = glm::angleAxis(angle_radians, glm::normalize(g_axis));
        return from_glm(gq);
    }

    float QuaternionOps::length(const Quaternion& q)
    {
        return std::sqrt(length_squared(q));
    }

    float QuaternionOps::length_squared(const Quaternion& q)
    {
        return q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z;
    }

    Quaternion QuaternionOps::normalize(const Quaternion& q, float epsilon)
    {
        glm::quat g = to_glm(q);
        float len_sq = glm::dot(g, g);

        if (len_sq <= epsilon * epsilon)
        {
            return q;
        }

        g = glm::normalize(g);
        return from_glm(g);
    }

    Quaternion QuaternionOps::conjugate(const Quaternion& q)
    {
        return Quaternion(q.w, -q.x, -q.y, -q.z);
    }

    Quaternion QuaternionOps::inverse(const Quaternion& q, float epsilon)
    {
        glm::quat g = to_glm(q);
        float len_sq = glm::dot(g, g);

        if (len_sq <= epsilon * epsilon)
        {
            return identity();
        }

        g = glm::inverse(g);
        return from_glm(g);
    }

    Quaternion QuaternionOps::multiply(const Quaternion& a, const Quaternion& b)
    {
        glm::quat ga = to_glm(a);
        glm::quat gb = to_glm(b);
        glm::quat gr = ga * gb;
        return from_glm(gr);
    }

    Quaternion QuaternionOps::add(const Quaternion& a, const Quaternion& b)
    {
        return Quaternion(a.w + b.w,
            a.x + b.x,
            a.y + b.y,
            a.z + b.z);
    }

    Quaternion QuaternionOps::sub(const Quaternion& a, const Quaternion& b)
    {
        return Quaternion(a.w - b.w,
            a.x - b.x,
            a.y - b.y,
            a.z - b.z);
    }

    float QuaternionOps::dot(const Quaternion& a, const Quaternion& b)
    {
        return a.w * b.w +
            a.x * b.x +
            a.y * b.y +
            a.z * b.z;
    }

    Quaternion QuaternionOps::slerp(const Quaternion& a, const Quaternion& b, float t, float epsilon)
    {
        if (t <= 0.0f)
        {
            return a;
        }
        if (t >= 1.0f)
        {
            return b;
        }

        glm::quat ga = to_glm(a);
        glm::quat gb = to_glm(b);

        glm::quat g_res = glm::slerp(ga, gb, t);

        float len_sq = glm::dot(g_res, g_res);
        if (len_sq <= epsilon * epsilon)
        {
            g_res = glm::normalize(g_res);
        }

        return from_glm(g_res);
    }

    Vec3 QuaternionOps::rotate_vector(const Quaternion& q, const Vec3& v)
    {
        glm::quat gq = to_glm(q);
        glm::vec3 gv = to_glm(v);
        glm::vec3 gv_rot = glm::rotate(gq, gv);
        return from_glm(gv_rot);
    }

    Quaternion QuaternionOps::angle_axis(float angle_radians, const Vec3& axis)
    {
        return from_axis_angle(axis, angle_radians);
    }

    Vec3 QuaternionOps::rotate(const Quaternion& q, const Vec3& v)
    {
        return rotate_vector(q, v);
    }

    Quaternion QuaternionOps::from_euler_xyz(float x_radians, float y_radians, float z_radians)
    {
        // Build rotation matrix from Euler XYZ, then convert to quaternion.
        glm::mat4 r = glm::eulerAngleXYZ(x_radians, y_radians, z_radians);
        glm::quat q = glm::quat_cast(r);
        return from_glm(q);
    }

    Vec3 QuaternionOps::to_euler_xyz(const Quaternion& q)
    {
        glm::quat gq = to_glm(q);

        // glm::eulerAngles returns a vec3 of Euler angles (in radians).
        // Interpretation corresponds to the chosen extraction convention.
        glm::vec3 e = glm::eulerAngles(gq);
        return from_glm(e);
    }

    Mat4 QuaternionOps::to_mat4(const Quaternion& q)
    {
        glm::quat gq = to_glm(q);
        glm::mat4 gm = glm::toMat4(gq);
        return from_glm(gm);
    }
}