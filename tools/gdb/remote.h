extern int remote_desc, remote_timeout;

extern void remote_reset(void);
extern void remote_continue(void);
extern int remote_write_bytes(unsigned long, char *, int);
