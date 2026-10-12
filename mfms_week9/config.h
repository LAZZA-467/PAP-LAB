#ifndef CONFIG_H
#define CONFIG_H

/*
 * config.h - single shared configuration header for the whole MFMS.
 * Every module that needs an application-wide constant includes this file.
 */

#define APP_NAME        "MFMS"
#define APP_VERSION     "1.0"

/* Capacity limits */
#define MAX_EMPLOYEES   100
#define MAX_BUDGETS     200
#define MAX_SUPPLIERS   100

/* Field limits (buffer sizes include the terminating '\0') */
#define MAX_NAME_LEN    50
#define MAX_CATEGORY_LEN 30
#define MAX_DESC_LEN    80

#endif /* CONFIG_H */