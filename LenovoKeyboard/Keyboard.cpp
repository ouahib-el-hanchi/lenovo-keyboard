#include "Keyboard.hpp"

namespace Lenovo
{
	static const char *deviceName = "\\\\.\\EnergyDrv";
	static const unsigned int ioControlCode = 2198872296U;

	enum Operation
	{
		GET_KEYBOARD_STATE = 2u,

		TURN_ON_BACKLIGHT = 8u,
		TURN_OFF_BACKLIGHT = 9u,

		TURN_ON_FNLOCK = 14u,
		TURN_OFF_FNLOCK = 15u,
	};

	static unsigned int ioDeviceControl(HANDLE handle, Operation operation);

	static bool isBitSet(unsigned int bits, unsigned int index);

	Keyboard::Keyboard()
	{
		m_handle = ::CreateFile(
			deviceName,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		if (m_handle == INVALID_HANDLE_VALUE) {
			throw UnsupportedKeyboard("Unsupported keyboard");
		}
	}

	Keyboard & Keyboard::getInstance()
	{
		static Keyboard instance;

		return instance;
	}

	bool Keyboard::isBacklightOn() const
	{
		unsigned int result = ioDeviceControl(m_handle, GET_KEYBOARD_STATE);

		return isBitSet(result, 5);
	}

	bool Keyboard::isBacklightOff() const
	{
		return !isBacklightOn();
	}

	void Keyboard::turnOnBacklight() const
	{
		ioDeviceControl(m_handle, TURN_ON_BACKLIGHT);
	}

	void Keyboard::turnOffBacklight() const
	{
		ioDeviceControl(m_handle, TURN_OFF_BACKLIGHT);
	}

	void Keyboard::toggleBacklight() const
	{
		isBacklightOn() ? turnOffBacklight() : turnOnBacklight();
	}

	bool Keyboard::isFnLockOn() const
	{
		unsigned int result = ioDeviceControl(m_handle, GET_KEYBOARD_STATE);

		return isBitSet(result, 10);
	}

	bool Keyboard::isFnLockOff() const
	{
		return !isFnLockOn();
	}

	void Keyboard::turnOnFnLock() const
	{
		ioDeviceControl(m_handle, TURN_ON_FNLOCK);
	}

	void Keyboard::turnOffFnLock() const
	{
		ioDeviceControl(m_handle, TURN_OFF_FNLOCK);
	}

	void Keyboard::toggleFnLock() const
	{
		isFnLockOn() ? turnOffFnLock() : turnOnFnLock();
	}

	Keyboard::~Keyboard()
	{
		if (m_handle != INVALID_HANDLE_VALUE) {
			::CloseHandle(m_handle);
			m_handle = INVALID_HANDLE_VALUE;
		}
	}

	unsigned int ioDeviceControl(HANDLE handle, Operation operation)
	{
		unsigned int output;

		if (!::DeviceIoControl(
			handle,
			ioControlCode,
			&operation,
			sizeof(operation),
			&output,
			sizeof(output),
			NULL,
			NULL
		)) {
			throw OperationFailed("Failed to preform operation!");
		}

		return output;
	}

	bool isBitSet(unsigned int bits, unsigned int index)
	{
		return (bits & (1u << index)) == (1u << index);
	}
}

