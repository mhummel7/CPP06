/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:46:00 by mhummel           #+#    #+#             */
/*   Updated: 2025/07/14 10:06:26 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Serializer.hpp
#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP

# include "Data.hpp"
# include <stdint.h>

class Serializer
{
	private:
		Serializer();
		Serializer(const Serializer &);
		Serializer &operator=(const Serializer &);
		~Serializer();

	public:
		static uintptr_t serialize(Data *ptr);
		static Data *deserialize(uintptr_t raw);
};

#endif
