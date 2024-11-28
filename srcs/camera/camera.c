#include "camera.h"
#include "miniRT.h"

/*

*/
double	calcul_theta_y(t_minirt *minirt)
{
	t_vec2	v1; // direction monde 0.0.1
	t_vec2	v2; // direction camera
	double	theta_y;
	float	sign = 0;

	v1.x = 0;
	v1.y = 1;
	v2.x = minirt->cam.direction.x;
	v2.y = minirt->cam.direction.z;
	v2 = normalize_vec2(v2);
	theta_y = acos(dot_vec2(v1, v2));
	sign = (v1.x * v2.y) - (v1.y * v2.x);
	if (sign < 0)
		theta_y = -theta_y;
	return (theta_y);
}

double	calcul_theta_x(t_minirt *minirt)
{
	t_vec2	v1; // direction monde 0.0.1
	t_vec2	v2; // direction camera
	double	theta_x;
	float	sign = 0;

	v1.x = 0;
	v1.y = 1;
	v2.x = minirt->cam.direction.y;
	v2.y = minirt->cam.direction.z;
	v2 = normalize_vec2(v2);
	theta_x = acos(dot_vec2(v1, v2));
	sign = (v1.x * v2.y) - (v1.y * v2.x);
	if (sign < 0)
		theta_x = -theta_x;
	return (theta_x);
}

void	camera(t_minirt *minirt)
{
	double theta_x = calcul_theta_x(minirt);
	double theta_y = calcul_theta_y(minirt);
	printf("theta_x = %f, theta_y = %f\n", theta_x, theta_y);
	printf("theta_x = %f, theta_y = %f\n", theta_x * 180 / M_PI, theta_y * 180 / M_PI);
}


//CREER 2 matrices de rotation pour x et y


//arc cosinus -> avec la valeur entre -1 et 1, retourne l'angle en radian
//cosinus -> pour un angle retourne un rapport entre le cote adjacent et l'hypotenuse
//sinus -> pour un angle retourne un rapport entre le cote oppose et l'hypotenuse
//tan -> pour un angle retourne un rapport entre le cote oppose et le cote adjacent	



