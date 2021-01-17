#ifndef _LOGMSG_H_
#define _LOGMSG_H_

#define logmsge(msg) logmsg(LOGP_ERROR, msg)
#define logmsgw(msg) logmsg(LOGP_WARNNING, msg)
#define logmsgd(msg) logmsg(LOGP_DEBUG, msg)

/* log priorities */
enum log_priority {
	LOGP_ERROR,
	LOGP_WARNNING,
	LOGP_DEBUG,
};

/* logmsg
*	Output a log message according to a specific priority
*
* @priority: priority  level
* @msg: message
*/
void logmsg(int const priority, char const *msg);

#endif /* _LOGMSG_H_ */