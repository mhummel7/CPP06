/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:46:50 by mhummel           #+#    #+#             */
/*   Updated: 2025/07/14 10:06:22 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// main.cpp
// #include "Serializer.hpp"
// #include <iostream>

// int main() {
// 	Data data;
// 	data.value = 42;
// 	Data* ptr = &data;
// 	uintptr_t raw = Serializer::serialize(ptr);
// 	Data* new_ptr = Serializer::deserialize(raw);

// 	std::cout << "Original pointer: " << ptr << std::endl;
// 	std::cout << "Deserialized pointer: " << new_ptr << std::endl;
// 	std::cout << "Original value: " << ptr->value << std::endl;
// 	std::cout << "Deserialized value: " << new_ptr->value << std::endl;

// 	if (ptr == new_ptr) {
// 		std::cout << "Pointers are equal!" << std::endl;
// 	} else {
// 		std::cout << "Pointers are not equal!" << std::endl;
// 	}

// 	return 0;
// }

#include "Serializer.hpp"
#include <iostream>

void testSerialization(Data* original, int expectedValue) {
	uintptr_t raw = Serializer::serialize(original);
	Data* deserialized = Serializer::deserialize(raw);

	std::cout << "Original pointer: " << original << std::endl;
	std::cout << "Deserialized pointer: " << deserialized << std::endl;
	std::cout << "Original value: " << original->value << std::endl;
	std::cout << "Deserialized value: " << deserialized->value << std::endl;

	if (original == deserialized && deserialized->value == expectedValue) {
		std::cout << "Test passed: Pointers equal and values match!" << std::endl;
	} else {
		std::cout << "Test failed: Pointers or values do not match!" << std::endl;
	}
	std::cout << "------------------------" << std::endl;
}

int main() {
	// Test 1: Einfacher positiver Wert
	Data data1;
	data1.value = 42;
	testSerialization(&data1, 42);

	// Test 2: Negativer Wert
	Data data2;
	data2.value = -100;
	testSerialization(&data2, -100);

	// Test 3: Null-Wert
	Data data3;
	data3.value = 0;
	testSerialization(&data3, 0);

	// Test 4: Großer Wert (nahe INT_MAX)
	Data data4;
	data4.value = 2147483647;  // INT_MAX
	testSerialization(&data4, 2147483647);

    return 0;
}