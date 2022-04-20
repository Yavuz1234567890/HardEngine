#ifndef EVENTS_H_
#define EVENTS_H_

#include "Core/Containers/String.h"

struct Event
{
	enum
	{
		KEYDOWN,
		KEYUP,
		MOUSEDOWN,
		MOUSEUP,
		MOUSEMOVE,
		MOUSESCROLL,
		WINDOWSIZE,
		WINDOWMOVE,
		WINDOWCLOSE
	};

	Event(const int type)
		: Type(type)
	{

	}

	template<typename T>
	static T& GetEvent(const Event& src)
	{
		return *((T*)&src);
	}

	int Type;
};

struct KeyDownEvent : public Event
{
	KeyDownEvent(const int key)
		: Event(Event::KEYDOWN),
		Key(key)
	{

	}

	static int GetType() { return Event::KEYDOWN; }

	int Key;
};

struct KeyUpEvent : public Event
{
	KeyUpEvent(const int key)
		: Event(Event::KEYUP),
		Key(key)
	{

	}

	static int GetType() { return Event::KEYUP; }

	int Key;
};

struct MouseDownEvent : public Event
{
	MouseDownEvent(const int button)
		: Event(Event::MOUSEDOWN),
		Button(button)
	{

	}

	static int GetType() { return Event::MOUSEDOWN; }

	int Button;
};

struct MouseUpEvent : public Event
{
	MouseUpEvent(const int button)
		: Event(Event::MOUSEUP),
		Button(button)
	{

	}

	static int GetType() { return Event::MOUSEUP; }

	int Button;
};

struct MouseMoveEvent : public Event
{
	MouseMoveEvent(const float x, const float y)
		: Event(Event::MOUSEMOVE),
		X(x),
		Y(y)
	{

	}

	static int GetType() { return Event::MOUSEMOVE; }

	float X, Y;
};

struct MouseScrollEvent : public Event
{
	MouseScrollEvent(const float delta)
		: Event(Event::MOUSESCROLL),
		Delta(delta)
	{

	}

	static int GetType() { return Event::MOUSESCROLL; }

	float Delta;
};

struct WindowSizeEvent : public Event
{
	WindowSizeEvent(const int width, const int height)
		: Event(Event::WINDOWSIZE),
		Width(width),
		Height(height)
	{

	}

	static int GetType() { return Event::WINDOWSIZE; }

	int Width, Height;
};

struct WindowMoveEvent : public Event
{
	WindowMoveEvent(const int x, const int y)
		: Event(Event::WINDOWMOVE),
		X(x),
		Y(y)
	{

	}

	static int GetType() { return Event::WINDOWMOVE; }

	int X, Y;
};

struct WindowCloseEvent : public Event
{
	WindowCloseEvent()
		: Event(Event::WINDOWCLOSE)
	{

	}

	static int GetType() { return Event::WINDOWCLOSE; }
};

#define HA_DISPATCH_EVENT(e, type, function)	\
	if(e.Type == type::GetType())				\
	{											\
		function(Event::GetEvent<type>(e));		\
	}

#endif
