/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:25:01 by mhummel           #+#    #+#             */
/*   Updated: 2025/06/25 10:34:34 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <limits>
#include <iomanip>
#include <cerrno>
#include <cstring>
#include <cmath>

void ScalarConverter::convert(const std::string& input) {
	// Helper function to check if string is a pseudo-literal
	auto isPseudoLiteral = [](const std::string& str) -> bool {
		return str == "nan" || str == "+inf" || str == "-inf" ||
		       str == "nanf" || str == "+inff" || str == "-inff";
	};

	// Helper function to check if string is a float literal (ends with 'f')
	auto isFloatLiteral = [&isPseudoLiteral](const std::string& str) -> bool {
		if (str.length() <= 1 || str[str.length() - 1] != 'f') return false;
		if (isPseudoLiteral(str.substr(0, str.length() - 1))) return true;
		// Check for valid float format (e.g., 123.456f, -123.456f)
		size_t dotCount = 0, start = (str[0] == '-' || str[0] == '+') ? 1 : 0;
		for (size_t i = start; i < str.length() - 1; ++i) {
			if (str[i] == '.') dotCount++;
			else if (!std::isdigit(str[i])) return false;
		}
		return dotCount == 1;
	};

	// Helper function to check if string is a double literal
	auto isDoubleLiteral = [&isPseudoLiteral](const std::string& str) -> bool {
		if (isPseudoLiteral(str)) return true;
		// Check for valid double format (e.g., 123.456, -123.456)
		size_t dotCount = 0, start = (str[0] == '-' || str[0] == '+') ? 1 : 0;
		for (size_t i = start; i < str.length(); ++i) {
			if (str[i] == '.') dotCount++;
			else if (!std::isdigit(str[i])) return false;
		}
		return dotCount == 1;
	};

	// Helper function to count significant digits (excluding leading sign)
	auto countSignificantDigits = [](const std::string& str) -> size_t {
		size_t start = (str[0] == '-' || str[0] == '+') ? 1 : 0;
		size_t digits = 0;
		for (size_t i = start; i < str.length(); ++i) {
			if (std::isdigit(str[i])) digits++;
		}
		return digits;
	};

	// Helper function to check if string is a valid integer
	auto isIntLiteral = [](const std::string& str) -> bool {
		if (str.empty()) return false;
		size_t start = (str[0] == '-' || str[0] == '+') ? 1 : 0;
		for (size_t i = start; i < str.length(); ++i)
			if (!std::isdigit(str[i]))
				return false;
		return true; // No digit limit here, handled in conversion
	};

	// Initialize variables
	char charValue = 0;
	int intValue = 0;
	float floatValue = 0.0f;
	double doubleValue = 0.0;
	bool isChar = false, isInt = false, isFloat = false, isDouble = false;
	bool floatFailed = false, doubleFailed = false;

	// Step 1: Detect type
	if (input.length() == 1 && std::isprint(input[0]) && !std::isdigit(input[0])) {
		isChar = true;
		charValue = input[0];
	} else if (isPseudoLiteral(input)) {
		if (input == "nan" || input == "+inf" || input == "-inf") {
			isDouble = true;
			if (input == "nan") doubleValue = std::numeric_limits<double>::quiet_NaN();
			else if (input == "+inf") doubleValue = std::numeric_limits<double>::infinity();
			else doubleValue = -std::numeric_limits<double>::infinity();
		} else {
			isFloat = true;
			if (input == "nanf") floatValue = std::numeric_limits<float>::quiet_NaN();
			else if (input == "+inff") floatValue = std::numeric_limits<float>::infinity();
			else floatValue = -std::numeric_limits<float>::infinity();
		}
	} else if (isFloatLiteral(input)) {
		isFloat = true;
		char* endptr;
		errno = 0;
		doubleValue = std::strtod(input.c_str(), &endptr);
		if (errno == ERANGE || *endptr != 'f' || endptr == input.c_str()) {
			floatFailed = true;
			doubleFailed = true;
		} else {
			floatValue = static_cast<float>(doubleValue);
		}
	} else if (isDoubleLiteral(input)) {
		isDouble = true;
		char* endptr;
		errno = 0;
		doubleValue = std::strtod(input.c_str(), &endptr);
		if (errno == ERANGE || *endptr != '\0' || endptr == input.c_str()) {
			doubleFailed = true;
		}
	} else if (isIntLiteral(input)) {
		char* endptr;
		errno = 0;
		doubleValue = std::strtod(input.c_str(), &endptr);
		size_t digits = countSignificantDigits(input);
		if (errno == ERANGE || *endptr != '\0' || endptr == input.c_str()) {
			floatFailed = true;
			doubleFailed = true;
		} else if (digits > 7) {
			floatFailed = true; // Too many digits for float precision
			if (digits > 15) {
				doubleFailed = true; // Too many digits for double precision
			}
		} else if (doubleValue >= std::numeric_limits<int>::min() &&
		           doubleValue <= std::numeric_limits<int>::max() &&
		           doubleValue == static_cast<long>(doubleValue)) {
			isInt = true;
			intValue = static_cast<int>(doubleValue);
		} else {
			isDouble = true;
		}
	} else {
		floatFailed = true;
		doubleFailed = true;
	}

	// Step 2: Convert to other types
	if (isChar) {
		intValue = static_cast<int>(charValue);
		floatValue = static_cast<float>(charValue);
		doubleValue = static_cast<double>(charValue);
	} else if (isInt && !floatFailed) {
		charValue = static_cast<char>(intValue);
		floatValue = static_cast<float>(intValue);
		doubleValue = static_cast<double>(intValue);
	} else if (isFloat && !floatFailed) {
		charValue = static_cast<char>(floatValue);
		intValue = static_cast<int>(floatValue);
		doubleValue = static_cast<double>(floatValue);
	} else if (isDouble && !doubleFailed) {
		charValue = static_cast<char>(doubleValue);
		intValue = static_cast<int>(doubleValue);
		floatValue = static_cast<float>(doubleValue);
	}

	// Step 3: Output results
	// Char
	if (floatFailed || isnan(floatValue) || isinf(floatValue) ||
	    doubleValue < std::numeric_limits<char>::min() || doubleValue > std::numeric_limits<char>::max()) {
		std::cout << "char: impossible" << std::endl;
	} else if (!std::isprint(charValue)) {
		std::cout << "char: Non displayable" << std::endl;
	} else {
		std::cout << "char: '" << charValue << "'" << std::endl;
	}

	// Int
	if (floatFailed || isnan(floatValue) || isinf(floatValue) ||
	    doubleValue < std::numeric_limits<int>::min() || doubleValue > std::numeric_limits<int>::max()) {
		std::cout << "int: impossible" << std::endl;
	} else {
		std::cout << "int: " << intValue << std::endl;
	}

	// Float
	if (floatFailed) {
		std::cout << "float: impossible" << std::endl;
	} else if (isnan(floatValue)) {
		std::cout << "float: nanf" << std::endl;
	} else if (isinf(floatValue)) {
		std::cout << "float: " << (floatValue > 0 ? "+inff" : "-inff") << std::endl;
	} else {
		if (doubleValue == static_cast<long>(doubleValue) &&
		    doubleValue >= -std::numeric_limits<float>::max() &&
		    doubleValue <= std::numeric_limits<float>::max()) {
			std::cout << "float: " << static_cast<long>(doubleValue) << ".0f" << std::endl;
		} else {
			std::cout << "float: " << std::fixed << std::setprecision(1) << floatValue << "f" << std::endl;
		}
	}

	// Double
	if (doubleFailed) {
		std::cout << "double: impossible" << std::endl;
	} else if (isnan(doubleValue)) {
		std::cout << "double: nan" << std::endl;
	} else if (isinf(doubleValue)) {
		std::cout << "double: " << (doubleValue > 0 ? "+inf" : "-inf") << std::endl;
	} else {
		if (doubleValue == static_cast<long>(doubleValue)) {
			std::cout << "double: " << static_cast<long>(doubleValue) << ".0" << std::endl;
		} else {
			std::cout << "double: " << std::fixed << std::setprecision(1) << doubleValue << std::endl;
		}
	}
}
