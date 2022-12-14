#include "InputSystem.h"
#include <Windows.h>

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::update()
{
	POINT current_mouse_pos = {};
	::GetCursorPos(&current_mouse_pos);

	if (m_first_time)
	{
		m_first_time = false;
		m_old_mouse_pos = Vector2(current_mouse_pos.x, current_mouse_pos.y);
	}

	if (current_mouse_pos.x != m_old_mouse_pos.x || current_mouse_pos.y != m_old_mouse_pos.y)
	{
		std::unordered_set<InputListener*, InputListener*>::iterator it = m_set_listeners.begin();

		while (it != m_set_listeners.end())
		{
			(*it)->onMouseMove(Vector2(current_mouse_pos.x - m_old_mouse_pos.x, current_mouse_pos.y - m_old_mouse_pos.y));
			++it;
		}
	}

	m_old_mouse_pos = Vector2(current_mouse_pos.x, current_mouse_pos.y);

	if (::GetKeyboardState(m_keys_state))
	{
		for (unsigned int i = 0; i < 256; i++)
		{
			if (m_keys_state[i] & 0x80) //first frame key pressed
			{
				if (m_keys_state[i] != m_old_keys_state[i])
				{
					std::unordered_set<InputListener*, InputListener*>::iterator it = m_set_listeners.begin();

					while (it != m_set_listeners.end())
					{
						if (i == VK_LBUTTON)
						{
							(*it)->onLeftMouseDown(Vector2(current_mouse_pos.x, current_mouse_pos.y));
						}
						else if (i == VK_RBUTTON)
						{
							(*it)->onRightMouseDown(Vector2(current_mouse_pos.x, current_mouse_pos.y));
						}

						(*it)->onKeyDown(i);
						++it;
					}
				}
			}
			else if (m_keys_state[i] != m_old_keys_state[i]) //first frame key not pressed
			{
				std::unordered_set<InputListener*, InputListener*>::iterator it = m_set_listeners.begin();

				while (it != m_set_listeners.end())
				{
					if (i == VK_LBUTTON)
						(*it)->onLeftMouseUp(Vector2(current_mouse_pos.x, current_mouse_pos.y));
					else if (i == VK_RBUTTON)
						(*it)->onRightMouseUp(Vector2(current_mouse_pos.x, current_mouse_pos.y));
					else
						(*it)->onKeyUp(i);
					++it;
				}
			}
			else //while key is pressed (ignore first)
			{
				std::unordered_set<InputListener*, InputListener*>::iterator it = m_set_listeners.begin();

				while (it != m_set_listeners.end())
				{
					if (i == VK_LBUTTON)
						(*it)->whileLeftMouseDown(Vector2(current_mouse_pos.x, current_mouse_pos.y));
					if (i == VK_RBUTTON)
						(*it)->whileRightMouseDown(Vector2(current_mouse_pos.x, current_mouse_pos.y));

					(*it)->whileKeyDown(i);
					++it;
				}
			}
		}
		::memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
	}
}

void InputSystem::addListener(InputListener* listener)
{
	m_set_listeners.insert(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
	m_set_listeners.erase(listener);
}

InputSystem* InputSystem::get()
{
	static InputSystem system;
	return &system;
}
