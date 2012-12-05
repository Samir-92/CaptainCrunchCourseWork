#pragma once

#include "IComponent.h"

#include <D3D10.h>
#include <D3DX10.h>

//Transform component, this represents a transformation
//Scale, Rotation, Rotation combine to World Matrix
class CTransformComponent:public CBaseComponent
{
public:
	//Constructor
	CTransformComponent()
	{
		//Set to default values
		m_vecPosition=D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_vecRotation=D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_vecScale=D3DXVECTOR3(1.0f,1.0f,1.0f);
		D3DXMatrixIdentity(&m_matTranslate);
		D3DXMatrixIdentity(&m_matRotation);
		D3DXMatrixIdentity(&m_matScale);
		D3DXMatrixIdentity(&m_matWorld);
		D3DXQuaternionIdentity(&m_quatRotation);
		m_direction=D3DXVECTOR3(1.0f,0.0f,1.0f);
		m_strName="TransformComponent";
	};
	
	~CTransformComponent(){};

	//Update method
	void update(float elapsedTime)
	{
		//We are using Quaternion for rotation, no gimble lock
		D3DXQuaternionRotationYawPitchRoll(&m_quatRotation,m_vecRotation.y,m_vecRotation.x,m_vecRotation.z);
		//Build a rotation matrix, we can't use quaternions directly
		D3DXMatrixRotationQuaternion(&m_matRotation,&m_quatRotation);

		//Create translation matrix
		D3DXMatrixTranslation(&m_matTranslate,m_vecPosition.x,m_vecPosition.y,m_vecPosition.z);
		//Create scale matrix
		D3DXMatrixScaling(&m_matScale,m_vecScale.x,m_vecScale.y,m_vecScale.z);

		//Multiply the matrices together
		D3DXMatrixMultiply(&m_matWorld,&m_matScale,&m_matRotation);
		D3DXMatrixMultiply(&m_matWorld,&m_matWorld,&m_matTranslate);
		
	};

	//set position
	void setPosition(float x,float y,float z)
	{
		m_vecPosition=D3DXVECTOR3(x,y,z);
	};

	//set rotation
	void setRotation(float x,float y,float z)
	{
		m_vecRotation=D3DXVECTOR3(x,y,z);
		
	};

	//set scale
	void setScale(float x,float y,float z)
	{
		m_vecScale=D3DXVECTOR3(x,y,z);
	};

	D3DXVECTOR3& getPosition()
	{
		return m_vecPosition;
	};

	D3DXVECTOR3& getDirection()
	{
		return m_direction;
	};

	bool getIsMoving()
	{
		return m_isMoving;
	}

	void setIsMoving(bool isMoving)
	{
		m_isMoving = isMoving;
	}

	int getMovementDirection()
	{
		//1/true for right
		//0/false for left
		return m_moveDirRight;
	}

	void setMovementDirection(bool moveDir)
	{
		//1/true for right
		//0/false for left
		m_moveDirRight = moveDir;
	}

	//get world
	D3DXMATRIX& getWorld()
	{
		return m_matWorld;
	};

	//rotate
	void rotate(float x,float y,float z)
	{
		if((m_vecRotation.y < 90)){
			m_vecRotation.x+=x;
			m_vecRotation.y+=y;
			m_vecRotation.z+=z;
		}
	};

	//translate
	void translate(float x,float y,float z)
	{
		m_vecPosition.x+=x;
		m_vecPosition.y+=y;
		m_vecPosition.z+=z;
	};

	//scale
	void scale(float x,float y, float z)
	{
		m_vecScale.x+=x;
		m_vecScale.y+=y;
		m_vecScale.z+=z;
	};

	void MoveForward(float speed)
	{
		//Don't move the car if we are going to go off the screen.
		if((m_vecPosition.x >= -5) && (m_vecPosition.x <= 5)){
			
			//Calculate direction from rotation, replace the following line
			m_direction=D3DXVECTOR3(1.0f,0.0f,1.0f);
			//Normalize
			D3DXVec3Normalize(&m_direction,&m_direction);
			//m_direction*=speed;

			m_vecPosition.x+=(m_direction.x*sin(m_vecRotation.y));
			m_vecPosition.z+=(m_direction.z*cos(m_vecRotation.y));
			m_direction.x=m_direction.x*sin(m_vecRotation.y);
			m_direction.z=m_direction.z*cos(m_vecRotation.y);


		}
	};
	void enemyMovement(float speed)
	{
		//Don't move the zombie if zombie going off platform
		//need to add
		
		////calculate direction from rotation
		//m_direction=D3DXVECTOR3(1.0f,0.0f,1.0f);
		////Normalize
		//D3DXVec3Normalize(&m_direction, &m_direction);

	 //   m_vecPosition.x+=(m_direction.x*sin(m_vecRotation.y));
		//m_vecPosition.z+=(m_direction.z*cos(m_vecRotation.y));
		//m_direction.x=m_direction.x*sin(m_vecRotation.y);
		//m_direction.z=m_direction.z*cos(m_vecRotation.y);

		//Move the zombie between a distance back and forward between distance
		if(m_moveDirRight){
			m_vecPosition.z += 0.001;
			if(m_vecPosition.z >= 40.0){
				m_vecRotation.y = 3;
				m_moveDirRight = false;
			}
		}else{
			m_vecPosition.z -= 0.001;
			if(m_vecPosition.z <= -4.5){
				m_vecRotation.y = 0;
				m_moveDirRight = true;
			}
		}

	};
	void enemyMovementLR(float speed)
	{
		//Don't move the zombie if zombie going off platform
		//need to add
		
		////calculate direction from rotation
		//m_direction=D3DXVECTOR3(1.0f,0.0f,1.0f);
		////Normalize
		//D3DXVec3Normalize(&m_direction, &m_direction);

	 //   m_vecPosition.x+=(m_direction.x*sin(m_vecRotation.y));
		//m_vecPosition.z+=(m_direction.z*cos(m_vecRotation.y));
		//m_direction.x=m_direction.x*sin(m_vecRotation.y);
		//m_direction.z=m_direction.z*cos(m_vecRotation.y);

		//Move the zombie between a distance back and forward between distance
		if(m_moveDirRight){
			m_vecPosition.x += 0.001;
			if(m_vecPosition.x >= 9.3){
				m_vecRotation.y = 1.5; 
				m_moveDirRight = false;
			}
		}else{
			m_vecPosition.x -= 0.001;
			if(m_vecPosition.x <= -9.3){
				m_vecRotation.y = -1.5;
				m_moveDirRight = true;
			}
		}

	};

private:
	//vectors
	D3DXVECTOR3 m_vecPosition;
	D3DXVECTOR3 m_vecRotation;
	D3DXVECTOR3 m_vecScale;
	D3DXVECTOR3 m_direction;

	bool m_isMoving;
	bool m_moveDirRight;

	//matrices
	D3DXMATRIX m_matTranslate;
	D3DXMATRIX m_matRotation;
	D3DXMATRIX m_matScale;

	//quaternion
	D3DXQUATERNION m_quatRotation;

	D3DXMATRIX m_matWorld;
};