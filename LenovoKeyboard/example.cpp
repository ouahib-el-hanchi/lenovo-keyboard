#include <iostream>

#include "Keyboard.hpp"

int main()
{
	try {
		auto & keyboard = Lenovo::Keyboard::getInstance();

		std::cout << std::boolalpha;
		
		std::cout << "[-] Backlight is turned on: " << keyboard.isFnLockOn() << std::endl;
		keyboard.toggleBacklight();
		std::cout << "[-] Backlight is turned off: " << keyboard.isFnLockOff() << std::endl;

		std::cout << "[-] Function keys lock is turned on: " << keyboard.isFnLockOn() << std::endl;
		keyboard.toggleFnLock();
		std::cout << "[-] Function keys lock is turned off: " << keyboard.isFnLockOff() << std::endl;
	}
	catch (const Lenovo::UnsupportedKeyboard & error) {
		std::cerr << "*** " << error.what() << std::endl;
	}
	catch (const Lenovo::Error & error) {
		std::cerr << "*** " << error.what() << std::endl;
	}

	(void) std::getchar();

	return 0;
}