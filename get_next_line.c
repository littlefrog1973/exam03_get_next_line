
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE BUFSIZ
#endif

size_t	ft_strlen(const char *str)
{
	size_t	len = 0;

	while(str[len] != 0)
		len++;
	return (len);
}

size_t	ft_strlcpy(char	*dst, const char *src, size_t size)
{
	size_t	s_len;
	size_t	d_len;
	size_t	i;

	i = s_len = d_len = 0;
	s_len = ft_strlen(src);
	if (size > 0)
	{
		while ((i + 1 < size) && (i <= s_len))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	return (s_len);
}

char	*line_copy(char *dst, const char *src)
{
	size_t	src_len;
	size_t	dst_len;
	char	*temp;

	src_len = ft_strlen(src);
	if (src_len == 0)
		return (dst);
	dst_len = ft_strlen(dst);
	temp = dst;
	dst = malloc(src_len + dst_len + 1);
	ft_strlcpy(dst, temp, dst_len + 1);
	ft_strlcpy(&dst[dst_len], src, src_len + 1);
	free(temp);
	return (dst);
}

ssize_t	search_n(char *str)
{
	ssize_t	i;

	i = 0;
	while ((str[i] != '\n') && (str[i] != 0))
		i++;
	if (str[i] == '\n')
		return (i);
	else
		return (-1);
}

char	*chop(char *str)
{
	char	*temp;

	int		pos_to_chop;

	if (str == NULL)
		return (NULL);
	if ((pos_to_chop = search_n(str)) < 0)
		pos_to_chop = ft_strlen(str);
	if (pos_to_chop >= 0 && str[pos_to_chop] == '\n')
	{
		temp = malloc(pos_to_chop + 2);
		ft_strlcpy(temp, str, pos_to_chop + 2);
		ft_strlcpy(str, (str + pos_to_chop + 1), ft_strlen(str) - pos_to_chop);
		return (temp);
	}
	if (pos_to_chop >= 0 && str[pos_to_chop] == 0)
	{
		temp = malloc(pos_to_chop + 1);
		ft_strlcpy(temp, str, pos_to_chop + 1);
		str[0] = 0;
		return (temp);
	}
	return (NULL);
}

char *get_next_line(int fd)
{
	char			*r_line;
	ssize_t			r_sig = 0;
	static char		*temp;
	ssize_t			n_pos;
	int				i;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (!temp)
	{
		temp = malloc(1);
		temp[0] = 0;
	}
	r_line = malloc(BUFFER_SIZE + 1);
	i = 0;
	while (i < BUFFER_SIZE + 1)
	{
		r_line[i] = 0;
		i++;
	}
	while ((r_sig = read(fd, r_line, BUFFER_SIZE)) > 0)
	{
		r_line[r_sig] = 0;
		temp = line_copy(temp, r_line);
		n_pos = search_n(temp);
		if (n_pos >= 0)
			break;
	}
	if (r_sig == -1 || (!ft_strlen(temp) && !r_sig))
	{
		free (temp);
		free (r_line);
		temp = NULL;
		return (NULL);
	}
	return (free(r_line), chop(temp));
}
/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	int		fd;
	char	*line;

	printf("this machine has BUFSIZ = %d bytes", BUFSIZ);
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
//		(void) argv;
		while((line = get_next_line(fd)))
		{
			printf("%s", line);
			free(line);
		}
	}
	return (0);
}
*/
