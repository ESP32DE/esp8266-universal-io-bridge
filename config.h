#ifndef config_h
#define config_h

#include "uart.h"
#include "gpios.h"
#include "util.h"

#include <stdint.h>

enum
{
	config_magic = 0x4afb4afc,
	config_version = 12
};

typedef enum __attribute__ ((__packed__))
{
	config_flag_strip_telnet,
	config_flag_print_debug,
	config_flag_tsl_high_sens,

	config_flag_size
} config_flag_enum_t;

_Static_assert(sizeof(config_flag_enum_t) == 1, "sizeof(config_flag_enum_t) != 1");

typedef struct
{
	config_flag_enum_t id;
	const char *const short_name;
	const char *const long_name;
} config_flag_t;

typedef struct
{
	uint32_t			magic;
	uint32_t			version;
	char				ssid[32];
	char				passwd[32];
	uint32_t			flags;
	uart_parameters_t	uart;
	gpio_t				gpios[gpio_size];
} config_t;

extern config_t *config;
extern config_t *tmpconfig;

const char *		config_flag_to_string(config_flag_enum_t);
config_flag_enum_t	config_flag_to_id(const char *);

bool_t		config_get_flag(config_flag_enum_t);
bool_t		config_set_flag(config_flag_enum_t, bool_t onoff);

bool_t		config_get_flag_by_name(const char *);
bool_t		config_set_flag_by_name(const char *, bool_t);

uint16_t	config_flags_to_string(uint16_t, char *, uint32_t);

bool_t	config_init(void);
void	config_read_alt(config_t *);
void	config_read(void);
void	config_write_alt(config_t *);
void	config_write(void);
void	config_dump(uint16_t size, char *);

#endif
