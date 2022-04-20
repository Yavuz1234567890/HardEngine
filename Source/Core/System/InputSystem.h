#ifndef INPUT_SYSTEM_H_
#define INPUT_SYSTEM_H_

#define HA_MAX_KEYS 348

class Keyboard
{
public:
	static void Reset();
	static void OnKeyDown(const int key);
	static void OnKeyUp(const int key);
	static bool IsKey(const int key);
	static bool IsKeyDown(const int key);
	static bool IsKeyUp(const int key);
	static bool IsAnyKey();
	static bool IsAnyKeyDown();
	static bool IsAnyKeyUp();
private:
	static bool s_KeysDown[HA_MAX_KEYS], s_AnyKeyDown;
	static bool s_KeysUp[HA_MAX_KEYS], s_AnyKeyUp;
	static bool s_Keys[HA_MAX_KEYS], s_AnyKey;
};

#define HA_MAX_BUTTONS 4

class Mouse
{
public:
	static void Reset();
	static void OnMouseDown(const int button);
	static void OnMouseUp(const int button);
	static void OnMouseMove(const float x, const float y);
	static void OnMouseScroll(const float delta);
	static bool IsButton(const int button);
	static bool IsButtonDown(const int button);
	static bool IsButtonUp(const int button);
	static bool IsAnyButton();
	static bool IsAnyButtonDown();
	static bool IsAnyButtonUp();
	static float GetMouseX();
	static float GetMouseY();
	static float GetMouseDelta();
private:
	static bool s_ButtonsDown[HA_MAX_BUTTONS], s_AnyButtonDown;
	static bool s_ButtonsUp[HA_MAX_BUTTONS], s_AnyButtonUp;
	static bool s_Buttons[HA_MAX_BUTTONS], s_AnyButton;
	static float s_MouseX, s_MouseY;
	static float s_MouseDelta;
};

#define HA_MAX_CONTROLLER_BUTTONS 14

class Controller
{
public:
	struct Axis
	{
		float X, Y;
	};

	Controller();

	void SetButton(const int button, bool value);
	void SetLeftTrigger(const float value);
	void SetRightTrigger(const float value);
	void SetRightAxis(const Axis& axis);
	void SetLeftAxis(const Axis& axis);
	void SetConnected(bool value);
	bool IsButton(const int button) const;
	float GetLeftTrigger() const;
	float GetRightTrigger() const;
	Axis GetLeftAxis() const;
	Axis GetRightAxis() const;
	bool IsConnected() const;
private:
	bool m_Buttons[HA_MAX_CONTROLLER_BUTTONS];
	float m_LeftTrigger, m_RightTrigger;
	Axis m_LeftAxis, m_RightAxis;
	bool m_Connected;
};

#endif
