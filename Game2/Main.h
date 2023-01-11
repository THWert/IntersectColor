#pragma once
class Main : public Scene
{
private:
	ObRect*		rc;
	ObCircle*	cc;

	Vector2		lastPos;

public:
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
