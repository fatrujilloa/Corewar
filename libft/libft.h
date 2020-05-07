/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 14:01:33 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/11/25 19:47:45 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFF_SIZE 1

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

# define COLOR_H
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define EOC "\033[0m"

typedef struct s_fd_list			t_fd_list;

struct								s_fd_list
{
	char							*str;
	int								fd;
	t_fd_list						*next;
};

typedef struct s_list				t_list;

struct								s_list
{
	void							*content;
	size_t							content_size;
	int								arcw;
	t_list							*next;
};

typedef struct s_data				t_data;
typedef struct s_long_double_bits	t_long_double_bits;
typedef union u_double				t_double;

struct								s_data
{
	va_list							ap;
	int								res;
	char							buffer[BUFF_SIZE];
	int								i;
	int								option;
	const char						*converterror;
	int								sharp;
	int								zero;
	int								minus;
	int								space;
	int								plus;
	int								fieldwidth;
	int								precision;
	int								length;
	int								left_spaces;
	int								sign;
	int								zeros;
	int								size;
	int								right_spaces;
	int								apos;
	int								bits;
	int								fd;
};

struct								s_long_double_bits
{
	unsigned long long				mantiss:64;
	unsigned long long				power:15;
	unsigned long long				sign:1;
};

union								u_double
{
	long double						value;
	t_long_double_bits				long_double_bits;
};

size_t								ft_strlen(const char *str);
void								*ft_memcpy(void *dst, const void *src,
				size_t n);
void								*ft_memccpy(void *dst, const void *src,
				int c, size_t n);
char								*ft_strcpy(char *dst, const char *src);
char								*ft_strncpy(char *dst, const char *src,
				size_t len);
char								*ft_strcat(char *s1, const char *s2);
char								*ft_strncat(char *s1, const char *s2,
				size_t n);
size_t								ft_strlcat(char *dst, const char *src,
				size_t size);
int									ft_strcmp(const char *s1, const char *s2);
int									ft_strncmp(const char *s1, const char *s2,
				size_t n);
int									ft_atoi(const char *str);
int									ft_isalpha(int c);
int									ft_isdigit(int c);
int									ft_is_plus_minus(int c);
int									ft_isalnum(int c);
int									ft_isascii(int c);
int									ft_isprint(int c);
int									ft_toupper(int c);
int									ft_tolower(int c);
char								*ft_strchr(const char *s, int c);
char								*ft_strrchr(const char *s, int c);
char								*ft_strstr(const char *str,
				const char *to_find);
void								*ft_memmove(void *dst, const void *src,
				size_t len);
char								*ft_strnstr(const char *str,
				const char *to_find, size_t len);
char								*ft_strdup(const char *s1);
void								ft_bzero(void *s, size_t n);
void								*ft_memset(void *b, int c, size_t len);
void								*ft_memchr(const void *s, int c, size_t n);
int									ft_memcmp(const void *s1, const void *s2,
				size_t n);
void								*ft_memalloc(size_t size);
void								ft_memdel(void**ap);
char								*ft_strnew(size_t size);
void								ft_strdel(char **as);
void								ft_strclr(char *s);
void								ft_striter(char*s, void(*f)(char*));
void								ft_striteri(char*s,
				void(*f)(unsigned int, char *));
char								*ft_strmap(char const *s, char (*f)(char));
char								*ft_strmapi(char const *s,
				char (*f)(unsigned int, char));
int									ft_strequ(char const *s1, char const *s2);
int									ft_strnequ(char const *s1, char const *s2,
				size_t n);
char								*ft_strsub(char const *s,
				unsigned int start, size_t len);
char								*ft_strjoin(char const *s1,
				char const *s2);
char								*ft_strtrim(char const *s);
char								**ft_strsplit(char const *s, char c);
char								*ft_itoa(int n);
void								ft_putchar(char c);
void								ft_putstr(char const *s);
void								ft_putendl(char const *s);
void								ft_putnbr(int n);
void								ft_putchar_fd(char c, int fd);
void								ft_putstr_fd(char const *s, int fd);
void								ft_putendl_fd(char const *s, int fd);
void								ft_putnbr_fd(int n, int fd);
t_list								*ft_lstnew(void const *content,
				size_t content_size);
void								ft_lstadd(t_list **alst, t_list *new);
void								ft_lstdelone(t_list **alst,
				void (*del)(void *, size_t));
void								ft_lstdel(t_list **alst,
				void (*del)(void *, size_t));
void								ft_lstiter(t_list *lst,
				void (*f)(t_list *elem));
t_list								*ft_lstmap(t_list *lst,
				t_list *(*f)(t_list *elem));
void								ft_foreach(int *tab, int length,
				void (*f)(int));
int									ft_issp(char c);
char								*ft_itoa_base(int n, int base);
int									ft_clamp(int nb, int min, int max);
void								ft_lstpushback(t_list **alst, t_list *new);
int									ft_printf(const char *restrict format,
				...);
void								ft_init_data(t_data *data, int fd);
void								ft_reset_data_options(t_data *data);
void								ft_print_data(t_data *data);
char								ft_parse_flags(const char *restrict format,
				t_data *data, int *i);
void								ft_attrib(const char *restrict str,
				int *i, t_data *data);
void								ft_fieldwidth(const char *restrict str,
				int *i, t_data *data);
void								ft_precision(const char *restrict str,
				int *i, t_data *data);
void								ft_lengthmod(const char *restrict str,
				int *i, t_data *data);
void								ft_fill_buffer(t_data *data,
				const char *str, unsigned int size);
void								ft_putstr_printf(t_data *data);
void								ft_putchar_printf(t_data *data);
void								ft_putnbr_printf(t_data *data);
void								ft_putnbr_o(t_data *data);
void								ft_putnbr_x(t_data *data);
void								ft_putnbr_u(t_data *data);
void								ft_putnbr_xx(t_data *data);
void								ft_set_padding(t_data *data, long long nb);
void								ft_set_padding_float(t_data *data,
				long double nb);
void								ft_set_padding_u(t_data *data);
void								ft_put_zeros(t_data *data);
void								ft_put_left_spaces(t_data *data);
void								ft_put_left_spaces_float(t_data *data);
void								ft_put_left_spaces_whole_float(t_data *d);
void								ft_put_right_spaces(t_data *data);
void								ft_put_right_spaces_float(t_data *data);
void								ft_put_sign(t_data *data, long long nb);
void								ft_put_sign_u(t_data *data);
void								ft_put_sign_float(t_data *data,
				long double db);
void								ft_put_space(t_data *data, long long nb);
void								ft_put_space_u(t_data *data);
void								ft_put_space_float(t_data *data,
				long double db);
void								ft_percent(t_data *data);
void								ft_p(t_data *data);
void								ft_putlong(long long nb, t_data *data);
void								ft_putlong_x(unsigned long long nb,
				t_data *data);
void								ft_putlong_xx(unsigned long long nb,
				t_data *data);
void								ft_putfloat(t_data *data);
void								ft_put_extra_zeros(t_data *data, int prec);
void								ft_putfloat_ext_one(t_data *data,
				long double db);
void								ft_putfloat_ext_two(t_data *data,
				long double db, long long nb, int prec);
void								ft_prec_zero(t_data *data, long double db);
void								ft_put_dec(t_data *data, long double db);
void								ft_puttab(t_data *data);
void								ft_putbits_ints(t_data *data,
				long long nb);
void								ft_putbits_u(t_data *data,
				unsigned long long nb);
void								ft_parse_colour(t_data *data,
				const char *format, int *i);
void								ft_putbits_float(t_data *data,
				unsigned long long sign, unsigned long long power,
				unsigned long long mantiss);
int									ft_sizeof_nbr(int nb);
int									ft_abs(int a, int b);
int									ft_printf_err(const char *restrict format,
				...);
int									get_next_line(const int fd, char **line);
int									ft_count_words(char *s);
int									ft_ln_w(char *str, int i);
char								**ft_split_whitespaces(const char *str);

#endif
