/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:34:40 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/09/17 08:23:40 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return ((r << 24) | (g << 16) | (b << 8) | a);
}

int set_color(char position)
{
    int sq_color;

    sq_color = ft_pixel(32, 32, 32, 0); // Default
    if (position == '0')
        sq_color = ft_pixel(255, 245, 224, 255); // white
    if (position == '1')
        sq_color = ft_pixel(144, 159, 145, 255); // blue
    if (position == 'P')
        sq_color = ft_pixel(130, 93, 14, 255); // yellow
    return (sq_color);
}