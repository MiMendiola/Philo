
#include "../includes/philo.h"

void	*ft_memset(void *str, int value, size_t len)
{
	size_t			i;
	unsigned char	*s;

	i = 0;
	s = (unsigned char *)str;
	while (len > i)
	{
		s[i] = (unsigned char)value;
		i++;
	}
	return (s);
}

void	ft_bzero(void *str, size_t len)
{
	ft_memset(str, '\0', len);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	str = malloc(count * size);
	if (!str)
		return (NULL);
	ft_bzero(str, count * size);
	return (str);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}