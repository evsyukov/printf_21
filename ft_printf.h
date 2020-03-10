/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clashund <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 20:52:17 by clashund          #+#    #+#             */
/*   Updated: 2020/02/05 20:52:19 by clashund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# define CT_NRM "\x1b[0;0m"
# define CT_RED "\x1b[0;31m"
# define CT_GRN "\x1b[0;32m"
# define CT_YEL "\x1b[0;33m"
# define CT_BLU "\x1b[0;34m"
# define CT_MAG "\x1b[0;35m"
# define CT_CYN "\x1b[0;36m"
# define CT_WHT "\x1b[0;37m"
# define CT_BRED "\x1b[1;31m"
# define CT_BGRN "\x1b[1;32m"
# define CT_BYEL "\x1b[1;33m"
# define CT_BBLU "\x1b[1;34m"
# define CT_BMAG "\x1b[1;35m"
# define CT_BCYN "\x1b[1;36m"
# define CT_BWHT "\x1B[1;37m"
# define CT_DRED "\x1b[2;31m"
# define CT_DGRN "\x1b[2;32m"
# define CT_DYEL "\x1b[2;33m"
# define CT_DBLU "\x1b[2;34m"
# define CT_DMAG "\x1b[2;35m"
# define CT_DCYN "\x1b[2;36m"
# define CT_DWHT "\x1B[2;37m"
# define CT_IRED "\x1b[3;31m"
# define CT_IGRN "\x1b[3;32m"
# define CT_IYEL "\x1b[3;33m"
# define CT_IBLU "\x1b[3;34m"
# define CT_IMAG "\x1b[3;35m"
# define CT_ICYN "\x1b[3;36m"
# define CT_IWHT "\x1B[3;37m"
# define CT_URED "\x1b[4;31m"
# define CT_UGRN "\x1b[4;32m"
# define CT_UYEL "\x1b[4;33m"
# define CT_UBLU "\x1b[4;34m"
# define CT_UMAG "\x1b[4;35m"
# define CT_UCYN "\x1b[4;36m"
# define CT_UWHT "\x1B[4;37m"

typedef struct		s_convs
{
	int		sharp;
	int		zero;
	int		minus;
	int		space;
	int		plus;
	int		width;
	int		precision;
	int		length;
	char	conversion;
}					t_convs;

int					ft_printf(const char *fmt, ...);
int					is_flag(char c);
int					is_length(char c);
int					is_conversion(int c);
size_t				letspars_flags(const char *fmt, size_t index,
						t_convs *p_convs);
size_t				letspars_width(const char *fmt, size_t index,
						t_convs *p_convs, va_list *ap);
size_t				letspars_precision(const char *fmt, size_t index,
						t_convs *p_convs, va_list *ap);
size_t				letspars_length(const char *fmt, size_t index,
						t_convs *p_convs);
size_t				letspars_conversion(const char *fmt, size_t index,
						t_convs *p_convs);
size_t				letsprint_csp(t_convs *p_convs, va_list *ap);
size_t				letsprint_dioux(t_convs *p_convs, va_list *ap);
size_t				letsprint_f(t_convs *p_convs, va_list *ap);
size_t				ft_putnbrull(unsigned long long n);
char				*ft_lltoa_base(long long n, int b);
char				*ft_ulltoa_base(unsigned long long n, int b);
char				*get_p(const char *s, int prec);
size_t				not_pval(t_convs *p);
size_t				pval_p(t_convs *p, const char *str);
size_t				print_diu(t_convs *p_convs, va_list *ap);
size_t				print_ox(t_convs *p_convs, va_list *ap);
size_t				print_s(t_convs *p_convs, char *sval);
size_t				print_c(t_convs *p_convs, char cval);
size_t				print_p(t_convs *p_convs, unsigned long pval);
size_t				letsprint_percent(t_convs *p_convs, va_list	*ap);
void				printstralig(char *c, int *arr, char ch);
void				ft_printcharcount(char ch, size_t count);
int					ft_tolower(int c);
size_t				ft_strlen(const char *str);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strchr(const char *s1, int c);
int					ft_isdigit(int c);
void				ft_putstr(char const *s);
char				*ft_strnew(size_t size);
int					ft_unumlen(unsigned long long num);
char				*get_str_float(t_convs *p_convs, long double dval);
long long			get_arg(t_convs *p_convs, va_list *ap);
unsigned long long	get_uarg(t_convs *p_convs, va_list *ap);
size_t				print_char_n(char c, int num);

#endif
