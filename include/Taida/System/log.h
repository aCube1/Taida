#ifndef _LOG_H_
#define _LOG_H_

#define taida_log_error(msg) taida_log(LOGP_ERROR, msg)
#define taida_log_warn(msg) taida_log(LOGP_WARNNING, msg)
#define taida_log_debug(msg) taida_log(LOGP_DEBUG, msg)
#define taida_log_info(msg) taida_log(LOGP_INFO, msg)

/* log priorities */
enum log_priority {
	LOGP_ERROR,
	LOGP_WARNNING,
	LOGP_DEBUG,
	LOGP_INFO,
};

/* taida_log
*	Output a log message according to a specific priority
*
* @priority: priority  level
* @msg: message
*/
void taida_log(int const priority, char const *msg);

#endif /* _LOG_H_ */
