/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:47:50 by mhummel           #+#    #+#             */
/*   Updated: 2025/07/14 09:47:55 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>
#include <cstdlib>
#include <cerrno>
#include <cmath>
#include <climits>
#include <cfloat>
#include <iomanip>
#include <string>

static bool isPseudoFloat(const std::string& literal) {
	return literal == "-inff" || literal == "+inff" || literal == "nanf";
}

static bool isPseudoDouble(const std::string& literal) {
	return literal == "-inf" || literal == "+inf" || literal == "nan";
}

static bool isValidFloatingPoint(const std::string& s) {
	if (s.empty()) return false;
	size_t i = 0;
	if (s[i] == '+' || s[i] == '-') ++i;
	bool hasDigitsBefore = false;
	while (i < s.size() && std::isdigit(s[i])) {
		++i;
		hasDigitsBefore = true;
	}
	bool hasDot = false;
	if (i < s.size() && s[i] == '.') {
		hasDot = true;
		++i;
	}
	bool hasDigitsAfter = false;
	while (i < s.size() && std::isdigit(s[i])) {
		++i;
		hasDigitsAfter = true;
	}
	bool hasExp = false;
	if (i < s.size() && (s[i] == 'e' || s[i] == 'E')) {
		hasExp = true;
		++i;
		if (i < s.size() && (s[i] == '+' || s[i] == '-')) ++i;
		bool hasExpDigits = false;
		while (i < s.size() && std::isdigit(s[i])) {
			++i;
			hasExpDigits = true;
		}
		if (!hasExpDigits) return false;
	}
	if (i != s.size()) return false;
	if (!hasDigitsBefore && !hasDigitsAfter && !hasDot && !hasExp) return false;
	return true;
}

static bool isChar(const std::string& literal) {
	return literal.length() == 1 && !std::isdigit(literal[0]);
}

static bool isInt(const std::string& literal) {
	if (literal.empty()) return false;
	size_t i = 0;
	if (literal[0] == '+' || literal[0] == '-') ++i;
	if (i == literal.size()) return false;
	while (i < literal.size()) {
		if (!std::isdigit(literal[i])) return false;
		++i;
	}
	return true;
}

static bool isFloat(const std::string& literal) {
	if (literal.empty()) return false;
	if (isPseudoFloat(literal)) return true;
	if (literal.back() != 'f') return false;
	std::string num = literal.substr(0, literal.size() - 1);
	return isValidFloatingPoint(num);
}

static bool isDouble(const std::string& literal) {
	if (isPseudoDouble(literal)) return true;
	return isValidFloatingPoint(literal);
}

static void printChar(double value) {
	if (std::isnan(value) || std::isinf(value) || value < 0 || value > 127) {
		std::cout << "char: impossible" << std::endl;
	} else {
		char c = static_cast<char>(value);
		if (std::isprint(c)) {
			std::cout << "char: '" << c << "'" << std::endl;
		} else {
			std::cout << "char: Non displayable" << std::endl;
		}
	}
}

static void printInt(double value) {
	if (std::isnan(value) || std::isinf(value) || value < INT_MIN || value > INT_MAX) {
		std::cout << "int: impossible" << std::endl;
	} else {
		std::cout << "int: " << static_cast<int>(value) << std::endl;
	}
}

static void printFloat(double value) {
	float f = static_cast<float>(value);
	if (std::isnan(value)) {
		std::cout << "float: nanf" << std::endl;
	} else if (std::isinf(value)) {
		std::cout << "float: " << (value < 0 ? "-" : "+") << "inff" << std::endl;
	} else if (value < -FLT_MAX || value > FLT_MAX) {
		std::cout << "float: impossible" << std::endl;
	} else {
		std::cout << "float: " << std::fixed << std::setprecision(1) << f << "f" << std::endl;
	}
}

static void printDouble(double value) {
	if (std::isnan(value)) {
		std::cout << "double: nan" << std::endl;
	} else if (std::isinf(value)) {
		std::cout << "double: " << (value < 0 ? "-" : "+") << "inf" << std::endl;
	} else {
		std::cout << "double: " << std::fixed << std::setprecision(1) << value << std::endl;
	}
}

void ScalarConverter::convert(const std::string& literal) {
	double value = 0.0;

	if (isChar(literal)) {
		value = static_cast<double>(literal[0]);
	} else if (isInt(literal)) {
		char* end;
		errno = 0;
		long l = std::strtol(literal.c_str(), &end, 10);
		if (errno == ERANGE || l < INT_MIN || l > INT_MAX) {
			std::cout << "char: impossible" << std::endl;
			std::cout << "int: impossible" << std::endl;
			std::cout << "float: impossible" << std::endl;
			std::cout << "double: impossible" << std::endl;
			return;
		}
		value = static_cast<double>(l);
	} else if (isFloat(literal) || isDouble(literal)) {
		char* end;
		errno = 0;
		value = std::strtod(literal.c_str(), &end);
		if (errno == ERANGE && literal.find("inf") == std::string::npos && literal.find("nan") == std::string::npos) {
			std::cout << "char: impossible" << std::endl;
			std::cout << "int: impossible" << std::endl;
			std::cout << "float: impossible" << std::endl;
			std::cout << "double: impossible" << std::endl;
			return;
		}
		if (*end != '\0' && *end != 'f') {
			std::cout << "Invalid literal" << std::endl;
			return;
		}
	} else {
		std::cout << "Invalid literal" << std::endl;
		return;
	}

	printChar(value);
	printInt(value);
	printFloat(value);
	printDouble(value);
}
