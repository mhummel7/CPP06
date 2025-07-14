/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:24:43 by mhummel           #+#    #+#             */
/*   Updated: 2025/07/14 08:33:39 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>

class ScalarConverter {
public:
	static void convert(const std::string& literal);

private:
	ScalarConverter(); // Private constructor
	ScalarConverter(const ScalarConverter&); // Private copy constructor
	ScalarConverter& operator=(const ScalarConverter&); // Private assignment operator
	~ScalarConverter(); // Private destructor
};

#endif
