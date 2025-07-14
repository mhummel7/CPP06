/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:26:14 by mhummel           #+#    #+#             */
/*   Updated: 2025/07/14 10:54:47 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

Base * generate(void) {
	int choice = rand() % 3;
	switch (choice) {
		case 0: return new A;
		case 1: return new B;
		default: return new C;
	}
}

void identify(Base* p) {
	if (dynamic_cast<A*>(p)) {
		std::cout << "A";
	} else if (dynamic_cast<B*>(p)) {
		std::cout << "B";
	} else if (dynamic_cast<C*>(p)) {
		std::cout << "C";
	}
}

void identify(Base& p) {
	try {
		(void)dynamic_cast<A&>(p);
		std::cout << "A";
		return;
	} catch (const std::bad_cast&) {}
	try {
		(void)dynamic_cast<B&>(p);
		std::cout << "B";
		return;
	} catch (const std::bad_cast&) {}
	try {
		(void)dynamic_cast<C&>(p);
		std::cout << "C";
		return;
	} catch (const std::bad_cast&) {}
}

int main() {
	srand(static_cast<unsigned int>(time(NULL)));

	std::cout << "Running 10 tests for type identification:" << std::endl;
	for (int i = 0; i < 10; ++i) {
		int choice = rand() % 3;
		Base* obj = nullptr;
		std::string generatedType;
		switch (choice) {
			case 0: obj = new A; generatedType = "A"; break;
			case 1: obj = new B; generatedType = "B"; break;
			default: obj = new C; generatedType = "C"; break;
		}
		std::cout << "Test " << i + 1 << ": Generated " << generatedType << " | ";
		identify(obj);
		std::cout << " (pointer) | ";
		identify(*obj);
		std::cout << " (reference)" << std::endl;
		delete obj;
	}

	return 0;
}
