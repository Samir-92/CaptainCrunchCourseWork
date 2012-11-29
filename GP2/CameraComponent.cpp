#include "CameraComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"

CCameraComponent::CCameraComponent()
{
	m_vecLookAt=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_vecUp=D3DXVECTOR3(0.0f,1.0f,0.0f);

	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProjection);

	m_fAspectRatio=640.0f/480.0f;
	m_fFOV=D3DX_PI/4.0f;
	m_fNearClip=1.0f;
	m_fFarClip=1000.0f;
	m_pTarget=NULL;

	m_strName="CameraComponent";
}

CCameraComponent::~CCameraComponent()
{
}

void CCameraComponent::update(float elapsedTime)
{
	CTransformComponent *pTransform=m_pParent->getTransform();
	D3DXVECTOR3 camPos= getParent()->getTransform()->getPosition();
	if(m_pTarget)
	{
		D3DXVECTOR3 objPos= m_pTarget->getTransform()->getPosition();
		D3DXVECTOR3 direction=m_pTarget->getTransform()->getDirection();
		camPos.z=objPos.z-(direction.z*-20.0f);
		camPos.x=objPos.x-(direction.x*-20.0f);
		pTransform->setPosition(camPos.x,camPos.y,camPos.z);
		m_vecLookAt=objPos;
	}
	D3DXMatrixLookAtLH(&m_matView,&camPos,&m_vecLookAt,&m_vecUp);
	D3DXMatrixPerspectiveFovLH(&m_matProjection,m_fAspectRatio,m_fFOV,m_fNearClip,m_fFarClip);


}