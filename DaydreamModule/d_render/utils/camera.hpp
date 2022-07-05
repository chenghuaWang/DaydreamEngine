#ifndef H_CAMERA
#define H_CAMERA

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "d_core/pch.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace daydream {
namespace renderer {

	class D_API_EXPORT camera_obj {
	public:
		camera_obj(float w, float h);

		void set_w(float a);
		void set_h(float a);
		float get_w();
		float get_h();

		float get_aspect();

		bool is_activited();
		void set_activited(bool enable);

	public:
		bool	m_activated = false;
		float	m_w, m_h;
		float	m_aspect;
	};

	class D_API_EXPORT camera2d :public camera_obj {
	public:
		camera2d(float w, float h, const std::string& name);

		void set_idx(float a);
		void reset_name(const std::string &name);

		float get_idx() const;
		const std::string& get_name() const;

	private:
		float		m_idx;
		std::string m_name;
	};

	class D_API_EXPORT camera3d :public camera_obj {
	public:
		camera3d(float w=1920, float h=1080, const std::string& name="default inited");

		int getIdx() const;
		const std::string& getName() const;

		const float& getPitch() const { return m_Pitch; }
		const float& getYaw() const { return m_Yaw; }
		const float& getFov() const { return m_Fov; }
		const float& getAspect() const { return m_aspect; }

		const glm::vec3& getPosition() const { return m_Position; }
		const glm::vec3& getUpVector() const { return m_Up; }
		const glm::vec3& getFrontVector() const { return m_Front; }
		const glm::vec3& getRightVector() const { return m_Right; }

		const glm::mat4& getProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& getViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& getViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

		const float& getNearPlane() const { return m_ZNear; }
		const float& getFarPlane() const { return m_ZFar; }

		void SetPosition(const glm::vec3& position) {
			if (m_Position == position)return;
			m_Position = position; UpdateViewMatrix();
		}

		void SetPitch(const float pitch) {
			if (m_Pitch == pitch)return;
			m_Pitch = pitch; UpdateViewMatrix();
		}

		void SetYaw(const float yaw) {
			if (m_Yaw == yaw)return;
			m_Yaw = yaw; UpdateViewMatrix();
		}

		void SetFov(float fov) {
			if (m_Fov == fov)return;
			m_Fov = fov; UpdateProjectionMatrix();
		}

		void SetAspect(float aspect) {
			if (m_aspect == aspect)return;
			m_aspect = aspect; UpdateProjectionMatrix();
		}

		void SetNearPlane(const float& val) {
			if (m_ZNear == val)return;
			m_ZNear = val;
			UpdateProjectionMatrix();
			UpdateViewMatrix();
		}

		void SetFarPlane(const float& val) {
			if (m_ZFar == val)return;
			m_ZFar = val;
			UpdateProjectionMatrix();
			UpdateViewMatrix();
		}

	private:
		void UpdateViewMatrix();
		void UpdateProjectionMatrix();
		void UpdateViewProjectionMatrix() { m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix; }

	private:
		int									m_idx;
		std::string							m_name;

		float								m_ZNear;
		float								m_ZFar;
		float								m_Fov;
		float								m_Pitch = -30.0f;
		float								m_Yaw = -60.0f;
		glm::vec3							m_Position = { -17.0f, 23.0f, 32.0f };
		glm::vec3							m_Front = { 0.0f, 0.0f, -1.0f };
		glm::vec3							m_Up = { 0.0f, 1.0f, 0.0f };
		glm::vec3							m_Right = { 1.0f, 0.0f, 0.0f };
		glm::mat4							m_ViewMatrix;
		glm::mat4							m_ProjectionMatrix;
		glm::mat4							m_ViewProjectionMatrix;
	};

	class D_API_EXPORT camera3dDispatcher {
	public:
		void addCamera3d(camera3d &rhs);
		camera3d& getCamera3d(int a);
		void deleteCamera3d(int a);

	private:
		REF(camera3d)						m_cur_activated_cam = nullptr;
		std::unordered_map<int, camera3d>	m_data;
	};

}
}

#endif // !H_CAMERA
