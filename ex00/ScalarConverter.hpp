/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:24:43 by mhummel           #+#    #+#             */
/*   Updated: 2025/06/25 10:34:32 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>

class ScalarConverter {
public:
	static void convert(const std::string& input);

private:
	ScalarConverter(); // Private constructor
	~ScalarConverter(); // Private destructor
	ScalarConverter(const ScalarConverter& other); // Private copy constructor
	ScalarConverter& operator=(const ScalarConverter& other); // Private assignment operator
};

#endif // SCALARCONVERTER_HPP
