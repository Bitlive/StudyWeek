#pragma once
#include "MoveObject.h"

class GEnemy :public CMoveObject 
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of object</param>
	GEnemy(SVector2 _pos) : CMoveObject(_pos) {}

	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of object</param>
	/// <param name="_size">width and height of rect</param>
	GEnemy(SVector2 _pos, SVector2 _size) : CMoveObject(_pos, _size) {}

	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of object</param>
	/// <param name="_size">width and height of rect</param>
	/// <param name="_pRenderer">renderer</param>
	/// <param name="_pFileName">file path name (relative)</param>
	GEnemy(SVector2 _pos, SVector2 _size, CRenderer* _pRenderer,
		const char* _pFileName) : CMoveObject(_pos, _size, _pRenderer, _pFileName) {}

	/// <summary>
	/// destructor
	/// </summary>
	~GEnemy() {}
#pragma endregion

#pragma region public override function
	/// <summary>
	/// update every frame
	/// </summary>
	/// <param name="_deltaTime">time since last frame</param>
	void Update(float _deltaTime) override;
#pragma endregion
};