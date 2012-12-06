#pragma once

#include "IComponent.h"
#include <D3D10.h>
#include <D3DX10.h>

class CCameraComponent:public CBaseComponent
{
public:
	CCameraComponent();
	~CCameraComponent();

	void update(float elapsedTime);

	D3DXMATRIX& getView()
	{
		return m_matView;
	};

	D3DXMATRIX& getProjection()
	{
		return m_matProjection;
	};

	void setLookAt(float x,float y,float z)
	{
		m_vecLookAt=D3DXVECTOR3(x,y,z);
	};

	void setUp(float x,float y,float z)
	{
		m_vecUp=D3DXVECTOR3(x,y,z);
	};

	void setFOV(float fov)
	{
		m_fFOV=fov;
	};

	void setAspectRatio(float aspectRatio)
	{
		m_fAspectRatio=aspectRatio;
	};

	void setNearClip(float nearClip)
	{
		m_fNearClip=nearClip;
	};

	void setFarClip(float farClip)
	{
		m_fFarClip=farClip;
	};

	void setTarget(CGameObject* target)
	{
		m_pTarget = target;
	};
	
	void setPosition(float x, float y, float z)
	{
		m_position = D3DXVECTOR3(x,y,z);
	};

	D3DXVECTOR3& getPosition()
	{
		return m_position;
	};

	bool isDebug()
	{
		return m_debug;
	};

	void setDebug(bool debug)
	{
		m_debug = debug;
	};
private:
	D3DXMATRIX m_matView;
	D3DXMATRIX m_matProjection;

	bool m_debug;

	D3DXVECTOR3 m_vecUp;
	D3DXVECTOR3 m_vecLookAt;

	D3DXVECTOR3 m_position;

	float m_fAspectRatio;
	float m_fFOV;
	float m_fNearClip;
	float m_fFarClip;

	CGameObject* m_pTarget;
};