#include "CameraComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"

CCameraComponent::CCameraComponent()
{
	m_vecLookAt=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_vecUp=D3DXVECTOR3(0.0f,1.0f,0.0f);
	m_position=D3DXVECTOR3(0.0f,2.0f,-5.0f);

	m_debug=false;

	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProjection);

	m_fAspectRatio=640.0f/480.0f;
	m_fFOV=D3DX_PI/4.0f;
	m_fNearClip=1.0f;
	m_fFarClip=1000.0f;

	m_strName="CameraComponent";
}

CCameraComponent::~CCameraComponent()
{
}

void CCameraComponent::update(float elapsedTime)
{
	CTransformComponent *pTransform=m_pParent->getTransform();

	D3DXVECTOR3 camPos = getParent()->getTransform()->getPosition();
    D3DXVECTOR3 objPos = m_pTarget->getTransform()->getPosition();
	//Rotation of the car
	D3DXVECTOR3 objRot = m_pTarget->getTransform()->getRotation();
	
	if(m_pTarget){

		//New position of camera
		D3DXVECTOR3 updateCamPos = D3DXVECTOR3(objPos.x,camPos.y,objPos.z - 10.0f);

			D3DXVECTOR3 direction = D3DXVECTOR3(1.0f,0.0f,1.0f);
			//Normalize
			D3DXVec3Normalize(&direction,&direction);
			direction*=30;

		//Uncomment these lines for an attempt at camera facing direction of car
		//updateCamPos.x -= (direction.x*sin(objRot.y)); 
		//updateCamPos.z -= (direction.z*cos(objRot.y));

		//Set position of camera
		getParent()->getTransform()->setPosition(updateCamPos.x,updateCamPos.y,updateCamPos.z);

		//Where the camera looks
		m_vecLookAt = objPos;
	}

	D3DXMatrixLookAtLH(&m_matView,&pTransform->getPosition(),&m_vecLookAt,&m_vecUp);
	D3DXMatrixPerspectiveFovLH(&m_matProjection,m_fAspectRatio,m_fFOV,m_fNearClip,m_fFarClip);
}