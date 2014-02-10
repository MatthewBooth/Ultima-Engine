#pragma once

#include <d3dx9.h>

/*	A first person camera implementation
	See acompanying notes
	Keith Ditchburn May 2007
*/
class cCamera
{
private:
	D3DXVECTOR3 m_position; // camera position
	float m_yaw;  // rotation around the y axis
	float m_pitch; // rotation around the x axis
	float m_roll; // rotation around the z axis
	D3DXVECTOR3 m_up,m_look,m_right; // camera axis

	float RestrictAngleTo360Range(float angle) const;
public:
	cCamera(D3DXVECTOR3 startPos);
	~cCamera(void);

	void CalculateViewMatrix(D3DXMATRIX *viewMatrix);

	// Gets
	float GetYaw() const {return m_yaw;}
	float GetPitch() const {return m_pitch;}
	float GetRoll() const {return m_roll;}
	D3DXVECTOR3 GetPosition() const {return m_position;}	

	//Xu
	void SetPosition(float x, float y, float z);

	// Move operations
	void MoveForward(float amount);
	void MoveRight(float amount);
	void MoveUp(float amount);

	// Rotations
	void Yaw(float amount); // rotate around x axis
	void Pitch(float amount); // rotate around x axis
	void Roll(float amount); // rotate around z axis	
};
