#ifndef LENOVO_KEYBOARD_HPP
#define LENOVO_KEYBOARD_HPP

#include <stdexcept>

#include <Windows.h>

namespace Lenovo
{
	class Keyboard
	{
	public:
		static Keyboard & getInstance();

		bool Keyboard::isBacklightOn() const;
		bool Keyboard::isBacklightOff() const;

		void Keyboard::turnOnBacklight() const;
		void Keyboard::turnOffBacklight() const;

		void Keyboard::toggleBacklight() const;

		bool Keyboard::isFnLockOn() const;
		bool Keyboard::isFnLockOff() const;

		void Keyboard::turnOnFnLock() const;
		void Keyboard::turnOffFnLock() const;

		void Keyboard::toggleFnLock() const;

		~Keyboard();
	private:
		Keyboard();
		Keyboard(const Keyboard & copy) {};
		Keyboard & operator=(const Keyboard & copy) {};

		HANDLE m_handle;
	};

	class Error : public std::runtime_error
	{
	public:
		Error(const char *message) : std::runtime_error(message)
		{}
	};

	class UnsupportedKeyboard : public Error
	{
	public:
		UnsupportedKeyboard(const char *message) : Error(message)
		{}
	};

	class OperationFailed : public Error
	{
	public:
		OperationFailed(const char *message) : Error(message)
		{}
	};
}

#endif // LENOVO_KEYBOARD_HPP